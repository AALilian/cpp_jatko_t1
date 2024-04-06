#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>

class SimpleClass {
public:
	SimpleClass() {
		std::cout << "jo";
	}
	~SimpleClass() {
		std::cout << "tain";
	}
};

template <class T>
class Log_Ptr {
	T* ptr; 
	const std::chrono::time_point<std::chrono::system_clock> timestamp;
	std::time_t end_t;

	int ref_count;


public: 
	Log_Ptr(T* ptrValue) : ptr(ptrValue), timestamp(std::chrono::system_clock::now()), end_t(std::chrono::system_clock::to_time_t(timestamp)) {
		std::cout << std::ctime(&end_t) << " omistajuus siirretty " << &ptr << "\n";
		AddRef();
	}

	~Log_Ptr() {
		timestamp = std::chrono::system_clock::now();
		end_t = std::chrono::system_clock::to_time_t(timestamp);
		

		if (ref_count == 0) {
			std::cout << std::ctime(&end_t) << " olio tuhottu " << &ptr << "\n";
			delete ptr;
		}
	}	

	void AddRef() {
		timestamp = std::chrono::system_clock::now();
		end_t = std::chrono::system_clock::to_time_t(timestamp);
		std::cout << std::ctime(&end_t) << " reference count nousee yhdellä.\n";
		ref_count++;
	}

	int Release() {
		timestamp = std::chrono::system_clock::now();
		end_t = std::chrono::system_clock::to_time_t(timestamp);
		std::cout << std::ctime(&end_t) << " reference count laskee yhdellä.\n";
		return --ref_count;
	}

	//// Delete the copy constructor
	//Log_Ptr(const Log_Ptr&) = delete;

	//// Delete the copy assignment operator
	//Log_Ptr& operator=(const Log_Ptr&) = delete;

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


//std::shared_ptr<Class> return_shared_ptr(std::shared_ptr<Class> shared) {
//	std::cout << "joku funktio kutsuttu ja shared ptr palautetaan";
//	return shared;
//}

int main() {
	
	/*std::shared_ptr<Class> o1 = std::make_shared<Class>();
	std::shared_ptr<Class> o2 = return_shared_ptr(o1);
	
	std::shared_ptr<Class> o3 = o2; 
	*/

	Log_Ptr<SimpleClass> p1(new SimpleClass());

	std::cout << "loppu";

	return 0;
}