#include <iostream>
#include <cstring>

class VString
{
	public:
		VString(const char *str)
		{
			n_ = strlen(str);
			str_ = new char[n_ + 1];
			std::memcpy((void *)str_, str, n_ + 1);
		}

		// Copy initialized
		VString(const VString& that)
		{
			n_ = that.n_;
			str_ = new char[n_ + 1];
			std::memcpy((void *) str_, that.str_, that.n_);
		}

		// Copy assigned
		VString& operator=(const VString& that)
		{
			// Remove old data
			delete str_;

			// Copy new data
			n_ = that.n_;
			str_ = new char[n_ + 1];
			std::memcpy((void *) str_, that.str_, that.n_);
			return *this;
		}

		~VString()
		{
			delete str_;
		}

		const char *c_string()
		{
			return str_;
		}

		const char length() {
			return n_;
		}

		friend std::ostream& operator<<(std::ostream& os, const VString& vs)
		{
			os << vs.str_;
			return os;
		}

	private:
		char *str_;
		int n_;
};
