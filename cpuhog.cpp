#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <iostream>

#define DBG1(msg,x) std::cout << msg << ":" << x << std::endl;
#define DBG2(msg,x,y) std::cout << msg << ":" << x << " : " << y << std::endl;

void worker(int worker_id)
{
#define DBG_WORKER(x) DBG2("worker", worker_id, x)
	std::default_random_engine generator{};
	std::uniform_int_distribution<int> distribution{};
	auto dice = std::bind(distribution, generator);
	std::vector<int> a{};
	a.resize(1 << 20); // 1M
	// do some useless work
	while (true)
	{
		// fill with random data
		std::generate(a.begin(), a.end(), dice);

		std::sort(a.begin(), a.end());
	}
}

int main()
{
	std::vector<std::thread> threads{};
	for (int i = 0; i < std::thread::hardware_concurrency(); ++i)
	{
		threads.push_back(std::thread{[i]{worker(i);}});
	}

	DBG1("threads", threads.size());

	for (auto &t : threads)
	{
		t.join();
	}

	return 0;
}
