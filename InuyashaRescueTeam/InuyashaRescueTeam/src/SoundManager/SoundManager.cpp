#include "SoundManager\SoundManager.h"
#include <iostream>

void SoundManager::Init()
{
	cardSEMap["WindScar"] = SEType::WindScar;
	cardSEMap["BladesOfBlood"] = SEType::BladesOfBlood;
	cardSEMap["IronReaver"] = SEType::IronReaver;

	SOUND_MANAGER->LoadBgm(BGMType::BattleField, "sound\\BattleTheme.wav");
	SOUND_MANAGER->LoadBgm(BGMType::StartScene, "sound\\Grip.wav");
	SOUND_MANAGER->LoadBgm(BGMType::BossTheme, "sound\\BossBattleTheme.wav");
	SOUND_MANAGER->LoadBgm(BGMType::NoneBattleField, "sound\\AffectionsTouchingAcrossTime.wav");//bgm추가
	SOUND_MANAGER->LoadBgm(BGMType::BossMapTheme, "sound\\BossTheme.wav");

	SOUND_MANAGER->LoadSE(SEType::WindScar, "sound\\WindScar.wav");
	SOUND_MANAGER->LoadSE(SEType::BladesOfBlood, "sound\\BladesOfBlood.wav");
	SOUND_MANAGER->LoadSE(SEType::IronReaver, "sound\\IronReaver.wav");
	SOUND_MANAGER->LoadSE(SEType::blop, "sound\\blop.wav");
	SOUND_MANAGER->LoadSE(SEType::buy, "sound\\buy.wav");//효과음추가

	SOUND_MANAGER->SetBgmVolume(10.f);//소리설정
	SOUND_MANAGER->SetSEVolume(10.f);
}

SEType SoundManager::GetCardSEType(std::string s)
{
	return cardSEMap[s];
}

void SoundManager::LoadBgm(BGMType type, const std::string& path)
{
	auto music = std::make_unique<sf::Music>();
	if (music->openFromFile(path)) {
		bgm[type] = std::move(music);
        bgm[type]->setLoop(true);
	}
}

void SoundManager::PlayBgm(BGMType type)
{
	if (bgm.count(type)) {
		bgm[type]->play();
	}
}

void SoundManager::LoadSE(SEType type, const std::string& path)
{
	if (!buffer[type].loadFromFile(path)) {
		std::cout << "SoundManager error" << std::endl;
	}
	sound[type].setBuffer(buffer[type]);
}

void SoundManager::PlaySE(SEType type)
{
	sound[type].play();
}

void SoundManager::SetBgmVolume(float volume) {
	for (auto& pair : bgm) {
		if (pair.second) {
			pair.second->setVolume(volume);  // unique_ptr -> sf::Music 접근
		}
	}
}

void SoundManager::SetSEVolume(float volume)
{
	for (auto& a : sound) {
		a.second.setVolume(volume);
	}
}




