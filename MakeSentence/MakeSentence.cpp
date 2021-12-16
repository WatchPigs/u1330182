#include <stdlib.h>
#include <stdio.h>
#include <cstdio>

inline void grow(char*& begin, size_t& usedSize, size_t& ownedSize)
{
	if (usedSize >= ownedSize)
	{
		ownedSize = static_cast<size_t>(ownedSize * 1.5);
		char* reallocedBegin = static_cast<char*>(malloc(ownedSize));
		if (reallocedBegin) for (int i = 0; i < usedSize; i++) *(reallocedBegin + i) = *(begin + i);
		free(begin);
		begin = reallocedBegin;
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
	if (pSentence && begin) for (int i = 0; i < usedSize; i++) *(pSentence + i) = *(begin + i);
	free(begin);

	return pSentence;
}

char* MakeSentenceByInput(const char query[])
{
	char* begin;
	size_t usedSize;
	size_t ownedSize;

	begin = static_cast<char*>(malloc(1024));
	usedSize = 0;
	ownedSize = 1024;

	while (true)
	{
		printf("%s", query);
		char buffer[100];
		gets_s(buffer);

		if (buffer[0] == '\0') break;

		for (const char* pChar = buffer; *pChar; pChar++)
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
	if (pSentence && begin) for (int i = 0; i < usedSize; i++) *(pSentence + i) = *(begin + i);
	free(begin);

	return pSentence;
}