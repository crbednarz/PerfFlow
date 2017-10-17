#include "stdafx.h"
#include "CppUnitTest.h"
#include "symbols/SymbolRepository.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace PerfFlow;

namespace PerfFlowTests
{


	TEST_CLASS(ThreadSampleTests)
	{

		TEST_METHOD(emptyOnConstruction)
		{
			SymbolRepository repo;

			Assert::AreEqual(size_t(0), repo.totalSymbols());
		}

	};


}