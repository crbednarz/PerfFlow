#pragma once
#include <stdint.h>
#include <functional>


namespace PerfFlow
{
	

class SymbolId
{
public:
	explicit SymbolId(size_t symbolAddress);
	bool operator ==(const SymbolId &rhs) const;
	bool operator !=(const SymbolId &rhs) const;

	size_t address() const;

private:
	size_t _address;
};


}

namespace std
{
	template<> 
	struct hash<PerfFlow::SymbolId>
	{
		size_t operator()(const PerfFlow::SymbolId& value) const noexcept
		{
			return hash<size_t>{}(value.address());
		}
	};
}


inline PerfFlow::SymbolId::SymbolId(size_t symbolAddress) :
	_address(symbolAddress)
{

}


inline bool PerfFlow::SymbolId::operator==(const SymbolId& rhs) const
{
	return _address == rhs._address;
}


inline bool PerfFlow::SymbolId::operator!=(const SymbolId& rhs) const
{
	return !(*this == rhs);
}


inline size_t PerfFlow::SymbolId::address() const
{
	return _address;
}
