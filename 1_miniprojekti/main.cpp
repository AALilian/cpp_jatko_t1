#include "TaskQueue.h"

int main() {
	unsigned int threads = std::thread::hardware_concurrency();
	std::cout << threads << " concurrent threads are supported.\n";

	TaskQueue t_queue(threads);

	for (int i = 0; i < 5; ++i) {
		t_queue.addJob(new Task1);
		t_queue.addJob(new Task2);
	} 

	return 0;
}