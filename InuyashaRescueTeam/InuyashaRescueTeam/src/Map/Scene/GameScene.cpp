#include "Map/Scene/GameScene.h"
#include "Map/Actor/APlayer.h"
#include "Map/Component/TAnimRenderer.h"
#include "Map/Component/TSpriteRenderer.h"
#include "Map/Component/Collider.h"
#include "Map/Camera.h"
#include "Map/Managers/SceneManager.h"
#include "Map/Managers/MapManager.h"

void GameScene::Enter()
{
	player = new APlayer();
	TAnimRenderer* playerAnimRenderer = player->AddComponent<TAnimRenderer>();

	vector<TSprite> spriteIdle;
	spriteIdle.push_back(TSprite(Vector2D(5, 3), L"??O???/|\\??/ \\?"));

	vector<TSprite> spritesUpDown;
	spritesUpDown.push_back(TSprite(Vector2D(5, 3), L"??O???.|`??` .?"));
	spritesUpDown.push_back(TSprite(Vector2D(5, 3), L"??O???(|`??` )?"));
	spritesUpDown.push_back(TSprite(Vector2D(5, 3), L"??O???(|`??` )?"));
	spritesUpDown.push_back(TSprite(Vector2D(5, 3), L"??O???.|`??` .?"));
	spritesUpDown.push_back(TSprite(Vector2D(5, 3), L"??O???`|.??. `?"));
	spritesUpDown.push_back(TSprite(Vector2D(5, 3), L"??O???`|)??( `?"));
	spritesUpDown.push_back(TSprite(Vector2D(5, 3), L"??O???`|)??( `?"));
	spritesUpDown.push_back(TSprite(Vector2D(5, 3), L"??O???`|.??. `?"));

	vector<TSprite> spritesSide;
	spritesSide.push_back(TSprite(Vector2D(5, 3), L"??O???.|\\??/ .?"));
	spritesSide.push_back(TSprite(Vector2D(5, 3), L"??O???.|\\??/ .?"));
	spritesSide.push_back(TSprite(Vector2D(5, 3), L"??O????|????|??"));
	spritesSide.push_back(TSprite(Vector2D(5, 3), L"??O???/|.??. \\?"));
	spritesSide.push_back(TSprite(Vector2D(5, 3), L"??O???/|.??. \\?"));
	spritesSide.push_back(TSprite(Vector2D(5, 3), L"??O????|????|??"));

	TAnimation* animIdle = new TAnimation("Idle", Vector2F(0.5f, 1.0f));
	animIdle->SetSprites(spriteIdle);
	playerAnimRenderer->AddAnimation(animIdle);

    TAnimation* animWalkUpDown = new TAnimation("WalkUpDown", Vector2F(0.5f, 1.0f));
	animWalkUpDown->SetSprites(spritesUpDown);
	playerAnimRenderer->AddAnimation(animWalkUpDown);

    TAnimation* animWalkSide = new TAnimation("WalkSide", Vector2F(0.5f, 1.0f));
	animWalkSide->SetSprites(spritesSide);
	playerAnimRenderer->AddAnimation(animWalkSide);

	playerAnimRenderer->SetCurrAnim("Idle");

	Collider* playerCollider = player->AddComponent<Collider>();
	playerCollider->SetMyChannel(CollideChannel::Player);
	playerCollider->SetChannelResonse(CollideChannel::Actor | CollideChannel::WorldObj);
	playerCollider->SetSize({ 0.5f, 1.0f }, { 3, 1 });
	player->SetPos({ 25, 7 });
	AddActor(player);

	MAP_MANAGER->EnterNextStage();

	/*Actor* a = new Actor();
	TSpriteRanderer* aSprite = a->AddComponent<TSpriteRanderer>();
	aSprite->SetSprite({ 0.5f, 1.0f }, { 7, 5 }, "========     ==     ==     ========");
	Collider* aCollider = a->AddComponent<Collider>();
	aCollider->SetSize({ 0.5f, 1.0f }, { 7, 5 });
	aCollider->SetMyChannel(CollideChannel::Actor);
	aCollider->SetChannelResonse(CollideChannel::All);
	a->SetPos({ 20, 10 });
	AddActor(a);*/

	camera = new Camera();
	camera->SetTarget(player);
}

void GameScene::Render()
{
	Scene::Render();
}
