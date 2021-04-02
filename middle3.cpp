#include <iostream>
#include <vector>

class Vehicle
{
public:
    Vehicle() {};

    virtual std::ostream& print(std::ostream& out) const
    {
        out << "";
        return out;
    }
    virtual ~Vehicle()
    {
//        std::cout << " Destructor Vehicle \n";
    }
    friend std::ostream& operator<<(std::ostream& out, const Vehicle& v)
    {
        return v.print(out);
    }
};

class Wheel
{
public:
    Wheel(float d) : m_radius(d)
    {
    }
    float const GetRadius() { return m_radius; }
    virtual ~Wheel()
    {
//        std::cout << " Destructor Wheel \n";
    }

private:
    float m_radius = 0;
};

class Engine
{
public:
    Engine(float d) : m_power(d)
    {
    }
    float GetPower() { return m_power; }
    virtual ~Engine()
    {
//        std::cout << " Destructor Engine \n";
    }

private:
    float m_power = 0;
};

class WaterVehicle : public Vehicle
{
public:
    WaterVehicle(float rh) : m_draft(rh)
    {
    }
    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Water Vehicle, Draft: " << m_draft << "\n";
        return out;
    }
protected:
    float m_draft = 0;
};

class RoadVehicle : public Vehicle
{
public:
    RoadVehicle(float rh) : m_rideHeight(rh)
    {
    }
    virtual ~RoadVehicle()
    {
//        std::cout << " Destructor RoadVehicle \n";
    }
    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Road Vehicle, Ride height: " << m_rideHeight << "\n";
        return out;
    }
protected:
    float m_rideHeight = 0;
};

class Bicycle : public RoadVehicle
{
public:
    Bicycle(Wheel wr1, Wheel wr2, float rh) : m_wheel1(new Wheel(wr1)), m_wheel2(new Wheel(wr2)), RoadVehicle(rh)
    {
    }

    virtual ~Bicycle()
    {
//        std::cout << " Destructor Bicycle \n";
        delete m_wheel1;
        delete m_wheel2;
    }

    virtual std::ostream& print(std::ostream& out) const override
    {
        if (m_wheel1 && m_wheel2)
        {
            out << "Bicycle, Wheels: " << m_wheel1->GetRadius() << " " << m_wheel2->GetRadius() << ", Ride height: " << m_rideHeight;
        }
        return out;
    }
private:
    Wheel* m_wheel1 = nullptr;
    Wheel* m_wheel2 = nullptr;
};

class Car : public RoadVehicle
{
public:
    Car(Engine en, Wheel wr1, Wheel wr2, Wheel wr3, Wheel wr4, float rh) 
        : m_engine(new Engine(en)), m_wheel1(new Wheel(wr1)), m_wheel2(new Wheel(wr2)), m_wheel3(new Wheel(wr3)), m_wheel4(new Wheel(wr4)), RoadVehicle(rh)
    {
    }

    virtual ~Car()
    {
//        std::cout << " Destructor Car \n";
        delete m_wheel1;
        delete m_wheel2;
        delete m_wheel3;
        delete m_wheel4;
        delete m_engine;
    }
    
    float GetPower() { return m_engine->GetPower(); }

    virtual std::ostream& print(std::ostream& out) const override
    {
        if (m_wheel1 && m_wheel2 && m_wheel3 && m_wheel4 && m_engine)
        {
            out << "Car, Engine:" 
                << m_engine->GetPower() 
                << ", Wheels: " 
                << m_wheel1->GetRadius() << " " 
                << m_wheel2->GetRadius() << " " 
                << m_wheel3->GetRadius() << " " 
                << m_wheel4->GetRadius() 
                << ", Ride height: " << m_rideHeight;
        }
        return out;
    }
private:
    Wheel* m_wheel1 = nullptr;
    Wheel* m_wheel2 = nullptr;
    Wheel* m_wheel3 = nullptr;
    Wheel* m_wheel4 = nullptr;
    Engine* m_engine = nullptr;
};


float getHighestPower(std::vector<Vehicle*> &vvv)
{
    float m_max = 0;
    for (auto tt : vvv)
    {
        const auto c = dynamic_cast<Car*>(tt);
        if (!c) continue;
        m_max = m_max < c->GetPower() ? c->GetPower() : m_max;
    }

    return m_max;
}


int main()
{
    Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);
    Bicycle t(Wheel(20), Wheel(20), 150);

    std::cout << c << "\n";
    std::cout << t << "\n";
    std::cout << "\n\n";

    std::vector<Vehicle*> v;

    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));
    v.push_back(new Bicycle(Wheel(20), Wheel(20), 150));
    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));
    v.push_back(new WaterVehicle(5000));

    //TODO: Вывод элементов вектора v здесь
    for (auto tt : v)
    {
        std::cout << *tt << "\n";
    }

    std::cout << "The highest power is " << getHighestPower(v) << '\n'; // реализуйте эту функцию

    //TODO: Удаление элементов вектора v здесь
    for (auto tt : v)
    {
        delete tt;
    }
    v.clear();

    return 0;
}
