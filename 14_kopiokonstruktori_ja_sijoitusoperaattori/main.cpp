/*Toteuta luokka Big_Data, jonka konstruktorin parametrina annetaan varattavan ”bufferin” koko tavuina.
Konstruktori varaa muistin malloc:lla, ja destruktori vapauttaa muistin.
Toteuta luokalle kopiokonstruktori ja sijoitusoperaattori, niin että ao. ohjelmarivit toimivat korrektisti. Eri
oliot eivät siis saa osoittaa samaan bufferiin, vaan tarpeen tullen bufferin sisältö kopioidaan toisen olion
bufferiin. Testaa.
Big_Data a(1024);
Big_Data b(1024);
a = a;
a = b;
BigData c(a);*/

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
};

int main() {
	Big_Data a(1024);
	Big_Data b(1024);
	a = a;
	a = b;
	Big_Data c(a); 

	return 0;
}