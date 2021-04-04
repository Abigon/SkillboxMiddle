
#include <iostream>

class Fraction
{
public:
    Fraction(int n, int d) : numerator(n), denominator(d)
    {
        if (d == 0)
        {
            throw std::runtime_error("Denominator must NOT equal 0!!");
        }
    }
    float Result()
    {
        return static_cast<float>(numerator) / denominator;
    }

private:
    int numerator;
    int denominator;
};


int main()
{
    int num, den;
    std::cout << "Enter Numerator: ";
    std::cin >> num;
    std::cout << "\n";

    std::cout << "Enter Denominator: ";
    std::cin >> den;
    std::cout << "\n";

    Fraction* fr = nullptr;

    try
    {
        fr = new Fraction(num, den);
    }
    catch (std::exception & exception)
    {
        std::cout << "Exception: " << exception.what() << "\n";
    }

    if (fr)
    {
        std::cout << "Result: " << fr->Result() << "\n";
        delete fr;
    }

    return 0;
}

