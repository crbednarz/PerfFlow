#pragma once
#include <string>

namespace PerfFlow
{
class ProcessModule;


class Symbol
{
public:
	explicit Symbol(size_t address, const std::string& name, const ProcessModule* processModule);

	size_t address() const;
	const std::string& name() const;
	const ProcessModule& processModule() const;

private:
	size_t _address;
	std::string _name;
	const ProcessModule* _processModule;
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


inline const PerfFlow::ProcessModule& PerfFlow::Symbol::processModule() const
{
	return *_processModule;
}
