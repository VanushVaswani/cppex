#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <list>

class VInMemoryCache
{
	typedef std::pair<std::unique_ptr<uint8_t[]>, size_t> Value;
	public:
		VInMemoryCache(int capacity) : capacity_{capacity}, data_{}, order_{} {}
		void put(std::string key, uint8_t *in_data, size_t sz)
		{
			// Check if key is in list
			if (data_.find(key) == data_.end()) {
				if (data_.size() == capacity_) {
					// Evict oldest item
					auto key = order_.back();
					order_.pop_back();
					data_.erase(key);
					li_map_.erase(key);
					std::cerr << "Evicting item " << key << std::endl;
				}
			} else {
				// The old version is out of date
				// so get rid of it
				order_.erase(li_map_[key]);
			}

			// Accounting
			order_.push_front(key);
			li_map_[key] = order_.begin();

			data_[key] = std::make_pair(std::make_unique<uint8_t[]>(sz), sz);
			std::memcpy(data_[key].first.get(), in_data, sz);
		}

		uint8_t *get(std::string key, size_t *sz)
		{
			auto res = data_.find(key);

			if (res == data_.end()) {
				return nullptr;
			}

			order_.erase(li_map_[key]);
			order_.push_front(key);
			li_map_[key] = order_.begin();

			Value& p = data_[key];
			*sz = p.second;
			return p.first.get();
		}

		bool keyInCache(std::string key)
		{
			return (data_.find(key) != data_.end());
		}

	private:
		int capacity_;
		std::unordered_map<std::string, Value> data_;
		std::unordered_map<std::string, std::list<std::string>::iterator> li_map_;
		std::list<std::string> order_;
};

uint8_t *generate_bytes(uint8_t *in, size_t num)
{
	for(int i = 0; i < num; i++) {
		in[i] = std::rand() % 256;
	}
	return in;
}
