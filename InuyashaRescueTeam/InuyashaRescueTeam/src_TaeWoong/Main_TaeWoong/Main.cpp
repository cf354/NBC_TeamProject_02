#include "Player.hpp"
#include "C_Attack.hpp"
#include "C_Guard.hpp"
#include "C_Move.hpp"
#include <memory> // std::make_shared 사용

int main()
{
    Player player("Hero", 1, 100, 50, 10, 5);
    hideCursor(); // 시작 전 커서 숨기기

    // 테스트용 카드 생성 및 플레이어에게 추가 
    bool attackRange[3][3] = { {0, 1, 0}, {1, 1, 1}, {0, 1, 0} };
    player.AddCard(std::make_shared<C_Attack>("강타", 2, 0, 10, attackRange));
    player.AddCard(std::make_shared<C_Move>("전진", 1, 0, 1, 0, 1)); // 아래로 1칸 이동
    player.AddCard(std::make_shared<C_Guard>("방패 막기", 1, 0, 5));

    while (true) {
        // 커서 위치 갱신 
        setCursorPosition(0, 0);

        std::cout << "***** 플레이어 이동 및 카드 테스트 *****" << std::endl;
        std::cout << "  - 방향키: 이동" << std::endl;
        std::cout << "  - E: 경험치 증가" << std::endl;
        std::cout << "  - S: 보유 카드 보기 및 사용" << std::endl;
        std::cout << "  - Q: 게임 종료" << std::endl;
        player.PrintStatus();
        setCursorPosition(0, 15);

        // _getch()는 키를 누르는 즉시 문자를 반환 (Enter 키 불필요)
        int keyInput = _getch();

        if (keyInput == 'e' || keyInput == 'E')
        {
            player.AddEXP(50);
        }
        else if (keyInput == 'q' || keyInput == 'Q') 
        {
            std::cout << "게임을 종료합니다." << std::endl;
            break;
        }
        else if (keyInput == 's' || keyInput == 'S')
        {
            player.ShowCards();
            std::cout << "사용할 카드의 번호를 입력하세요 (취소: 0): ";
            int cardNum;
            std::cin >> cardNum;
            std::cin.clear(); // 입력 버퍼 클리어
            std::cin.ignore(LLONG_MAX, '\n');

            if (cardNum > 0)
            {
                player.UseCard(cardNum);
                Sleep(1500); // 사용 결과 메시지를 1.5초 동안 보여줌
            }
        }

        // * 참고 : 방향키 입력은 224라는 특수 값과 함께 입력됨
        if (keyInput == 224) {
            keyInput = _getch(); // 실제 방향키 값을 얻기 위해 한 번 더 호출
            switch (keyInput) {
            case 72: // 위쪽 방향키
                player.Move(Direction::UP);
                break;
            case 80: // 아래쪽 방향키
                player.Move(Direction::DOWN);
                break;
            case 75: // 왼쪽 방향키
                player.Move(Direction::LEFT);
                break;
            case 77: // 오른쪽 방향키
                player.Move(Direction::RIGHT);
                break;
            }
        }
    }
    return 0;
}