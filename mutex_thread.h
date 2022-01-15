#ifndef MUTEX_THREAD
#define MUTEX_THREAD

#include"header.h"

namespace MUTEX
{
	enum class lockType
	{
		kMutex,
		kTimedMutex,
		kRecursiveMutex,
		kRecursiveTimedMutex
	};

	int g_counter = 0;
	std::mutex g_mutex;
	std::timed_mutex g_timed_mutex;// 只是增加了try_lock_for和_Try_lock_until
	std::recursive_mutex g_recursive_mutex;//允许多次lock，但是lock和unlock的数量应当一致
	std::recursive_timed_mutex g_recursive_timed_mutex;
	void do_work(lockType type, int thread_id)
	{
		while (g_counter < 1000)
		{			

#if 1//有保护的锁
			switch (type)
			{
			case MUTEX::lockType::kMutex:
			{
				std::lock_guard<std::mutex> lk(g_mutex);
				g_counter++;
				break;
			}
			case MUTEX::lockType::kTimedMutex:
			{
				std::unique_lock<std::timed_mutex> lk(g_timed_mutex);
				g_counter++;
				break;
			}
			case MUTEX::lockType::kRecursiveMutex:
			{
				//允许连续lock
				std::unique_lock<std::recursive_mutex> lk(g_recursive_mutex);
				std::unique_lock<std::recursive_mutex> lk2(g_recursive_mutex);

				g_counter++;
				break;
			}
			case MUTEX::lockType::kRecursiveTimedMutex:
			{
				//允许连续lock
				std::lock_guard<std::recursive_timed_mutex> lk(g_recursive_timed_mutex);
				std::lock_guard<std::recursive_timed_mutex> lk2(g_recursive_timed_mutex);
				g_counter++;
					break;
			}
			default:
				break;
			}

			for (int i = 0; i < thread_id; i++)
			{
				cout << "\t";
			}
			cout << "thread id " << thread_id << " exec g_counter      "<<g_counter << endl;
#else  //original lock
			g_recursive_mutex.lock();
			g_counter++;
			g_recursive_mutex.unlock();
#endif
			//g_recursive_mutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	void test_mutexs()
	{
		std::vector<std::thread> threads;

		std::thread t0(do_work, MUTEX::lockType::kMutex, 0);
		threads.push_back(std::move(t0));

		std::thread t1(do_work, MUTEX::lockType::kTimedMutex, 1);
		threads.push_back(std::move(t1));

		std::thread t2(do_work, MUTEX::lockType::kRecursiveMutex, 2);
		threads.push_back(std::move(t2));

		std::thread t3(do_work, MUTEX::lockType::kRecursiveTimedMutex, 3);
		threads.push_back(std::move(t3));

		for (auto& t: threads)
		{
			if (t.joinable())
			{
				t.join();
			}
		}

	}
}//END MUTEX

#endif // !MUTEX_THREAD

