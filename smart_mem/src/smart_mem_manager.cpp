#include "smart_mem_manager.h"
#include "mem_exceptions.h"

template <class __VALUE>
SmartMemoryManager<__VALUE>::~SmartMemoryManager()
{
	if (container != nullptr)
	{
		KEY_VALUE_CONTAINER *tmp;
		while (container != nullptr)
		{
			tmp = container->next;
			// calls the destructor of KEY_VALUE_CONTAINER
			// and free the memory of value holding by this instance
			delete container;
			total_item--;
			container = tmp;
		}
		container_last = container;
	}
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::check_key_existence(const key_type &key) const
{
	KEY_VALUE_CONTAINER *tmp = container;
	bool status = true;
	// check that key exists or not
	while (tmp != nullptr)
	{
		if (key == tmp->key_code)
			return status;
		tmp = tmp->next;
	}
	std::string msg = "\n**wrong key given** there is no such key:- " + key+"\n";
	if (error_handler != nullptr)
	{
		error_handler(ErrorType::KEY_ERROR, msg);
	}
	if (throw_error)
		throw(KeyError(msg));
	if (!throw_error)
		status = false;

	return status;
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::check_item_existence(const value_type value) const
{
	KEY_VALUE_CONTAINER *tmp = container;
	bool status = true;
	while (tmp != nullptr)
	{
		if (tmp->value == value)
			return true;
		tmp = tmp->next;
	}
	std::string msg = "Item Error:: there is no such item: " + get_address_str(value);
	if (error_handler != nullptr)
		error_handler(ErrorType::ITEM_ERROR, msg);
	if (throw_error)
		throw(ItemError(msg));
	if (!throw_error)
		status = false;

	return status;
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::check_for_total_item() const
{
	std::string msg;
	bool status = true;
	if (total_item <= 0)
	{
		LengthError len_err;
		if (error_handler != nullptr)
			error_handler(ErrorType::LENGTH_ERROR, len_err.getMessage());
		if (throw_error)
			throw(len_err);
		if (!throw_error)
			status = false;
	}
	return status;
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::check_length_for_swap() const
{
	std::string msg;
	bool status = true;
	if (total_item == 0)
		msg = "Length error: there is no item in container";
	if (total_item == 1)
		msg = "Length error: only one item in container";
	if (total_item <= 1)
	{
		if (error_handler != nullptr)
			error_handler(ErrorType::LENGTH_ERROR, msg);
		if (throw_error)
			throw(LengthError(msg));
		if (!throw_error)
			status = false;
	}
	return status;
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::check_equality(const key_type &key1, const key_type &key2) const
{
	bool status = true;
	if (key1 == key2)
	{
		std::string msg = "both keys are same: " + key1 + " == " + key2;
		if (error_handler != nullptr)
			error_handler(ErrorType::KEY_ERROR, msg);
		if (throw_error)
			throw(KeyError(msg));
		if (!throw_error)
			status = false;
	}

	return status;
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::check_equality(const value_type val1, const value_type val2) const
{
	bool status = true;
	if (val1 == val2)
	{
		std::string ss1 = get_address_str(val1);
		std::string ss2 = get_address_str(val2);
		std::string msg = "both items are same: " + ss1 + " == " + ss2;
		if (error_handler != nullptr)
			error_handler(ErrorType::ITEM_ERROR, msg);
		if (throw_error)
			throw(ItemError(msg));
		if (!throw_error)
			status = false;
	}

	return status;
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::check_array_index(const int &index) const
{
	bool status = true;
	if (index >= total_item)
	{
		std::string msg = "Error:**Array index out of bounds**";
		if (error_handler != nullptr)
		{
			error_handler(ErrorType::ARRAY_INDEX_ERROR, msg);
		}
		if (throw_error)
			throw(ArrayIndexError());
		if (!throw_error)
			status = false;
	}
	return status;
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::swap_item(const key_type &key1, const key_type &key2)
{
	bool c_f_t = check_length_for_swap();
	bool c_e = check_equality(key1, key2);
	bool c_k_e1 = check_key_existence(key1);
	bool c_k_e2 = check_key_existence(key2);

	if (c_f_t && c_e && c_k_e1 && c_k_e2)
	{
		KEY_VALUE_CONTAINER *tmp = container;
		KEY_VALUE_CONTAINER *key1_node, *key2_node;
		key1_node = key2_node = nullptr;
		while (tmp != nullptr)
		{
			if (key1_node == nullptr)
			{
				if (tmp->key_code == key1)
					key1_node = tmp;
			}
			if (key2_node == nullptr)
			{
				if (tmp->key_code == key2)
					key2_node = tmp;
			}

			tmp = tmp->next;
		}
		value_type tmp_val = key1_node->value;
		key1_node->value = key2_node->value;
		key2_node->value = tmp_val;
	}
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::swap_item(const value_type val1, const value_type val2)
{
	bool c_f_t = check_length_for_swap();
	bool c_e = check_equality(val1, val2);
	bool c_i_e1 = check_item_existence(val1);
	bool c_i_e2 = check_item_existence(val2);

	if (c_f_t && c_e && c_i_e1 && c_i_e2)
	{
		KEY_VALUE_CONTAINER *val1_node, *val2_node;
		KEY_VALUE_CONTAINER *tmp = container;
		val1_node = val2_node = nullptr;
		while (tmp != nullptr)
		{
			if (val1_node == nullptr)
			{
				if (tmp->value == val1)
					val1_node = tmp;
			}
			if (val2_node == nullptr)
			{
				if (tmp->value == val2)
					val2_node = tmp;
			}

			tmp = tmp->next;
		}
		value_type tmp_val = val1_node->value;
		val1_node->value = val2_node->value;
		val2_node->value = tmp_val;
	}
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::swap_key(const value_type val1, const value_type val2)
{
	bool c_f_t = check_length_for_swap();
	bool c_e = check_equality(val1, val2);
	bool c_i_e1 = check_item_existence(val1);
	bool c_i_e2 = check_item_existence(val2);

	if (c_f_t && c_e && c_i_e1 && c_i_e2)
	{
		KEY_VALUE_CONTAINER *val1_node, *val2_node;
		KEY_VALUE_CONTAINER *tmp = container;
		val1_node = val2_node = nullptr;
		while (tmp != nullptr)
		{
			if (val1_node == nullptr)
			{
				if (tmp->value == val1)
					val1_node = tmp;
			}
			if (val2_node == nullptr)
			{
				if (tmp->value == val2)
					val2_node = tmp;
			}

			tmp = tmp->next;
		}
		key_type tmp_key = val1_node->key_code;

		val1_node->key_code = val2_node->key_code;
		val2_node->key_code = tmp_key;
	}
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::swap_key(const key_type &key1, const key_type &key2)
{
	bool c_f_t = check_length_for_swap();
	bool c_e = check_equality(key1, key2);
	bool c_k_e1 = check_key_existence(key1);
	bool c_k_e2 = check_key_existence(key2);

	if (c_f_t && c_e && c_k_e1 && c_k_e2)
	{
		KEY_VALUE_CONTAINER *key1_node, *key2_node;
		KEY_VALUE_CONTAINER *tmp = container;
		key1_node = key2_node = nullptr;
		while (tmp != nullptr)
		{
			if (key1_node == nullptr)
			{
				if (tmp->key_code == key1)
					key1_node = tmp;
			}
			if (key2_node == nullptr)
			{
				if (tmp->key_code == key2)
					key2_node = tmp;
			}

			tmp = tmp->next;
		}
		key_type tmp_key = key1_node->key_code;

		key1_node->key_code = key2_node->key_code;
		key2_node->key_code = tmp_key;
	}
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::clear()
{
	this->~SmartMemoryManager();
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::at_begining(const key_type &key, const value_type val)
{
	KEY_VALUE_CONTAINER *tmp = new KEY_VALUE_CONTAINER(key, val);
	if (container == nullptr)
	{
		container = tmp;
		container_last = tmp;
	}
	else
	{
		tmp->next = container;
		container->prev = tmp;
		container = tmp;
	}
	total_item++;
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::append(const key_type &key, const value_type val)
{
	if (container == nullptr)
		container = container_last = new KEY_VALUE_CONTAINER(key, val);
	else
	{
		KEY_VALUE_CONTAINER *tmp = new KEY_VALUE_CONTAINER(key, val);
		container_last->next = tmp;
		tmp->prev = container_last;
		// pointing the last node
		container_last = tmp;
	}

	total_item++;
}

template <class __VALUE>
__VALUE SmartMemoryManager<__VALUE>::first_value() const
{
	if (container != nullptr)
		return container->value;
	else
		return nullptr;
}

template <class __VALUE>
__VALUE SmartMemoryManager<__VALUE>::last_value() const
{
	if (container_last != nullptr)
		return container_last->value;
	else
		return nullptr;
}

template <class __VALUE>
std::string SmartMemoryManager<__VALUE>::first_key() const
{
	if (container != nullptr)
		return container->key_code;
	else
		return "";
}

template <class __VALUE>
std::string SmartMemoryManager<__VALUE>::last_key() const
{
	if (container_last != nullptr)
		return container_last->key_code;
	else
		return "";
}

template <class __VALUE>
int SmartMemoryManager<__VALUE>::count() const
{
	return total_item;
}

template <class __VALUE>
__VALUE SmartMemoryManager<__VALUE>::get_item(const key_type &key) const
{
	bool c_f_t = check_for_total_item();
	value_type val = nullptr;
	if (c_f_t)
	{
		KEY_VALUE_CONTAINER *tmp = container;
		while (tmp != nullptr)
		{
			if (tmp->key_code == key)
			{
				val = tmp->value;
				break;
			}
			tmp = tmp->next;
		}
	}

	return val;
}

template <class __VALUE>
std::string SmartMemoryManager<__VALUE>::get_key(const value_type item) const
{
	bool c_f_t = check_for_total_item();
	std::string key = "";
	if (c_f_t)
	{
		KEY_VALUE_CONTAINER *tmp = container;
		while (tmp != nullptr)
		{
			if (tmp->value == item)
			{
				key = tmp->key_code;
				break;
			}
			tmp = tmp->next;
		}
	}
	return key;
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::remove(const key_type &key)
{
	bool c_f_t = check_for_total_item();
	bool c_k_e = check_key_existence(key);

	if (c_f_t && c_k_e)
	{
		KEY_VALUE_CONTAINER *tmp = container;
		KEY_VALUE_CONTAINER *node_to_remove = nullptr;
		while (tmp != nullptr)
		{
			if (tmp->key_code == key)
			{
				node_to_remove = tmp;
				break;
			}
			tmp = tmp->next;
		}
		// means key match found
		if (node_to_remove != nullptr)
		{
			// it means there is only one node created
			if (node_to_remove->next == nullptr && node_to_remove->prev == nullptr)
			{
				total_item = 0;
				delete node_to_remove;
				container = container_last = nullptr;
			}
			// it means this is last node
			if (node_to_remove->next == nullptr && node_to_remove->prev != nullptr)
			{
				node_to_remove->prev->next = nullptr;
				container_last = node_to_remove->prev;
				total_item--;
				delete node_to_remove;
			}
			// it means this is first node
			if (node_to_remove->prev == nullptr && node_to_remove->next != nullptr)
			{
				container = node_to_remove->next;
				container->prev = nullptr;
				total_item--;
				delete node_to_remove;
			}
			// it means node found somewhere b/w in all nodes
			if (node_to_remove->next != nullptr && node_to_remove->prev != nullptr)
			{
				node_to_remove->next->prev = node_to_remove->prev;
				node_to_remove->prev->next = node_to_remove->next;
				total_item--;
				delete node_to_remove;
			}
		}
	}
	return (c_f_t && c_k_e);
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::remove(const value_type val)
{
	bool c_f_t = check_for_total_item();
	bool c_i_e = check_item_existence(val);

	if (c_f_t && c_i_e)
	{
		KEY_VALUE_CONTAINER *tmp = container;
		KEY_VALUE_CONTAINER *node_to_remove = nullptr;
		while (tmp != nullptr)
		{
			if (tmp->value == val)
			{
				node_to_remove = tmp;
				break;
			}
			tmp = tmp->next;
		}
		// means item match found
		if (node_to_remove != nullptr)
		{
			// it means there is only one node created
			if (node_to_remove->next == nullptr && node_to_remove->prev == nullptr)
			{
				total_item = 0;
				delete node_to_remove;
				container = container_last = nullptr;
			}
			// it means this is last node
			if (node_to_remove->next == nullptr && node_to_remove->prev != nullptr)
			{
				node_to_remove->prev->next = nullptr;
				container_last = node_to_remove->prev;
				total_item--;
				delete node_to_remove;
			}
			// it means this is first node
			if (node_to_remove->prev == nullptr && node_to_remove->next != nullptr)
			{
				container = node_to_remove->next;
				container->prev = nullptr;
				total_item--;
				delete node_to_remove;
			}
			// it means node found somewhere b/w in all nodes
			if (node_to_remove->next != nullptr && node_to_remove->prev != nullptr)
			{
				node_to_remove->next->prev = node_to_remove->prev;
				node_to_remove->prev->next = node_to_remove->next;
				total_item--;
				delete node_to_remove;
			}
		}
	}

	return (c_f_t && c_i_e);
}

template <class __VALUE>
__VALUE SmartMemoryManager<__VALUE>::operator[](const key_type &key) const
{
	bool c_f_t = check_for_total_item();
	bool c_k_e = check_key_existence(key);
	value_type val = nullptr;
	if (c_f_t && c_k_e)
	{
		KEY_VALUE_CONTAINER *tmp = container;
		while (tmp != nullptr)
		{
			// match found
			if (tmp->key_code == key)
			{
				val = tmp->value;
				break;
			}
			tmp = tmp->next;
		}
	}
	return val;
}

template <class __VALUE>
__VALUE SmartMemoryManager<__VALUE>::operator[](const int &index) const
{
	bool c_a_i = check_array_index(index);
	value_type val = nullptr;
	if (c_a_i)
	{
		if (index == 0)
			val = first_value();
		if (index == total_item - 1)
			val = last_value();

		if (val == nullptr)
		{
			KEY_VALUE_CONTAINER *tmp = container;
			for (int i = 1; i <= index; i++)
				tmp = tmp->next;
			val = tmp->value;
		}
	}
	return val;
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::for_each(void callback(value_type value)) const
{
	KEY_VALUE_CONTAINER *tmp = container;
	while (tmp != nullptr)
	{
		callback(tmp->value);
		tmp = tmp->next;
	}
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::register_error_handler(void (*error_handler)(ErrorType, std::string), bool throw_error)
{
	this->error_handler = error_handler;
	this->throw_error = throw_error;
}