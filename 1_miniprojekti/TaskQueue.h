#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include "GameTask.h"

class TaskQueue {
	int threads;
	std::vector<std::thread> v_threads;
	std::mutex mtx;
	std::condition_variable con_variable;
	std::queue<GameTask*> tasks;

	bool running;
	/*int tasks_total = 0;*/

	void worker() {
		// odottaa teht�vi� ja suorittaa ne 

		while (running) {
			GameTask* task;
			{
				std::cout << "tasks " << tasks.size() << "\n";
				std::unique_lock<std::mutex> lock(mtx);

				con_variable.wait(lock, [this] { return !tasks.empty() || !running;  });

				if (running && !tasks.empty()) {
					//task = std::move(tasks.front());
					task = tasks.front();
					tasks.pop();

					if (task) {
						task->perform();
						/*--tasks_total;*/
					}

					/*con_variable.notify_one();*/
				}
			}
		}
	}

public:
	TaskQueue(int nof_threads) : threads(nof_threads), running(true) {
		// Luo ty�jonon, ja halutun m��r�n s�ikeit� t�iden suorittamiseen
		std::cout << "Luodaan jonot\n";

		for (int i = 0; i < threads; ++i) {
			v_threads.emplace_back(&TaskQueue::worker, this);
		}
	}

	~TaskQueue() {
		// tyhjent�� ty�jonon ja odottaa, ett� kaikki k�ynniss� olevan ty�t ovat valmistuneet.
		{
			std::unique_lock<std::mutex> lock(mtx);
			running = false;
		}

		// her�tt�� kaikki s�ikeet niin, ett� ne lopettavat toimintansa.
		con_variable.notify_all();

		for (std::thread& thread : v_threads) {
			thread.join();
		}

		while (tasks.size() > 0) {
			tasks.pop();
		}

		std::cout << "jonot tuhottu\n";
	}

	void addJob(GameTask* task) {
		std::unique_lock<std::mutex> lock(mtx);
		tasks.push(std::move(task));
		con_variable.notify_one(); // signaloi s�ikeit� saapuneesta ty�st�
		/*++tasks_total;*/
	}
};