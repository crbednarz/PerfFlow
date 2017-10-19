#pragma once
#include <memory>
#include "WindowsIncludes.h"


namespace PerfFlow
{


	class Win32Handle
	{
	public:
		Win32Handle();
		explicit Win32Handle(HANDLE handle);

		HANDLE get() const;
		bool isValid() const;

	private:
		static void handleDestructor(HANDLE handle);

		std::unique_ptr<void, void(*)(HANDLE)> _handle;
	};


}

inline PerfFlow::Win32Handle::Win32Handle() :
	_handle(nullptr, handleDestructor)
{

}


inline PerfFlow::Win32Handle::Win32Handle(HANDLE handle) :
	_handle(handle, handleDestructor)
{
}


inline HANDLE PerfFlow::Win32Handle::get() const
{
	return _handle.get();
}


inline bool PerfFlow::Win32Handle::isValid() const
{
	return _handle != nullptr && _handle.get() != INVALID_HANDLE_VALUE;
}


inline void PerfFlow::Win32Handle::handleDestructor(HANDLE handle)
{
	if (handle != nullptr && handle != INVALID_HANDLE_VALUE)
		CloseHandle(handle);
}
