#pragma once
#include <vector>
#include <string>
#include "MapTypes.h"
#include "Common/Singleton.h"

using namespace std;
using namespace Map;

// 나중에 namespace로 묶을까 고민 중
struct Node
{
	int id;
	Vector2D pos;
	Vector2D size;
	int doorDirection = 0;

	Node(int id, Vector2D pos) : id(id), pos(pos) {}

	inline bool operator ==(const Node& other) const
	{
		return this->pos == other.pos;
	}
};

struct Edge
{
	Node* node1;
	Node* node2;
	float distance;

	Edge(Node* n1, Node* n2) : node1(n1), node2(n2), distance(Vector2D::Distance(n1->pos, n2->pos)) {}

	inline bool operator==(const Edge& other) const
	{
		return (this->node1 == other.node1 && this->node2 == other.node2) || (this->node1 == other.node2 && this->node2 == other.node1);
	}
};

struct Circle
{
	Vector2F center;
	float radius;

	Circle(Vector2F center, float radius) : center(center), radius(radius) {}

	inline bool Contains(Vector2F point) const
	{
		float d = Vector2F::Distance(center, point);
		return radius >= d;
	}
};

struct Triangle
{
	Node* a;
	Node* b;
	Node* c;
	Circle* circumCircle;
	vector<Edge*> edges;

	Triangle(Node* a, Node* b, Node* c) : a(a), b(b), c(c)
	{
		circumCircle = calCircumCicle(a->pos, b->pos, c->pos);
		edges.push_back(new Edge(a, b));
		edges.push_back(new Edge(b, c));
		edges.push_back(new Edge(c, a));
	}

	~Triangle()
	{
		if (circumCircle != nullptr)
			delete circumCircle;
		circumCircle = nullptr;
	}

	inline bool Equals(const Triangle* other) const
	{
		return (a == other->a && b == other->b && c == other->c);
	}

	inline Circle* calCircumCicle(Vector2F a, Vector2F b, Vector2F c) const
	{
		// 같은 점이 있으면 삼각형 아님. 외접원 구할 수 없음.
		if (a == b || b == c || c == a)
		{
			return nullptr;
		}

		float mab = (b.x - a.x) / (b.y - a.y) * -1.0f;		// 직선 ab에 수직이등분선의 기울기
		float a1 = (b.x + a.x) / 2.0f;						// 직선 ab의 x축 중심 좌표
		float b1 = (b.y + a.y) / 2.0f;						// 직선 ab의 z축 중심 좌표

		// 직선 bc
		float mbc = (b.x - c.x) / (b.y - c.y) * -1.0f;		// 직선 bc에 수직이등분선의 기울기
		float a2 = (b.x + c.x) / 2.0f;						// 직선 bc의 x축 중심 좌표
		float b2 = (b.y + c.y) / 2.0f;						// 직선 bc의 z축 중심 좌표

		// 두 수직이등분선이 평행함. 교점 구할 수 없음.
		if (mab == mbc)
		{
			return nullptr;
		}

		float x = (mab * a1 - mbc * a2 + b2 - b1) / (mab - mbc);
		float y = mab * (x - a1) + b1;
		if (b.x == a.x)     // 수직이등분선의 기울기가 0인 경우(수평선)
		{
			x = a2 + (b1 - b2) / mbc;
			y = b1;
		}

		if (b.y == a.y)     // 수직이등분선의 기울기가 무한인 경우(수직선)
		{
			x = a1;
			if (0.0f == mbc)
			{
				y = b2;
			}
			else
			{
				y = mbc * (a1 - a2) + b2;
			}
		}

		if (b.x == c.x)     // 수직이등분선의 기울기가 0인 경우(수평선)
		{
			x = a1 + (b2 - b1) / mab;
			y = b2;
		}

		if (b.y == c.y)     // 수직이등분선의 기울기가 무한인 경우(수직선)
		{
			x = a2;
			if (0.0f == mab)
			{
				y = b1;
			}
			else
			{
				y = mab * (a2 - a1) + b1;
			}
		}

		Vector2F center(x, y);
		float radius = Vector2F::Distance(center, a);

		return new Circle(center, radius);
	}
};

// 그리드 A* 경로탐색 시 오브젝트별 가중치
enum class CostAStar
{
	Hallway = 1,
	RoomToDoor = 5,
	Empty = 10,
	Room = -1,
};

struct AStarNode
{
	int x, y;
	inline int F() { return g + h; };
	int g, h;

	bool closed = false;
	AStarNode* parentNode;
};


// 간단한 게임이므로 오브젝트 타입으로 구분해서 충돌 처리
// 충돌도 그냥 ObjType으로 구분해서, Player인 경우만 나머지랑 충돌처리 하게 함
enum class ObjType
{
	None = -1,
	WorldStatic,
	Stairs,
	Merchant,
	Boss
};

class MapManager : public Singleton<MapManager>
{
public:
	/// <summary>
	/// 방 무작위 배치
	/// </summary>
	void PlaceNode();
	/// <summary>
	/// 들로네 삼각분할 (보이어 왓슨) 알고리즘으로 방 사이 연결 계산
	/// 1. 모든 노드를 덮는 superTriangle 생성
	/// 2. 삼각형의 외접원 안에 다른 점이 포함되면, 해당 삼각형 지우고 다른 점으로 다시 삼각형 생성 (반복)
	/// 3. superTriangle 꼭짓점과 이어진 삼각형 제거
	/// </summary>
	void Triangulate();
	/// <summary>
	/// 최소 스패닝 트리로 유효한 간선 선택 + 일부 간선 확률적 추가 연결(선택)
	/// </summary>
	void MST();
	/// <summary>
	/// a* 알고리즘으로 경로 탐색하여 복도 결정
	/// </summary>
	void FindPaths();
	/// <summary>
	/// PlaceNode -> Triangulate -> MST -> FindPath
	/// </summary>
	void GenerateGrid();

	void CreateMap();
	void CreateMap(unsigned int seed);
	void GenerateMapData();
	void MakeMapActors();

	void Release();

	void EnterNextStage();
	void MakeStairs();
	void MakeMerchant();
	void MakePlayerObj();
	void PlaceMapObjRandomRoom(MapObj* obj, ObjType type, bool randomPos);		// MapObj 랜덤한 방에 가장자리에서 2씩 떨어진 자리에 생성 (여유 공간 충분해야 함)
	void CreateBossRoom();
	void UpdatePlayer();
	void Draw();

	Triangle* CreateTriangle(Node* a, Node* b, Node* c);
	Triangle* CreateSuperTriangle(const vector<Vector2D>& points);
	void RemoveSuperTriangle();
	void AddNode(Node* node);
	void SetEdges();
	void AdditionalConnectRandomly(const vector<Edge*>& edgesNotConnected);
	void SetDoorDirection();
	void AStarPathFind(Edge* edge, int gridSizeX, int gridSizeY);

private:
	const Vector2D UNIT_GRID_SIZE = Vector2D(19, 11);
	const Vector2D ROOM_SIZE_MIN = Vector2D(8, 5);
	const Vector2D ROOM_SIZE_MAX = Vector2D(15, 7);
	const float ADDITIONAL_CONNECT_PROB = 0.1f;					// MST로 연결되지 않은 간선들이 추가적으로 확률

	unsigned int seed;
	int roomCount = 24;
	bool additionalConnect = true;								// MST로 연결된 간선 외에, 간선 추가 연결 여부
	// 기본적으로 제작된 맵은 복도 사이즈 1인 크기이므로, 플레이 체감에 따라 배수를 키워서 맵 크기 확대
	// Default 맵을 제외한 맵은 가로벽의 경우, y축으로 한 칸 더 벽을 그려줘서 입체감을 줌. 이를 위해, sizeMultipleY > 1 이어야 함.
	int sizeMultipleX = 5, sizeMultipleY = 3;

	const int TOTAL_STAGE = 3;
	int currStage = 0;											// 0으로 시작해서, 첫 스테이지 입장시 1
    const double MIN_ENCOUNT_ENEMY = 0.0005;
    const double DELTA_ENCOUNT_ENEMY = 0.000025;
    double encountEnemy = MIN_ENCOUNT_ENEMY;
	vector<int> vecSeed;										// 스테이지별 시드값 저장 (중복 없게 생성)

	int gridCount;
	vector<Node*> vecNode;
	vector<Triangle*> vecTriangle;
	Triangle* superTriangle;
	vector<Edge*> vecEdge;
	vector<vector<CostAStar>> grid;

	vector<vector<wchar_t>> mapData;
	int mapWidth, mapHeight;

	// 맵만 만들려고 했는데, 그려내는 문제 때문에 씬매니저 같은 역할도 해야 할 듯
	// 분리해서 만들기엔 게임 규모가 너무 작음
	// 콜라이더 빼버림
	vector<MapObj*> objects;
	MapObj* objPlayer;
	vector<vector<ObjType>> vecType;
	vector<int> vecUsingNode;		// 플레이어, 계단, 상인 다 다른 방에 배치하기 위해, 이미 배치가 된 방 저장
};

#define MAP_MANAGER (MapManager::GetInstance())
