/*Oletetaan, ett‰ pelin suorittamille toimenpiteille (teko‰lyn ajaminen, pelimaailman p‰ivitys, jne.)
on m‰‰ritelty yhteinen yliluokka Game_Task. Luokassa on m‰‰ritelty puhdas virtuaalifunktio
perform(), joka suorittaa ko. toimenpiteen:
virtual void Game_Task::perform() = 0;
Kaikki toimenpiteet ovat toisistaan riippumattomia (eiv‰t k‰yt‰ samaa dataa tms.).
Peli yll‰pit‰‰ vektoria toimenpiteist‰. Toimenpiteet suoritetaan per‰kk‰in silmukassa:
	std::vector<Game_Task*> tasks;
	Ö
	int number_of_tasks = tasks.size();
	for (int i = 0; i < number_of_tasks; i++)
	{
	task[i]->perform();
	}
	// Continue only after all tasks are complete!
Hahmottele, miten em. silmukka voitaisiin rinnakkaistaa k‰ytt‰en std::thread -luokkaa. Etsi
ohjelmallinen tapa selvitt‰‰, kuinka montaa samanaikaista s‰iett‰ laitteistosi pystyy
suorittamaan fyysisesti; k‰yt‰ rinnakkaistamiseen yksi s‰ie v‰hemm‰n.
Luo testaamista varten yliluokka Game_Task ja sille muutama aliluokka, joiden perform-funktio
kuluttaa sopivasti prosessoriaikaa johonkin. Mittaa rinnakkaistamisesta saamasi
suoritusaikahyˆty.

K‰yt‰ rinnakkaistamiseen asynkronisia funktiokutsuja. Yksinkertaisuuden
vuoksi samanaikaisten kutsujen m‰‰r‰‰ ei tarvitse rajoittaa.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <chrono>

class Game_Task
{
public:
	virtual void perform() = 0;
	virtual ~Game_Task() {}
};

class Task_1 : public Game_Task
{
public:
	void perform() override 
	{
		for (int i = 0; i < 120000; ++i)
		{
			int a = i * i;
		}
	}
};

class Task_2 : public Game_Task
{
public:
	void perform() override 
	{
		for (int i = 0; i < 600000; ++i)
		{
			int a = i + 1;
		}
	}
};

int main()
{
	std::vector<Game_Task*> tasks;

	tasks.push_back(new Task_1());
	tasks.push_back(new Task_2());

	int number_of_tasks = tasks.size();

	auto start = std::chrono::steady_clock::now();

	std::vector<std::future<void>> futures;
	for (int i = 0; i < number_of_tasks; i++)
	{
		futures.push_back(std::async(std::launch::async, [&tasks, i]()
		{
			tasks[i]->perform();
		}));			
	}
	
	// Continue only after all tasks are complete!
	for (std::future<void>& future : futures) 
	{
		future.wait();
	}

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = end - start;

	std::cout << "Suoritusaika: " << duration.count() << " s\n"; // 0.0014257 s

	for (Game_Task* task : tasks) 
	{
		delete task;
	}

	return 0;
}