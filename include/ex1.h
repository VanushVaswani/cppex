#include <iostream>
#include <vector>
#include <tuple>

template <typename T>
class VStack
{
	public:
		// Constructor
		VStack(int size = 0) : size_{size} {
			data_.reserve(size_);
		}

		// Copy constructor
		VStack(const VStack<T>& that)
		{
			size_ = that.size_;
			data_ = that.data_;
		}

		// Copy assignment
		VStack& operator=(const VStack<T>& that)
		{
			size_ = that.size_;
			data_ = that.data_;
			return *this;
		}

		void push(const T item)
		{
			if (data_.size()) assert(data_.size() != size_);
			data_.push_back(item);
		}

		T pop() // O(n)
		{
			assert(!data_.empty());
			T item = data_.back();
			data_.pop_back();
			return item;
		}

		const T& peek() const
		{
			assert(!data_.empty());
			const T& item = data_.back();
			return item;
		}

		bool empty() const
		{
			return data_.empty();
		}

	private:
		std::vector<T> data_;
		int size_;

};

template <class T>
class MaxVStack : public VStack<T>
{

	public:
		MaxVStack(int size = 0) : VStack<T>(size) {}

		MaxVStack(const MaxVStack<T>& that)
		{
			track_ = that.track_;
		}

		MaxVStack& operator=(const MaxVStack<T>& that)
		{
			track_ = that.track_;
			return *this;
		}

		void push(const T item)
		{
			if (!VStack<T>::empty()) {
				auto back{VStack<T>::peek()};
				track_.push((item > back) ? item : back);
			} else {
				track_.push(item);
			}

			VStack<T>::push(item);
		}

		T pop()
		{
			assert(!track_.empty());
			track_.pop();
			return VStack<T>::pop();
		}

		const T& max() const
		{
			const auto& val = track_.peek();
			return val;
		}

	private:
		VStack<T> track_; // Keep track of maximum in auxiliary stack.
};
