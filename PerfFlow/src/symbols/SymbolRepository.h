#pragma once
#include "Symbol.h"
#include "sampling/SamplingEntityRepository.h"


namespace PerfFlow
{


using SymbolRepository = SamplingEntityRepository<size_t, Symbol>;
using SymbolId = SymbolRepository::Id;

}
