#include <iostream>
#include <thread>
#include <mutex>

int main()
{
	uint16_t resource  = 0;
	std::mutex mutex;

	auto report = [](uint16_t value)
	{
		std::cout << "The value is: " << value << std::endl;
	};

	auto threadFunction =
		[&resource, &mutex, report](uint16_t which)
		{
			while (resource < 10)
			{
				std::lock_guard<std::mutex> lock(mutex);
				if (resource % 2 == which)
				{
					resource++;
					report(resource);
				}
			}
		};

	std::thread thread1(threadFunction, 0);
	std::thread thread2(threadFunction, 1);

	thread1.join();
	thread2.join();

	return 0;
}

