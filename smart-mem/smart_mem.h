// userdefined template(generic class) for smart memory management
// author:- sandeep mishra
#ifndef SMART_MEM_H
#define SMART_MEM_H
#include <string>
#include <sstream>
//const short NOT_FOUND = -1;

template <class __VALUE>
class SmartMemoryManager
{
  private:
	typedef std::string key_type;
	typedef __VALUE value_type;
	int total_item = 0;
	bool check_key_existence(const key_type &key) const;
	bool check_item_existence(const value_type value) const;
	std::string get_address_string(value_type vl) const
	{
		const void *address = static_cast<const void *>(vl);
		std::stringstream ss;
		ss<<address;
		return ss.str();
	}

	struct KEY_VALUE_CONTAINER
	{
		key_type key_code;
		value_type value = nullptr;

		KEY_VALUE_CONTAINER *next = nullptr;
		KEY_VALUE_CONTAINER *prev = nullptr;

		KEY_VALUE_CONTAINER() {}

		KEY_VALUE_CONTAINER(const key_type &key, const value_type val)
		{
			key_code = key;
			value = val;
		}
		~KEY_VALUE_CONTAINER()
		{
			if (value != nullptr)
			{
				delete value;
				value = nullptr;
			}
		}
	};

	KEY_VALUE_CONTAINER *container = nullptr;
	KEY_VALUE_CONTAINER *container_last = nullptr;
	// protect default object initialization from rvalue to lvalue
	SmartMemoryManager &operator=(const SmartMemoryManager &obj);

  public:
	SmartMemoryManager() {}
	~SmartMemoryManager();
	void clear();
	int count() const;
	void append(const key_type &key, const value_type val);
	void at_begining(const key_type &key, const value_type val);
	value_type first_value() const;
	value_type last_value() const;
	key_type first_key() const;
	key_type last_key() const;
	value_type get_item(const key_type &key) const;
	key_type get_key(const value_type item) const;
	bool remove(const key_type &key);
	bool remove(const value_type val);
	void swap_item(const key_type &key1, const key_type &key2);
	void swap_item(const value_type val1, const value_type val2);
	void swap_key(const value_type val1, const value_type val2);
	void swap_key(const key_type &key1, const key_type &key2);
	value_type operator[](const key_type &key) const;
	value_type operator[](const int &index) const;
};

#endif // SMART_MEM_H
