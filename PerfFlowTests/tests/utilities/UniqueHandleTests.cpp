#include "stdafx.h"
#include "CppUnitTest.h"
#include "utilities/UniqueHandle.h"
#include "TestHandleGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PerfFlow;

namespace PerfFlowTests
{

	
TEST_CLASS(UniqueHandleTests)
{
	using TestHandle = UniqueHandle<int, TestHandleGenerator::destroy, TestHandleGenerator::INVALID_HANDLE>;


	TEST_METHOD(handlesAreReleased)
	{
		{
			TestHandle handle(TestHandleGenerator::allocate());
			Assert::AreEqual(static_cast<size_t>(1), TestHandleGenerator::remainingHandles(), L"A single handle should exist after first allocation.");
		}

		Assert::AreEqual(static_cast<size_t>(0), TestHandleGenerator::remainingHandles(), L"No handles should exist after leaving handle's scope.");
	}


	TEST_METHOD(handlesShouldBeMoveable)
	{
		{
			TestHandle sourceHandle(TestHandleGenerator::allocate());
			auto destinationHandle = std::move(sourceHandle);

			Assert::IsFalse(sourceHandle.isValid(), L"Source handle should not be valid after move.");
			Assert::IsTrue(destinationHandle.isValid(), L"Destination handle should be valid after move.");
		}

		Assert::AreEqual(static_cast<size_t>(0), TestHandleGenerator::remainingHandles(), L"No handles should exist after handle has been destroyed.");
	}


	TEST_METHOD(releasedHandlesAreNotValid)
	{
		TestHandle handle(TestHandleGenerator::allocate());
		Assert::IsTrue(handle.isValid(), L"Allocated handle should be valid");
		
		auto rawHandle = handle.release();
		Assert::IsFalse(handle.isValid(), L"Released handle should no longer be valid.");

		TestHandleGenerator::destroy(rawHandle);
		Assert::AreEqual(static_cast<size_t>(0), TestHandleGenerator::remainingHandles(), L"No handles should exist after handle has been destroyed.");
	}


	TEST_METHOD(handlesCanBeReset)
	{
		TestHandle handleA(TestHandleGenerator::allocate());
		TestHandle handleB(TestHandleGenerator::allocate());

		Assert::AreEqual(static_cast<size_t>(2), TestHandleGenerator::remainingHandles(), L"Two handles should exist after two allocations.");

		handleA.reset(handleB.release());
		Assert::AreEqual(static_cast<size_t>(1), TestHandleGenerator::remainingHandles(), L"One handle should exist after reseting one.");

		handleA.reset();
		Assert::AreEqual(static_cast<size_t>(0), TestHandleGenerator::remainingHandles(), L"No handles should remain after resetting both.");
	}


};


}