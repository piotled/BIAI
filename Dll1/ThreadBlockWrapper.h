#pragma once
#include <thread>
#include <defines.h>

class ThreadBlockWrapper {
	uint threadCount;
	uint startedThreads;
	std::thread ** threads;
public:
	ThreadBlockWrapper(uint threadCount) :threadCount(threadCount), startedThreads(0) {
		threads = new std::thread*[threadCount];
	}

	~ThreadBlockWrapper() {
		for (uint i = 0; i < startedThreads; i++) {
			threads[i]->join();
			delete threads[i];
		}
		delete threads;
	}

	bool isRoom() {
		if (startedThreads < threadCount)
			return true;
		else return false;
	}

	void save(std::thread * threadPtr) {
		threads[startedThreads++] = threadPtr;
	}
};