#include "BitArray.h"
#include <vcruntime_string.h>
#include <intrin0.inl.h>

BitArray* BitArray::Create(void* pBitArrayMemory, size_t i_numBits, bool i_startClear)
{
	BitArray* pBitArray = static_cast<BitArray*>(pBitArrayMemory);

	pBitArray->m_pBitData = reinterpret_cast<t_BitData*>(pBitArray + 1);

	pBitArray->m_numBits = i_numBits;
	pBitArray->bitsPerElement = sizeof(t_BitData) * 8;

	if ((pBitArray->m_numBits) % (pBitArray->bitsPerElement) > 0) pBitArray->m_numBitData = i_numBits / pBitArray->bitsPerElement + 1;
	else pBitArray->m_numBitData = i_numBits / pBitArray->bitsPerElement;
	memset(pBitArray->m_pBitData, i_startClear ? 0 : -1, pBitArray->m_numBitData);

	return pBitArray;
}

size_t BitArray::SizeOfBitArray() const
{
	return sizeof(t_BitData) * m_numBitData;
}

bool BitArray::AreAllBitsClear() const
{
	size_t bitNumber;
	if (GetFirstSetBit(bitNumber)) return false;
	return true;
}

bool BitArray::IsBitSet(size_t i_bitNumber) const
{
	size_t bitDataNumber = i_bitNumber / bitsPerElement;
	size_t bitNumOnElement = i_bitNumber % bitsPerElement;

	const t_BitData* pBitData = m_pBitData + bitDataNumber;
	t_BitData mask = 1;
	mask <<= bitNumOnElement;
	mask = ~mask;

	if ((*pBitData | mask) == -1) return true;
	else return false;
}

void BitArray::SetBit(size_t i_bitNumber)
{
	size_t bitDataNumber = i_bitNumber / bitsPerElement;
	size_t bitNumOnElement = i_bitNumber % bitsPerElement;

	t_BitData* pBitData = m_pBitData + bitDataNumber;
	t_BitData mask = 1;
	mask <<= bitNumOnElement;

	*pBitData |= mask;
}

void BitArray::ClearBit(size_t i_bitNumber)
{
	size_t bitDataNumber = i_bitNumber / bitsPerElement;
	size_t bitNumOnElement = i_bitNumber % bitsPerElement;

	t_BitData* pBitData = m_pBitData + bitDataNumber;
	t_BitData mask = 1;
	mask <<= bitNumOnElement;
	mask = ~mask;

	*pBitData &= mask;
}

bool BitArray::GetFirstClearBit(size_t& o_bitNumber) const
{
	for (size_t i = 0; i < m_numBitData; i++)
	{
		if (*(m_pBitData + i) != -1)
		{
			t_BitData mask = ~*(m_pBitData + i);
			unsigned long index;
#ifdef _WIN64
			unsigned char found = _BitScanForward64(&index, mask);
#else
			unsigned char found = _BitScanForward(&index, mask);
#endif //_WIN64
			if (found && (i < m_numBitData - 1 || index < m_numBits % bitsPerElement))
			{
				o_bitNumber = index + i * bitsPerElement;
				return true;
			}
		}
	}
	return false;
}

bool BitArray::GetFirstSetBit(size_t& o_bitNumber) const
{
	for (size_t i = 0; i < m_numBitData; i++)
	{
		if (*(m_pBitData + i) != 0)
		{
			t_BitData mask = *(m_pBitData + i);
			unsigned long index;
#ifdef _WIN64
			unsigned char found = _BitScanForward64(&index, mask);
#else
			unsigned char found = _BitScanForward(&index, mask);
#endif //_WIN64
			if (found && (i < m_numBitData - 1 || index < m_numBits % bitsPerElement))
			{
				o_bitNumber = index + i * bitsPerElement;
				return true;
			}
		}
	}
	return false;
}
