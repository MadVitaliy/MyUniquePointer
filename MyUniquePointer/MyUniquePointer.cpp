#include <iostream>

template<class T>
class MyUniquePointer
{
public:
	MyUniquePointer(T* t) : _managedObject(t)
	{
		std::cout << "constructor" << std::endl;
	}
	~MyUniquePointer()
	{
		delete _managedObject;
		_managedObject = nullptr;
		std::cout << "destructor" << std::endl;
	}

	MyUniquePointer(const MyUniquePointer& obj) = delete;

	MyUniquePointer(const MyUniquePointer&& objToMove) {
		delete _managedObject;
		_managedObject = objToMove._managedObject;
		objToMove._managedObject = nullptr;
	};

	T* realease()
	{
		T* temp = _managedObject;
		_managedObject = nullptr;
		return temp;
	}

	void reset(T* newObject)
	{
		delete _managedObject;
		_managedObject = newObject;
	}

	T operator*()
	{
		return *_managedObject;
	}

	T& operator*()
	{
		return *_managedObject;
	}

private:
	T* _managedObject = nullptr;
};


int main()
{

	std::cout << "Hello World!\n";
}
