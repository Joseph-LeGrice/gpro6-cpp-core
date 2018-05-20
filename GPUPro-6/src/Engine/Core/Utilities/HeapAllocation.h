#pragma once

class HeapAllocation
{
public:
	~HeapAllocation();

	void Allocate(size_t size);
	void Deallocate();

	size_t GetSize();
	void* GetPointer();

private:
	size_t m_size = 0;
	void* m_allocPointer = nullptr;
};