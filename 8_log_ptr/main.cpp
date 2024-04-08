#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>

class SimpleClass {
public:
	SimpleClass() {
		std::cout << "jo\n";
	}
	~SimpleClass() {
		std::cout << "tain\n";
	}

	std::shared_ptr<SimpleClass> ReturnSharedPtr(std::shared_ptr<SimpleClass> shared) {
		std::cout << "joku funktio kutsuttu ja shared ptr palautetaan";
		return shared;
	}
};

template <class T>
class Log_Ptr {
	T* ptr; 
	std::chrono::time_point<std::chrono::system_clock> timestamp;
	std::time_t end_t;
	int ref_count;

public: 
	Log_Ptr(T* ptrValue) : ptr(ptrValue), timestamp(std::chrono::system_clock::now()), end_t(std::chrono::system_clock::to_time_t(timestamp)), ref_count(0) {
		std::cout << std::ctime(&end_t) << " omistajuus siirretty " << &ptr << "\n";
		AddRef();
	}

	~Log_Ptr() {
		Release();		

		if (ref_count == 0) {
			timestamp = std::chrono::system_clock::now();
			end_t = std::chrono::system_clock::to_time_t(timestamp);
			std::cout << std::ctime(&end_t) << " olio tuhottu " << &ptr << "\n";
			delete ptr;
		}		
	}	

	void AddRef() {
		timestamp = std::chrono::system_clock::now();
		end_t = std::chrono::system_clock::to_time_t(timestamp);		
		ref_count++;
		std::cout << std::ctime(&end_t) << " reference count nousi: " << ref_count << "\n";
	}

	void Release() {
		if (ref_count > 0) {
			timestamp = std::chrono::system_clock::now();
			end_t = std::chrono::system_clock::to_time_t(timestamp);
			ref_count--;
			std::cout << std::ctime(&end_t) << " reference count laski: " << ref_count << "\n";
		}		
	}

	// Delete the copy constructor
	Log_Ptr(const Log_Ptr&) = delete;

	// Delete the copy assignment operator
	Log_Ptr& operator=(const Log_Ptr&) = delete;

	// dereference operator
	T& operator* () {		
		timestamp = std::chrono::system_clock::now();
		end_t = std::chrono::system_clock::to_time_t(timestamp);
		std::cout << std::ctime(&end_t) << " operator-> " << &ptr << "\n";
		return *ptr;
	}

	T* operator-> () {
		timestamp = std::chrono::system_clock::now();
		end_t = std::chrono::system_clock::to_time_t(timestamp);
		std::cout << std::ctime(&end_t) << " operator* " << &ptr << "\n";
		return ptr;
	}
};


int main() {
	
	/*std::shared_ptr<Class> o1 = std::make_shared<Class>();
	std::shared_ptr<Class> o2 = return_shared_ptr(o1);
	
	std::shared_ptr<Class> o3 = o2; 
	*/


	Log_Ptr<SimpleClass> l1(new SimpleClass);

	std::shared_ptr<SimpleClass> s1 = std::make_shared<SimpleClass>();
	std::shared_ptr<SimpleClass> s2 = l1->ReturnSharedPtr(s1);

	Log_Ptr<SimpleClass> p2(new SimpleClass);
	Log_Ptr<SimpleClass> p3(new SimpleClass);
	Log_Ptr<SimpleClass> p4(new SimpleClass);



	std::cout << "loppu\n";

	return 0;
}