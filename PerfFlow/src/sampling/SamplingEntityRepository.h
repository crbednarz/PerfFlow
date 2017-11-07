#pragma once
#include <unordered_map>
#include <mutex>
#include <assert.h>


namespace PerfFlow
{


template <typename TKey, typename TEntity>
class SamplingEntityRepository
{
public:
	SamplingEntityRepository();

	const TEntity* add(TKey key, const TEntity& entity);
	const TEntity* tryGet(TKey key);
	bool has(TKey key);

	size_t count();

private:
	struct EntityWithUserData
	{
		EntityWithUserData(const TEntity& entity, void* userData);
		TEntity _entity;
		void* _userData;
	};

	std::unique_ptr<std::unordered_map<TKey, EntityWithUserData>> _entities;
	std::mutex _mutex;

};


}


template <typename TKey, typename TEntity>
const TEntity* PerfFlow::SamplingEntityRepository<TKey, TEntity>::tryGet(const TKey key)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	const auto it = _entities->find(key);

	if (it != _entities->end())
		return &it->second._entity;

	return nullptr;
}


template <typename TKey, typename TEntity>
bool PerfFlow::SamplingEntityRepository<TKey, TEntity>::has(const TKey key)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _entities->find(key) != _entities->end();
}


template <typename TKey, typename TEntity>
size_t PerfFlow::SamplingEntityRepository<TKey, TEntity>::count()
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _entities->size();
}


template <typename TKey, typename TEntity>
PerfFlow::SamplingEntityRepository<TKey, TEntity>::EntityWithUserData::EntityWithUserData(const TEntity& entity, void* userData) :
	_entity(entity),
	_userData(userData)
{
}


template <typename TKey, typename TEntity>
PerfFlow::SamplingEntityRepository<TKey, TEntity>::SamplingEntityRepository() :
	_entities(std::make_unique<std::unordered_map<TKey, EntityWithUserData>>())
{

}


template <typename TKey, typename TEntity>
const TEntity* PerfFlow::SamplingEntityRepository<TKey, TEntity>::add(const TKey key, const TEntity& entity)
{
	assert(!has(key));

	EntityWithUserData repoItem(entity, nullptr);

	std::lock_guard<std::mutex> lockGuard(_mutex);
	const auto it = _entities->insert(std::make_pair(key, repoItem));
	
	return &it.first->second._entity;
}
