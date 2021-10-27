#include "HeapManagerProxy.h"
#include <assert.h>
#include <stdio.h>

using namespace HeapManagerProxy;

inline bool IsPowerOfTwo(size_t n)
{
	if (n <= 0) return false;
	if (n == 1) return false;
	while (n != 1)
	{
		if (n % 2 == 0) n /= 2;
		else return false;
	}
	return true;
}

inline size_t AlignDown(size_t i_value, size_t i_align)
{
	assert(i_align);
	assert(IsPowerOfTwo(i_align));

	return i_value & ~(i_align - 1);
}

inline size_t AlignUp(size_t i_value, size_t i_align)
{
	assert(i_align);
	assert(IsPowerOfTwo(i_align));

	return (i_value + (i_align - 1)) & ~(i_align - 1);
}

HeapManager* HeapManagerProxy::CreateHeapManager(void* pHeapMemory, size_t sizeHeap, unsigned int numDescriptors)
{
	//initialize HeapManager
	HeapManager* pHeapManager = (HeapManager*)pHeapMemory;
	pHeapManager->pFreeList = (MemoryBlock*)(pHeapManager + 1);
	pHeapManager->pOutstandingAllocations = nullptr;
	pHeapManager->sizeHeap = sizeHeap - sizeof(HeapManager);

	//initialize pFreeList with the first free block
	pHeapManager->pFreeList->pBaseAddress = (void*)(pHeapManager->pFreeList + 1);
	pHeapManager->pFreeList->BlockSize = pHeapManager->sizeHeap - sizeof(MemoryBlock);
	pHeapManager->pFreeList->pNextBlock = nullptr;

	return pHeapManager;
}

void* HeapManagerProxy::alloc(HeapManager* pHeapManager, size_t sizeAlloc, const unsigned int alignment)
{
	MemoryBlock* pBlockIter = pHeapManager->pFreeList;

	size_t i_align = alignment;

	bool failed = false;

	while (true)
	{
		void* tailAddress = (void*)((char*)pBlockIter->pBaseAddress + pBlockIter->BlockSize);
		void* requiredMemoryBlockBeginAddress = (void*)(AlignDown((size_t)tailAddress - sizeAlloc, i_align) - sizeof(MemoryBlock));
		if (pBlockIter->BlockSize > sizeAlloc && requiredMemoryBlockBeginAddress > pBlockIter->pBaseAddress)
		{
			//create new allocated block
			MemoryBlock* pNewBlock = (MemoryBlock*)requiredMemoryBlockBeginAddress;
			pNewBlock->BlockSize = (size_t)tailAddress - (size_t)requiredMemoryBlockBeginAddress - sizeof(MemoryBlock);
			pNewBlock->pBaseAddress = (void*)(pNewBlock + 1);
			pNewBlock->pNextBlock = nullptr;

			//add new allocated block into the pOutstandingAllocations list
			if (pHeapManager->pOutstandingAllocations == nullptr) pHeapManager->pOutstandingAllocations = pNewBlock;
			else
			{
				MemoryBlock* pOutstandingAllocationsBlockIter = pHeapManager->pOutstandingAllocations;
				while (pOutstandingAllocationsBlockIter != nullptr)
				{
					if ((pOutstandingAllocationsBlockIter->pNextBlock == nullptr) || (pOutstandingAllocationsBlockIter->pNextBlock < pNewBlock))
					{
						pNewBlock->pNextBlock = pOutstandingAllocationsBlockIter->pNextBlock;
						pOutstandingAllocationsBlockIter->pNextBlock = pNewBlock;
						break;
					}
					else pOutstandingAllocationsBlockIter = pOutstandingAllocationsBlockIter->pNextBlock;
				}
			}

			//shrink the block size of the free block
			pBlockIter->BlockSize -= (size_t)tailAddress - (size_t)requiredMemoryBlockBeginAddress;

			return pNewBlock->pBaseAddress;
		}

		if (pBlockIter->pNextBlock) pBlockIter = pBlockIter->pNextBlock;
		else
		{
			return nullptr;
		}
	}
}

bool HeapManagerProxy::free(HeapManager* pHeapManager, void* pPtr)
{
	if (pHeapManager == nullptr) return false;

	MemoryBlock* pBlockIter = pHeapManager->pOutstandingAllocations;

	MemoryBlock* pLastBlockIter = nullptr;

	while (pBlockIter != nullptr)
	{
		if (pBlockIter->pBaseAddress == pPtr)
		{
			//excludes the block from the outstanding allocations list
			if (pLastBlockIter != nullptr) pLastBlockIter->pNextBlock = pBlockIter->pNextBlock;
			else pHeapManager->pOutstandingAllocations = pBlockIter->pNextBlock;


			//add the block into the free list
			if (pHeapManager->pFreeList == nullptr) pHeapManager->pFreeList = pBlockIter;
			else
			{
				MemoryBlock* pFreeListBlockIter = pHeapManager->pFreeList;
				while (pFreeListBlockIter != nullptr)
				{
					if ((pFreeListBlockIter->pNextBlock == nullptr) || (pFreeListBlockIter->pNextBlock < pBlockIter))
					{
						pBlockIter->pNextBlock = pFreeListBlockIter->pNextBlock;
						pFreeListBlockIter->pNextBlock = pBlockIter;
						return true;
					}
					else pFreeListBlockIter = pFreeListBlockIter->pNextBlock;
				}
			}
			
			return false;
		}
		else if (pBlockIter->pBaseAddress < pPtr) return false;
		else
		{
			pLastBlockIter = pBlockIter;
			pBlockIter = pBlockIter->pNextBlock;
		}
	}

	return false;
}

void HeapManagerProxy::Collect(HeapManager* pHeapManager)
{
	MemoryBlock* pFreeListBlockIter = pHeapManager->pFreeList;
	MemoryBlock* pLastFreeListBlockIter = nullptr;

	while (pFreeListBlockIter != nullptr && pFreeListBlockIter->pNextBlock != nullptr)
	{
		if (((size_t)pFreeListBlockIter->pNextBlock->pBaseAddress + pFreeListBlockIter->pNextBlock->BlockSize) == (size_t)pFreeListBlockIter)
		{
			pFreeListBlockIter->pNextBlock->BlockSize += (pFreeListBlockIter->BlockSize + sizeof(MemoryBlock));
			if (pLastFreeListBlockIter != nullptr) pLastFreeListBlockIter->pNextBlock = pFreeListBlockIter->pNextBlock;
			else pHeapManager->pFreeList = pFreeListBlockIter->pNextBlock;
		}
		else pLastFreeListBlockIter = pFreeListBlockIter;
		pFreeListBlockIter = pFreeListBlockIter->pNextBlock;
	}

}

void HeapManagerProxy::ShowFreeBlocks(HeapManager* pHeapManager)
{
	printf("FreeBlocks:\n");
	printf("pBaseAddress\tBlockSize\t\n");

	MemoryBlock* pFreeListBlockIter = pHeapManager->pFreeList;
	while (pFreeListBlockIter != nullptr)
	{
		printf("%llu\t%llu\t\n", (size_t)pFreeListBlockIter->pBaseAddress, pFreeListBlockIter->BlockSize);
		pFreeListBlockIter = pFreeListBlockIter->pNextBlock;
	}

}

void HeapManagerProxy::ShowOutstandingAllocations(HeapManager* pHeapManager)
{
	printf("OutstandingAllocations:\n");
	printf("pBaseAddress\tBlockSize\t\n");

	MemoryBlock* pOutstandingAllocationsBlockIter = pHeapManager->pOutstandingAllocations;
	while (pOutstandingAllocationsBlockIter != nullptr)
	{
		printf("%llu\t%llu\t\n", (size_t)pOutstandingAllocationsBlockIter->pBaseAddress, pOutstandingAllocationsBlockIter->BlockSize);
		pOutstandingAllocationsBlockIter = pOutstandingAllocationsBlockIter->pNextBlock;
	}
}

bool HeapManagerProxy::Contains(HeapManager* pHeapManager, void* pPtr)
{
	if (IsAllocated(pHeapManager, pPtr)) return true;
	else
	{
		if (pHeapManager == nullptr) return false;

		MemoryBlock* pBlockIter = pHeapManager->pFreeList;

		while (pBlockIter != nullptr)
		{
			if (pBlockIter->pBaseAddress == pPtr) return true;
			else if (pBlockIter->pBaseAddress < pPtr) return false;
			else pBlockIter = pBlockIter->pNextBlock;
		}
		return false;
	}
}

bool HeapManagerProxy::IsAllocated(HeapManager* pHeapManager, void* pPtr)
{
	if (pHeapManager == nullptr) return false;

	MemoryBlock* pBlockIter = pHeapManager->pOutstandingAllocations;

	while (pBlockIter != nullptr)
	{
		if (pBlockIter->pBaseAddress == pPtr) return true;
		else if (pBlockIter->pBaseAddress < pPtr) return false;
		else pBlockIter = pBlockIter->pNextBlock;
	}

	return false;
}

void HeapManagerProxy::Destroy(HeapManager* pHeapManager)
{
}