#include "stdafx.h"
#include "CppUnitTest.h"
#include "symbols/ModuleRepository.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PerfFlow;

namespace PerfFlowTests
{


	TEST_CLASS(ThreadSampleTests)
	{

		TEST_METHOD(emptyOnConstruction)
		{
			ModuleRepository repo;

			Assert::AreEqual(size_t(0), repo.count());
		}

		TEST_METHOD(canAddSymbols)
		{
			ModuleRepository repo;

			for (size_t i = 0; i < 10; i++)
			{
				repo.add(std::to_string(i), i, 1, i);

				Assert::AreEqual(i + 1, repo.count());
			}
		}

		TEST_METHOD(canRetrieveSymbol)
		{
			ModuleRepository repo;

			for (size_t i = 0; i < 10; i++)
				repo.add(std::to_string(i), i, 1, i);

			for (size_t i = 0; i < 10; i++)
			{
				auto symbol = repo.tryGetAtAddress(i);
				Assert::IsNotNull(symbol);
			}
		}

	};


}