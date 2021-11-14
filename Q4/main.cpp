//Question:
//A function that returns true if a passed string is a palindrome(it's the same string forward or backward).
//	bool IsPalindrome(const char* i_pString);

#include <cstdio>

//Solution
bool IsPalindrome(const char* i_pString)
{
	const char* pLeft = i_pString;
	const char* pRight;
	for (pRight = i_pString; *(pRight + 1); pRight++);

	while (pLeft < pRight)
	{
		if (*pLeft != *pRight) return false;
		pLeft++;
		pRight--;
	}
	return true;
}

//Input Samples
int main()
{
	const char apple[] = "apple";
	printf("%s\n", IsPalindrome(apple) ? "true" : "false");
	const char hannah[] = "hannah";
	printf("%s\n", IsPalindrome(hannah) ? "true" : "false");
	const char testset[] = "testset";
	printf("%s\n", IsPalindrome(testset) ? "true" : "false");

	return 0;
}