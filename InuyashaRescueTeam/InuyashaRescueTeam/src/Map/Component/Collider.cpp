#include "Map/Component/Collider.h"
#include "Map/Actor/Actor.h"

int Collider::callbackId = 0;
vector<Collider*> Collider::colliders;

CollideChannel operator|(CollideChannel ch1, CollideChannel ch2)
{
	return static_cast<CollideChannel>(static_cast<unsigned int>(ch1) | static_cast<unsigned int>(ch2));
}

CollideChannel operator&(CollideChannel ch1, CollideChannel ch2)
{
	return static_cast<CollideChannel>(static_cast<unsigned int>(ch1) & static_cast<unsigned int>(ch2));
}

Collider::Collider()
	: myChannel(CollideChannel::None), channelResponse(CollideChannel::None), lt(), rb()
{
	colliders.push_back(this);
}

Collider::~Collider()
{
	auto it = find(colliders.begin(), colliders.end(), this);
	delete *it;
	colliders.erase(it);
}

void Collider::Update()
{
	Vector2D pos = owner->GetPos();
	lt = { pos.x - (int)((size.x - 1) * pivot.x), pos.y - (int)((size.y - 1) * pivot.y) };
	rb = { lt.x + size.x - 1, lt.y + size.y - 1 };
	DetectCollision();
}

void Collider::SetSize(Vector2F pivot, Vector2D size)
{
	this->pivot = pivot;
	this->size = size;
}

void Collider::SetMyChannel(CollideChannel channel)
{
	myChannel = channel;
}

void Collider::SetChannelResonse(CollideChannel channel)
{
	channelResponse = channel;
}

int Collider::AddOnHit(function<void(const vector<Actor*>&)> onHit)
{
	listOnHit.push_back(make_pair(callbackId, onHit));
	return callbackId++;
}

void Collider::RemoveOnHit(int callbackId)
{
	auto it = find_if(listOnHit.begin(), listOnHit.end(),
		[callbackId](const auto& pair)
		{
			return pair.first == callbackId;
		});

	if (it != listOnHit.end())
	{
		listOnHit.erase(it);
	}
}

Vector2F Collider::GetPivot()
{
    return pivot;
}

Vector2D Collider::GetSize()
{
	return size;
}

Vector2D Collider::GetLT()
{
	return lt;
}

Vector2D Collider::GetRB()
{
	return rb;
}

CollideChannel Collider::GetChannel()
{
	return myChannel;
}

CollideChannel Collider::GetChannelResponse()
{
	return channelResponse;
}

vector<Actor*> Collider::DetectCollision()
{
	vector<Actor*> result;
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i] == this || !colliders[i]->GetOwner()->GetActive() || (myChannel & colliders[i]->GetChannelResponse()) == CollideChannel::None)
			continue;

		Vector2D otherLT = colliders[i]->GetLT();
		Vector2D otherRB = colliders[i]->GetRB();
		if (otherRB.x < lt.x || otherLT.x > rb.x || otherRB.y < lt.y || otherLT.y > rb.y)
			continue;
		result.push_back(colliders[i]->GetOwner());
	}

	if (!result.empty())
	{
		for (const auto& pair : listOnHit)
		{
			pair.second(result);
		}
	}

	return result;
}
