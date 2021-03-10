#pragma once

class ImageButton;
class GameObject;
class GDIBitmap;

template <class T>
class ArrayList
{
public:
	ArrayList() : items(NULL), lenght(0), size(0), version(0)
	{}

	ArrayList(int capacity) : items(NULL), lenght(capacity), size(0), version(0)
	{
		items = new T[capacity];
	}

	virtual int Add(T item)
	{
		if (size == lenght)
			EnsureCapacity(size + 1);

		items[size] = item;

		version++;
		return size++;
	}

	virtual void Replace(int index, T item)
	{
		delete items[index];

		items[index] = item;

		version++;
	}

	virtual void Clear()
	{
		if (size > 0)
		{
			for(int i = 0; i < size; i++)
			{
				if (items[i] != NULL)
					delete items[i];

				items[i] = NULL;
			}

			size = 0;
		}

		version++;
	}

	virtual int IndexOf(T item) const
	{
		for (int i = 0; i < size; i++)
			if(items[i] == item)
				return i;

		return -1;
	}

	virtual void Remove(T obj)
	{
		int index = IndexOf(obj);
		if (index >= 0)
			RemoveAt(index);
	}

	virtual void RemoveAt(int index)
	{
		--size;
		delete items[index];
		items[index] = NULL;

		for(int i = index; i < size; i++)
			items[i] = items[i+1];

		items[size] = NULL;

		version++;
	}

	virtual void TrimToSize()
	{
		Capacity(size);
	}

	int Capacity() const
	{
		return lenght;
	}

	virtual void Capacity(int num)
	{
		if (num == lenght)
			return;

		if (num > 0)
		{
			T* destinationArray = new T[num];

			if (size > 0)
				for (int i = 0; i < size; i++)
					destinationArray[i] = items[i];

			if (items != NULL)
			{
				delete items;
				items = NULL;
			}

			items = destinationArray;
			lenght = num;
		}
		else
		{
			lenght = 4;

			if (size > 0)
				for (int i = 0; i < size; i++) {
					delete items[i];
					items[i] = NULL;
				}

			delete []items;
			items = NULL;

			items = new T[lenght];
		}
	}

	int Count()
	{
		return size;
	}

	virtual T operator[] (int num)
	{
		return items[num];
	}

	virtual ~ArrayList(void)
	{
		Clear();

		if (items != NULL)
		{
			delete []items;
			items = NULL;
		}
	}

private:
	T* items;
	int size;
	int version;
	int lenght;

	void EnsureCapacity(int min)
	{
		if (lenght < min)
		{
			int num = (lenght == 0) ? 4 : (lenght * 2);
			if (num < min)
				num = min;

			Capacity(num);
		}
	}

};

typedef ArrayList<GDIBitmap*>			GDImageList;
typedef ArrayList<ImageButton*>			ButtonList;
typedef ArrayList<GameObject*>			GameList;
