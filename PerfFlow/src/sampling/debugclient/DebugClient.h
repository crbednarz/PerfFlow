#pragma once


#include "utilities/ComIncludes.h"
#include <vector>
#include "ComThreadSample.h"


namespace PerfFlow
{
class Process;


/// Wraps functionality of COM's IDebugClient and related classes.
class DebugClient
{
public:
	explicit DebugClient(const Process& process);

	void sample(std::vector<ComThreadSample>& outputCallstacks);

	bool isValid() const;

private:
	bool _isValid;
	ComPtr<IDebugClient> _client;
	ComPtr<IDebugControl> _control;
	ComPtr<IDebugSystemObjects> _systemObjects;

	std::vector<ULONG> _threadIds;

	static bool waitForClientToAttach(const ComPtr<IDebugControl>& debugControl);
};


}


inline bool PerfFlow::DebugClient::isValid() const
{
	return _isValid;
}
