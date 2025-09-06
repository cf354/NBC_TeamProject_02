#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <map>



enum class BGMType {
	BattleField,
	BossTheme,
	NoneBattleField,
	StartScene
	
};
enum class SEType {
	WindScar,
	BladesOfBlood,
	IronReaver,
};

class SoundManager
{
private:
	std::map<BGMType, sf::Music>bgm;//브금

	std::map<SEType, sf::SoundBuffer>buffer;//효과음 버퍼
	std::map<SEType, sf::Sound> sound;
	std::map<std::string, SEType> cardSEMap;
	
public:
	SoundManager();
	SEType GetCardSEType(std::string s);
	void LoadBgm(BGMType type,const std::string&path);
	void PlayBgm(BGMType type);

	void LoadSE(SEType type, const std::string& path);
	void PlaySE(SEType type);

	void SetBgmVolume(float volume);

	void SetSEVolume(float volume);
};

