#include "stdafx.h"
#include "CppUnitTest.h"
#include "sampling\SamplingEntityRepository.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PerfFlow;

namespace PerfFlowTests
{
	using MockRepository = SamplingEntityRepository<size_t, std::string>;

	TEST_CLASS(SamplingEntityRepositoryTests)
	{

		TEST_METHOD(emptyOnConstruction)
		{
			MockRepository repo;

			Assert::AreEqual(size_t(0), repo.count());
		}

		TEST_METHOD(canAddSymbols)
		{
			MockRepository repo;

			for (size_t i = 0; i < 10; i++)
			{
				const auto result = repo.add(i, std::to_string(i));

				Assert::AreEqual(i + 1, repo.count());
				Assert::AreEqual(std::to_string(i), *result);
			}
		}

		TEST_METHOD(canRetrieveSymbol)
		{
			MockRepository repo;

			for (size_t i = 0; i < 10; i++)
				repo.add(i, std::to_string(i));

			for (size_t i = 0; i < 10; i++)
			{
				auto symbol = repo.tryGet(i);
				Assert::IsNotNull(symbol);
			}
		}

	};


}