#include <iostream>
#include <string>
#include <array>


// ������ �������
const int ArraySize = 100;

// ������� �����
std::array<unsigned int, ArraySize> HashElements;

// djb2 hash function ��������� ��� ������
unsigned int GetStringHash(std::string m_String)
{
    unsigned int m_hash = 0;

    for (unsigned int i = 0; i < m_String.length(); i++)
    {
        m_hash = (m_hash << 5) + m_hash + m_String[i];
    }

    return m_hash;
}

// ���������� ������ � ������� �����
int GetIndex(std::string m_String)
{
    unsigned int m_Hash = GetStringHash(m_String);  // �������� ���
    int m_TempIndex = m_Hash % ArraySize;           // ������������ ������

    if (HashElements[m_TempIndex] == m_Hash)
    {
       // ���� �� ������������� ������� �� ������� ����������� ���
        std::cout << "Hash: " << std::hex << m_Hash << " Already placed at Index: " << std::dec << m_TempIndex << "\n\n";
        return m_TempIndex;
    }
    else if (HashElements[m_TempIndex] == 0)
    {
       // ���� �� ������������ ������� �����, �� ��������� ���
        HashElements[m_TempIndex] = m_Hash;
        std::cout << "Hash: " << std::hex << m_Hash << " Placed at Index: " << std::dec << m_TempIndex << "\n\n";
        return m_TempIndex;
    }
    else    // ���� �������� �� ������������� ������� ������ � �� ����� ���� �������� ������� �� ������� � ������
            // �� ����� ����������� �������
    {
       for (int i = 0; i < HashElements.size(); i++)
       {
           if (HashElements[i] == m_Hash)
           {
               // ���� ������� �������� ���� �� ������� ������� 
               std::cout << "Hash: " << std::hex << m_Hash << " Already placed at Index: " << std::dec << i << " (instead of: " << m_TempIndex << ")" << "\n\n";
               return i;
           }
           else if (HashElements[i] == 0)
           {
               // ����������� �������� ���� � �� ������� ���������� �������
               HashElements[i] = m_Hash;
               std::cout << "Hash: " << std::hex << m_Hash << " Placed at Index: " << std::dec << i << " (instead of: " << m_TempIndex << ")" << "\n\n";
               return i;
           }
       }
    }
    // ���� ������ �����
    // ������������ �������� ��������� ��������
    std::cout << "Hash Array is FULL" << "\n" << "\n";
    return 100;
}

//unsigned int GetHash(std::string m_String)
//{
//    ��� ���� ������� ��������� ����
// 
//    const int m_k = 317;
//
//    unsigned int m_hash = 0, m_m = 1;
//
//    for (unsigned int i = 0; i < (int) m_String.length(); i++)
//    {
//        m_hash = (m_hash + m_m * (int) m_String[i]);
//        m_m = (m_m * m_k);
//    }
//
//    return m_hash % ArraySize;
//}


int main()
{
    std::string m_NewString;

    std::cout << "Enter String to get HASH. Enter Empty string to close program\n";

    while (true)
    {
        std::getline(std::cin, m_NewString);    // �������� �������
        if (m_NewString.empty()) break;         // ������ ������ ��������� ����

        GetIndex(m_NewString);                  // �������� ������. � ��������� �� ������������ 

    }
}
