#include "HeapManagerProxy.h"

using namespace HeapManagerProxy;

HeapManager* HeapManagerProxy::CreateHeapManager(void* pHeapMemory, size_t sizeHeap, unsigned int numDescriptors)
{
	return nullptr;
}

void* HeapManagerProxy::alloc(HeapManager* pHeapManager, size_t sizeAlloc, const unsigned int alignment)
{
	return nullptr;
}

bool HeapManagerProxy::free(HeapManager* pHeapManager, void* pPtr)
{
	return false;
}

void HeapManagerProxy::ShowFreeBlocks(HeapManager* pHeapManager)
{
}

void HeapManagerProxy::ShowOutstandingAllocations(HeapManager* pHeapManager)
{
}

bool HeapManagerProxy::Contains()
{
	return false;
}

bool HeapManagerProxy::IsAllocated()
{
	return false;
}
