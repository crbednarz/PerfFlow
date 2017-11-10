#pragma once
#include <unordered_map>
#include <mutex>
#include <deque>
#include <typeindex>
#include <assert.h>


namespace PerfFlow
{


template <typename TKey, typename TEntity>
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


/// Simple dictionary used for sampling data such as modules or symbols.
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
	using Id = SamplingEntityId<TKey, TEntity>;

	SamplingEntityRepository();
	explicit SamplingEntityRepository(size_t initialCapacity);

	Id add(TKey key, const TEntity& entity);
	Id getId(TKey key) const;
	bool has(TKey key);

	const TEntity& get(Id id) const;

	/// Sets the type of data to be used for user-data, and clears out any existing user-data. 
	/// Only one type of user data may be active at any given time.
	template <typename TUserData>
	void setupUserData();

	/// Returns a reference to the user-data pointer for the given entry.
	/// setupUserData must be called at least once to initialize user data of the specified type.
	template <typename TUserData>
	TUserData*& userData(TKey key);

	/// Returns a reference to the user-data pointer for the given entry.
	/// setupUserData must be called at least once to initialize user data of the specified type.
	template <typename TUserData>
	TUserData*& userData(Id id);

	size_t count() const;

private:
	struct EntityWithUserData
	{
		EntityWithUserData(const TEntity& entity, void* userData);
		TEntity _entity;
		void* _userData;
	};

	std::unordered_map<TKey, Id> _entityDictionary;
	std::deque<EntityWithUserData> _entities;
	mutable std::mutex _mutex;
	std::type_index _userDataType;
};


}

template <typename TKey, typename TEntity>
PerfFlow::SamplingEntityId<TKey, TEntity> PerfFlow::SamplingEntityId<TKey, TEntity>::None = SamplingEntityId();


template <typename TKey, typename TEntity>
PerfFlow::SamplingEntityId<TKey, TEntity>::SamplingEntityId() :
	_index(~static_cast<uint32_t>(0))
{
}


template <typename TKey, typename TEntity>
PerfFlow::SamplingEntityId<TKey, TEntity>::SamplingEntityId(const uint32_t index) :
	_index(index)
{
}


template <typename TKey, typename TEntity>
bool PerfFlow::SamplingEntityId<TKey, TEntity>::operator==(const SamplingEntityId<TKey, TEntity>& rhs) const
{
	return _index == rhs._index;
}


template <typename TKey, typename TEntity>
bool PerfFlow::SamplingEntityId<TKey, TEntity>::operator!=(const SamplingEntityId<TKey, TEntity>& rhs) const
{
	return !(*this == rhs);
}


template <typename TKey, typename TEntity>
uint32_t PerfFlow::SamplingEntityId<TKey, TEntity>::index() const
{
	return _index;
}


template <typename TKey, typename TEntity>
PerfFlow::SamplingEntityRepository<TKey, TEntity>::SamplingEntityRepository() :
	_userDataType(typeid(void))
{
}


template <typename TKey, typename TEntity>
PerfFlow::SamplingEntityRepository<TKey, TEntity>::SamplingEntityRepository(size_t initialCapacity) :
	_entityDictionary(initialCapacity),
	_userDataType(typeid(void))
{
	_entities.reserve(initialCapacity);
}


template <typename TKey, typename TEntity>
typename PerfFlow::SamplingEntityRepository<TKey, TEntity>::Id PerfFlow::SamplingEntityRepository<TKey, TEntity>::add(TKey key, const TEntity& entity)
{
	assert(!has(key));

	EntityWithUserData repoItem(entity, nullptr);

	std::lock_guard<std::mutex> lockGuard(_mutex);

	_entities.push_back(repoItem);

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
	return _entities[id.index()]._entity;
}


template <typename TKey, typename TEntity>
template <typename TUserData>
void PerfFlow::SamplingEntityRepository<TKey, TEntity>::setupUserData()
{
	std::lock_guard<std::mutex> lockGuard(_mutex);

	for (auto& entity : _entities)
		entity._userData = nullptr;

	_userDataType = typeid(TUserData);
}


template <typename TKey, typename TEntity>
template <typename TUserData>
TUserData*& PerfFlow::SamplingEntityRepository<TKey, TEntity>::userData(TKey key)
{
	return userData<TUserData>(getId(key));
}


template <typename TKey, typename TEntity>
template <typename TUserData>
TUserData*& PerfFlow::SamplingEntityRepository<TKey, TEntity>::userData(Id id)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return reinterpret_cast<TUserData*&>(_entities[id.index()]._userData);
}


template <typename TKey, typename TEntity>
size_t PerfFlow::SamplingEntityRepository<TKey, TEntity>::count() const
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _entities.size();
}


template <typename TKey, typename TEntity>
PerfFlow::SamplingEntityRepository<TKey, TEntity>::EntityWithUserData::EntityWithUserData(const TEntity& entity, void* userData) :
	_entity(entity),
	_userData(userData)
{

}


namespace std
{
	template <typename TKey, typename TEntity>
	struct hash<PerfFlow::SamplingEntityId<TKey, TEntity>>
	{
		size_t operator()(const PerfFlow::SamplingEntityId<TKey, TEntity>& value) const noexcept
		{
			return hash<size_t>{}(value.index());
		}
	};
}
