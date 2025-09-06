#include "SoundManager\SoundManager.h"
#include <iostream>



SoundManager::SoundManager()
{
	cardSEMap["WindScar"] = SEType::WindScar;
	cardSEMap["BladesOfBlood"] = SEType::BladesOfBlood;
	cardSEMap["IronReaver"] = SEType::IronReaver;
}

SEType SoundManager::GetCardSEType(std::string s)
{
	return cardSEMap[s];
}

void SoundManager::LoadBgm(BGMType type, const std::string& path)
{
	if (!bgm[type].openFromFile(path)) {
		std::cout << "SoundManager error" << std::endl;
	}
}

void SoundManager::PlayBgm(BGMType type)
{
	bgm[type].setLoop(true);
	bgm[type].play();
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

void SoundManager::SetBgmVolume(float volume)
{
	for (auto& a : bgm) {
		a.second.setVolume(volume);
	}
		
}

void SoundManager::SetSEVolume(float volume)
{
	for (auto& a : sound) {
		a.second.setVolume(volume);
	}
}




