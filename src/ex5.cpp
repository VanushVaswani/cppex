#include <queue>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

template <typename T>
class VQueue {
	public:
		VQueue(int capacity) : capacity_{capacity} {}
		void put(T val)
		{
			std::unique_lock<std::mutex> lock_(m_);
			// Wait on non full
			cv_full_.wait(lock_, [this]{ return data_.size() != capacity_; });
			data_.push(val);
			// Unlock before notify
			lock_.unlock();
			cv_empty_.notify_all();
		}

		T get()
		{
			std::unique_lock<std::mutex> lock_(m_);
			cv_empty_.wait(lock_, [this]{ return data_.size() > 0; });
			T val = data_.front();
			data_.pop();
			// Unlock before notify
			lock_.unlock();
			cv_full_.notify_all();
			return val;
		}

	private:
		int capacity_;
		std::queue<T> data_;
		std::mutex m_;
		std::condition_variable cv_full_;
		std::condition_variable cv_empty_;


};


void producer(VQueue<int>& q)
{
	int i = 0;
	while (i < 200)
	{
		auto val = i;
		q.put(val);
		std::cout << "Sent "<< val << std::endl;
		i++;
	}
}

void consumer(VQueue<int>& q)
{
	int i = 0;
	while (i < 200)
	{
		auto val = q.get();
		std::cout << "Got " << val << std::endl;
		i++;
	}
}

int main(int argc, char *argv[])
{
	VQueue<int> q(5);
	std::thread p{producer, std::ref(q)};
	std::thread c{consumer, std::ref(q)};
	p.join();
	c.join();
	return 0;
}
