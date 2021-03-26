
#include <iostream>
#include <cmath>

class Vector
{
public:
    Vector()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Vector(float new_x, float new_y, float new_z)
    {
        x = new_x;
        y = new_y;
        z = new_z;
    }

    operator float()
    {
        return sqrt(x * x + y * y + z * z);
    }

    friend Vector operator+(const Vector& a, const Vector& b);
    friend Vector operator-(const Vector& a, const Vector& b);
    friend Vector operator*(const Vector& a, const float b);

    friend std::ostream& operator<<(std::ostream& out, const Vector& v);
    friend std::istream& operator>>(std::istream& in, Vector& v);

    friend bool operator>(const Vector& a, const Vector& b);

    float operator[](int index)
    {
        switch (index)
        {
        case 0: return x; break;
        case 1: return y; break;
        case 2: return z; break;
        default:
            std::cout << "index error";
            return 0;
            break;
        }
    }

private:
    float x;
    float y;
    float z;
};

bool operator>(const Vector& a, const Vector& b)
{
    return false;
}

Vector operator+(const Vector& a, const Vector& b)
{
    return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator-(const Vector& a, const Vector& b)
{
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector operator*(const Vector& a, float b)
{
    return Vector(a.x * b, a.y * b, a.z * b);
}

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
    out << "( " << v.x << ", " << v.y << ", " << v.z << " )";
    return out;
}

std::istream& operator>>(std::istream& in, Vector& v)
{
    in >> v.x >> v.y >> v.z;
    return in;
}

int main()
{
    Vector v1(0, 1, 2);
    Vector v2(3, 4, 5);
    Vector v3;
  
    std::cout << "Please, input Vector - x y z: ";

    std::cin >> v3;

    std::cout << v3 << '\n';
    std::cout << "v3 length = " << float(v3) << '\n';
    std::cout << "v3 - v1 = " << v3-v1 << '\n';
    std::cout << "v3 * 3 = " << v3 * 3.f << '\n';
}
