#pragma once
#include "ComIncludes.h"
#include <cassert>


namespace PerfFlow
{
	
/// Wrapper class for several COM methods to allow for better debugging via asserts.
class ComHelper
{
public:
	ComHelper() = delete;

	/// Equivalent to COM's FAILED macro. Returns true if result is a failure. 
	static bool failed(HRESULT result);

	/// Equivalent to COM'S SUCCEEDED macro. Returns true if result is a success. 
	static bool succeeded(HRESULT result);


private:
	static const bool ASSERT_ON_RESULT_FAILURE = true;

};


}


inline bool PerfFlow::ComHelper::failed(HRESULT result)
{
	if (ASSERT_ON_RESULT_FAILURE)
		assert(SUCCEEDED(result));

	return FAILED(result);
}


inline bool PerfFlow::ComHelper::succeeded(HRESULT result)
{
	if (ASSERT_ON_RESULT_FAILURE)
		assert(SUCCEEDED(result));
	
	return SUCCEEDED(result);
}
