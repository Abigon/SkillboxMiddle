#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <array>

int main()
{
     //////////////////////////////////////////////////////////////////////////////////
    // Homework 6.4
    // generate

    std::cout << "-------  Homework 6.4 ------- \n\n";

    srand(time(0));
    std::vector<int> m_GenerateVector(10), m_GenerateVector2(10);

    // generate int from 0 to 99 
    std::generate(m_GenerateVector.begin(), m_GenerateVector.end(), []() {return rand() % 100; });
    std::generate(m_GenerateVector2.begin(), m_GenerateVector2.end(), []() {return rand() % 100; });

    std::cout << "generate result 1: ";
    std::for_each(m_GenerateVector.cbegin(), m_GenerateVector.cend(), [](int n) { std::cout << n << " "; });
    std::cout << "\n";
    std::cout << "generate result 2: ";
    std::for_each(m_GenerateVector2.cbegin(), m_GenerateVector2.cend(), [](int n) { std::cout << n << " "; });
    std::cout << "\n\n";



    //////////////////////////////////////////////////////////////////////////////////
    // Homework 7.4
    
    std::cout << "-------  Homework 7.4 ------- \n\n";
    

    //partial_sort_copy

    std::cout << "partial_sort_copy result: \n";

    // Copy 4 lowest sorted elemets from m_GenerateVector to m_GenerateVector2 
    std::partial_sort_copy(m_GenerateVector.begin(), m_GenerateVector.end(), m_GenerateVector2.begin(), m_GenerateVector2.begin()+4);

    std::for_each(m_GenerateVector2.cbegin(), m_GenerateVector2.cend(), [](int n) { std::cout << n << " "; });
    std::cout << "\n\n\n";

    
    // set::lower_bound, set::upper_bound

    std::cout << "lower_bound & upper_bound result: \n";

    // Sort in ascending order m_GenerateVector2 
    std::cout << "m_GenerateVector2 sorted result: ";
    std::sort(m_GenerateVector2.begin(), m_GenerateVector2.end());
    std::for_each(m_GenerateVector2.cbegin(), m_GenerateVector2.cend(), [](int n) { std::cout << n << " "; });
    std::cout << "\n\n";

    std::cout << "m_GenerateVector2 elements between 20 & 60: \n";
    auto m_LowerIt = std::lower_bound(m_GenerateVector2.begin(), m_GenerateVector2.end(), 20);
    auto m_UpperIt = std::upper_bound(m_GenerateVector2.begin(), m_GenerateVector2.end(), 60);
    std::for_each(m_LowerIt, m_UpperIt, [](int n) { std::cout << n << " "; });
    std::cout << "\n\n\n";



    // includes è set_difference

    std::cout << "includes & set_difference result: \n";

    std::sort(m_GenerateVector.begin(), m_GenerateVector.end());

    std::cout << "sorted vector 1: ";
    std::for_each(m_GenerateVector.cbegin(), m_GenerateVector.cend(), [](int n) { std::cout << n << " "; });
    std::cout << "\n";
    std::cout << "sorted vector 2: ";
    std::for_each(m_GenerateVector2.cbegin(), m_GenerateVector2.cend(), [](int n) { std::cout << n << " "; });
    std::cout << "\n\n";

    // Are Includes 2 first elements of m_GenerateVector2 in m_GenerateVector
    bool m_Res = std::includes(m_GenerateVector.begin(), m_GenerateVector.end(), m_GenerateVector2.begin(), m_GenerateVector2.begin() + 2);

    std::for_each(m_GenerateVector2.cbegin(), m_GenerateVector2.cbegin() + 2, [](int n) { std::cout << n << " "; });
    if (m_Res)
    {
        std::cout << "are includes in m_GenerateVector \n\n";
    }
    else
    {
        std::cout << "are not includes in m_GenerateVector \n\n";
    }


    std::vector<int> m_DiffVector;

    std::set_difference(m_GenerateVector.begin(), m_GenerateVector.end(), 
        m_GenerateVector2.begin(), m_GenerateVector2.end(), std::inserter(m_DiffVector, m_DiffVector.begin()));


    // Copies the elements from m_GenerateVector which are not found in m_GenerateVector2
    std::cout << "m_GenerateVector - m_GenerateVector2:\n";
    std::for_each(m_DiffVector.cbegin(), m_DiffVector.cend(), [](int n) { std::cout << n << " "; });
    std::cout << "\n\n";
}
