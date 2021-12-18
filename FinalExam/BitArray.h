#pragma once
#include <stdint.h>

class BitArray
{
private:

#ifdef _WIN64
	typedef uint64_t t_BitData;
#else
	typedef uint32_t t_BitData;
#endif //_WIN64

	size_t bitsPerElement;

	size_t m_numBits;

	t_BitData* m_pBitData;
	size_t m_numBitData;

public:
	static BitArray* Create(void* pBitArrayMemory, size_t i_numBits, bool i_startClear = true);

	size_t SizeOfBitArray() const;

	bool AreAllBitsClear() const;

	bool IsBitSet(size_t i_bitNumber) const;

	void SetBit(size_t i_bitNumber);
	void ClearBit(size_t i_bitNumber);

	bool GetFirstClearBit(size_t& o_bitNumber) const;
	bool GetFirstSetBit(size_t& o_bitNumber) const;
};

