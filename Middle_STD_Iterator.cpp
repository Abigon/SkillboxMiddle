#include <iostream>
#include <vector>


int main()
{
    srand(time(0));                                 // ���������� ��������� ��������� �����

    std::vector<int> m_Vector;
    for (int i = 0; i < 10; i++)
    {
        m_Vector.push_back(rand() % 100);           // ��������� ���������� ���������� �� 0 �� 99
    }

    std::vector<int>::const_iterator m_Iterator;    // ��������� ����������� ��������
    m_Iterator = m_Vector.begin();                  // ����������� ��������� ��������� ������� �������
    while (m_Iterator < m_Vector.end())            // ��������� ����, ���� �������� �� ��������� ���������� ��������
    {
        std::cout << *m_Iterator << " ";            // ������� �������� ��������, �� ������� ��������� ��������
        m_Iterator++;                               // � ��������� � ���������� ��������
    }
    std::cout << "\n\n";
}
