#include "Player.hpp"
#include "C_Attack.hpp"
#include "C_Guard.hpp"
#include "C_Move.hpp"
#include <memory> // std::make_shared ���

int main()
{
    Player player("Hero", 1, 100, 50, 10, 5);
    hideCursor(); // ���� �� Ŀ�� �����

    // �׽�Ʈ�� ī�� ���� �� �÷��̾�� �߰� 
    bool attackRange[3][3] = { {0, 1, 0}, {1, 1, 1}, {0, 1, 0} };
    player.AddCard(std::make_shared<C_Attack>("��Ÿ", 2, 0, 10, attackRange));
    player.AddCard(std::make_shared<C_Move>("����", 1, 0, 1, 0, 1)); // �Ʒ��� 1ĭ �̵�
    player.AddCard(std::make_shared<C_Guard>("���� ����", 1, 0, 5));

    while (true) {
        // Ŀ�� ��ġ ���� 
        setCursorPosition(0, 0);

        std::cout << "***** �÷��̾� �̵� �� ī�� �׽�Ʈ *****" << std::endl;
        std::cout << "  - ����Ű: �̵�" << std::endl;
        std::cout << "  - E: ����ġ ����" << std::endl;
        std::cout << "  - S: ���� ī�� ���� �� ���" << std::endl;
        std::cout << "  - Q: ���� ����" << std::endl;
        player.PrintStatus();
        setCursorPosition(0, 15);

        // _getch()�� Ű�� ������ ��� ���ڸ� ��ȯ (Enter Ű ���ʿ�)
        int keyInput = _getch();

        if (keyInput == 'e' || keyInput == 'E')
        {
            player.AddEXP(50);
        }
        else if (keyInput == 'q' || keyInput == 'Q') 
        {
            std::cout << "������ �����մϴ�." << std::endl;
            break;
        }
        else if (keyInput == 's' || keyInput == 'S')
        {
            player.ShowCards();
            std::cout << "����� ī���� ��ȣ�� �Է��ϼ��� (���: 0): ";
            int cardNum;
            std::cin >> cardNum;
            std::cin.clear(); // �Է� ���� Ŭ����
            std::cin.ignore(LLONG_MAX, '\n');

            if (cardNum > 0)
            {
                player.UseCard(cardNum);
                Sleep(1500); // ��� ��� �޽����� 1.5�� ���� ������
            }
        }

        // * ���� : ����Ű �Է��� 224��� Ư�� ���� �Բ� �Էµ�
        if (keyInput == 224) {
            keyInput = _getch(); // ���� ����Ű ���� ��� ���� �� �� �� ȣ��
            switch (keyInput) {
            case 72: // ���� ����Ű
                player.Move(Direction::UP);
                break;
            case 80: // �Ʒ��� ����Ű
                player.Move(Direction::DOWN);
                break;
            case 75: // ���� ����Ű
                player.Move(Direction::LEFT);
                break;
            case 77: // ������ ����Ű
                player.Move(Direction::RIGHT);
                break;
            }
        }
    }
    return 0;
}