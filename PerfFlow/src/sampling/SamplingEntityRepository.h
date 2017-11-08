#pragma once
#include <unordered_map>
#include <mutex>
#include <deque>
#include <typeindex>
#include <assert.h>


namespace PerfFlow
{


/// Simple dictionary used for sampling data such as modules or symbols.
/// To avoid additional lookups all returned pointers will only be invalidated at the end of its owning repository's life.
/// Additionally, a single user-data pointer may be stored per entity to help track visualizer information relevant to the entity.
template <typename TKey, typename TEntity>
class SamplingEntityRepository
{
public:
	/* In regards to user data, there was a common pattern occuring on the visualizer side where visualizers would need to store their own dictionary 
	 * of SymbolId -> Symbol. This ended up not being very suitable for the volumes of data that were being processed. To counter this, a single pointer
	 * may be stored per entity. This can be accessed via the pointer to the entity at almost no cost. This also solved the issue of tracking first-time
	 * appearances of a particular symbol inside of a visualizer, as user-data defaults to nullptr after setupUserData();
	 */

	SamplingEntityRepository();

	const TEntity* add(TKey key, const TEntity& entity);
	const TEntity* tryGet(TKey key);
	bool has(TKey key);

	/// Sets the type of data to be used for user-data, and clears out any existing user-data. 
	/// Only one type of user data may be active at any given time.
	template <typename TUserData>
	void setupUserData();

	/// Returns a reference to the user-data pointer for the given entry.
	/// setupUserData must be called at least once to initialize user data of the specified type.
	template <typename TUserData>
	TUserData*& userData(TKey key);

	/// Returns a reference to the user-data pointer for the given entity.
	/// setupUserData must be called at least once to initialize user data of the specified type.
	template <typename TUserData>
	TUserData*& userData(const TEntity* entity);

	size_t count();

private:
	struct EntityWithUserData
	{
		EntityWithUserData(const TEntity& entity, void* userData);
		TEntity _entity;
		void* _userData;
	};

	std::unordered_map<TKey, EntityWithUserData*> _entityDictionary;
	std::unique_ptr<std::deque<EntityWithUserData>> _entities;
	std::mutex _mutex;
	std::type_index _userDataType;

};


}


template <typename TKey, typename TEntity>
const TEntity* PerfFlow::SamplingEntityRepository<TKey, TEntity>::tryGet(const TKey key)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	const auto it = _entityDictionary.find(key);

	if (it != _entityDictionary.end())
		return &it->second->_entity;

	return nullptr;
}


template <typename TKey, typename TEntity>
bool PerfFlow::SamplingEntityRepository<TKey, TEntity>::has(const TKey key)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _entityDictionary.find(key) != _entityDictionary.end();
}


template <typename TKey, typename TEntity>
template <typename TUserData>
void PerfFlow::SamplingEntityRepository<TKey, TEntity>::setupUserData()
{
	std::lock_guard<std::mutex> lockGuard(_mutex);

	for (auto& entity : *_entities)
		entity._userData = nullptr;

	_userDataType = typeid(TUserData);
}


template <typename TKey, typename TEntity>
template <typename TUserData>
TUserData*& PerfFlow::SamplingEntityRepository<TKey, TEntity>::userData(TKey key)
{
	return userData<TUserData>(tryGet(key));
}


template <typename TKey, typename TEntity>
template <typename TUserData>
TUserData*& PerfFlow::SamplingEntityRepository<TKey, TEntity>::userData(const TEntity* entity)
{
	assert(_userDataType == typeid(TUserData));
	assert(entity != nullptr);

	auto entry = reinterpret_cast<const EntityWithUserData*>(entity);
	auto& userData = reinterpret_cast<TUserData* const &>(entry->_userData);

	// const_cast here because we're not actually modifying entity, but rather the memory next to it.
	return const_cast<TUserData*&>(userData);
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
	_entities(std::make_unique<std::deque<EntityWithUserData>>()),
	_userDataType(typeid(void))
{

}


template <typename TKey, typename TEntity>
const TEntity* PerfFlow::SamplingEntityRepository<TKey, TEntity>::add(const TKey key, const TEntity& entity)
{
	assert(!has(key));

	EntityWithUserData repoItem(entity, nullptr);

	std::lock_guard<std::mutex> lockGuard(_mutex);

	_entities->push_back(repoItem);

	_entityDictionary.insert(std::make_pair(key, &_entities->back()));
	
	return &_entities->back()._entity;
}
