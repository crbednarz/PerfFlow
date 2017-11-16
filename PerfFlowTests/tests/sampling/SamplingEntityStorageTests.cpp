#include "stdafx.h"
#include "CppUnitTest.h"
#include "sampling/SamplingEntityStorage.h"
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PerfFlow;

namespace PerfFlowTests
{


	TEST_CLASS(SamplingEntityStorageTests)
	{
		struct SamplingEntity
		{
			int _value;
		};
		
		using Storage = SamplingEntityStorage<SamplingEntity, int>;

		TEST_METHOD(isEmptyOnAllocation)
		{
			Storage storage;

			Assert::AreEqual(size_t(0), storage.count());
			Assert::AreEqual(size_t(0), storage.capacity());
		}

		TEST_METHOD(addingItemsIncreasesCount)
		{
			Storage storage;
			std::vector<int> items{ 5, 2, 0, 100, 8 };

			size_t count = 0;
			for (auto value : items)
			{
				storage.create(Storage::Id(value), value * 2);
				Assert::AreEqual(++count, storage.count());
			}
		}

		TEST_METHOD(addingItemsIncreasesCapacity)
		{
			Storage storage;
			std::vector<int> items{ 5, 2, 0, 100, 8 };

			size_t capacity = 0;
			for (auto value : items)
			{
				storage.create(Storage::Id(value), value * 2);

				capacity = std::max(capacity, size_t(value + 1));
				Assert::AreEqual(capacity, storage.capacity());
			}
		}

		TEST_METHOD(createdItemsAreCorrectlyStored)
		{
			Storage storage;
			const auto& constStorage = storage;
			std::vector<int> items{ 5, 2, 0, 100, 8 };

			for (auto value : items)
				storage.create(Storage::Id(value), value * 2);
			
			for (auto value : items)
			{
				Assert::AreEqual(value * 2, storage[Storage::Id(value)]);
				Assert::AreEqual(value * 2, constStorage[Storage::Id(value)]);
			}
		}

		TEST_METHOD(canTestIfItemIsSet)
		{
			Storage storage;
			std::vector<int> items{ 5, 2, 0, 100, 8 };

			for (auto value : items)
				storage.create(Storage::Id(value), value * 2);

			for (auto value : items)
			{
				Assert::IsTrue(storage.has(Storage::Id(value)));
				Assert::IsFalse(storage.has(Storage::Id(value + 1)));
			}
		}

		TEST_METHOD(canIterate)
		{
			Storage storage;
			std::vector<int> items{ 5, 2, 3, 100, 8 };
			std::vector<int> sortedItems{ 2, 3, 5, 8, 100 };
			for (auto value : items)
				storage.create(Storage::Id(value), value * 2);

			int i = 0;
			for (auto item : storage)
			{
				Assert::AreEqual(sortedItems[i++] * 2, item);
			}
		}


		TEST_METHOD(canConstIterate)
		{
			Storage storage;
			std::vector<int> items{ 5, 2, 3, 100, 8 };
			std::vector<int> sortedItems{ 2, 3, 5, 8, 100 };
			for (auto value : items)
				storage.create(Storage::Id(value), value * 2);

			const auto& constStorage = storage;

			int i = 0;
			for (const auto& item : constStorage)
			{
				Assert::AreEqual(item, sortedItems[i++] * 2);
			}
		}

		TEST_METHOD(canAssignInRangeLoop)
		{
			Storage storage;
			std::vector<int> items{ 5, 2, 3, 100, 8 };
			std::vector<int> sortedItems{ 2, 3, 5, 8, 100 };
			for (auto value : items)
				storage.create(Storage::Id(value), value * 2);

			int i = 0;
			for (auto& item : storage)
				item = i++;

			i = 0;
			for (auto& it : storage)
				Assert::AreEqual(i++, it);
		}

	};


}