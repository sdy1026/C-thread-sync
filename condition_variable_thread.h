#ifndef CONDITION_VARIABLE_THREAD
#define CONDITION_VARIABLE_THREAD

#include"header.h"

namespace CONDITION_VARIABLE
{

	void test_condition_variable()
	{
		std::mutex mutex_lock;
		std::condition_variable condition_var;
		int i = 0;

		std::thread t([&]() {
		
			cout << "sub thread exec, thread Id is " << std::this_thread::get_id() << endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::unique_lock<std::mutex> lock(mutex_lock);
			i = 11;
			condition_var.notify_one();

            cout << "sub thread notified" << endl;
		});

        std::this_thread::sleep_for(std::chrono::seconds(1));

        cout << "main thread exec, sleeped for 2 seconds  "<< endl;

        std::unique_lock<std::mutex> uniquelock(mutex_lock);

        condition_var.wait(uniquelock, [&]() {
            //阻塞，直到i不为0。 返回值为false，等待，返回值为true，解锁
            return i!= 0;
        });

        //阻塞，直到被唤醒
        // 如果notify先于wait则会一直等待下去
        //condition_var.wait(uniquelock);

        cout << "after waited   "<<"    i is "<< i << endl;
        if (t.joinable())
        {
            t.join();
        }
	}


    namespace PRODEUCT_CONSUME
    {
        std::mutex g_cvMutex;
        std::condition_variable g_cv;

        //缓存区
        std::deque<int> g_data_deque;
        //缓存区最大数目
        const int  MAX_NUM = 30;
        //数据
        int g_next_index = 0;

        //生产者，消费者线程个数
        const int PRODUCER_THREAD_NUM = 3;
        const int CONSUMER_THREAD_NUM = 3;

        void  producer_thread(int thread_id)
        {
            while (true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                //加锁
                std::unique_lock <std::mutex> lk(g_cvMutex);
                //当队列未满时，继续添加数据
                g_cv.wait(lk, []() { return g_data_deque.size() <= MAX_NUM; });
                g_next_index++;
                g_data_deque.push_back(g_next_index);
                std::cout << "producer_thread: " << thread_id << " producer data: " << g_next_index;
                std::cout << " queue size: " << g_data_deque.size() << std::endl;
                //唤醒其他线程 
                g_cv.notify_all();
                //自动释放锁
            }
        }

        void  consumer_thread(int thread_id)
        {
            while (true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                //加锁
                std::unique_lock <std::mutex> lk(g_cvMutex);
                //lambda表达式返回false时一直等待，返回true解锁
                g_cv.wait(lk, [] { return !g_data_deque.empty(); });
                //互斥操作，消息数据
                int data = g_data_deque.front();
                g_data_deque.pop_front();
                std::cout << "\tconsumer_thread: " << thread_id << " consumer data: ";
                std::cout << data << " deque size: " << g_data_deque.size() << std::endl;
                //唤醒其他线程
                g_cv.notify_all();
                //自动释放锁
            }
        }


        int test_product_consume()
        {
            std::thread arrRroducerThread[PRODUCER_THREAD_NUM];
            std::thread arrConsumerThread[CONSUMER_THREAD_NUM];

            for (int i = 0; i < PRODUCER_THREAD_NUM; i++)
            {
                arrRroducerThread[i] = std::thread(producer_thread, i);
            }

            for (int i = 0; i < CONSUMER_THREAD_NUM; i++)
            {
                arrConsumerThread[i] = std::thread(consumer_thread, i);
            }

            for (int i = 0; i < PRODUCER_THREAD_NUM; i++)
            {
                arrRroducerThread[i].join();
            }

            for (int i = 0; i < CONSUMER_THREAD_NUM; i++)
            {
                arrConsumerThread[i].join();
            }

            return 0;
        }
    }  

}//END CONDITION_VARIABLE






#endif // !CONDITION_VARIABLE_THREAD

