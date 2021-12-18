#pragma once
#include <inttypes.h>
#include <malloc.h>
#include "HeapManager.h"
#include "FixedSizeAllocator.h"

extern HeapManager* pHeapManager;
extern FixedSizeAllocator* FSAs[3];

bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

void Collect();

void DestroyMemorySystem();

void* __cdecl malloc(size_t i_size);

void __cdecl free(void* i_ptr);

void* operator new(size_t i_size);

void operator delete(void* i_ptr);

void* operator new[](size_t i_size);

void operator delete[](void* i_ptr);