#pragma once
#include "ProcessModule.h"
#include "sampling/SamplingEntityRepository.h"


namespace PerfFlow
{
	

using ModuleRepository = SamplingEntityRepository<size_t, ProcessModule>;


}
