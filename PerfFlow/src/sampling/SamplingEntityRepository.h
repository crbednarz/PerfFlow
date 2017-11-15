#pragma once
#include "SamplingEntityId.h"
#include <unordered_map>
#include <mutex>
#include <deque>
#include <typeindex>
#include <assert.h>
#include "SamplingEntityStorage.h"


namespace PerfFlow
{


/// Simple dictionary used for sampling data such as modules or symbols.
/// Additionally, a single user-data pointer may be stored per entity to help track visualizer information relevant to the entity.
template <typename TKey, typename TEntity>
class SamplingEntityRepository
{
public:
	using Id = SamplingEntityId<TEntity>;

	SamplingEntityRepository() = default;
	explicit SamplingEntityRepository(size_t initialCapacity);

	Id add(TKey key, const TEntity& entity);
	Id getId(TKey key) const;
	bool has(TKey key);

	const TEntity& get(Id id) const;

	template <typename T>
	SamplingEntityStorage<TEntity, T> createStorage();

	size_t count() const;

private:
	std::unordered_map<TKey, Id> _entityDictionary;
	std::deque<TEntity> _entities;
	mutable std::mutex _mutex;
};


}

template <typename TKey, typename TEntity>
PerfFlow::SamplingEntityRepository<TKey, TEntity>::SamplingEntityRepository(size_t initialCapacity) :
	_entityDictionary(initialCapacity)
{
	_entities.reserve(initialCapacity);
}


template <typename TKey, typename TEntity>
typename PerfFlow::SamplingEntityRepository<TKey, TEntity>::Id PerfFlow::SamplingEntityRepository<TKey, TEntity>::add(TKey key, const TEntity& entity)
{
	assert(!has(key));

	std::lock_guard<std::mutex> lockGuard(_mutex);

	_entities.push_back(entity);

	Id id(static_cast<uint32_t>(_entities.size() - 1));
	_entityDictionary.insert(std::make_pair(key, id));

	return id;
}


template <typename TKey, typename TEntity>
typename PerfFlow::SamplingEntityRepository<TKey, TEntity>::Id PerfFlow::SamplingEntityRepository<TKey, TEntity>::getId(TKey key) const
{
	std::lock_guard<std::mutex> lockGuard(_mutex);

	const auto it = _entityDictionary.find(key);

	if (it != _entityDictionary.end())
		return it->second;

	return Id::None;
}


template <typename TKey, typename TEntity>
bool PerfFlow::SamplingEntityRepository<TKey, TEntity>::has(TKey key)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _entityDictionary.find(key) != _entityDictionary.end();
}


template <typename TKey, typename TEntity>
const TEntity& PerfFlow::SamplingEntityRepository<TKey, TEntity>::get(Id id) const
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _entities[id.index()];
}


template <typename TKey, typename TEntity>
template <typename T>
PerfFlow::SamplingEntityStorage<TEntity, T> PerfFlow::SamplingEntityRepository<TKey, TEntity>::createStorage()
{
	return SamplingEntityStorage<TEntity, T>();
}


template <typename TKey, typename TEntity>
size_t PerfFlow::SamplingEntityRepository<TKey, TEntity>::count() const
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _entities.size();
}
