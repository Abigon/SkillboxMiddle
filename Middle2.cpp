#include <iostream>

class TestClass
{
public:
	TestClass()
	{
		array_x = 0;
		array_y = 0;
		array = nullptr;
		info = nullptr;
		std::cout << "Zero constructor\n";
	}

	TestClass(const int x, const int y, std::string str)
	{
		array_x = x;
		array_y = y;
		info = new std::string(str);
		InitArray();
		std::cout << "Init constructor\n";
	}

	TestClass(const TestClass& other)
	{
		array_x = other.array_x;
		array_y = other.array_y;
		if (other.info)
		{
			info = new std::string(*(other.info));
		}
		if (other.array)
		{
			InitArray();
			CopyArray(other.array);
		}
		std::cout << "Init from copy constructor\n";
	}

	TestClass& operator=(const TestClass& other)
	{
		array_x = other.array_x;
		array_y = other.array_y;
		if (other.info)
		{
			if (info) delete info;
			info = new std::string(*(other.info));
		}
		if (other.array)
		{
			DeleteArray();
			InitArray();
			CopyArray(other.array);
		}
		std::cout << "Init from = operator\n";
		return (*this);
	}

	~TestClass()
	{
		if (info)
		{
			delete info;
		}
		DeleteArray();
		std::cout << "destructor\n";
	}

	void InitArray()
	{
		array = new int* [array_x];
		for (int i = 0; i < array_x; i++)
		{
			array[i] = new int[array_y];
		}
		std::cout << "Init Array\n";
	}

	void CopyArray(int** other)
	{
		for (int i = 0; i < array_x; i++)
		{
			for (int w = 0; w < array_y; w++)
			{
				array[i][w] = other[i][w];
			}
		}
	}

	void DeleteArray()
	{
		if (array)
		{
			for (int i = 0; i < array_x; i++) {
				delete[] array[i];
			}
			delete[] array;
		}
	}

	int GetArray11()
	{
		if (array)
		{
			return array[1][1];
		}
		return 0;
	}

	void SetArray11(int aaa)
	{
		if (array)
		{
			array[1][1] = aaa;
		}
	}

private:
	int** array;
	int array_x;
	int array_y;

	std::string* info;
};

int main()
{
	TestClass* t1 = new TestClass();
	std::cout << "[1][1] t1: " << t1->GetArray11() << "\n";

	TestClass t2(7, 6, "Hello");
	t2.SetArray11(14);
	std::cout << "[1][1] t2: " << t2.GetArray11() << "\n";

	TestClass t3(t2);
	std::cout << "[1][1] t3: " << t3.GetArray11() << "\n";
	t3.SetArray11(32);
	std::cout << "[1][1] t3: " << t3.GetArray11() << "\n";

	TestClass t4(t3);
	std::cout << "[1][1] t4: " << t4.GetArray11() << "\n";

	t4 = t2;
	std::cout << "[1][1] t4: " << t4.GetArray11() << "\n";

	delete t1;
}
