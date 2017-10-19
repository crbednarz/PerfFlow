#include "stdafx.h"
#include "Process.h"
#include <tlhelp32.h>
#include <memory>
#include "utilities/Win32Handle.h"


PerfFlow::Process::Process() :
	_id(0)
{
}


PerfFlow::Process::Process(IdType id) :
	_id(id)
{

}


PerfFlow::Process::Process(IdType id, std::wstring name) :
	_id(id),
	_name(name)
{

}


std::vector<PerfFlow::Process> PerfFlow::Process::CreateProcessList()
{
	Win32Handle handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD, 0));
	std::vector<Process> processList;

	PROCESSENTRY32 processEntry = { 0 };
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	auto firstItem = true;
	while ((firstItem ? Process32First : Process32Next)(handle.get(), &processEntry))
	{
		firstItem = false;

		processList.push_back(Process(processEntry.th32ProcessID, processEntry.szExeFile));

		processEntry.dwSize = sizeof(PROCESSENTRY32);
	}

	return processList;
}
