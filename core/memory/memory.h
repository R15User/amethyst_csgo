#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <Psapi.h>


#define in_range(x,a,b)   (x >= a && x <= b)
#define get_bits( x )    (in_range((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (in_range(x,'0','9') ? x - '0' : 0))
#define get_byte( x )    (get_bits(x[0]) << 4 | get_bits(x[1]))

namespace memory
{
	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
	uintptr_t pattern_scan(const char* mod, const char* sig);

	template<typename func_type>
	__forceinline static func_type call_virtual(void* ppClass, int index) {
		int* pVTable = *(int**)ppClass;
		int dwAddress = pVTable[index];
		return (func_type)(dwAddress);
	}
};