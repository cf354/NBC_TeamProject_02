#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <map>
#include <Common/Singleton.h>



enum class BGMType {
	BattleField,
	BossTheme,
	NoneBattleField,
	StartScene,
	BossMapTheme
	
};
enum class SEType {
	WindScar,
	BladesOfBlood,
	IronReaver,
	blop,
	buy
};

class SoundManager : public Singleton<SoundManager>
{
private:
	std::map<BGMType, std::unique_ptr<sf::Music>>bgm;//브금

	std::map<SEType, sf::SoundBuffer>buffer;//효과음 버퍼
	std::map<SEType, sf::Sound> sound;
	std::map<std::string, SEType> cardSEMap;
	
public:
	void Init();

	SEType GetCardSEType(std::string s);
	void LoadBgm(BGMType type,const std::string&path);
	void PlayBgm(BGMType type);

	void LoadSE(SEType type, const std::string& path);
	void PlaySE(SEType type);

	void SetBgmVolume(float volume);

	void SetSEVolume(float volume);
};

#define SOUND_MANAGER (SoundManager::GetInstance())
