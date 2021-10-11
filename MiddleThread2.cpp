
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>
#include <random>
#include <conio.h>

#include <Windows.h>

using namespace std;

const chrono::milliseconds FrameDelay = 200ms;

const int Width = 2;
const int Height = 10;
const int FieldStartX = 10; // must be >0
const int FieldStartY = 0;

const float BlockProbability = 50.f;

const char Border(186);
const char Block(219);
const char Player(1);

char Field[Width][Height];

int PlayerX = FieldStartX;
int PlayerY = FieldStartY + Height - 1;

bool bIsPrevLineBlock = false;
bool bEndGame = false;

mutex MutexField;

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void SetCursorVisibility(bool bIsShow)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hOut, &structCursorInfo);
    structCursorInfo.bVisible = bIsShow;
    SetConsoleCursorInfo(hOut, &structCursorInfo);
}

int GetRandomInRange(const int min, const int max)
{
    static default_random_engine gen(
        static_cast<unsigned>(
            chrono::system_clock::now().time_since_epoch().count()
            )
    );
    uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

void DrawMap()
{
    int x1 = FieldStartX - 1;
    int x2 = FieldStartX + Width;
    for (int y = FieldStartY; y < (FieldStartY + Height); y++)
    {
        setCursorPosition(x1, y);
        cout << Border;
        setCursorPosition(x2, y);
        cout << Border;
    }
    setCursorPosition(PlayerX, PlayerY);
    cout << (Player);
}

void InitField()
{
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            Field[x][y] = ' ';
        }
    }
}

void DrawPlayer(int oldX)
{
    setCursorPosition(oldX, PlayerY);
    cout << ' ';
    setCursorPosition(PlayerX, PlayerY);
    cout << (Player);
}

void KeyPressed()
{
    int oldX;
    while (!bEndGame)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 113: //Q
                MutexField.lock();
                bEndGame = true; 
                MutexField.unlock();
                break; 
            case 75:  //Left
                if (PlayerX > FieldStartX)
                {
                    MutexField.lock();
                    oldX = PlayerX;
                    PlayerX--;
                    DrawPlayer(oldX);
                    MutexField.unlock();
                }
                break;
            case 77: //Right
                if (PlayerX < FieldStartX + Width - 1)
                {
                    MutexField.lock();
                    oldX = PlayerX;
                    PlayerX++;
                    DrawPlayer(oldX);
                    MutexField.unlock();
                }
                break;
            default: break;
            }
        }
    }
}

void CheckCollision()
{
    while (!bEndGame)
    {
        MutexField.lock();
        bEndGame = (Field[PlayerX - FieldStartX][PlayerY - FieldStartY] == Block) ? true : false;
        MutexField.unlock();
    }
}

void DrawRoad()
{
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            setCursorPosition(x + FieldStartX, y + FieldStartY);
            cout << (Field[x][y]);
        }
    }
    setCursorPosition(PlayerX, PlayerY);
    cout << (Player);
}

void MoveRoad()
{
    while (!bEndGame)
    {
        chrono::time_point<chrono::steady_clock> FrameStart = chrono::high_resolution_clock::now();

        MutexField.lock();

        for (int y = Height - 1; y > 0; y--)
        {
            for (int x = 0; x < Width; x++)
            {
                Field[x][y] = Field[x][y - 1];
            }
        }
        for (int x = 0; x < Width; x++)
        {
            Field[x][0] = ' ';
        }

        bool bIsBlock = (!bIsPrevLineBlock) && (GetRandomInRange(0, 100) <= BlockProbability);
        bIsPrevLineBlock = bIsBlock;
        if (bIsBlock)
        {
            Field[GetRandomInRange(0, Width - 1)][0] = Block;
        }

        DrawRoad();

        MutexField.unlock();

        // Moving Delay
        chrono::duration<float> FrameDelta = FrameDelay - (chrono::high_resolution_clock::now() - FrameStart);
        chrono::milliseconds DeltaT = chrono::duration_cast<std::chrono::milliseconds>(FrameDelta);
        this_thread::sleep_for(chrono::milliseconds(DeltaT));
    }
}

int main()
{
    chrono::time_point<chrono::steady_clock> StartClock, EndClock;
    chrono::duration<float> DurationClock;

    srand(static_cast<unsigned int>(time(0)));

    SetCursorVisibility(false);

    InitField();
    DrawMap();

    thread RunKey([&]()
        {
            KeyPressed();
        });
    thread RunRoad([&]()
        {
            MoveRoad();
        });
    thread CheckThread([&]()
        {
            CheckCollision();
        });


    StartClock = chrono::high_resolution_clock::now();

    RunKey.join();
    RunRoad.join();
    CheckThread.join();

    EndClock = chrono::high_resolution_clock::now();
    DurationClock = EndClock - StartClock;
    cout << endl;
    cout << "You time record: " << DurationClock.count() << endl;
    SetCursorVisibility(true);
}
