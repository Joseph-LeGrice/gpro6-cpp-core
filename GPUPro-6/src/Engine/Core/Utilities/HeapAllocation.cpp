#include "stdafx.h"
#include "HeapAllocation.h"

HeapAllocation::~HeapAllocation()
{
	Deallocate();
}

void HeapAllocation::Allocate(size_t size)
{
	Deallocate();
	m_size = size;
	m_allocPointer = malloc(size);
}

void HeapAllocation::Deallocate()
{
	if (m_allocPointer != nullptr)
	{
		free(m_allocPointer);
		m_allocPointer = nullptr;
		m_size = 0;
	}
}

size_t HeapAllocation::GetSize()
{
	return m_size;
}

void* HeapAllocation::GetPointer()
{
	return m_allocPointer;
}