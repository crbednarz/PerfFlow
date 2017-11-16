#pragma once
#include "SamplingEntityId.h"
#include "SamplingEntityStorageIterator.h"
#include <deque>
#include <assert.h>


namespace PerfFlow
{
	

/// Additional per-entity storage for SamplingEntityRepository
template <typename TEntity, typename TValue>
class SamplingEntityStorage
{
private:
	struct OptionalValue
	{
		OptionalValue();
		TValue _value;
		bool _isSet;
	};

public:
	using Id = SamplingEntityId<TEntity>;
	using iterator = SamplingEntityStorageIterator<std::deque<OptionalValue>, TEntity>;
	using const_iterator = SamplingEntityStorageIterator<const std::deque<OptionalValue>, TEntity>;

	SamplingEntityStorage();

	void create(Id id, TValue value);
	bool has(Id id);

	size_t count() const;
	size_t capacity() const;

	TValue& operator[](Id id);
	const TValue& operator[](Id id) const;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

private:
	std::deque<OptionalValue> _storage;
	size_t _count;

	void ensureCapacityForId(Id id);
	size_t firstSetIndex() const;
};


}


template <typename TEntity, typename TValue>
PerfFlow::SamplingEntityStorage<TEntity, TValue>::OptionalValue::OptionalValue() :
	_value(),
	_isSet(false)
{
}


template <typename TEntity, typename TValue>
PerfFlow::SamplingEntityStorage<TEntity, TValue>::SamplingEntityStorage() :
	_count(0)
{

}


template <typename TEntity, typename TValue>
void PerfFlow::SamplingEntityStorage<TEntity, TValue>::create(Id id, TValue value)
{
	assert(id != Id::None);

	ensureCapacityForId(id);

	_storage[id.index()]._value = value;
	_storage[id.index()]._isSet = true;
	_count++;
}


template <typename TEntity, typename TValue>
bool PerfFlow::SamplingEntityStorage<TEntity, TValue>::has(Id id)
{
	if (id == Id::None || id.index() >= _storage.size())
		return false;

	return _storage[id.index()]._isSet;
}


template <typename TEntity, typename TValue>
size_t PerfFlow::SamplingEntityStorage<TEntity, TValue>::count() const
{
	return _count;
}


template <typename TEntity, typename TValue>
size_t PerfFlow::SamplingEntityStorage<TEntity, TValue>::capacity() const
{
	return _storage.size();
}


template <typename TEntity, typename TValue>
TValue& PerfFlow::SamplingEntityStorage<TEntity, TValue>::operator[](Id id)
{
	assert(id != Id::None);
	assert(id.index() < _storage.size());
	assert(_storage[id.index()]._isSet);

	return _storage[id.index()]._value;
}


template <typename TEntity, typename TValue>
const TValue& PerfFlow::SamplingEntityStorage<TEntity, TValue>::operator[](Id id) const
{
	assert(id != Id::None);
	assert(id.index() < _storage.size());
	assert(_storage[id.index()]._isSet);

	return _storage[id.index()]._value;
}


template <typename TEntity, typename TValue>
typename PerfFlow::SamplingEntityStorage<TEntity, TValue>::iterator PerfFlow::SamplingEntityStorage<TEntity, TValue>::begin()
{
	return iterator(&_storage, firstSetIndex());
}


template <typename TEntity, typename TValue>
typename PerfFlow::SamplingEntityStorage<TEntity, TValue>::iterator PerfFlow::SamplingEntityStorage<TEntity, TValue>::end()
{
	return iterator(&_storage, _storage.size());
}


template <typename TEntity, typename TValue>
typename PerfFlow::SamplingEntityStorage<TEntity, TValue>::const_iterator PerfFlow::SamplingEntityStorage<TEntity, TValue>::begin() const
{
	return cbegin();
}


template <typename TEntity, typename TValue>
typename PerfFlow::SamplingEntityStorage<TEntity, TValue>::const_iterator PerfFlow::SamplingEntityStorage<TEntity, TValue>::end() const
{
	return cend();
}


template <typename TEntity, typename TValue>
typename PerfFlow::SamplingEntityStorage<TEntity, TValue>::const_iterator PerfFlow::SamplingEntityStorage<TEntity, TValue>::cbegin() const
{
	return const_iterator(&_storage, firstSetIndex());
}


template <typename TEntity, typename TValue>
typename PerfFlow::SamplingEntityStorage<TEntity, TValue>::const_iterator PerfFlow::SamplingEntityStorage<TEntity, TValue>::cend() const
{
	return const_iterator(&_storage, _storage.size());
}


template <typename TEntity, typename TValue>
void PerfFlow::SamplingEntityStorage<TEntity, TValue>::ensureCapacityForId(Id id)
{
	while (id.index() >= _storage.size())
		_storage.push_back(OptionalValue());
}


template <typename TEntity, typename TValue>
size_t PerfFlow::SamplingEntityStorage<TEntity, TValue>::firstSetIndex() const
{
	size_t i;

	for (i = 0;i < _storage.size(); i++)
	{
		if (_storage[i]._isSet)
			return i;
	}

	return i;
}

