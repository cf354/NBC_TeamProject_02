#include "Map/MapManager.h"
#include "Common/RandomManager.h"
#include <numeric>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <deque>
#include "Entity/Player.h"
#include "GameManager/GameManager.h"
#include "Common/ConsolePrinter.h"

void MapManager::PlaceNode()
{
	vecNode.clear();
	// 전체 영역의 크기를 (방 갯수 * 2)만큼 잡고, 제곱근하여 한 축의 크기 설정 (크게 잡을 수록 방들이 멀어짐)
	// 
	// 방의 갯수를 n개로 잡으면, 그리드의 크기 = (int)ceil(sqrt(n * 2)) ^ 2
	gridCount = (int)ceil(sqrt(roomCount * 2));
	int arrSize = gridCount * gridCount;
	int currentRoomCount = 0;
	vector<bool> arrExistRoom(arrSize, false);
	RANDOM_MANAGER->SetSeed(seed);
	while (currentRoomCount < roomCount)
	{
		int randomIdx = RANDOM_MANAGER->Range(0, arrSize);
		if (!arrExistRoom[randomIdx])
		{
			arrExistRoom[randomIdx] = true;
			currentRoomCount++;
		}
	}

	for (int i = 0; i < arrSize; i++)
	{
		if (arrExistRoom[i])
		{
			int roomSizeX = RANDOM_MANAGER->Range(ROOM_SIZE_MIN.x, ROOM_SIZE_MAX.x + 1);
			int roomSizeY = RANDOM_MANAGER->Range(ROOM_SIZE_MIN.y, ROOM_SIZE_MAX.y + 1);

			// 방 한 변의 길이를 홀수로 설정하기 위해서 (방 중앙을 pos로 두고, 양옆 또는 위아래로 같은 크기여야 하기 때문에 홀수가 표현하기 좋음)
			roomSizeX = roomSizeX % 2 == 0 ? roomSizeX - 1 : roomSizeX;
			roomSizeY = roomSizeY % 2 == 0 ? roomSizeY - 1 : roomSizeY;

			int roomPosX = (i % gridCount) * UNIT_GRID_SIZE.x + RANDOM_MANAGER->Range(roomSizeX / 2 + 1, UNIT_GRID_SIZE.x - roomSizeX / 2 - 1);
			int roomPosY = (i / gridCount) * UNIT_GRID_SIZE.y + RANDOM_MANAGER->Range(roomSizeY / 2 + 1, UNIT_GRID_SIZE.y - roomSizeY / 2 - 1);
			Node* newNode = new Node(vecNode.size(), Vector2D(roomPosX, roomPosY));
			newNode->size = Vector2D(roomSizeX, roomSizeY);
			vecNode.push_back(newNode);
		}
	}
}

void MapManager::Triangulate()
{
	vector<Vector2D> points;
	points.push_back(Vector2D(-1, -1));
	points.push_back(Vector2D(-1, UNIT_GRID_SIZE.y * roomCount * 4));
	points.push_back(Vector2D(UNIT_GRID_SIZE.x * roomCount * 4, UNIT_GRID_SIZE.y * roomCount * 4));
	points.push_back(Vector2D(UNIT_GRID_SIZE.x * roomCount * 4, -1));

	for (int i = 0; i < vecTriangle.size(); i++)
	{
		delete vecTriangle[i];
	}
	vecTriangle.clear();
	superTriangle = CreateSuperTriangle(points);
	if (superTriangle == nullptr)
		return;
	vecTriangle.push_back(superTriangle);
	for (int i = 0; i < vecNode.size(); i++)
	{
		AddNode(vecNode[i]);
	}
	RemoveSuperTriangle();

	SetEdges();
}

/// <summary>
/// 최소 스패닝 트리 - 크루스칼
/// </summary>
void MapManager::MST()
{
	sort(vecEdge.begin(), vecEdge.end(), [](const auto& e1, const auto& e2) { return e1->distance < e2->distance; });
	for_each(vecEdge.begin(), vecEdge.end(),
		[](const auto& edge)
		{
			if (edge->node2->id < edge->node1->id)
			{
				Node* temp = edge->node1;
				edge->node1 = edge->node2;
				edge->node2 = temp;
			}
		});

	vector<int> parents(roomCount);
	vector<int> rank(roomCount);
	for (int i = 0; i < roomCount; i++)
	{
		parents[i] = i;
		rank[i] = 0;
	}

	auto GetParent = [&parents](int idx)
		{
			while (parents[idx] != idx)
			{
				idx = parents[idx];
			}
			return idx;
		};

	auto Union = [GetParent, &parents, &rank](int idx1, int idx2)
		{
			int parent1 = GetParent(idx1);
			int parent2 = GetParent(idx2);

			if (parent1 != parent2)
			{
				if (rank[parent1] < rank[parent2])
					parents[parent1] = parent2;
				else if (rank[parent1] > rank[parent2])
					parents[parent2] = parent1;
				else
				{
					parents[parent2] = parent1;
					rank[parent1]++;
				}
			}
		};

	vector<Edge*> edgesNotConnected;
	for (int i = 0; i < vecEdge.size(); i++)
	{
		int parent1 = GetParent(vecEdge[i]->node1->id);
		int parent2 = GetParent(vecEdge[i]->node2->id);
		if (parent1 != parent2)
		{
			parents[vecEdge[i]->node2->id] = GetParent(vecEdge[i]->node1->id);
			Union(parent1, parent2);
		}
		else
		{
			edgesNotConnected.push_back(vecEdge[i]);
			vecEdge.erase(vecEdge.begin() + i--);
		}
	}

	if (additionalConnect)
	{
		AdditionalConnectRandomly(edgesNotConnected);
	}

	SetDoorDirection();
}

void MapManager::FindPaths()
{
	int gridSizeX = gridCount * UNIT_GRID_SIZE.x;
	int gridSizeY = gridCount * UNIT_GRID_SIZE.y;
	grid = vector<vector<CostAStar>>(gridSizeY, vector<CostAStar>(gridSizeX));
	for (int i = 0; i < gridSizeY; i++)
	{
		for (int j = 0; j < gridSizeX; j++)
		{
			grid[i][j] = CostAStar::Empty;
		}
	}

	for (int i = 0; i < vecNode.size(); i++)
	{
		int startX = vecNode[i]->pos.x - vecNode[i]->size.x / 2;
		int startY = vecNode[i]->pos.y - vecNode[i]->size.y / 2;
		int endX = startX + vecNode[i]->size.x - 1;
		int endY = startY + vecNode[i]->size.y - 1;

		startX = max(startX, 0);
		startY = max(startY, 0);
		endX = min(endX, gridSizeX - 1);
		endY = min(endY, gridSizeY - 1);
		for (int j = startY; j <= endY; j++)
		{
			for (int k = startX; k <= endX; k++)
			{
				// 중심부에서 한 칸 이상 떨어지고 문 방향은 가중치 1로 계산, 중심부도 추가
				// E->S->W->N
				if ((j == vecNode[i]->pos.y && k == vecNode[i]->pos.x) ||
					((vecNode[i]->doorDirection & 1) != 0 && j == vecNode[i]->pos.y && k > vecNode[i]->pos.x) ||
					((vecNode[i]->doorDirection & 2) != 0 && k == vecNode[i]->pos.x && j > vecNode[i]->pos.y) ||
					((vecNode[i]->doorDirection & 4) != 0 && j == vecNode[i]->pos.y && k < vecNode[i]->pos.x) ||
					((vecNode[i]->doorDirection & 8) != 0 && k == vecNode[i]->pos.x && j < vecNode[i]->pos.y))
				{
					grid[j][k] = CostAStar::RoomToDoor;
					continue;
				}
				grid[j][k] = CostAStar::Room;
			}
		}
	}

	for (int i = 0; i < vecEdge.size(); i++)
	{
		AStarPathFind(vecEdge[i], gridSizeX, gridSizeY);
	}
}

void MapManager::GenerateGrid()
{
	PlaceNode();
	Triangulate();
	MST();
	FindPaths();
}

void MapManager::CreateMap()
{
	RANDOM_MANAGER->SetCompletelyRandom();
	return CreateMap(RANDOM_MANAGER->GetSeed());
}

void MapManager::CreateMap(unsigned int seed)
{
	this->seed = seed;
	RANDOM_MANAGER->SetSeed(seed);

	// 기존 grid에 사용된 데이터 해제
	Release();
	// 새 grid 데이터 생성
	GenerateGrid();

	// grid 데이터로 맵 데이터 및 오브젝트 생성
	GenerateMapData();
	MakeMapActors();
}

void MapManager::GenerateMapData()
{
	int gridHeight = grid.size();
	int gridWidth = grid[0].size();
	mapHeight = gridHeight * sizeMultipleY;
	mapWidth = gridWidth * sizeMultipleX;
	mapData = vector<vector<wchar_t>>(mapHeight, vector<wchar_t>(mapWidth, ' '));
	auto setData = [this](int i, int j, char c)
		{
			if (mapData[i][j] != '|')
				mapData[i][j] = c;
		};
	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++)
		{
			if (grid[i][j] == CostAStar::Empty)
				continue;

			Vector2D lt = Vector2D(j * sizeMultipleX, i * sizeMultipleY);
			Vector2D rb = lt + Vector2D(sizeMultipleX - 1, sizeMultipleY - 1);

			// 네 귀퉁이
			for (int k = -1; k <= 1; k += 2)
			{
				for (int l = -1; l <= 1; l += 2)
				{
					if (grid[i + k][j + l] == CostAStar::Empty)
					{
						int y = k > 0 ? rb.y + 1 : lt.y - 1;
						int x = l > 0 ? rb.x + 1 : lt.x - 1;
						mapData[y - 1][x] = '|';
						mapData[y][x] = '|';
					}
				}
			}

			// 가로벽
			for (int k = -1; k <= 1; k += 2)
			{
				if (grid[i + k][j] == CostAStar::Empty)
				{
					int y = k > 0 ? rb.y + 1 : lt.y - 1;
					for (int l = 0; l < sizeMultipleX; l++)
					{
						setData(y - 1, lt.x + l, '=');// map[y - 1][lt.x + l] = '=';
						setData(y, lt.x + l, '='); // map[y][lt.x + l] = '=';
					}
				}
			}

			// 세로벽
			for (int k = -1; k <= 1; k += 2)
			{
				if (grid[i][j + k] == CostAStar::Empty)
				{
					int x = k > 0 ? rb.x + 1 : lt.x - 1;
					for (int l = 0; l < sizeMultipleY; l++)
					{
						mapData[lt.y + l - 1][x] = '|';
						mapData[lt.y + l][x] = '|';
					}
				}
			}
		}
	}
}

void MapManager::MakeMapActors()
{
	vecType = vector<vector<ObjType>>(mapHeight, vector<ObjType>(mapWidth, ObjType::None));
	vector<int> visited(mapWidth * mapHeight, 0);
	for (int i = mapHeight - 1; i >= 0; i--)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			int idx = i * mapWidth + j;
			if (mapData[i][j] == ' ' || visited[idx] > 0)
				continue;

			int rowCont = 1;
			for (int k = i - 1; k >= 0; k--)
			{
				if (mapData[k][j] == ' ')
					break;
				rowCont++;
			}

			// colCont: rowCont(y축 콜리더 사이즈)가 같은 연속적인 x축의 갯수
			// Collider 수를 줄이기 위해 연속적인 같은 사이즈의 Collider는 하나의 액터로 묶어서 제작
			int colCont = 1;
			for (int k = j + 1; k < mapWidth; k++)
			{
				int nextRowCont = 0;
				for (int l = i; l >= 0; l--)
				{
					if (mapData[l][k] == ' ')
						break;
					nextRowCont++;
				}

				if (nextRowCont != rowCont)
					break;
				colCont++;
			}

			wstring str = L"";
			for (int k = rowCont - 1; k >= 0; k--)
			{
				for (int l = 0; l < colCont; l++)
				{
					idx = (i - k) * mapWidth + j + l;
					visited[idx] = 1;
					str += mapData[i - k][j + l];
				}
			}

			int r = max(1, rowCont - 1);
			for (int k = 0; k < r; k++)
			{
				for (int l = 0; l < colCont; l++)
				{
					vecType[i - k][j + l] = ObjType::WorldStatic;
				}
			}
			MapObj* obj = new MapObj();
			obj->pos = Vector2D(j + (colCont - 1) / 2, i);
			obj->size = Vector2D(colCont, rowCont);
			obj->strRender = str;
			objects.push_back(obj);
		}
	}
}

void MapManager::Release()
{
	for (int i = 0; i < vecNode.size(); i++)
	{
		delete vecNode[i];
	}
	vecNode.clear();

	delete superTriangle;
	superTriangle = nullptr;

	for (int i = 0; i < vecTriangle.size(); i++)
	{
		delete vecTriangle[i];
	}
	vecTriangle.clear();

	for (int i = 0; i < vecEdge.size(); i++)
	{
		delete vecEdge[i];
	}
	vecEdge.clear();

	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	objects.clear();

	vecUsingNode.clear();
}

void MapManager::EnterNextStage()
{
	if (currStage >= TOTAL_STAGE)
		return;

	// 이미 다른 스테이지에서 사용한 시드값이면 다시 할당
	while (find(vecSeed.begin(), vecSeed.end(), RANDOM_MANAGER->GetSeed()) != vecSeed.end())
	{
		RANDOM_MANAGER->SetCompletelyRandom();
	}
	this->seed = RANDOM_MANAGER->GetSeed();
	vecSeed.push_back(this->seed);
	if (++currStage < TOTAL_STAGE)
	{
		CreateMap(seed);
		MakePlayerObj();
		MakeStairs();
		MakeMerchant();
		PlaceMapObjRandomRoom(objPlayer, ObjType::None, false);
        SOUND_MANAGER->PlayBgm(BGMType::NoneBattleField);
		/*int playerRoom = RANDOM_MANAGER->Range(0, vecNode.size());
		Vector2D roomPos = vecNode[playerRoom]->pos;
		objPlayer->pos = Vector2D(roomPos.x * sizeMultipleX, roomPos.y * sizeMultipleY);*/
	}
	else
	{
		CreateBossRoom();
		MakePlayerObj();
		objPlayer->pos = Vector2D(DATA_WIDTH / 8 * 3, DATA_HEIGHT / 2);

        MapObj* objBoss = new MapObj();
        objBoss->size = Vector2D(11, 3);
        objBoss->strRender = L"┌─────────┐│ B O S S │└─────────┘";
        objects.push_back(objBoss);
        objBoss->pos = Vector2D(DATA_WIDTH / 8 * 5, DATA_HEIGHT / 2 + (objBoss->size.y - 1) / 2);
        Vector2D lt = objBoss->pos - Vector2D((objBoss->size.x - 1) / 2, objBoss->size.y - 1);
        for (int i = 0; i < objBoss->size.y; i++)
        {
            for (int j = 0; j < objBoss->size.x; j++)
            {
                vecType[lt.y + i][lt.x + j] = ObjType::Boss;
            }
        }
        SOUND_MANAGER->PlayBgm(BGMType::BossMapTheme);
	}
}

void MapManager::MakeStairs()
{
	//   #
	//  ##
	// ###
	MapObj* objStairs = new MapObj();
	objStairs->size = Vector2D(3, 3);
	objStairs->strRender = L"  # #####";
	objects.push_back(objStairs);
	PlaceMapObjRandomRoom(objStairs, ObjType::Stairs, true);	
}

void MapManager::MakeMerchant()
{
	MapObj* objMerchant = new MapObj();
	objMerchant->size = Vector2D(11, 4);
	objMerchant->strRender = L"┌─────────┐│ I T E M ││S T O R E│└─────────┘";
	objects.push_back(objMerchant);
	PlaceMapObjRandomRoom(objMerchant, ObjType::Merchant, true);
}

void MapManager::MakePlayerObj()
{
	objPlayer = new MapObj();
	objPlayer->size = Vector2D(1, 1);
	objPlayer->strRender = L"@";
	objects.push_back(objPlayer);
}

// 랜덤 방의 가장자리에서 2씩 안쪽에 있는 영역에 오브젝트 위치
void MapManager::PlaceMapObjRandomRoom(MapObj* obj, ObjType type, bool randomPos)
{
	int randomRoomIdx;
	do
	{
		randomRoomIdx = RANDOM_MANAGER->Range(0, vecNode.size());
	} while (find(vecUsingNode.begin(), vecUsingNode.end(), randomRoomIdx) != vecUsingNode.end());
	vecUsingNode.push_back(randomRoomIdx);
	Node* randomRoomNode = vecNode[randomRoomIdx];
	Vector2D pos;
	if (randomPos)
	{
		// 오브젝트(pivot: 중하단) 시작점 위치 구하기 (lt ~ rb 사이 랜덤)
		Vector2D lt = Vector2D((randomRoomNode->pos.x - randomRoomNode->size.x / 2) * sizeMultipleX + (obj->size.x - 1) / 2, (randomRoomNode->pos.y - randomRoomNode->size.y / 2) * sizeMultipleY + obj->size.y - 1);
		Vector2D rb = lt + Vector2D((randomRoomNode->size.x - 1) * sizeMultipleX - (obj->size.x - 1) / 2, (randomRoomNode->size.y - 1) * sizeMultipleY);
		// lt, rb 에서 2칸씩 더 안쪽에 생성
		lt += Vector2D(2, 2);
		rb -= Vector2D(2, 2);
		pos = Vector2D(RANDOM_MANAGER->Range(lt.x, rb.x + 1), RANDOM_MANAGER->Range(lt.y, rb.y + 1));
	}
	else
	{
		pos = Vector2D(randomRoomNode->pos.x * sizeMultipleX, randomRoomNode->pos.y * sizeMultipleY);
	}

	int left = pos.x - (obj->size.x - 1) / 2;
	for (int k = 0; k < obj->size.y; k++)
	{
		for (int l = 0; l < obj->size.x; l++)
		{
			vecType[pos.y - k][left + l] = type;
		}
	}
	obj->pos = pos;
}

void MapManager::CreateBossRoom()
{
	Release();
	mapHeight = DATA_HEIGHT;
	mapWidth = DATA_WIDTH;
	mapData = vector<vector<wchar_t>>(mapHeight, vector<wchar_t>(mapWidth, ' '));
	Vector2D lt = Vector2D(mapWidth / 4, mapHeight / 4);
	Vector2D rb = lt + Vector2D(mapWidth / 2 - 1, mapHeight / 2 - 1);
	for (int i = lt.x; i <= rb.x; i++)
	{
		mapData[lt.y - 1][i] = '=';
		mapData[lt.y][i] = '=';
		mapData[rb.y - 1][i] = '=';
		mapData[rb.y][i] = '=';
	}

	for (int i = lt.y - 1; i <= rb.y; i++)
	{
		mapData[i][lt.x] = '|';
		mapData[i][rb.x] = '|';
	}

	MakeMapActors();
}

void MapManager::UpdatePlayer()
{
	// 벽에 막혔을 때, 대각 이동 입력 시 벽을 타고 움직이게 하기 위해 x, y 이동 분리
	Vector2D move[2];
	move[0] = Vector2D((GetAsyncKeyState(VK_LEFT) & 0x8000 ? -1 : GetAsyncKeyState(VK_RIGHT) & 0x8000 ? 1 : 0), 0);
	move[1] = Vector2D(0, (GetAsyncKeyState(VK_UP) & 0x8000 ? -1 : GetAsyncKeyState(VK_DOWN) & 0x8000 ? 1 : 0));
	for (int i = 0; i < 2; i++)
	{
        if (move[i] == Vector2D(0, 0))
            continue;

		Vector2D lastPos = objPlayer->pos;
		Vector2D newPos = objPlayer->pos + move[i];
		switch (vecType[newPos.y][newPos.x])
		{
			case ObjType::None:
                {
                    objPlayer->pos = newPos;
                    if (currStage < TOTAL_STAGE)
                    {
                        encountEnemy += DELTA_ENCOUNT_ENEMY;
                        if (RANDOM_MANAGER->Range(0.0, 1.0) <= encountEnemy)
                        {
                            GAME_MANAGER->Battle(false);
                            encountEnemy = MIN_ENCOUNT_ENEMY;
                            return;
                        }
                    }
                    break;
                }
			case ObjType::Stairs:
				EnterNextStage();
				return;
			case ObjType::Merchant:
                GAME_MANAGER->SetState(GameManagerState::Merchant);
				return;
			case ObjType::Boss:
                GAME_MANAGER->Battle(true);
				return;
			default:
				break;
		}
	}
	Sleep(10);	// deltatime 신경 안쓰고, 걍 빠른 움직임 늦추기 위해 Sleep 사용
}

void MapManager::Draw()
{
	sort(objects.begin(), objects.end(), [](const auto& obj1, const auto& obj2)
		{
			return obj1->pos.y < obj2->pos.y;
		});

	Vector2D playerPos = objPlayer->pos;
	Vector2D lt = Vector2D(max(0, playerPos.x - DATA_WIDTH / 2), max(0, playerPos.y - DATA_HEIGHT / 2));
	Vector2D rb = lt + Vector2D(DATA_WIDTH - 1, DATA_HEIGHT - 1);
	int idx, x, y;
	Vector2D objLT, objSize;
	for (int i = 0; i < objects.size(); i++)
	{
		objSize = objects[i]->size;
		objLT = Vector2D(objects[i]->pos.x - (objSize.x - 1) / 2, objects[i]->pos.y - (objSize.y - 1));
		for (int j = 0; j < objSize.y; j++)
		{
			for (int k = 0; k < objSize.x; k++)
			{
				y = objLT.y + j;
				x = objLT.x + k;
				if (y < lt.y || y > rb.y || x < lt.x || x > rb.x)
					continue;
				idx = j * objSize.x + k;
				CONSOLE_PRINTER->SetData(y - lt.y, x - lt.x, objects[i]->strRender[idx]);
			}
		}
	}
}

Triangle* MapManager::CreateTriangle(Node* a, Node* b, Node* c)
{
	if (a == b || b == c || c == a)
	{
		return nullptr;
	}

	Triangle* triangle = new Triangle(a, b, c);
	return triangle;
}

Triangle* MapManager::CreateSuperTriangle(const vector<Vector2D>& points)
{
	int minX = INT_MAX;
	int maxX = INT_MIN;
	int minY = INT_MAX;
	int maxY = INT_MIN;
	for (const auto p : points)
	{
		minX = min(minX, p.x);
		maxX = max(maxX, p.x);
		minY = min(minY, p.y);
		maxY = max(maxY, p.y);
	}

	int dx = maxX - minX;
	int dy = maxY - minY;

	// super triangle을 포인트 리스트 보다 크게 잡는 이유는
	// super triangle의 변과 포인트가 겹치게 되면 삼각형이 아닌 직선이 되므로 델로네 삼각분할을 적용할 수 없기 때문이다.
	Vector2D a = Vector2D(minX - dx, minY - dy);
	Vector2D b = Vector2D(minX - dx, maxY + dy * 3);
	Vector2D c = Vector2D(maxX + dx * 3, minY - dy);

	// super triangle이 직선이면 nullptr 반환
	if (a == b || b == c || c == a)
	{
		return nullptr;
	}

	return CreateTriangle(new Node(-1, a), new Node(-1, b), new Node(-1, c));
}

void MapManager::RemoveSuperTriangle()
{
	if (superTriangle == nullptr)
		return;

	vector<Triangle*> toRemove;
	for (const auto& triangle : vecTriangle)
	{
		if (triangle->a == superTriangle->a || triangle->a == superTriangle->b || triangle->a == superTriangle->c ||
			triangle->b == superTriangle->a || triangle->b == superTriangle->b || triangle->b == superTriangle->c ||
			triangle->c == superTriangle->a || triangle->c == superTriangle->b || triangle->c == superTriangle->c)
			toRemove.push_back(triangle);
	}

	for (const auto& t : toRemove)
	{
		delete t;
		auto it = find(vecTriangle.begin(), vecTriangle.end(), t);
		vecTriangle.erase(it);
	}
}

void MapManager::AddNode(Node* node)
{
	vector<Triangle*> badTriangles;
	for (const auto& t : vecTriangle)
	{
		if (t->circumCircle->Contains(node->pos))
		{
			badTriangles.push_back(t);
		}
	}

	vector<Edge*> polygon;
	for (const auto triangle : badTriangles)
	{
		const vector<Edge*>& edges = triangle->edges;
		for (const auto& edge : edges)
		{
			bool unique = true;
			for (const auto& other : badTriangles)
			{
				if (other->Equals(triangle))
					continue;

				for (const auto& otherEdge : other->edges)
				{
					if (*edge == *otherEdge)
					{
						unique = false;
						break;
					}
				}

				if (!unique)
					break;
			}

			if (unique)
				polygon.push_back(edge);
		}
	}

	for (const auto& t : badTriangles)
	{
		auto it = find(vecTriangle.begin(), vecTriangle.end(), t);
		vecTriangle.erase(it);
	}

	for (const auto& edge : polygon)
	{
		Triangle* t = CreateTriangle(edge->node1, edge->node2, node);
		if (t == nullptr)
			continue;
		vecTriangle.push_back(t);
	}
}

void MapManager::SetEdges()
{
	vecEdge.clear();
	for (int i = 0; i < vecTriangle.size(); i++)
	{
		for (int j = 0; j < vecTriangle[i]->edges.size(); j++)
		{
			vecEdge.push_back(vecTriangle[i]->edges[j]);
		}
	}
}

void MapManager::AdditionalConnectRandomly(const vector<Edge*>& edgesNotConnected)
{
	for (int i = 0; i < edgesNotConnected.size(); i++)
	{
		if (RANDOM_MANAGER->Range(0.0f, 1.0f) < ADDITIONAL_CONNECT_PROB)
		{
			vecEdge.push_back(edgesNotConnected[i]);
		}
	}
}

void MapManager::SetDoorDirection()
{
	for (int i = 0; i < vecEdge.size(); i++)
	{
		Node* startNode = vecEdge[i]->node1;
		Node* endNode = vecEdge[i]->node2;

		int diffX = endNode->pos.x - startNode->pos.x;
		int diffY = endNode->pos.y - startNode->pos.y;
		if (abs(diffY) > abs(diffX))
		{
			startNode->doorDirection |= diffY > 0 ? 2 : 8;
			endNode->doorDirection |= diffY > 0 ? 8 : 2;
		}
		else
		{
			startNode->doorDirection |= diffX > 0 ? 1 : 4;
			endNode->doorDirection |= diffX > 0 ? 4 : 1;
		}
	}
}

void MapManager::AStarPathFind(Edge* edge, int gridSizeX, int gridSizeY)
{
	Vector2D startPos = edge->node1->pos;
	Vector2D endPos = edge->node2->pos;
	int rangeX[2] = { min(startPos.x, endPos.x), max(startPos.x, endPos.x) };
	int rangeY[2] = { min(startPos.y, endPos.y), max(startPos.y, endPos.y) };

	vector<vector<AStarNode*>> astarGrid(gridSizeY, vector<AStarNode*>(gridSizeX));
	for (int i = rangeY[0]; i <= rangeY[1]; i++)
	{
		for (int j = rangeX[0]; j <= rangeX[1]; j++)
		{
			AStarNode* newNode = new AStarNode();
			newNode->x = j;
			newNode->y = i;
			newNode->h = abs(endPos.x - newNode->x) + abs(endPos.y - newNode->y);
			astarGrid[i][j] = newNode;
		}
	}

	map<int, deque<AStarNode*>> mapOpen;
	auto AddOpen = [&mapOpen](AStarNode* node)
		{
			int f = node->F();
			if (mapOpen.find(f) == mapOpen.end())
			{
				mapOpen[f] = deque<AStarNode*>();
			}
			mapOpen[f].push_back(node);
		};

	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	unordered_set<AStarNode*> setOpen;
	AStarNode* startNode = astarGrid[startPos.y][startPos.x];
	startNode->g = 0;
	AddOpen(startNode);
	setOpen.insert(startNode);
	while (mapOpen.size() > 0)
	{
		AStarNode* node = *(mapOpen.begin()->second.begin());
		node->closed = true;
		setOpen.erase(node);
		mapOpen.begin()->second.pop_front();
		if (mapOpen.begin()->second.empty())
		{
			mapOpen.erase(mapOpen.begin());
		}

		if (node->h == 0)
		{
			while (node != nullptr)
			{
				// 빈 공간이라면 통로로 설정
				if (grid[node->y][node->x] == CostAStar::Empty)
				{
					grid[node->y][node->x] = CostAStar::Hallway;
				}
				node = node->parentNode;
			}
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int newX = node->x + dx[i];
			int newY = node->y + dy[i];
			AStarNode* newNode = astarGrid[newY][newX];
			// 범위 안에 없으면
			if (newX < rangeX[0] || newX > rangeX[1] || newY < rangeY[0] || newY > rangeY[1])
				continue;

			// 닫힌 노드라면
			if (newNode->closed)
				continue;

			int newG = node->g + (int)grid[newY][newX];
			bool isInSetOpen = setOpen.find(newNode) != setOpen.end();
			// 새 g가 기존 g보다 작거나, 열린 리스트에 노드가 없으면
			if (newG < newNode->g || !isInSetOpen)
			{
				if (isInSetOpen)
				{
					const auto& list = mapOpen[newNode->F()];
					auto it = find(list.begin(), list.end(), newNode);
					mapOpen[newNode->F()].erase(it);
					if (mapOpen[newNode->F()].empty())
					{
						mapOpen.erase(newNode->F());
					}
				}
				newNode->g = newG;
				newNode->parentNode = node;
				AddOpen(newNode);
				setOpen.insert(newNode);
			}
		}
	}
}
