1. Put all the needed objects(HeapManager/FixedSizeAllocator/BitArray/BitArrayMemory) in the memory given by heapalloc.
Where: MemorySystem.cpp:9

2. Use static member functions to initialize heapmanager, bitarray, and fixedsizeallocator rather than constructor.
Where: HeapManager.h:22, BitArray.h:22, FixedSizeAllocator.h:13

3. Check if there are still outstanding allocations on destroying memory system.
Where: MemorySystem.cpp:24, HeapManager.cpp:218, FixedSizeAllocator.cpp:68

4. Validate the returns memory is a valid outstanding allocation from it block pool on freeing.
Where: MemorySystem.cpp:53/80/107, HeapManager.cpp:92, FixedSizeAllocator.cpp:32

5. Use _BitScanForward/_BitScanForward64 to get first set/clear bit in BitArray.
Where: BitArray.cpp:81/104

6. Collect and coalesce free blocks in attempt to create larger blocks in default HeapManager.
Where: HeapManager.cpp:139

7.Align address on allocating memory in default HeapManager.
Where: HeapManager.cpp:52

8.Avoid to use malloc/free/new/delete in code that implements memory systems.
Where: everywhere