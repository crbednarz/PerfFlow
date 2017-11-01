#pragma once
#include "SymbolId.h"
#include "Symbol.h"
#include <unordered_map>
#include <mutex>


namespace PerfFlow
{
class ProcessModule;


class SymbolRepository
{
public:
	SymbolRepository() = default;

	void add(SymbolId id, const std::string& name, const ProcessModule* processModule = nullptr);
	const Symbol* tryGet(SymbolId id);
	bool has(SymbolId id);
	size_t count();

private:
	std::unordered_map<SymbolId, Symbol> _symbols;
	std::mutex _mutex;

};


}
