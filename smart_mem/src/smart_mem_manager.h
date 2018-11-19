// A STL for smart memory management
// Author:- sandeep mishra
#ifndef SMART_MEM_H
#define SMART_MEM_H
#include <string>
#include <sstream>
#include <type_traits>
#include "mem_exceptions.h"

template <class __VALUE>
class SmartMemoryManager
{
  private:
	//key data type
	typedef std::string key_type;
	//value data type
	typedef __VALUE value_type;
	bool is_pointer_type = std::is_pointer<value_type>::value;
	//an error handler called before throwing any exception (if provided)
	void (*error_handler)(ErrorType, std::string) = nullptr;
	// indicates that error will thrown or not
	bool throw_error = true;
	// no of items
	int total_item = 0;
	// checks that key exists or not
	bool check_key_existence(const key_type &key) const;
	// checks that provided item exists or not
	bool check_item_existence(const value_type value) const;
	// checks the length of items and throw exception when necessary
	bool check_for_total_item() const;
	// checks length of item for swapping
	bool check_length_for_swap() const;
	// checks that both keys are equal or not
	bool check_equality(const key_type &key1, const key_type &key2) const;
	// checks that both items are equal or not
	bool check_equality(const value_type val1, const value_type val2) const;
	// checks given index if index >= total_item ArrayIndexError exception thrown
	bool check_array_index(const int &index) const;
	// converts objects physicall address into std::string
	std::string get_address_str(void *vl) const
	{
		const void *address = static_cast<const void *>(vl);
		std::stringstream ss;
		ss << address;
		return ss.str();
	}

	// data structure for holding key and value(items)
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
	//holds the very first node of KEY_VALUE_PAIR
	KEY_VALUE_CONTAINER *container = nullptr;
	//holds the last node of KEY_VALUE_PAIR
	KEY_VALUE_CONTAINER *container_last = nullptr;
	// protect default object initialization from rvalue to lvalue
	SmartMemoryManager &operator=(const SmartMemoryManager &obj);

  public:
	SmartMemoryManager()
	{
		std::cout<<is_pointer_type;
	}
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
	void for_each(void callback(const value_type value)) const;
	void register_error_handler(void (*error_handler)(ErrorType, std::string), bool throw_error = true);
	value_type operator[](const key_type &key) const;
	value_type operator[](const int &index) const;
};

#endif // SMART_MEM_H
