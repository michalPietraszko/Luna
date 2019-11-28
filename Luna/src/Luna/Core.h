#pragma once

#ifdef LN_PLATFORM_WINDOWS
	#define not !
	#define and &&
	#define or || 
	
	#ifdef LN_BUILD_DLL
		#define LUNA_API __declspec(dllexport)
	#else
		#define LUNA_API __declspec(dllimport)
	#endif
#else
	#error Luna only supports Windows!
#endif

#ifdef LN_ENABLE_ASSERTS
	#define LN_ASSERT(x, ...)                                        /
		{ if(!(x)) { LN_ERROR("Assertion failed: {0}", __VA_ARGS__); /
			__debugbreak();}}
	#define LN_CORE_ASSERT(x, ...)                                        /
		{ if(!(x)) { LN_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); /
			__debugbreak();}}
#else 
	#define LN_ASSERT(x, ...)
	#define LN_CORE_ASSERT(X, ...)
#endif

#define BIT(x) (1 << x)