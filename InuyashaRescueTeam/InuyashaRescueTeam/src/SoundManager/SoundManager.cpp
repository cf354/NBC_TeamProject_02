#include "SoundManager\SoundManager.h"
#include <iostream>

void SoundManager::Init()
{
    cardSEMap["BladeStrike"] = SEType::BladeStrike;
	cardSEMap["WindScar"] = SEType::WindScar;
	cardSEMap["BladesOfBlood"] = SEType::BladesOfBlood;
	cardSEMap["IronReaver"] = SEType::IronReaver;
    cardSEMap["Adamant_Barrage"] = SEType::Adamant_Barrage;
    cardSEMap["Backlash_Wave"] = SEType::Backlash_Wave;

	SOUND_MANAGER->LoadBgm(BGMType::BattleField, "sound\\BattleTheme.wav");
	SOUND_MANAGER->LoadBgm(BGMType::StartScene, "sound\\Grip.wav");
	SOUND_MANAGER->LoadBgm(BGMType::BossTheme, "sound\\BossBattleTheme.wav");
	SOUND_MANAGER->LoadBgm(BGMType::NoneBattleField, "sound\\AffectionsTouchingAcrossTime.wav");//bgm추가
	SOUND_MANAGER->LoadBgm(BGMType::BossMapTheme, "sound\\BossTheme.wav");
    SOUND_MANAGER->LoadBgm(BGMType::EndBgm, "sound\\EndBgm.wav");
    SOUND_MANAGER->LoadBgm(BGMType::ShopBgm, "sound\\ShopBgm.wav");

	SOUND_MANAGER->LoadSE(SEType::WindScar, "sound\\WindScar.wav");
	SOUND_MANAGER->LoadSE(SEType::BladesOfBlood, "sound\\BladesOfBlood.wav");
	SOUND_MANAGER->LoadSE(SEType::IronReaver, "sound\\IronReaver.wav");
	SOUND_MANAGER->LoadSE(SEType::blop, "sound\\blop.wav");
	SOUND_MANAGER->LoadSE(SEType::buy, "sound\\buy.wav");
    SOUND_MANAGER->LoadSE(SEType::BladeStrike, "sound\\BladeStrike.wav");
    SOUND_MANAGER->LoadSE(SEType::Adamant_Barrage, "sound\\Adamant_Barrage.wav");//효과음추가
    SOUND_MANAGER->LoadSE(SEType::Backlash_Wave, "sound\\Backlash_Wave.wav");
    SOUND_MANAGER->LoadSE(SEType::CardMoveSelect, "sound\\CardMoveSelect.wav");
    SOUND_MANAGER->LoadSE(SEType::CardSelect, "sound\\CardSelect.wav");
    SOUND_MANAGER->LoadSE(SEType::Naraku_Voice, "sound\\Naraku_Voice.wav");


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
	if (currentbgm && currentbgm->getStatus() == sf::Music::Playing) {
		currentbgm->stop();
	}
	if (bgm.count(type)) {
		currentbgm = bgm[type].get();
		currentbgm->play();
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
    if (type == SEType::None) return; // SE 없는 경우 무시
    if (sound.count(type))
        sound[type].play();
}

void SoundManager::SetBgmVolume(float volume) {
	for (auto& pair : bgm) {
		if (pair.second) {
			pair.second->setVolume(volume);  // unique_ptr -> sf::Music 접근
		}
	}
    bgm[BGMType::NoneBattleField]->setVolume(volume+40.f);
}

void SoundManager::SetSEVolume(float volume)
{
	for (auto& a : sound) {
		a.second.setVolume(volume);
	}
    sound[SEType::Naraku_Voice].setVolume(100.f);
}




