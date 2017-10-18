#pragma once
#include <string>

namespace PerfFlow
{
	

class Symbol
{
public:
	explicit Symbol(const std::string& name);

	const std::string& name() const;

private:
	std::string _name;

};


}


inline const std::string& PerfFlow::Symbol::name() const
{
	return _name;
}
