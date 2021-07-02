#include"memory.h"

uintptr_t memory::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}
	return addr;
}

uintptr_t memory::pattern_scan(const char* mod, const char* sig)
{
	MODULEINFO modInfo;
	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(mod), &modInfo, sizeof(MODULEINFO));
	uintptr_t startAddress = (uintptr_t)GetModuleHandleA(mod);
	uintptr_t endAddress = (startAddress + (uintptr_t)modInfo.SizeOfImage);
	const char* pat = sig;
	uintptr_t firstMatch = 0;
	for (uintptr_t pCur = startAddress; pCur < endAddress; pCur++) {
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == ('\?') || *(BYTE*)pCur == get_byte(pat)) {
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return firstMatch;
			if (*(PWORD)pat == ('\?\?') || *(PBYTE)pat != ('\?')) pat += 3;
			else pat += 2;
		}
		else {
			pat = sig;
			firstMatch = 0;
		}
	}
	return NULL;
}