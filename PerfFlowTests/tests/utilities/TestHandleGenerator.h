#pragma once
#include <unordered_set>

namespace PerfFlowTests
{
	

class TestHandleGenerator
{
public:
	static const int INVALID_HANDLE = 5;

	TestHandleGenerator() = delete;

	static int allocate();
	static void destroy(int handle);

	static size_t remainingHandles();


private:
	static std::unordered_set<int> _handles;
	static int _nextHandle;

};


}


inline size_t PerfFlowTests::TestHandleGenerator::remainingHandles()
{
	return _handles.size();
}