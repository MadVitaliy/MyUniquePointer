#include <iostream>

template<class T>
class MyUniquePointer
{
private:
	T* mp_managedObject = nullptr;
public:
	MyUniquePointer(T* t) noexcept : mp_managedObject(t) 
	{
		
	}
	~MyUniquePointer()
	{
		delete mp_managedObject;
		mp_managedObject = nullptr;
	}

	MyUniquePointer(const MyUniquePointer& obj) = delete;
	MyUniquePointer operator=(const MyUniquePointer& obj) = delete;

	MyUniquePointer(MyUniquePointer&& objToMove) noexcept
	{
		delete mp_managedObject;
		mp_managedObject = objToMove.mp_managedObject;
		objToMove.mp_managedObject = nullptr;
		std::cout << "Move constructor" << std::endl;
	};

	MyUniquePointer operator=(MyUniquePointer&& objToMove) noexcept
	{
		delete mp_managedObject;
		mp_managedObject = objToMove.mp_managedObject;
		objToMove.mp_managedObject = nullptr;
		std::cout << "Move assigment constructor" << std::endl;
	};

	T* realease() noexcept
	{
		T* temp = mp_managedObject;
		mp_managedObject = nullptr;
		return temp;
	}

	void reset(T* newObject)
	{
		delete mp_managedObject;
		mp_managedObject = newObject;
	}

	//T operator*()
	//{
	//	return *_managedObject;
	//}

	T& operator*()
	{
		return *mp_managedObject;
	}

	T* operator->() const
	{
		return mp_managedObject;
	}

};

template<typename T, typename... Types>
MyUniquePointer<T> MakeUnique(Types&&... Params)
{
	return MyUniquePointer<T>(new T(std::forward<Types>(Params)...));
}


class Date
{
public:
	Date() noexcept
	{
		m_date = "08.07.2021";
		m_objectCounter++;
		m_objectNumber = m_objectCounter;
		std::cout << "Data"<< m_objectNumber << " constructor" << std::endl;
	}

	Date(const std::string&  dataString) noexcept : m_date(dataString)
	{
		//m_date = "08.07.2021";
		m_objectCounter++;
		m_objectNumber = m_objectCounter;
		std::cout << "Data" << m_objectNumber << " constructor" << std::endl;
	}
	~Date() 
	{
		std::cout << "Data" << m_objectNumber << " destructor" << std::endl;
	};

	void getData() noexcept
	{
		std::cout << "Current date " << m_objectNumber << " : " << m_date << std::endl;
	}
private:
	static  int m_objectCounter;
	int m_objectNumber = 0;
	std::string m_date;
};
int Date::m_objectCounter = 0;

int main()
{
	auto sp = std::make_unique<Date>();
	sp->getData();
	MyUniquePointer<Date> up_date(new Date);
	up_date->getData();
	MyUniquePointer<Date> up_date2(new Date);
	up_date2->getData();
	up_date2.reset(new Date);
	up_date2->getData();

	MyUniquePointer<Date> up_date3 = MakeUnique<Date>();
	up_date3->getData();

	MyUniquePointer<Date> up_date4 = MakeUnique<Date>("some data");
	up_date4->getData();
	std::cout << "Hello World!\n";
}
