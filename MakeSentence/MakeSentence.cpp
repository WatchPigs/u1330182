#include <stdlib.h>
#include <string.h>

inline void grow(char*& begin, size_t& usedSize, size_t& ownedSize)
{
	if (usedSize >= ownedSize)
	{
		ownedSize = static_cast<size_t>(ownedSize * 1.5);
		char* reallocedBegin = static_cast<char*>(realloc(begin, ownedSize));
		if (reallocedBegin) begin = reallocedBegin;
	}
}

char* MakeSentence(const char* strings[])
{
	char* begin;
	size_t usedSize;
	size_t ownedSize;

	begin = static_cast<char*>(malloc(1024));
	usedSize = 0;
	ownedSize = 1024;

	for (int i = 0; strings[i] != nullptr; i++)
	{
		for (const char* pChar = strings[i]; *pChar; pChar++)
		{
			grow(begin, usedSize, ownedSize);
			if (begin) *(begin + usedSize) = *pChar;
			usedSize++;
		}
		grow(begin, usedSize, ownedSize);
		if (begin) *(begin + usedSize) = ' ';
		usedSize++;
	}
	if (begin) *(begin + usedSize - 1) = '.';
	grow(begin, usedSize, ownedSize);
	if (begin) *(begin + usedSize) = NULL;
	usedSize++;

	char* pSentence = static_cast<char*>(malloc(usedSize));
	if (pSentence && begin) memcpy(pSentence, begin, usedSize);
	free(begin);

	return pSentence;
}