#include "stdafx.h"
#include "CppUnitTest.h"
#include "sampling/SamplerOutputQueue.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PerfFlow;

namespace PerfFlowTests
{


	TEST_CLASS(SamplerOutputQueueTests)
	{

		TEST_METHOD(canEnqueueUntilFull)
		{
			const size_t CAPACITY = 100;

			auto queue = std::make_unique<SamplerOutputQueue>(CAPACITY);
			auto sample = std::make_unique<ProcessSample>();
		
			Assert::AreEqual(CAPACITY, queue->capacity());

			for (auto i = 0; i < CAPACITY; i++)
				Assert::IsTrue(queue->tryEnqueue(*sample));
		
			Assert::IsFalse(queue->tryEnqueue(*sample));
		}

		TEST_METHOD(canDequeUntilEmpty)
		{

			const size_t CAPACITY = 100;

			auto queue = std::make_unique<SamplerOutputQueue>(CAPACITY);
			auto sample = std::make_unique<ProcessSample>();

			for (auto i = 0; i < CAPACITY; i++)
				Assert::IsTrue(queue->tryEnqueue(*sample));


			for (auto i = 0; i < CAPACITY; i++)
				Assert::IsTrue(queue->tryDequeue(*sample));
		
			Assert::IsFalse(queue->tryDequeue(*sample));
		}


		TEST_METHOD(canEnqueAndDequeTogether)
		{
			const size_t CAPACITY = 100;

			auto queue = std::make_unique<SamplerOutputQueue>(CAPACITY);
			auto sample = std::make_unique<ProcessSample>();

			for (auto i = 0; i < CAPACITY; i++)
			{
				for (auto enqueueIndex = 0; enqueueIndex < i; enqueueIndex++)
					Assert::IsTrue(queue->tryEnqueue(*sample));

				for (auto dequeueIndex = 0; dequeueIndex < i; dequeueIndex++)
					Assert::IsTrue(queue->tryDequeue(*sample));

				Assert::IsFalse(queue->tryDequeue(*sample));
			}

			Assert::IsTrue(queue->tryEnqueue(*sample));

			for (auto i = 0; i < CAPACITY - 1; i++)
			{
				for (auto enqueueIndex = 0; enqueueIndex <  i; enqueueIndex++)
					Assert::IsTrue(queue->tryEnqueue(*sample));
				
				for (auto dequeueIndex = 0; dequeueIndex < i; dequeueIndex++)
					Assert::IsTrue(queue->tryDequeue(*sample));
			}

			Assert::IsTrue(queue->tryDequeue(*sample));
			Assert::IsFalse(queue->tryDequeue(*sample));
		}
	};


}