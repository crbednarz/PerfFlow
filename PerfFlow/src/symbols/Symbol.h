#pragma once
#include <string>

namespace PerfFlow
{
class ProcessModule;


class Symbol
{
public:
	explicit Symbol(const std::string& name, const ProcessModule* processModule);

	const std::string& name() const;
	const ProcessModule& processModule() const;

private:
	std::string _name;
	const ProcessModule* _processModule;
};


}


inline const std::string& PerfFlow::Symbol::name() const
{
	return _name;
}


inline const PerfFlow::ProcessModule& PerfFlow::Symbol::processModule() const
{
	return *_processModule;
}
