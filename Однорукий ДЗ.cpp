// Однорукий ДЗ.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//1) Создать имитацию игры «однорукий бандит». Происходит «вращение» 
//трех барабанов(естественно, количество шагов вращений
//	каждого из них выбирается случайно), на которых
//	изображены разные значки; и если выпадает определенная
//	комбинация, то игрок получает какой - то выигрыш
//	(использовать кольцевую очередь).

#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;
class QueueRing
{
    char* Wait;
    int MaxQueueLength;
    int QueueLength;

public:
    QueueRing(int m);
    ~QueueRing();
    void Add(char c);
    bool Extract();
    void Clear();
    bool IsEmpty();
    bool IsFull();
    int GetCount();
    void Show();
    char GetElement(int index);
    void Spin();
};

QueueRing::QueueRing(int m)
{
    MaxQueueLength = m;
    Wait = new char[MaxQueueLength];
    QueueLength = 0;
}

QueueRing::~QueueRing()
{
    delete[] Wait;
}

void QueueRing::Clear()
{
    QueueLength = 0;
}

bool QueueRing::IsEmpty()
{
    return QueueLength == 0;
}

bool QueueRing::IsFull()
{
    return QueueLength == MaxQueueLength;
}

int QueueRing::GetCount()
{
    return QueueLength;
}

void QueueRing::Add(char c)
{
    if (!IsFull())
        Wait[QueueLength++] = c;
}

bool QueueRing::Extract()
{
    if (!IsEmpty()) {
        char temp = Wait[0];
        for (int i = 1; i < QueueLength; i++)
            Wait[i - 1] = Wait[i];
        Wait[QueueLength - 1] = temp;
        return temp;
    }
    else
        return false;
}

void QueueRing::Show()
{
    for (int i = 0; i < QueueLength; i++) {
        cout << Wait[i] << " ";
    }
    cout << "\n-----\n";
}

char QueueRing::GetElement(int index)
{
    if (index >= 0 && index < QueueLength)
        return Wait[index];
    else
        return '\0'; // Возвращаем нулевой символ в случае недопустимого индекса
}

void QueueRing::Spin()
{
    int numSpins = rand() % 5 + 1; // Случайное количество вращений барабанов (от 1 до 5)

    // Вращение барабанов
    for (int spin = 0; spin < numSpins; spin++) {
        Extract();
    }
};

void main()
{
    srand(time(0));
    int totalPoints = 1000; // Начальное количество очков (TOTAL)

    QueueRing reel1(5); // Барабан 1
    QueueRing reel2(5); // Барабан 2
    QueueRing reel3(5); // Барабан 3

    // Заполнение барабанов символами мастей иг
    for (int i = 0; i < 5; i++) {
        reel1.Add(3 + (rand() % 4)); // Символы мастей карт от 3 до 6 (таблица ASCII)
        reel2.Add(3 + (rand() % 4));
        reel3.Add(3 + (rand() % 4));
    }
    // Отображение текущего состояния барабанов
    cout << "Reel 1: ";
    reel1.Show();
    cout << "Reel 2: ";
    reel2.Show();
    cout << "Reel 3: ";
    reel3.Show();

    while (totalPoints >= 50) {
        int choice;
        cout << "TOTAL Points =" << totalPoints << endl << "Enter 1 to spin(50 Poins) the reels, or 0 to quit: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting the game. Goodbye! You won is " << totalPoints << " Points" << endl;
            break;
        }
        else if (choice == 1) {
            totalPoints -= 50; // Каждый спин уменьшает количество очков на 50
            reel1.Spin();
            reel2.Spin();
            reel3.Spin();

            // Отображение текущего состояния барабанов
            cout << "Reel 1: ";
            reel1.Show();
            cout << "Reel 2: ";
            reel2.Show();
            cout << "Reel 3: ";
            reel3.Show();

            // Проверка на выигрышную комбинацию
            if (reel1.GetElement(0) == reel2.GetElement(0) && reel2.GetElement(0) == reel3.GetElement(0)) {
                cout << "Congratulations! You won!  " << endl;
                totalPoints += 100;
            } if (reel1.GetElement(1) == reel2.GetElement(1) && reel2.GetElement(1) == reel3.GetElement(1)) {
                cout << "Congratulations! You won!  " << endl;
                totalPoints += 100;
            }

            else if (reel1.GetElement(2) == reel2.GetElement(2) && reel2.GetElement(2) == reel3.GetElement(2)) {
                cout << "Congratulations! You won! " << endl;
                totalPoints += 100;
            }

            else if (reel1.GetElement(3) == reel2.GetElement(3) && reel2.GetElement(3) == reel3.GetElement(3)) {
                cout << "Congratulations! You won!" << endl;
                totalPoints += 100; // Каждая выигрышная комбинация добавляет 100 очков
            }

            else if (reel1.GetElement(4) == reel2.GetElement(4) && reel2.GetElement(4) == reel3.GetElement(4)) {
                cout << "Congratulations! You won! " << endl;
                totalPoints += 100;
            }

            else if (reel1.GetElement(0) == reel2.GetElement(1) && reel2.GetElement(1) == reel3.GetElement(2)) {
                cout << "Congratulations! You won!  " << endl;
                totalPoints += 100;
            }

            else if (reel1.GetElement(1) == reel2.GetElement(2) && reel2.GetElement(2) == reel3.GetElement(3)) {
                cout << "Congratulations! You won! " << endl;
                totalPoints += 100;
            }
            else if (reel1.GetElement(2) == reel2.GetElement(3) && reel2.GetElement(3) == reel3.GetElement(4)) {
                cout << "Congratulations!You won! " << endl;
                totalPoints += 100;
            }

            else if (reel1.GetElement(4) == reel2.GetElement(3) && reel2.GetElement(3) == reel3.GetElement(2)) {
                cout << "Congratulations! You won! " << endl;
                totalPoints += 100;
            }
            else if (reel1.GetElement(3) == reel2.GetElement(2) && reel2.GetElement(2) == reel3.GetElement(1)) {
                cout << "Congratulations! You won! " << endl;
                totalPoints += 100;
            }
            else if (reel1.GetElement(2) == reel2.GetElement(1) && reel2.GetElement(1) == reel3.GetElement(0)) {

                cout << "Congratulations! You won!  " << endl;
                totalPoints += 100;
            }

            else
            {
                cout << "Sorry, you didn't win this time." << endl;

            }
        }

        else {
            cout << "Invalid input. Please enter 1 to spin the reels, or 0 to quit." << endl;
        }

    }cout << "Game Over! Thank's for game!" << endl;

}
