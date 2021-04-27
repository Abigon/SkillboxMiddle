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
    // ������ ����������� �� �������� �������
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
    // �������� �������� ������ ���. ���������������� �� ��������� Test1
    auto st1 = SingletonConnector::GetInstance("Test1");

    // ��������� ��������
    st1->GetValue();

    // �������� �������� ������ ���. ������� ������������������� �� ���������  Test22222
    auto st2 = SingletonConnector::GetInstance("Test22222");

    // ��������� ��������. �������� ������ ���� �� ������ ������������� Test1
    st2->GetValue();

    delete st1;
    // ����� ������� ����������� �������� ������
 //   delete st2;

    return 0;
}
