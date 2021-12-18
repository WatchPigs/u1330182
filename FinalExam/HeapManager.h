#pragma once
class HeapManager
{
private:

	struct MemoryBlock
	{
		void* pBaseAddress;
		size_t BlockSize;
		MemoryBlock* pNextBlock;
	};

	MemoryBlock* pFreeList;
	MemoryBlock* pOutstandingAllocations;
	size_t sizeHeap;

	inline bool IsPowerOfTwo(size_t n);

	inline size_t AlignDown(size_t i_value, size_t i_align);

public:
	static HeapManager* Create(void* pHeapMemory, size_t sizeHeap);

	void* alloc(size_t sizeAlloc, const unsigned int alignment = 4);

	bool free(void* pPtr);

	void Collect();

	void ShowFreeBlocks() const;

	void ShowOutstandingAllocations() const;

	bool Contains(void* pPtr) const;

	bool IsAllocated(void* pPtr) const;

	bool Destroy();
};

