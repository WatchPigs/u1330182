#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#endif // _DEBUG

#include <stdio.h>
#include "MakeSentence.h"

void UnitTest();

int main(int i_argc, char** i_argl)
{
	char query[] = "Enter a word for the sentence, empty to end: ";
	char* pSentence = MakeSentenceByInput(query);

	printf("The Sentence is: %s\n", pSentence);

	free(pSentence);

	//UnitTest();

	return 0;
}

// This is only a simple unit test. 
void UnitTest()
{
	const char* strings[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	};

	char* pSentence = MakeSentence(strings);

	printf("(unit test)The Sentence is: %s", pSentence);

	free(pSentence);

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}