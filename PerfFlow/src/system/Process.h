#pragma once


#include "utilities/WindowsIncludes.h"


namespace PerfFlow
{


// Wraps a native process ID.
class Process
{
public:
	using IdType = DWORD;

	explicit Process(IdType id);

	IdType id() const;

private:
	IdType _id;

};


}


inline PerfFlow::Process::IdType PerfFlow::Process::id() const
{
	return _id;
}