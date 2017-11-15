#pragma once
#include "ProcessModule.h"
#include "sampling/SamplingEntityRepository.h"
#include "sampling/SamplingEntityStorage.h"


namespace PerfFlow
{
	

using ModuleRepository = SamplingEntityRepository<size_t, ProcessModule>;
using ModuleId = ModuleRepository::Id;

template <typename T>
using ModuleStorage = SamplingEntityStorage<ProcessModule, T>;

}
