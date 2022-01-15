#ifndef PACKAGED_TASK_FUTURE
#define PACKAGED_TASK_FUTURE

#include"header.h"

namespace PACKAGED_TASK
{
	void test_packaged_task_lambda()
	{
		 std::packaged_task<int(void)> task ( []() {
			cout << "packaged  one thread   model, current thread Id is " << std::this_thread::get_id()<<endl;
			return 21; 
		});

		cout <<endl << "before get,  function: " << __func__ << endl<<endl;
		
		//task();
		auto f = task.get_future();
		task();

		//execuate before get future or after get future cout the same result.
		cout << "one thread  get  result is " << f.get() << endl;
	}

	void test_packaged_task_thread()
	{
		std::packaged_task<double(int,int)> task([](int a, int b) {
			cout << "packaged  two thread   model, current thread Id is " << std::this_thread::get_id() << endl;
			std::this_thread::sleep_for(std::chrono::seconds(3));
			return std::pow(a,b);
		});

		cout << endl << "before get,  function: " << __func__ << endl << endl;

		auto f = task.get_future();

		std::thread t(std::move(task),2, 8);

		cout << "two thread  get  result is " << f.get() << endl;

		if (t.joinable())
		{
			t.join();
		}
	}


	double calculation_pow(int a, int b)
	{
		return std::pow(a, b);
	}

	void test_packaged_task_bind(int a,int b)
	{
		std::packaged_task<double()> task( std::bind(calculation_pow,a,b));

		cout << endl << "before get,  function: " << __func__ << endl << endl;

		auto f = task.get_future();

		task();

		cout << "two thread  get  result is " << f.get() << endl;
	}
	
}//END PACKAGED_TASK

#endif // !PACKAGED_TASK_FUTURE

