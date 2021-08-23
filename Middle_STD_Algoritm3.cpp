#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <array>


void PrintVector(const std::vector<int> v, const std::string header)
{
    std::cout << header;
    std::for_each(v.cbegin(), v.cend(), [](int n) { std::cout << n << " "; });
    std::cout << "\n";
}

//sort by remainder of division by 5 
bool HeapCompare(const int& a, const int& b)
{
    return (a % 5) < (b % 5);
}

void CheckHeap(const std::vector<int> v)
{
    if (std::is_heap(v.begin(), v.end(), &HeapCompare))
    {
        std::cout << "It's a heap...\n";
    }
    else
    {
        std::cout << "It's not a heap...\n";
    }
}

// numbers equal, greater or less by one are considered the same
bool permutation_cmp(const int& v1, const int& v2)
{
//    std::cout << "Compare: " << v1 << " & " << v2 << "\n";
    return (v1 == v2) || (v1 == (v2+1)) || (v1 == (v2-1));
}

int main()
{
    //////////////////////////////////////////////////////////////////////////////////
   // Homework 8.4
   // 
   // HEAP

    srand(time(0));
    std::vector<int> m_GenerateVector(10);

    std::generate(m_GenerateVector.begin(), m_GenerateVector.end(), []() {return rand() % 100; });
    PrintVector(m_GenerateVector, "Generate result: ");
    CheckHeap(m_GenerateVector);

    std::cout << "Make a Heap: \n";
    std::make_heap(m_GenerateVector.begin(), m_GenerateVector.end(), &HeapCompare);
    PrintVector(m_GenerateVector, "Make heap result: ");
    CheckHeap(m_GenerateVector);
    std::cout << "\n\n";


    // Permutation

    std::vector<int> v1{ 11,2,3,4,15 };
    std::vector<int> v2{ 14,10,2,5,3 };
    std::vector<int> v3{ 17,10,2,5,3 };
    PrintVector(v1, "v1: ");
    PrintVector(v2, "v2: ");
    PrintVector(v3, "v3: ");

    std::cout << "v1 is a permutation of v2? " << std::boolalpha << std::is_permutation(v1.begin(), v1.end(), v2.begin(), &permutation_cmp) << '\n';
    std::cout << "v1 is a permutation of v3? " << std::boolalpha << std::is_permutation(v1.begin(), v1.end(), v3.begin(), &permutation_cmp) << '\n';
    std::cout << "\n\n";



    // uninitialized_default_construct
    // 
    // for this part of the code to work, you need to enable C++17 support in Settings

    struct SSS
    {
        std::string Name{ "String " };
        int Amount{ 10 };

        void PrintSSS()
        {
            std::cout << "SSS: Name: " << Name << ", Amount: " << Amount << "\n";
        }
    };


    const int Count = 5;

    SSS* MyArray = nullptr;

    MyArray = (SSS*)malloc(sizeof(SSS) * Count);

    auto first = reinterpret_cast<SSS*>(MyArray);
    auto last = first + Count;


    // 1st initialization option of all elements
    //std::uninitialized_default_construct(first, last);

    // 2nd initialization option of all elements
    //std::uninitialized_default_construct_n(MyArray, Count);

    // Out & destroy all elenets (result for the two options above)
    //for (auto it = first ; it != last; it++) {
    //    if (it) it->PrintSSS();
    //    std::destroy_at(it);
    //}

    // Init only 3rd element 
    //auto el3 = first + 2;
    //std::uninitialized_default_construct_n(el3, 1);
    //el3->PrintSSS();
    //std::destroy_at(el3)

    // Initializing & out all elements individually 
    for (auto it = first ; it != last; it++) {
        std::uninitialized_default_construct_n(it, 1);
        if (it) it->PrintSSS();
        std::destroy_at(it);
    }

}
