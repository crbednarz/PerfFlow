#pragma once
#include <iterator>
#include <deque>
#include "SamplingEntityId.h"


namespace PerfFlow
{
	

template <typename TContainerType>
class SamplingEntityStorageIterator
{
public:
	using StoredType = typename std::remove_cv<typename std::remove_reference<decltype(TContainerType()[0]._value)>::type>::type;

	template <typename T, typename TEnabled = void>
	struct ConstCopyHelper
	{
		using ReferenceType = StoredType&;
		using PointerType = StoredType*;
	};

	template <typename T>
	struct ConstCopyHelper<T, typename std::enable_if<std::is_const_v<T>>::type>
	{
		using ReferenceType = const StoredType&;
		using PointerType = const StoredType*;
	};


	using Id = SamplingEntityId<StoredType>;

	using value_type = StoredType;
	using reference = typename ConstCopyHelper<TContainerType>::ReferenceType;
	using pointer = typename ConstCopyHelper<TContainerType>::PointerType;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = ptrdiff_t;

	explicit SamplingEntityStorageIterator(TContainerType* storage, size_t index);

	bool operator==(SamplingEntityStorageIterator& rhs) const;
	bool operator!=(SamplingEntityStorageIterator& rhs) const;

	SamplingEntityStorageIterator operator++();
	SamplingEntityStorageIterator operator++(int);

	reference operator*() const;
	pointer operator->() const;
	Id id() const;

private:
	TContainerType* _storage;
	size_t _index;
};


}


template <typename TContainerType>
PerfFlow::SamplingEntityStorageIterator<TContainerType>::SamplingEntityStorageIterator(TContainerType* storage, const size_t index) :
	_storage(storage),
	_index(index)
{

}


template <typename TContainerType>
bool PerfFlow::SamplingEntityStorageIterator<TContainerType>::operator==(SamplingEntityStorageIterator& rhs) const
{
	return _storage == rhs._storage && _index == rhs._index;
}


template <typename TContainerType>
bool PerfFlow::SamplingEntityStorageIterator<TContainerType>::operator!=(SamplingEntityStorageIterator& rhs) const
{
	return !(*this == rhs);
}


template <typename TContainerType>
PerfFlow::SamplingEntityStorageIterator<TContainerType> PerfFlow::SamplingEntityStorageIterator<TContainerType>::operator++()
{
	if (_index >= _storage->size())
		return *this;

	_index++;

	while (_index < _storage->size())
	{
		if ((*_storage)[_index]._isSet)
			return *this;
		_index++;
	}

	return *this;
}


template <typename TContainerType>
PerfFlow::SamplingEntityStorageIterator<TContainerType> PerfFlow::SamplingEntityStorageIterator<TContainerType>::operator++(int)
{
	auto previousState = *this;
	++(*this);
	return previousState;
}


template <typename TContainerType>
typename PerfFlow::SamplingEntityStorageIterator<TContainerType>::reference PerfFlow::SamplingEntityStorageIterator<TContainerType>::operator*() const
{
	return (*_storage)[_index]._value;
}


template <typename TContainerType>
typename PerfFlow::SamplingEntityStorageIterator<TContainerType>::pointer PerfFlow::SamplingEntityStorageIterator<TContainerType>::operator->() const
{
	return (*_storage)[_index]._value;
}


template <typename TContainerType>
typename PerfFlow::SamplingEntityStorageIterator<TContainerType>::Id PerfFlow::SamplingEntityStorageIterator<TContainerType>::id() const
{
	return Id(_index);
}

