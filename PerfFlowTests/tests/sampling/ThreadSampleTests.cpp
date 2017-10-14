#include "stdafx.h"
#include "CppUnitTest.h"
#include "sampling/ThreadSample.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PerfFlow;

namespace PerfFlowTests
{


	TEST_CLASS(ThreadSampleTests)
	{

		TEST_METHOD(canBeCleared)
		{
			ThreadSample sample;

			for (auto i = 0; i < 16; i++)
				sample.push(StackFrame(0));

			Assert::AreEqual(static_cast<size_t>(16), sample.frameCount());

			sample.clear();

			Assert::AreEqual(static_cast<size_t>(0), sample.frameCount());
		}


		TEST_METHOD(pushedDataIsRetained)
		{
			const size_t FRAMES_TO_TEST = 16;
			ThreadSample sample;

			for (auto i = 0; i < FRAMES_TO_TEST; i++)
				sample.push(StackFrame(i));

			for (size_t i = 0; i < FRAMES_TO_TEST; i++)
				Assert::AreEqual(i, sample.getFrame(i).instructionPointer());
		}
	};


}