#pragma once

#include <vector>

template<typename T>

class Pool
{
protected:
	std::vector<T *> objects_;
	unsigned int numLive_;

	void removeAt_(size_t index);
public:
	Pool(unsigned int size);
	virtual ~Pool();

	const typename std::vector<T *>::const_iterator cbegin() const;
	const typename std::vector<T *>::const_iterator cend() const;

	void add(T *object);

	bool vacancy() const;
	bool empty() const;
};

template<typename T>
Pool<T>::Pool(unsigned int size) :
	objects_(size, nullptr),
	numLive_(0)
{}

template<typename T>
Pool<T>::~Pool()
{
	for (unsigned int i = 0; i < numLive_; i++)
	{
		delete objects_.at(i);
		objects_.at(i) = nullptr;
	}
}

template<typename T>
const typename std::vector<T *>::const_iterator Pool<T>::cbegin() const
{
	return objects_.cbegin();
}

template<typename T>
const typename std::vector<T *>::const_iterator Pool<T>::cend() const
{
	return objects_.cbegin() + numLive_;
}

template<typename T>
void Pool<T>::add(T *object)
{
	objects_.at(numLive_++) = object;
}

template<typename T>
bool Pool<T>::vacancy() const
{
	return numLive_ < objects_.size();
}

template<typename T>
bool Pool<T>::empty() const
{
	return numLive_ == 0;
}

template<typename T>
void Pool<T>::removeAt_(size_t index)
{
	numLive_--;

	delete objects_.at(index);
	objects_.at(index) = objects_.at(numLive_);
	objects_.at(numLive_) = nullptr;
}