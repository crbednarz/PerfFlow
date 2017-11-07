#pragma once
#include "Symbol.h"
#include "SymbolId.h"
#include "sampling/SamplingEntityRepository.h"


namespace PerfFlow
{


using SymbolRepository = SamplingEntityRepository<SymbolId, Symbol>;


}
