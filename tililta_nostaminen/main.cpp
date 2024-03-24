#include <iostream>       
#include <thread>         
#include <mutex>          

std::mutex mtx;           

class Tili
{	
	int saldo;
public:
	void talletus(int arvo) 
	{
		saldo += arvo;
	}

	void nosto(int arvo)
	{
		saldo -= arvo;
	}

	int get_saldo()
	{
		return saldo;
	}

	void set_saldo(int s)
	{
		saldo = s;
	}
};

void talleta_tilille(Tili& tili, int arvo)
{
	std::lock_guard<std::mutex> lock(mtx);
	tili.talletus(arvo);
}

void nosta_tililta(Tili& tili, int arvo)
{
	std::lock_guard<std::mutex> lock(mtx);
	tili.nosto(arvo);
}


int main()
{
	int nosto = 40;
	int talletus = 20;
	int tapahtumia = 1500; // yht 3000 nosto ja talletustapahtumia

	Tili tili;
	tili.set_saldo(26798);

	std::thread th1(talleta_tilille, std::ref(tili), tapahtumia * talletus); // 1500 * 10 = 30 000
	std::thread th2(nosta_tililta, std::ref(tili), tapahtumia * nosto); // 1500 * 50 = 60 000

	th1.join();
	th2.join();

	std::cout << "tilin lopullinen saldo on " << tili.get_saldo() << " euroa.";

	return 0;
}
