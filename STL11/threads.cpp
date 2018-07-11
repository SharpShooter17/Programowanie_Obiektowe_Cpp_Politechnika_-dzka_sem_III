#include <iostream>
#include <thread>
#include<mutex>

int var = 0;
std::mutex mutex;

void thread_function()
{
	std::cout << "Hello form thread.." << std::endl;
}

void thread_args_func(int x, double y)
{
	std::cout << x << " " << y << std::endl;
}

void thread_change()
{
	std::lock_guard<std::mutex> lockGuard(mutex);
	for (int i = 0; i < 10000; i++)
	{
		var++;
	}
}

int main()
{
	std::thread threadOBj(thread_function);
	threadOBj.join();

	std::chrono::milliseconds dura( 2000 );
    std::this_thread::sleep_for( dura );
	
	std::thread threadArgs(thread_args_func, 4, 4.5);
	threadArgs.join();
	
	std::thread t1(thread_change);
	std::thread t2(thread_change);
	
	t1.join();
	t2.join();
	std::cout << var << std::endl;
	
	return 0;
}