#include "FixedSizeAllocator.h"

FixedSizeAllocator* FixedSizeAllocator::Create(void* pFixedSizeAllocatorMemory, size_t sizeBlock, size_t numBlocks)
{
	FixedSizeAllocator* pFixedSizeAllocator = static_cast<FixedSizeAllocator*>(pFixedSizeAllocatorMemory);

	pFixedSizeAllocator->m_sizeBlock = sizeBlock;
	pFixedSizeAllocator->m_numBlocks = numBlocks;

	pFixedSizeAllocator->m_pBitArray = BitArray::Create(static_cast<void*>(pFixedSizeAllocator + 1), pFixedSizeAllocator->m_numBlocks, true);
	pFixedSizeAllocator->m_pBaseAddress = static_cast<void*>(reinterpret_cast<char*>(pFixedSizeAllocator->m_pBitArray + 1) + pFixedSizeAllocator->m_pBitArray->SizeOfBitArray());

	return pFixedSizeAllocator;
}

size_t FixedSizeAllocator::GetSizeBlock() const
{
	return m_sizeBlock;
}

void* FixedSizeAllocator::alloc() const
{
	size_t bitNumber;
	if (m_pBitArray->GetFirstClearBit(bitNumber))
	{
		m_pBitArray->SetBit(bitNumber);
		return static_cast<void*>(static_cast<char*>(m_pBaseAddress) + bitNumber * m_sizeBlock);
	}
	else return nullptr;
}

bool FixedSizeAllocator::free(void* pPtr) const
{
	if (IsAllocated(pPtr))
	{
		m_pBitArray->ClearBit(static_cast<size_t>(static_cast<char*>(pPtr) - static_cast<char*>(m_pBaseAddress)) / m_sizeBlock);
		return true;
	}
	else return false;
}

bool FixedSizeAllocator::Contains(void* pPtr) const
{
	if ((pPtr >= m_pBaseAddress)
		&& (static_cast<size_t>(static_cast<char*>(pPtr) - static_cast<char*>(m_pBaseAddress)) < (m_sizeBlock * m_numBlocks))
		&& (static_cast<size_t>(static_cast<char*>(pPtr) - static_cast<char*>(m_pBaseAddress)) % m_sizeBlock == 0))
		return true;
	else return false;
}

bool FixedSizeAllocator::IsAllocated(void* pPtr) const
{
	if (Contains(pPtr))
	{
		if (Contains(pPtr) && m_pBitArray->IsBitSet(static_cast<size_t>(static_cast<char*>(pPtr) - static_cast<char*>(m_pBaseAddress)) / m_sizeBlock))
		{
			return true;
		}
	}
	return false;
}

void* FixedSizeAllocator::NextAddressOutOfIt() const
{
	return static_cast<void*>(static_cast<char*>(m_pBaseAddress) + m_sizeBlock * m_numBlocks);
}

bool FixedSizeAllocator::Destroy()
{
	if(m_pBitArray->AreAllBitsClear()) return true;
	else return false;
}
