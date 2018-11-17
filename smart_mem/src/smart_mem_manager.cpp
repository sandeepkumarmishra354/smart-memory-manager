#include "smart_mem.h"
#include "exceptions.h"

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
	// check that both keys exists or not
	while (tmp != nullptr)
	{
		if (key == tmp->key_code)
			return true;
		tmp = tmp->next;
	}
	string msg = "**wrong key given**\nthere is no such key:- " + key;
	throw(KeyError(msg));
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::check_item_existence(const value_type value) const
{
	KEY_VALUE_CONTAINER *tmp = container;
	while (tmp != nullptr)
	{
		if (tmp->value == value)
			return true;
		tmp = tmp->next;
	}
	string sad = get_address_string(value);
	throw(ItemError("Item Error:: there is no such item: " + sad));
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::swap_item(const key_type &key1, const key_type &key2)
{
	if (total_item == 0)
		throw(LengthError());
	if (total_item == 1)
		throw(LengthError("Length error: only one item in container can't swap"));
	if (key1 == key2)
		throw(KeyError("both keys are same: " + key1 + " == " + key2));

	check_key_existence(key1);
	check_key_existence(key2);

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

template <class __VALUE>
void SmartMemoryManager<__VALUE>::swap_item(const value_type val1, const value_type val2)
{
	if (total_item == 0)
		throw(LengthError());
	if (total_item == 1)
		throw(LengthError("Length error: only one item in container can't swap"));
	if (val1 == val2)
	{
		//get address of items
		string ss1 = get_address_string(val1);
		string ss2 = get_address_string(val2);
		throw(ItemError("both items are same: " + ss1 + " == " + ss2));
	}

	check_item_existence(val1);
	check_item_existence(val2);

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

template <class __VALUE>
void SmartMemoryManager<__VALUE>::swap_key(const value_type val1, const value_type val2)
{
	if (total_item == 0)
		throw(LengthError());
	if (total_item == 1)
		throw(LengthError("Length error: only one item in container can't swap"));
	if (val1 == val2)
	{
		//get address of items
		string ss1 = get_address_string(val1);
		string ss2 = get_address_string(val2);
		throw(ItemError("both items are same: " + ss1 + " == " + ss2));
	}

	check_item_existence(val1);
	check_item_existence(val2);

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

template <class __VALUE>
void SmartMemoryManager<__VALUE>::swap_key(const key_type &key1, const key_type &key2)
{
	if (total_item == 0)
		throw(LengthError());
	if (total_item == 1)
		throw(LengthError("Length error: only one item in container--- can't swap"));
	if (key1 == key2)
		throw(KeyError("both keys are same: " + key1 + " == " + key2));

	check_key_existence(key1);
	check_key_existence(key2);

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

template <class __VALUE>
void SmartMemoryManager<__VALUE>::clear()
{
	this->~SmartMemoryManager();
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::at_begining(const key_type &key, const value_type val)
{
	KEY_VALUE_CONTAINER *tmp = new KEY_VALUE_CONTAINER(key, val);
	total_item++;
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
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::append(const key_type &key, const value_type val)
{
	if (container == nullptr)
	{
		container = new KEY_VALUE_CONTAINER(key, val);
		total_item++;
		container->next = nullptr;
		container->prev = nullptr;
		// pointing the last node
		container_last = container;
	}
	else
	{
		KEY_VALUE_CONTAINER *tmp;

		tmp = new KEY_VALUE_CONTAINER(key, val);
		total_item++;
		tmp->next = nullptr;
		container_last->next = tmp;
		tmp->prev = container_last;
		// pointing the last node
		container_last = tmp;
	}
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
string SmartMemoryManager<__VALUE>::first_key() const
{
	if (container != nullptr)
		return container->key_code;
	else
		return "";
}

template <class __VALUE>
string SmartMemoryManager<__VALUE>::last_key() const
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
	if (total_item == 0)
		throw(LengthError());
	KEY_VALUE_CONTAINER *tmp = container;
	while (tmp != nullptr)
	{
		if (tmp->key_code == key)
			return tmp->value;
		else
			tmp = tmp->next;
	}
	// not found
	return nullptr;
}

template <class __VALUE>
string SmartMemoryManager<__VALUE>::get_key(const value_type item) const
{
	if (total_item == 0)
		throw(LengthError());
	KEY_VALUE_CONTAINER *tmp = container;

	while (tmp != nullptr)
	{
		if (tmp->value == item)
			return tmp->key_code;
		else
			tmp = tmp->next;
	}
	// not found
	return "";
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::remove(const key_type &key)
{
	if (total_item == 0)
		throw(LengthError());
	check_key_existence(key);

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
			return true;
		}
		// it means this is last node
		if (node_to_remove->next == nullptr && node_to_remove->prev != nullptr)
		{
			node_to_remove->prev->next = nullptr;
			container_last = node_to_remove->prev;
			total_item--;
			delete node_to_remove;
			return true;
		}
		// it means this is first node
		if (node_to_remove->prev == nullptr && node_to_remove->next != nullptr)
		{
			container = node_to_remove->next;
			container->prev = nullptr;
			total_item--;
			delete node_to_remove;
			return true;
		}
		// it means node found somewhere b/w in all nodes
		if (node_to_remove->next != nullptr && node_to_remove->prev != nullptr)
		{
			node_to_remove->next->prev = node_to_remove->prev;
			node_to_remove->prev->next = node_to_remove->next;
			total_item--;
			delete node_to_remove;
			return true;
		}
	}
}

template <class __VALUE>
bool SmartMemoryManager<__VALUE>::remove(const value_type val)
{
	if (total_item == 0)
		throw(LengthError());
	check_item_existence(val);

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
			return true;
		}
		// it means this is last node
		if (node_to_remove->next == nullptr && node_to_remove->prev != nullptr)
		{
			node_to_remove->prev->next = nullptr;
			container_last = node_to_remove->prev;
			total_item--;
			delete node_to_remove;
			return true;
		}
		// it means this is first node
		if (node_to_remove->prev == nullptr && node_to_remove->next != nullptr)
		{
			container = node_to_remove->next;
			container->prev = nullptr;
			total_item--;
			delete node_to_remove;
			return true;
		}
		// it means node found somewhere b/w in all nodes
		if (node_to_remove->next != nullptr && node_to_remove->prev != nullptr)
		{
			node_to_remove->next->prev = node_to_remove->prev;
			node_to_remove->prev->next = node_to_remove->next;
			total_item--;
			delete node_to_remove;
			return true;
		}
	}
	// item match not found wrong key given
	else
		throw(ItemError());
}

template <class __VALUE>
__VALUE SmartMemoryManager<__VALUE>::operator[](const key_type &key) const
{
	if (total_item == 0)
		throw(LengthError());
	check_key_existence(key);

	KEY_VALUE_CONTAINER *tmp = container;
	while (tmp != nullptr)
	{
		// match found
		if (tmp->key_code == key)
		{
			return tmp->value;
		}
		tmp = tmp->next;
	}
}

template <class __VALUE>
__VALUE SmartMemoryManager<__VALUE>::operator[](const int &index) const
{
	if (index >= total_item)
		throw(ArrayIndexError());

	if (index == 0)
		return first_value();
	if (index == total_item - 1)
		return last_value();

	KEY_VALUE_CONTAINER *tmp = container;
	for (int i = 1; i <= index; i++)
		tmp = tmp->next;
	return tmp->value;
}

template <class __VALUE>
void SmartMemoryManager<__VALUE>::for_each(void callback(value_type value)) const
{
	KEY_VALUE_CONTAINER *tmp = container;
	while(tmp != nullptr)
	{
		callback(tmp->value);
		tmp = tmp->next;
	}
}