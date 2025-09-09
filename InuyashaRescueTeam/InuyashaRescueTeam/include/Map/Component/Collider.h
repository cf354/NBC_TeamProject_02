#pragma once
#include <vector>
#include <list>
#include <functional>
#include "IComponent.h"
#include "Map/MapTypes.h"

using namespace std;
using namespace Map;

enum class CollideChannel : unsigned int
{
	None = 0,
	Actor = 1 << 0,
	Player = 1 << 1,
	WorldObj = 1 << 2,
	
	All = ~0u
};

CollideChannel operator|(CollideChannel ch1, CollideChannel ch2);
CollideChannel operator&(CollideChannel ch1, CollideChannel ch2);

class Collider : public IComponent
{
public:
	Collider();
	~Collider();

	void Update() override;

	void SetSize(Vector2F pivot, Vector2D size);
	void SetMyChannel(CollideChannel channel);
	void SetChannelResonse(CollideChannel channel);
	
	// 람다 캡쳐나 멤버 함수 포인터를 추가했을 때, 직접 비교하고 지우는 건 불가능. 따라서 id로 반환하고, id를 이용해서 제거.
	int AddOnHit(function<void(const vector<Actor*>&)> onHit);
	void RemoveOnHit(int callbackId);

    Vector2F GetPivot();
	Vector2D GetSize();
	Vector2D GetLT();
	Vector2D GetRB();
	CollideChannel GetChannel();								// 내 채널 반환
	CollideChannel GetChannelResponse();						// 내가 충돌 검사할 채널 반환
	vector<Actor*> DetectCollision();							// 부딪힌 액터 반환

private:
	Vector2F pivot;
	Vector2D size = { 3, 1 };
	Vector2D lt;
	Vector2D rb;

	CollideChannel myChannel;									// 내 충돌 채널
	CollideChannel channelResponse;								// 충돌 검사할 채널

	list<pair<int, function<void(const vector<Actor*>&)>>> listOnHit;
	static int callbackId;

	static vector<Collider*> colliders;
};

