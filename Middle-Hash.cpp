#include <iostream>
#include <string>

unsigned int GetStringHash(std::string m_String)
{
    unsigned int m_hash = 0;

    for (unsigned int i = 0; i < m_String.length(); i++)
    {
        m_hash = (m_hash << 5) + m_hash + m_String[i];
    }

    return m_hash;
}

int main()
{
    std::string m_NewString;

    std::cout << "Enter String to get HASH. Enter QUIT to close program\n";

    while (true)
    {
        std::getline(std::cin, m_NewString);
        if (m_NewString == "QUIT") break;

        std::cout << "Hash: " << std::hex << GetStringHash(m_NewString) << "\n" << "\n";
    }
}
