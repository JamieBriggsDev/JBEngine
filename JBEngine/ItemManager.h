#pragma once

#include <vector>

template <class T>
class ItemManager
{
private:
	std::vector<T*> m_items;
public:
	ItemManager() = default;
	~ItemManager() = default;
	bool AddItem(T* _item) {
		m_items.push_back(_item);
		return true;
	}
	T* GetItem(int _index) {
		return m_items[_index];
	}
	int Count()
	{
		return m_items.size();
	}

};

