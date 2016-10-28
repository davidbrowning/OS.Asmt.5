#include <iostream>
#include <thread>
#include <atomic>

int main()
{
	std::atomic<uint16_t> resource(0);

	auto report = [](uint16_t value)
	{
		std::cout << "The value is: " << value << std::endl;
	};

	auto threadFunction =
		[&resource, report](uint16_t which)
		{
			while (resource < 10)
			{
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

