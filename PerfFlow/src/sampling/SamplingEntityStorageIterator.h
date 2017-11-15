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
	using RawStoredType = typename std::remove_reference<decltype(TContainerType()[0]._value)>::type;

	template <typename T, typename TEnabled = void>
	struct ConstCopyHelper
	{
		using Type = RawStoredType;
	};

	template <typename T>
	struct ConstCopyHelper<T, typename std::enable_if<std::is_const_v<T>>::type>
	{
		using Type = const RawStoredType;
	};

	using StoredType = typename ConstCopyHelper<TContainerType>::Type;

	using CvFreeStoredType = typename std::remove_cv<StoredType>::type;
	using Id = SamplingEntityId<CvFreeStoredType>;

	struct Pair
	{
		Pair(Id id, StoredType& entity);

		const Id _id;
		StoredType& _value;
	};

	class PairPointer
	{
	public:
		PairPointer(Id id, StoredType& entity);

		Pair* operator->();

	private:
		Pair _pair;
	};

	using value_type = Pair;
	using reference = Pair;
	using pointer = PairPointer;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = ptrdiff_t;

	explicit SamplingEntityStorageIterator(TContainerType* storage, size_t index);

	bool operator==(SamplingEntityStorageIterator& rhs) const;
	bool operator!=(SamplingEntityStorageIterator& rhs) const;

	SamplingEntityStorageIterator operator++();
	SamplingEntityStorageIterator operator++(int);

	reference operator*() const;
	pointer operator->() const;

private:
	TContainerType* _storage;
	size_t _index;
};


}


template <typename TContainerType>
PerfFlow::SamplingEntityStorageIterator<TContainerType>::Pair::Pair(Id id, StoredType& entity) :
	_id(id),
	_value(entity)
{
}


template <typename TContainerType>
PerfFlow::SamplingEntityStorageIterator<TContainerType>::PairPointer::PairPointer(Id id, StoredType& entity) :
	_pair(id, entity)
{
}


template <typename TContainerType>
typename PerfFlow::SamplingEntityStorageIterator<TContainerType>::Pair* PerfFlow::SamplingEntityStorageIterator<TContainerType>::PairPointer::operator->()
{
	return &_pair;
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
	return Pair(Id(static_cast<uint32_t>(_index)), (*_storage)[_index]._value);
}


template <typename TContainerType>
typename PerfFlow::SamplingEntityStorageIterator<TContainerType>::pointer PerfFlow::SamplingEntityStorageIterator<TContainerType>::operator->() const
{
	return PairPointer(Id(static_cast<uint32_t>(_index)), (*_storage)[_index]._value);
}

