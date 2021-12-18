#include "HeapManager.h"
#include <assert.h>
#include <stdio.h>

inline bool HeapManager::IsPowerOfTwo(size_t n)
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

inline size_t HeapManager::AlignDown(size_t i_value, size_t i_align)
{
	assert(i_align);
	assert(IsPowerOfTwo(i_align));

	return i_value & ~(i_align - 1);
}

HeapManager* HeapManager::Create(void* pHeapMemory, size_t sizeHeap)
{
	//initialize HeapManager
	HeapManager* pHeapManager = static_cast<HeapManager*>(pHeapMemory);
	pHeapManager->pFreeList = reinterpret_cast<MemoryBlock*>(pHeapManager + 1);
	pHeapManager->pOutstandingAllocations = nullptr;
	pHeapManager->sizeHeap = sizeHeap - sizeof(HeapManager);

	//initialize pFreeList with the first free block
	pHeapManager->pFreeList->pBaseAddress = static_cast<void*>(pHeapManager->pFreeList + 1);
	pHeapManager->pFreeList->BlockSize = pHeapManager->sizeHeap - sizeof(MemoryBlock);
	pHeapManager->pFreeList->pNextBlock = nullptr;

	return pHeapManager;
}

void* HeapManager::alloc(size_t sizeAlloc, const unsigned int alignment)
{
	MemoryBlock* pBlockIter = pFreeList;

	size_t i_align = alignment;

	bool failed = false;

	while (true)
	{
		void* tailAddress = static_cast<void*>(static_cast<char*>(pBlockIter->pBaseAddress) + pBlockIter->BlockSize);
		void* requiredMemoryBlockBeginAddress = reinterpret_cast<void*>(AlignDown(reinterpret_cast<size_t>(tailAddress) - sizeAlloc, i_align) - sizeof(MemoryBlock));
		if (pBlockIter->BlockSize > sizeAlloc && requiredMemoryBlockBeginAddress > pBlockIter->pBaseAddress)
		{
			//create new allocated block
			MemoryBlock* pNewBlock = static_cast<MemoryBlock*>(requiredMemoryBlockBeginAddress);
			pNewBlock->BlockSize = reinterpret_cast<size_t>(tailAddress) - reinterpret_cast<size_t>(requiredMemoryBlockBeginAddress) - sizeof(MemoryBlock);
			pNewBlock->pBaseAddress = static_cast<void*>(pNewBlock + 1);
			pNewBlock->pNextBlock = nullptr;

			//add new allocated block into the pOutstandingAllocations list
			if (pOutstandingAllocations == nullptr) pOutstandingAllocations = pNewBlock;
			else
			{
				MemoryBlock* pOutstandingAllocationsBlockIter = pOutstandingAllocations;
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
			pBlockIter->BlockSize -= reinterpret_cast<size_t>(tailAddress) - reinterpret_cast<size_t>(requiredMemoryBlockBeginAddress);

			return pNewBlock->pBaseAddress;
		}

		if (pBlockIter->pNextBlock) pBlockIter = pBlockIter->pNextBlock;
		else
		{
			return nullptr;
		}
	}
}

bool HeapManager::free(void* pPtr)
{
	if (this == nullptr) return false;

	MemoryBlock* pBlockIter = pOutstandingAllocations;

	MemoryBlock* pLastBlockIter = nullptr;

	while (pBlockIter != nullptr)
	{
		if (pBlockIter->pBaseAddress == pPtr)
		{
			//excludes the block from the outstanding allocations list
			if (pLastBlockIter != nullptr) pLastBlockIter->pNextBlock = pBlockIter->pNextBlock;
			else pOutstandingAllocations = pBlockIter->pNextBlock;


			//add the block into the free list
			if (pFreeList == nullptr) pFreeList = pBlockIter;
			else
			{
				MemoryBlock* pFreeListBlockIter = pFreeList;
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

void HeapManager::Collect()
{
	MemoryBlock* pFreeListBlockIter = pFreeList;
	MemoryBlock* pLastFreeListBlockIter = nullptr;

	while (pFreeListBlockIter != nullptr && pFreeListBlockIter->pNextBlock != nullptr)
	{
		if ((reinterpret_cast<size_t>(pFreeListBlockIter->pNextBlock->pBaseAddress) + pFreeListBlockIter->pNextBlock->BlockSize) == reinterpret_cast<size_t>(pFreeListBlockIter))
		{
			pFreeListBlockIter->pNextBlock->BlockSize += (pFreeListBlockIter->BlockSize + sizeof(MemoryBlock));
			if (pLastFreeListBlockIter != nullptr) pLastFreeListBlockIter->pNextBlock = pFreeListBlockIter->pNextBlock;
			else pFreeList = pFreeListBlockIter->pNextBlock;
		}
		else pLastFreeListBlockIter = pFreeListBlockIter;
		pFreeListBlockIter = pFreeListBlockIter->pNextBlock;
	}
}

void HeapManager::ShowFreeBlocks() const
{
	printf("FreeBlocks:\n");
	printf("pBaseAddress\tBlockSize\t\n");

	MemoryBlock* pFreeListBlockIter = pFreeList;
	while (pFreeListBlockIter != nullptr)
	{
		printf("%zu\t%zu\t\n", reinterpret_cast<size_t>(pFreeListBlockIter->pBaseAddress), pFreeListBlockIter->BlockSize);
		pFreeListBlockIter = pFreeListBlockIter->pNextBlock;
	}
}

void HeapManager::ShowOutstandingAllocations() const
{
	printf("OutstandingAllocations:\n");
	printf("pBaseAddress\tBlockSize\t\n");

	MemoryBlock* pOutstandingAllocationsBlockIter = pOutstandingAllocations;
	while (pOutstandingAllocationsBlockIter != nullptr)
	{
		printf("%zu\t%zu\t\n", reinterpret_cast<size_t>(pOutstandingAllocationsBlockIter->pBaseAddress), pOutstandingAllocationsBlockIter->BlockSize);
		pOutstandingAllocationsBlockIter = pOutstandingAllocationsBlockIter->pNextBlock;
	}
}

bool HeapManager::Contains(void* pPtr) const
{
	if (IsAllocated(pPtr)) return true;
	else
	{
		if (this == nullptr) return false;

		MemoryBlock* pBlockIter = pFreeList;

		while (pBlockIter != nullptr)
		{
			if (pBlockIter->pBaseAddress == pPtr) return true;
			else if (pBlockIter->pBaseAddress < pPtr) return false;
			else pBlockIter = pBlockIter->pNextBlock;
		}
		return false;
	}
}

bool HeapManager::IsAllocated(void* pPtr) const
{
	if (this == nullptr) return false;

	MemoryBlock* pBlockIter = pOutstandingAllocations;

	while (pBlockIter != nullptr)
	{
		if (pBlockIter->pBaseAddress == pPtr) return true;
		else if (pBlockIter->pBaseAddress < pPtr) return false;
		else pBlockIter = pBlockIter->pNextBlock;
	}

	return false;
}

bool HeapManager::Destroy()
{
	if (pOutstandingAllocations == nullptr) return true;
	else return false;
}
