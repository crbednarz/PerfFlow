#pragma once
#include <string>


namespace PerfFlow
{
	

class ProcessModule
{
public:
	ProcessModule(const std::string& name, size_t address, size_t size, size_t index);

	const std::string& name() const;
	size_t address() const;
	size_t size() const;
	size_t index() const;

private:
	std::string _name;
	size_t _address;
	size_t _size;
	size_t _index;

};


}


inline const std::string& PerfFlow::ProcessModule::name() const
{
	return _name;
}


inline size_t PerfFlow::ProcessModule::address() const
{
	return _address;
}


inline size_t PerfFlow::ProcessModule::size() const
{
	return _size;
}


inline size_t PerfFlow::ProcessModule::index() const
{
	return _index;
}

