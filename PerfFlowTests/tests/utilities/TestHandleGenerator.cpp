#include "stdafx.h"
#include "TestHandleGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int PerfFlowTests::TestHandleGenerator::_nextHandle = 6;
std::unordered_set<int> PerfFlowTests::TestHandleGenerator::_handles;


int PerfFlowTests::TestHandleGenerator::allocate()
{
	auto handle = _nextHandle++;
	Assert::IsTrue(_handles.end() == _handles.find(handle), L"New handle must not already be in the handle table");
	_handles.insert(handle);

	return handle;
}


void PerfFlowTests::TestHandleGenerator::destroy(int handle)
{
	Assert::IsTrue(_handles.end() != _handles.find(handle), L"Destroyed handle must have been allocated.");
	_handles.erase(handle);
}
