/*Kirjoita ohjelma, joka laskee (suuren) taulukon (esim. vektorin) elementtien summan k‰ytt‰en useita
s‰ikeit‰. Jaa taulukko yht‰ suuriin osiin, anna jokainen osa eri s‰ikeelle ja anna niiden laskea oman
osansa summa. Lopuksi yhdist‰ kaikkien s‰ikeiden tulokset saadaksesi kokonaissumman. P‰‰ohjelma
luo s‰ikeet ja odottaa niiden p‰‰ttymist‰. Varmista, ett‰ tulos on oikein.
Luo s‰ikeet std::thread-luokan avulla.
K‰yt‰ toteutukseen asynkronisia funktiokutsuja !!!!!*/

#include <iostream>
#include <future>
#include <vector>
#include <thread>

int count_elements(const std::vector<int>& vector, int start, int end)
{
	int sum = 0;
	for (int i = start; i < end; ++i)
	{
		sum += vector[i];
	}

	return sum;
}

int main()
{
	int sum = 0;
	int total_elements = 12000;
	int threads = 5;

	std::vector<int> large_vector(total_elements, 2); //kaikki arvot on 2

	int chunk = total_elements / threads; // 12000 / 5 = 2400 
	std::vector<std::future<int>> futures(threads);

	for (int i = 0; i < threads; ++i)
	{
		int start = i * chunk;
		int end = (i == threads - 1) ? total_elements : (i + 1) * chunk;
		futures[i] = std::async(std::launch::async, count_elements, std::ref(large_vector), start, end);
	}

	int total = 0;
	for (std::future<int>& future : futures)
	{
		total += future.get();
	}

	std::cout << "Vektorin summa: " << total;

	return 0;
}
