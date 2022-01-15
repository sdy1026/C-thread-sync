#include<iostream>

#include"promise_future.h"
#include"async_future.h"
#include"packaged_task_future.h"
#include"condition_variable_thread.h"
#include"mutex_thread.h"

int main(int argc, char* argv[])
{
	cout << "main function exec begin  "<< endl;

	cout << "main  thread Id is " << std::this_thread::get_id()<<endl;

	//PROMISE::test_promise_set_execption();
	//PROMISE::test_promise_set_value();
	// 
	//ASYNC::test_async_default();
	//ASYNC::test_async_async();
	ASYNC::test_async_deferred();

	//PACKAGED_TASK::test_packaged_task_lambda();
	//PACKAGED_TASK::test_packaged_task_thread();
	//PACKAGED_TASK::test_packaged_task_bind(2,5);


	//CONDITION_VARIABLE::PRODEUCT_CONSUME::test_product_consume();
	//CONDITION_VARIABLE::test_condition_variable();
	
	//MUTEX::test_mutexs();


	cout << "main function exec end  " << endl;
	system("pause");
	return 0;

}