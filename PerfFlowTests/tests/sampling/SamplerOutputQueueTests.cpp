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
		TEST_METHOD(hasWorkingSampleWhenEmpty)
		{
			const size_t CAPACITY = 10;
			auto queue = std::make_unique<SamplerOutputQueue>(CAPACITY);

			Assert::IsTrue(queue->hasWorkingSample());
			
			for (size_t i = 0; i < CAPACITY; i++)
				queue->commit();
			Assert::IsFalse(queue->hasWorkingSample());

			for (size_t i = 0; i < CAPACITY; i++)
				queue->pop();
			Assert::IsTrue(queue->hasWorkingSample());
		}

		TEST_METHOD(canPeekWhenNotEmpty)
		{
			const size_t CAPACITY = 10;
			auto queue = std::make_unique<SamplerOutputQueue>(CAPACITY);

			Assert::IsFalse(queue->canPeek());

			queue->commit();
			Assert::IsTrue(queue->canPeek());

			queue->pop();
			Assert::IsFalse(queue->canPeek());
		}

		TEST_METHOD(canWriteAndReadFullQueue)
		{
			const size_t CAPACITY = 10;
			auto queue = std::make_unique<SamplerOutputQueue>(CAPACITY);
			
			for (size_t i = 0; i < CAPACITY; i++)
			{
				Assert::IsTrue(queue->hasWorkingSample());
				
				for (size_t threadIndex = 0; threadIndex < i; threadIndex++)
					queue->workingSample().addThread();
				
				queue->commit();
			}

			Assert::IsFalse(queue->hasWorkingSample());

			for (size_t i = 0; i < CAPACITY; i++)
			{
				Assert::IsTrue(queue->canPeek());
				Assert::AreEqual(i, queue->peek().threadCount());

				queue->pop();
			}

			Assert::IsFalse(queue->canPeek());
		}

		TEST_METHOD(samplesAreClearedAfterUse)
		{
			const size_t CAPACITY = 10;
			auto queue = std::make_unique<SamplerOutputQueue>(CAPACITY);

			for (size_t i = 0; i < CAPACITY; i++)
			{
				for (size_t threadIndex = 0; threadIndex < 10; threadIndex++)
					queue->workingSample().addThread();

				queue->commit();
			}

			for (size_t i = 0; i < CAPACITY; i++)
				queue->pop();

			queue->commit();

			Assert::AreEqual(size_t(0), queue->workingSample().threadCount());

		}
	};


}