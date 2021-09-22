
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>
#include <vector>
#include <algorithm>

#include <Windows.h>

using namespace std;

const int Producer1DataAmount = 7;
const int Producer2DataAmount = 8;
const int Producer3DataAmount = 3;
const int TotalDataAmount = Producer1DataAmount + Producer2DataAmount + Producer3DataAmount;

struct InfoStruct
{
    std::string Name;
    int Count = 0;
    float Duration = 0.f;
    int ProducerID = 0;
};

mutex MutexVector;

std::string gen_random_str(const int MaxLen)
{
    int len = rand() % MaxLen + 1;

    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
    {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

void Producer1(vector<InfoStruct>& VectorToFill)
{
    const int ProducerID = 1;

    for (int i = 0; i < Producer1DataAmount; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));

        InfoStruct Element;
        Element.Count = rand() % 100;
        Element.Duration = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
        Element.ProducerID = ProducerID;
        Element.Name = gen_random_str(20);

        MutexVector.lock();
        VectorToFill.push_back(Element);
        MutexVector.unlock();
    }
}

void Producer2(vector<InfoStruct>& VectorToFill)
{
    const int ProducerID = 2;

    for (int i = 0; i < Producer2DataAmount; i++)
    {

        this_thread::sleep_for(chrono::milliseconds(1500));

        InfoStruct Element;
        Element.Count = rand() % 100;
        Element.Duration = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
        Element.ProducerID = ProducerID;
        Element.Name = gen_random_str(20);

        MutexVector.lock();
        VectorToFill.push_back(Element);
        MutexVector.unlock();
    }
}

void Producer3(vector<InfoStruct>& VectorToFill)
{
    const int ProducerID = 3;

    for (int i = 0; i < Producer3DataAmount; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(500));

        InfoStruct Element;
        Element.Count = rand() % 100;
        Element.Duration = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
        Element.ProducerID = ProducerID;
        Element.Name = gen_random_str(20);

        MutexVector.lock();
        VectorToFill.push_back(Element);
        MutexVector.unlock();
    }
}

void SortVector(vector<InfoStruct>& VectorToSort, bool& bIsAll)
{
    MutexVector.lock();
    std::sort(VectorToSort.begin(), VectorToSort.end(), [](InfoStruct a, InfoStruct b) { return a.Name < b.Name; });
    if (VectorToSort.size() >= TotalDataAmount)
    {
        bIsAll = true;
    }
    MutexVector.unlock();
}

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

void PrintVector(const vector<InfoStruct>& VectorToPrint, bool& bIsAll)
{
    setCursorPosition(0, 1);

    MutexVector.lock();
    for (auto Element : VectorToPrint)
    {
        printf("%-20s %5d %10.4f %4d \n", Element.Name.c_str(), Element.Count, Element.Duration, Element.ProducerID);
    }
    if (VectorToPrint.size() >= TotalDataAmount)
    {
        bIsAll = true;
    }
    MutexVector.unlock();
}

int main()
{
    chrono::time_point<chrono::steady_clock> StartClock, EndClock;
    chrono::duration<float> DurationClock;
    StartClock = chrono::high_resolution_clock::now();

    srand(static_cast<unsigned int>(time(0)));

    vector<InfoStruct> InfoVector;
    InfoVector.clear();

    thread RunProducer1([&]()
        {
            Producer1(InfoVector);
        });
    thread RunProducer2([&]()
        {
            Producer2(InfoVector);
        });
    thread RunProducer3([&]()
        {
            Producer3(InfoVector);
        });

    SetCursorVisibility(false);
    printf("%-20s %5s %10s %4s \n", "Name", "Count", "Duration", "ID");

    bool bIsPrintAll = false;
    bool bIsSortAll = false;

    while (!bIsPrintAll || !bIsSortAll)
    {
        SortVector(InfoVector, bIsSortAll);
        PrintVector(InfoVector, bIsPrintAll);
    }

    RunProducer1.join();
    RunProducer2.join();
    RunProducer3.join();

    EndClock = chrono::high_resolution_clock::now();
    DurationClock = EndClock - StartClock;
    cout << endl;
    cout << "Duration: " << DurationClock.count() << endl;
    SetCursorVisibility(true);
}
