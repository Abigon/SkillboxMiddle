#include <iostream>

class SingletonConnector
{
public:
    ~SingletonConnector()
    {
        std::cout << " Destructor SingletonConnector \n";
    }

    static SingletonConnector* GetInstance(const std::string& value)
    {
        if (_Instance == nullptr) 
        {
            _Instance = new SingletonConnector(value);
        }
        return _Instance;
    }

    void GetValue() 
    {
        std::cout << " Value: " << _Value <<" \n";
    }

protected:
    // Прячем конструктор от внешнего доступа
    SingletonConnector(const std::string value) : _Value(value)
    {
    }

private:
    static SingletonConnector* _Instance;
    std::string _Value;
};

SingletonConnector* SingletonConnector::_Instance = nullptr;

int main()
{
    // Получаем синглтон первый раз. Инициализируется со значением Test1
    auto st1 = SingletonConnector::GetInstance("Test1");

    // Проверяем значение
    st1->GetValue();

    // Получаем синглтон второй раз. Пробуем проинициализировать со значением  Test22222
    auto st2 = SingletonConnector::GetInstance("Test22222");

    // Проверяем значение. Значение должно быть от первой инициализации Test1
    st2->GetValue();

    delete st1;
    // Вызов второго деструктора вызывает ошибку
 //   delete st2;

    return 0;
}
