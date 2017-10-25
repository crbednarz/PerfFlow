#include "stdafx.h"
#include "CppUnitTest.h"
#include "sampling/ProcessSample.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PerfFlow;

namespace PerfFlowTests
{


	TEST_CLASS(ProcessSampleTests)
	{

		TEST_METHOD(threadSamplesCanBeAdded)
		{
			ProcessSample sample;

			for (auto i = 0; i < ProcessSample::MaxThreads; i++)
			{
				sample.addThread();
				Assert::AreEqual(size_t(i + 1), sample.threadCount());
			}
		}


		TEST_METHOD(newThreadsAreNotTheSameReference)
		{
			ProcessSample sample;

			for (auto i = 0; i < ProcessSample::MaxThreads; i++)
			{
				auto& thread = sample.addThread();
				thread.push(StackFrame(i));
				Assert::AreEqual(size_t(1), thread.frameCount());
				Assert::AreEqual(size_t(i), thread.getFrame(0).instructionPointer());
			}
		}


		TEST_METHOD(newThreadSamplesAreEmpty)
		{
			ProcessSample sample;

			for (auto i = 0; i < ProcessSample::MaxThreads; i++)
			{
				auto& thread = sample.addThread();
				Assert::AreEqual(size_t(0), thread.frameCount());
			}
		}

		TEST_METHOD(canGetThread)
		{
			ProcessSample sample;

			for (auto i = 0; i < ProcessSample::MaxThreads; i++)
			{
				auto& thread = sample.addThread();
				thread.push(StackFrame(i));
			}

			for (size_t i = 0; i < ProcessSample::MaxThreads; i++)
			{
				auto& thread = sample.getThread(i);
				Assert::AreEqual(size_t(1), thread.frameCount());
				Assert::AreEqual(i, thread.getFrame(0).instructionPointer());
			}
		}

	};


}