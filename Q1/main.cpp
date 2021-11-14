//Question:
//Detect if a linked list is circular.
//	bool IsCircular(LinkNode * i_pRoot);
//	You'll need to define what a LinkNode is.

#include <cstdio>
#include <crtdbg.h>

struct LinkNode
{
	LinkNode* next;
};


//Solution
bool IsCircular(LinkNode* i_pRoot)
{
	LinkNode* slow = i_pRoot;
	LinkNode* fast = i_pRoot;
	while (fast->next && fast->next->next)
	{
		if (fast->next == slow || fast->next->next == slow) return true;
		fast = fast->next->next;
		slow = slow->next;
	}
	return false;
}

//Input Samples

LinkNode* Create0LikeCircularLinkedList(LinkNode* nodeList[])
{
	for (int i = 0; i < 10; i++)
	{
		nodeList[i] = new LinkNode;
		if (i > 0)
		{
			nodeList[i - 1]->next = nodeList[i];
		}
	}
	nodeList[9]->next = nodeList[0];

	return nodeList[0];
}

LinkNode* Create6LikeCircularLinkedList(LinkNode* nodeList[])
{
	for (int i = 0; i < 10; i++)
	{
		nodeList[i] = new LinkNode;
		if (i > 0)
		{
			nodeList[i - 1]->next = nodeList[i];
		}
	}
	nodeList[9]->next = nodeList[3];

	return nodeList[0];
}

LinkNode* CreateUncircularLinkedList(LinkNode* nodeList[])
{
	for (int i = 0; i < 10; i++)
	{
		nodeList[i] = new LinkNode;
		if (i > 0)
		{
			nodeList[i - 1]->next = nodeList[i];
		}
	}
	nodeList[9]->next = nullptr;

	return nodeList[0];
}

void DeleteLinkedList(LinkNode* nodeList[])
{
	for (int i = 0; i < 10; i++) delete nodeList[i];
}



int main()
{
	LinkNode* nodeList[10];

	printf("%s\n", IsCircular(CreateUncircularLinkedList(nodeList)) ? "true" : "false");
	DeleteLinkedList(nodeList);
	printf("%s\n", IsCircular(Create0LikeCircularLinkedList(nodeList)) ? "true" : "false");
	DeleteLinkedList(nodeList);
	printf("%s\n", IsCircular(Create6LikeCircularLinkedList(nodeList)) ? "true" : "false");
	DeleteLinkedList(nodeList);

	_CrtDumpMemoryLeaks();

	return 0;
}