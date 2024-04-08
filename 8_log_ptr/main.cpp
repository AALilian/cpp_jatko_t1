#include <iostream>
#include <memory>
#include <chrono>

void GetTimeStamp() {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::put_time(std::localtime(&now), "%F %T");
}

class SimpleClass {
	int id;
public:
	SimpleClass() : id(0) {
		std::cout << "jo\n";
	}
	SimpleClass(int id) : id(id) {
		std::cout << "jo\n";
	}
	~SimpleClass() {
		std::cout << "tain\n";
	}

	void SayHello() {
		std::cout << "h e l l o, my id is: " << id << "\n";
	}

	std::shared_ptr<SimpleClass> ReturnSharedPtr(std::shared_ptr<SimpleClass> shared) {
		GetTimeStamp();
		std::cout << " joku funktio kutsuttu ja shared ptr palautetaan\n";
		return shared;
	}
};

template <class T>
class Log_Ptr {
	T* ptr; 
	int* ref_count;

	void AddRef() {
		(*ref_count)++;
		GetTimeStamp();
		std::cout <<  " reference count nousi: " << *ref_count << "\n";
	}

	void Release() {
		if (*ref_count > 0) {
			(*ref_count)--;
			GetTimeStamp();
			std::cout <<  " reference count laski: " << *ref_count << "\n";
		}
	}

public: 
	Log_Ptr(T* ptrValue) : ptr(ptrValue), ref_count(new int(0)) {
		GetTimeStamp();
		std::cout << " omistajuus siirretty " << &ptr << "\n";
		AddRef();
	}

	Log_Ptr(const Log_Ptr<T>& copy) : ptr(copy.ptr), ref_count(copy.ref_count) {
		GetTimeStamp();
		std::cout << " olio kopioitu " << &ptr << "\n";
		AddRef();
	}	

	~Log_Ptr() {
		Release();		

		if (*ref_count == 0) {
			GetTimeStamp(); 
			std::cout << " olio tuhottu " << &ptr << "\n";
			delete ptr;
			delete ref_count;
		}		
	}		

	//// Delete the copy constructor
	//Log_Ptr<T>(const Log_Ptr<T>&) = delete;

	//// Delete the copy assignment operator
	//Log_Ptr<T>& operator=(const Log_Ptr<T>&) = delete;

	// dereference operator
	T& operator* () {		
		GetTimeStamp();
		std::cout << " operator* " << &ptr << "\n";
		return *ptr;
	}

	T* operator-> () {
		GetTimeStamp();
		std::cout << " operator-> " << &ptr << "\n";
		return ptr;
	}

	Log_Ptr<T>& operator=(const Log_Ptr<T>& copy) {
		if (this != &copy) {
			if (*ref_count == 0) {
				delete ptr;
				delete ref_count;
			}

			GetTimeStamp();
			std::cout << " operator= " << &ptr << "\n";

			ptr = copy.ptr;
			ref_count = copy.ref_count;
			AddRef();
		}
		return *this;
	}
};

int main() {

	Log_Ptr<SimpleClass> l1(new SimpleClass);

	std::shared_ptr<SimpleClass> s1 = std::make_shared<SimpleClass>();
	std::shared_ptr<SimpleClass> s2 = l1->ReturnSharedPtr(s1);

	SimpleClass* s3 = l1.operator->();

	Log_Ptr<SimpleClass> l2(new SimpleClass(3));
	l2->SayHello();

	{
		Log_Ptr<SimpleClass> l3 = l2;
		l3->SayHello();

		Log_Ptr<SimpleClass> l4 = l2;	
		l4->SayHello();
	}

	l2->SayHello();

	std::cout << "loppu\n";

	return 0;
}