#include "MemorySystem.h"
#include <stdio.h>
#include <windows.h>
#include <debugapi.h>

HeapManager* pHeapManager;
FixedSizeAllocator* FSAs[3];

bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	FSAs[0] = FixedSizeAllocator::Create(i_pHeapMemory, 16, 100);
	FSAs[1] = FixedSizeAllocator::Create(FSAs[0]->NextAddressOutOfIt(), 32, 200);
	FSAs[2] = FixedSizeAllocator::Create(FSAs[1]->NextAddressOutOfIt(), 96, 400);
	pHeapManager = HeapManager::Create(FSAs[2]->NextAddressOutOfIt(), i_sizeHeapMemory - (static_cast<char*>(FSAs[2]->NextAddressOutOfIt()) - static_cast<char*>(i_pHeapMemory)));

	return true;
}

void Collect()
{
	pHeapManager->Collect();
}

void DestroyMemorySystem()
{
	bool b_clear = true;

	for (int i = 0; i < 3; i++)
	{
		if (!FSAs[i]->Destroy()) b_clear = false;
		FSAs[i] = nullptr;
	}

	if (!pHeapManager->Destroy()) b_clear = false;
	pHeapManager = nullptr;

#if defined(_DEBUG)
	if(!b_clear) OutputDebugString(L"there are still outstanding allocations on destroying.\n");
#endif // _DEBUG
}

void* __cdecl malloc(size_t i_size)
{
	printf("malloc %zu\n", i_size);

	for (int i = 0; i < 3; i++)
	{
		if (i_size <= FSAs[i]->GetSizeBlock()) return FSAs[i]->alloc();
	}
	return pHeapManager->alloc(i_size, 4);
}

void __cdecl free(void* i_ptr)
{
	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));

	for (int i = 0; i < 3; i++)
	{
		if (FSAs[i]->free(i_ptr)) return;
	}
	if (pHeapManager->free(i_ptr)) return;

#if defined(_DEBUG)
	OutputDebugString(L"Free failed\n");
#endif // _DEBUG
	return;
}

void* operator new(size_t i_size)
{
	printf("new %zu\n", i_size);

	for (int i = 0; i < 3; i++)
	{
		if (i_size <= FSAs[i]->GetSizeBlock()) return FSAs[i]->alloc();
	}
	return pHeapManager->alloc(i_size, 4);
}

void operator delete(void* i_ptr)
{
	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));

	for (int i = 0; i < 3; i++)
	{
		if (FSAs[i]->free(i_ptr)) return;
	}
	if (pHeapManager->free(i_ptr)) return;

#if defined(_DEBUG)
	OutputDebugString(L"Delete failed\n");
#endif // _DEBUG
	return;
}

void* operator new[](size_t i_size)
{
	printf("new [] %zu\n", i_size);

	for (int i = 0; i < 3; i++)
	{
		if (i_size <= FSAs[i]->GetSizeBlock()) return FSAs[i]->alloc();
	}
	return pHeapManager->alloc(i_size, 4);
}

void operator delete [](void* i_ptr)
{
	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));

	for (int i = 0; i < 3; i++)
	{
		if (FSAs[i]->free(i_ptr)) return;
	}
	if (pHeapManager->free(i_ptr)) return;

#if defined(_DEBUG)
	OutputDebugString(L"Delete failed\n");
#endif // _DEBUG
	return;
}