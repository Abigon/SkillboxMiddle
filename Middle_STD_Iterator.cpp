#include <iostream>
#include <vector>


int main()
{
    srand(time(0));                                 // Сбрасываем генератор случайных чисел

    std::vector<int> m_Vector;
    for (int i = 0; i < 10; i++)
    {
        m_Vector.push_back(rand() % 100);           // Заполняем рандомными значениями от 0 до 99
    }

    std::vector<int>::const_iterator m_Iterator;    // объявляем константный итератор
    m_Iterator = m_Vector.begin();                  // присваиваем итератору начальный элемент вектора
    while (m_Iterator < m_Vector.end())            // запускаем цикл, пока итератор не достигнет последнего элемента
    {
        std::cout << *m_Iterator << " ";            // выводим значение элемента, на который указывает итератор
        m_Iterator++;                               // и переходим к следующему элементу
    }
    std::cout << "\n\n";
}
