/*Luo N alkion kokoinen (suuri) taulukko, johon on talletettu luvut 0ÖN-1. Kirjoita ohjelma, joka k‰y
kasvattamassa jokaisen alkion arvoa yhdell‰:
ï k‰yt‰ std::for_each-algoritmia
ï kokeile algoritmille erilaisia suorism‰‰reit‰:
o std::execution::seq
o std::execution::par
o std::execution::par_unseq
Havaitsetko n‰in yksinkertaisessa teht‰v‰ss‰ suorituskykyeroja eri suoritusm‰‰reiden v‰lill‰? Mit‰ eri
suoritusm‰‰reet tarkoittavat?
Huomaa, ett‰ teht‰v‰ vaatii v‰hint‰‰n C++17-version*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <chrono>

int main()
{
	int N = 120000;
	std::vector<int> large_vector(N);

	for (int i = 0; i < N; ++i)
	{
		large_vector[i] = i;
	}

	auto start = std::chrono::steady_clock::now();
	std::for_each(std::execution::seq, large_vector.begin(), large_vector.end(), [](int &n)
	{
		n++;
		//std::cout << n << " ";
	});
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = end - start;

	std::cout << "\n\nExecution time: " << duration.count() << " s\n";

	/*Suorituskykyerot eri suoritusm‰‰reiden v‰lill‰: 
	o std::execution::seq -> sequenital execution. Default, jos ei spesifioida execution policy a. "algorithm will be executed in the calling thread without any parallelization. It's useful when you want to ensure that the algorithm runs in a single-threaded, sequential manner."
		Suoritusaika : 0.0003252 s
	o std::execution::par -> paraller exe. "This execution policy specifies that the algorithm can execute in parallel if the standard library implementation supports parallel execution. It allows the implementation to use multiple threads to execute the algorithm concurrently, potentially speeding up the execution on multi-core processors."
		Suoritusaika : 0.0013197 s
	o std::execution::par_unseq -> sama ku edelline, mut vaatii stronger guarantees, but allows additional optimizationsl, "allows the standard library to use SIMD (Single Instruction, Multiple Data) instructions to process multiple elements simultaneously when executing the algorithm in parallel"
		Suoritusaika : 0.0015474 s
	*/
	

	return 0;
}