#pragma once
#include <stdint.h>


namespace PerfFlow
{
	

template <typename TEntity>
class SamplingEntityId
{
public:
	static SamplingEntityId None;

	SamplingEntityId();
	explicit SamplingEntityId(uint32_t index);
	bool operator ==(const SamplingEntityId &rhs) const;
	bool operator !=(const SamplingEntityId &rhs) const;

	uint32_t index() const;

private:
	uint32_t _index;
};


}


template <typename TEntity>
PerfFlow::SamplingEntityId<TEntity> PerfFlow::SamplingEntityId<TEntity>::None = SamplingEntityId();


template <typename TEntity>
PerfFlow::SamplingEntityId<TEntity>::SamplingEntityId() :
	_index(~static_cast<uint32_t>(0))
{
}


template <typename TEntity>
PerfFlow::SamplingEntityId<TEntity>::SamplingEntityId(const uint32_t index) :
	_index(index)
{
}


template <typename TEntity>
bool PerfFlow::SamplingEntityId<TEntity>::operator==(const SamplingEntityId<TEntity>& rhs) const
{
	return _index == rhs._index;
}


template <typename TEntity>
bool PerfFlow::SamplingEntityId<TEntity>::operator!=(const SamplingEntityId<TEntity>& rhs) const
{
	return !(*this == rhs);
}


template <typename TEntity>
uint32_t PerfFlow::SamplingEntityId<TEntity>::index() const
{
	return _index;
}

namespace std
{
	template <typename TEntity>
	struct hash<PerfFlow::SamplingEntityId<TEntity>>
	{
		size_t operator()(const PerfFlow::SamplingEntityId<TEntity>& value) const noexcept
		{
			return hash<size_t>{}(value.index());
		}
	};
}
