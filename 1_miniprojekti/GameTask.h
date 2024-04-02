#pragma once

#include <iostream>

class GameTask {
public:
	virtual void perform() = 0;
	virtual ~GameTask() {}
};

class Task1 : public GameTask {
public:
	void perform() override {
		for (int i = 0; i < 120000; ++i) {
			int a = i * i;
		}
		std::cout << "Task 1 done\n";
	}
};

class Task2 : public GameTask
{
public:
	void perform() override {
		for (int i = 0; i < 600000; ++i) {
			int a = i + 1;
		}
		std::cout << "Task 2 done\n";
	}
};