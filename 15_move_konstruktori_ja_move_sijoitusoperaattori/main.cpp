/*Toteuta Big_Data-luokalle move-konstruktori ja move-sijoitusoperaattori. Nämä saavat parametrina
rvalue-referenssin, ”varastavat” sen sisällön ja sen jälkeen ”resetoivat” alkuperäisen rvaluen. Testaa
toimintaa esim. seuraavilla ohjelmariveillä:
Big_Data a(Big_Data(1024));
Big_Data b(1024);
b = Big_Data(1024);
BigData c(std::move(a));*/

#include <iostream>
#include <cstring>

class Big_Data {
	int* buffer;
	size_t size;

public:
	Big_Data(size_t b) : size(b) {
		buffer = (int*)malloc(size);
		std::cout << "konstruktori\n";
	}

	Big_Data(const Big_Data& copy) : size(copy.size) {
		buffer = (int*)malloc(size);
		// sisältö kopioidaan toisen olion bufferiin:
		if (buffer != nullptr) {
			// memcpy(memory location to copy to, -//- copy from, num of bytes to copy);
			std::memcpy(buffer, copy.buffer, size);
		}
		std::cout << "kopiokonstruktori\n";
	}

	Big_Data(Big_Data&& copy) noexcept : size(0), buffer(nullptr){

		size = copy.size;
		buffer = copy.buffer;
		//buffer = std::move(copy.buffer);
		copy.size = 0;
		copy.buffer = nullptr;
		std::cout << "move konstruktori\n";
	}

	~Big_Data() {
		std::cout << "destruktori\n";

		free(buffer);
	}

	Big_Data& operator=(const Big_Data& copy) {
		if (this != &copy) {
			std::cout << "operator= \n";

			size = copy.size;
			buffer = (int*)malloc(size);
			if (buffer != nullptr) {
				std::memcpy(buffer, copy.buffer, size);
			}
		}
		return *this;
	}

	Big_Data& operator=(Big_Data&& copy) noexcept {
		if (this != &copy) {
			std::cout << "operator=(&&)\n";
			
			size = copy.size;
			buffer = copy.buffer;

			copy.size = 0;
			copy.buffer = nullptr;
		}
		return *this;
	}
};

int main() {
	Big_Data a(Big_Data(1024));
	Big_Data b(1024);
	b = Big_Data(1024);
	Big_Data c(std::move(a));

	std::cout << "bye bye\n";

	return 0;
}