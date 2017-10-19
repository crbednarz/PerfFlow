#pragma once


#include "utilities/WindowsIncludes.h"
#include <vector>


namespace PerfFlow
{


// Wraps a native process ID.
class Process
{
public:
	using IdType = DWORD;

	Process();
	explicit Process(IdType id);
	Process(IdType id, std::wstring name);

	IdType id() const;
	const std::wstring& name() const;

	static std::vector<Process> CreateProcessList();

private:
	IdType _id;
	std::wstring _name;

};


}


inline PerfFlow::Process::IdType PerfFlow::Process::id() const
{
	return _id;
}


inline const std::wstring& PerfFlow::Process::name() const
{
	return _name;
}