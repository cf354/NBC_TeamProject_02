// Boss.h
#pragma once
#include "Entity/Enemy.h"
#include <iostream>
#include <vector>
#include <map>
#include "Card/Card.h"
#include "SoundManager/SoundManager.h" // SoundManager 헤더 포함

// Boss 클래스: Enemy를 상속받아 보스 전용 카드 덱과 패턴을 제공
class Boss : public Enemy {
private:
    int phase = 1;    // 보스 전투 페이즈 (체력 조건 등에 따라 변경)
    bool phase2VoicePlayed = false; // 2페이즈 진입 사운드 재생 여부 

public:
    // 생성자에 EnemyType 인수를 추가
    Boss(std::string n, int lv, int h, int s, int a, int d, int dm, int de, const char* spritefilefath, EnemyType t)
        : Enemy(n, lv, h, s, a, d, dm, de, spritefilefath, t) {}

    // 보스 전용 덱 초기화 로직을 오버라이드
    void InitDeck() override;

    // 가중치 기반 카드 선택 (페이즈 전환 로직 포함)
    std::shared_ptr<Card> GetRandomCard(int playerX, int playerY, int enemyX, int enemyY) override;

    ~Boss() {}
};