#pragma once
#include "BitArray.h"

class FixedSizeAllocator
{
private:
	size_t m_sizeBlock;
	size_t m_numBlocks;
	BitArray* m_pBitArray;
	void* m_pBaseAddress;

public:
	static FixedSizeAllocator* Create(void* pFixedSizeAllocatorMemory, size_t sizeBlock, size_t numBlocks);

	size_t GetSizeBlock() const;

	void* alloc() const;

	bool free(void* pPtr) const;

	bool Contains(void* pPtr) const;

	bool IsAllocated(void* pPtr) const;

	void* NextAddressOutOfIt() const;

	bool Destroy();
};

