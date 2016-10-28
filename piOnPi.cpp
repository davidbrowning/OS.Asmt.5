#includ <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>

int calculateDigitofPi(int dig, std::mutex& mutex)
{
	std::lock_guard<std::mutex> lock(mutex);
	int pi [11] = {3,1,4,1,5,9,2,6,5,3,5};
	return pi[dig];
}


void threadStart(int threadId, std::mutex& mutex)
{
	for (int value = 0; value < 4; value++)
	{
		std::cout << "Thread: " << threadId;
		std::cout << " Value: " << calculateDigitofPi(value, mutex) << std::endl;
	}
}


int main()
{
	srand(time(NULL));

	std::mutex mutex;

	std::thread thread1(threadStart, 1, std::ref(mutex));
	std::thread thread2(threadStart, 2, std::ref(mutex));

	thread1.join();
	thread2.join();

	return 0;
}

