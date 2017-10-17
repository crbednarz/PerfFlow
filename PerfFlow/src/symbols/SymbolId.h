#pragma once
#include <stdint.h>


namespace PerfFlow
{
	

class SymbolId
{
public:
	explicit SymbolId(size_t symbolAddress);

	size_t address() const;

private:
	size_t _address;
};


}


inline PerfFlow::SymbolId::SymbolId(size_t symbolAddress) :
	_address(symbolAddress)
{

}


inline size_t PerfFlow::SymbolId::address() const
{
	return _address;
}
