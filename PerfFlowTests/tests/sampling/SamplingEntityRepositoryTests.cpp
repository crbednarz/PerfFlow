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

		TEST_METHOD(settingUserDataTypeResetsUserData)
		{
			MockRepository repo;
			repo.setupUserData<int>();
			auto entity = repo.add(1, "entity");
			int userData = 5;
			repo.userData<int>(entity) = &userData;

			Assert::AreEqual(&userData, repo.userData<int>(entity));

			repo.setupUserData<int>();

			Assert::AreEqual(static_cast<int*>(nullptr), repo.userData<int>(entity));
			
		}

	};


}