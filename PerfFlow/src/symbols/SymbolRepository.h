#pragma once
#include "Symbol.h"
#include "sampling/SamplingEntityRepository.h"
#include "sampling/SamplingEntityStorage.h"


namespace PerfFlow
{


using SymbolRepository = SamplingEntityRepository<size_t, Symbol>;
using SymbolId = SymbolRepository::Id;

template <typename T>
using SymbolStorage = SamplingEntityStorage<Symbol, T>;

}
