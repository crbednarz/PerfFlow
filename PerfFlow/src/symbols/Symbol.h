#pragma once
#include <string>
#include "ModuleRepository.h"


namespace PerfFlow
{
class ProcessModule;


class Symbol
{
public:
	explicit Symbol(size_t address, const std::string& name, ModuleId moduleId);

	size_t address() const;
	const std::string& name() const;
	ModuleId moduleId() const;

private:
	size_t _address;
	std::string _name;
	ModuleId _moduleId;
};


}


inline size_t PerfFlow::Symbol::address() const
{
	return _address;
}


inline const std::string& PerfFlow::Symbol::name() const
{
	return _name;
}


inline PerfFlow::ModuleId PerfFlow::Symbol::moduleId() const
{
	return _moduleId;
}
