#pragma once

namespace HeapManagerProxy
{
	struct MemoryBlock
	{
		void* pBaseAddress;
		size_t BlockSize;
		MemoryBlock* pNextBlock;
	};

	struct HeapManager
	{
		MemoryBlock* pFreeList;
		MemoryBlock* pOutstandingAllocations;
		size_t sizeHeap;
	};

	HeapManager * CreateHeapManager(void* pHeapMemory, size_t sizeHeap, unsigned int numDescriptors);

	void* alloc(HeapManager* pHeapManager, size_t sizeAlloc, const unsigned int alignment = 4);

	bool free(HeapManager* pHeapManager, void* pPtr);

	void Collect(HeapManager* pHeapManager);

	void ShowFreeBlocks(HeapManager* pHeapManager);

	void ShowOutstandingAllocations(HeapManager* pHeapManager);

	bool Contains(HeapManager* pHeapManager, void* pPtr);

	bool IsAllocated(HeapManager* pHeapManager, void* pPtr);

	void Destroy(HeapManager* pHeapManager);
}


