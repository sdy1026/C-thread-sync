#ifndef ASYNC_FUTURE
#define ASYNC_FUTURE

#include"header.h"

namespace ASYNC
{
	void test_async_default()
	{
		auto f = std::async([]() {
			cout << "default  model, current thread Id is " << std::this_thread::get_id()<<endl;
			return 8; 
		});
		cout <<endl << "before get,  function: " << __func__ << endl<<endl;

		auto s = f.share();	//std::shared_future can get more than one
		auto ret = s.get(); 	
		auto n = s.get();
		cout << "default async  get  result is " << ret << endl;

	}


	void test_async_async()
	{
		std::mutex mut;
		//{
			std::vector<std::future<int>> vec;
			for (int i = 0; i < 100; i++)
			{

				auto f = std::async(std::launch::async, [&i,&mut]() {
					std::unique_lock<std::mutex>locker(mut);
					cout << " async model,current id is "<<i<<" current thread Id is " << std::this_thread::get_id() << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					return 9;
				});
				//no pushback:f in same thread £»psuh :different thrread
				//vec.push_back(std::move(f));
			}
		//}

			// whether get or not,async will exec
			//for (auto & f:vec)
			//{
			//	//f.get();
			//}
		std::this_thread::sleep_for(std::chrono::seconds(100));
	
		//cout << endl << "before get,  function: " << __func__ << endl << endl;
		//auto ret = f.get();
		//cout << "async  async  get  result is " << ret << endl;
	}


	void test_async_deferred()
	{
		auto f = std::async(std::launch::deferred, []() {
			cout << "deferred model, current thread Id is " << std::this_thread::get_id() << endl;
			return 10;
		});
		cout << endl << "before get,  function: " << __func__ << endl << endl;

		// only  get,async will exec
		
		//auto ret = f.get();
		//cout << "deferred  async  get  result is " << ret << endl;

	}
	
}//END ASYNC

#endif // !ASYNC_FUTURE

