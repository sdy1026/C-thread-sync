#ifndef PROMISE_FUTURE
#define PROMISE_FUTURE

#include"header.h"

namespace PROMISE
{

	int g_counter = 0;
	//for future promise begin 
	void test_promise_set_value()
	{
		std::promise<int> p;
		std::future<int> f = p.get_future();
		std::thread t([&p]() {

			cout << "sub thread exec, thread Id is " << std::this_thread::get_id() << endl;
			//cannot set value twice or more
			//while (g_counter < 2)
			//{
			std::this_thread::sleep_for(std::chrono::seconds(2));
			int value = 50 * g_counter;
			p.set_value(value);
			//p.set_value_at_thread_exit(value);
			std::this_thread::sleep_for(std::chrono::seconds(2));
			cout << "promise value had been setted value " << value << endl;
			//}
		});

		cout << "main thread ----- sub thread has been started" << endl;


		auto ret = f.get();
		//cout << "sub thread set the calue is " << ret << endl;

		cout << __func__ << "   " << __LINE__ << endl;

		//Ensure  thread execution ends
		if (t.joinable())
		{
			t.join();
		}
		cout << __func__ << "   " << __LINE__ << endl;
	}

	void test_promise_set_execption()
	{
		std::promise<int> p;
		std::future<int> f = p.get_future();
		std::thread t([&p]() {
			try
			{
				throw std::runtime_error("Example");
			}
			catch (...)
			{
				try
				{
					p.set_exception(std::current_exception());
				}
				catch (...)
				{

				}
			}
		});

		try {
			std::cout << f.get();
		}
		catch (const std::exception& e) {
			std::cout << "Exception from the thread: " << e.what() << '\n';
		}

		//Ensure  thread execution ends
		if (t.joinable())
		{
			t.join();
		}
	}
}//END PROMISE

#endif // !PROMISE_FUTURE

