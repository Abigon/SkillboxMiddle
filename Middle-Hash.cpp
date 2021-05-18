#include <iostream>
#include <string>
#include <array>


// размер таблицы
const int ArraySize = 100;

// таблица хэшей
std::array<unsigned int, ArraySize> HashElements;

// djb2 hash function взвращает хэш строки
unsigned int GetStringHash(std::string m_String)
{
    unsigned int m_hash = 0;

    for (unsigned int i = 0; i < m_String.length(); i++)
    {
        m_hash = (m_hash << 5) + m_hash + m_String[i];
    }

    return m_hash;
}

// возвращает индекс в таблице хэшей
int GetIndex(std::string m_String)
{
    unsigned int m_Hash = GetStringHash(m_String);  // получаем хэш
    int m_TempIndex = m_Hash % ArraySize;           // рассчитываем индекс

    if (HashElements[m_TempIndex] == m_Hash)
    {
       // Если по рассчитанному индексу на ходится аналогичный хэш
        std::cout << "Hash: " << std::hex << m_Hash << " Already placed at Index: " << std::dec << m_TempIndex << "\n\n";
        return m_TempIndex;
    }
    else if (HashElements[m_TempIndex] == 0)
    {
       // Если по расчитанному индексу пусто, то размещаем хэш
        HashElements[m_TempIndex] = m_Hash;
        std::cout << "Hash: " << std::hex << m_Hash << " Placed at Index: " << std::dec << m_TempIndex << "\n\n";
        return m_TempIndex;
    }
    else    // Если значение по рассчитанному индексу занято и не равно хэшу начинаем перебор по ячейкам с начала
            // Не самый оптимальный вариант
    {
       for (int i = 0; i < HashElements.size(); i++)
       {
           if (HashElements[i] == m_Hash)
           {
               // Если находим значение хэша по другому индексу 
               std::cout << "Hash: " << std::hex << m_Hash << " Already placed at Index: " << std::dec << i << " (instead of: " << m_TempIndex << ")" << "\n\n";
               return i;
           }
           else if (HashElements[i] == 0)
           {
               // Распологаем значение хэша в по первому свободному индексу
               HashElements[i] = m_Hash;
               std::cout << "Hash: " << std::hex << m_Hash << " Placed at Index: " << std::dec << i << " (instead of: " << m_TempIndex << ")" << "\n\n";
               return i;
           }
       }
    }
    // Весь массив занят
    // Возвращается заведомо ошибочное значение
    std::cout << "Hash Array is FULL" << "\n" << "\n";
    return 100;
}

//unsigned int GetHash(std::string m_String)
//{
//    Еще один вариант получения хэша
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
        std::getline(std::cin, m_NewString);    // Получаем стороку
        if (m_NewString.empty()) break;         // Пустая строка завершает цикл

        GetIndex(m_NewString);                  // Получаем индекс. В программе не используется 

    }
}
