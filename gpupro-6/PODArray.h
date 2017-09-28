#pragma once

#include <vector>
#include <type_traits>

template<typename T>
struct PODArray
{
	static PODArray<T> New(size_t initialCapacity = 16)
	{
		static_assert(std::is_pod<T>::value, "T Must be POD Type in PODArray<T>");

		PODArray<T> poda;
		poda.m_capacity = 0;
		poda.m_arraySize = 0;
		poda.m_arrayPointer = nullptr;

		PODArray<T>::Reallocate(poda, initialCapacity);

		return poda;
	}

	static void PopulateWithVector(PODArray<T>& poda, std::vector<T> v)
	{
		Resize(poda, v.size());
		memcpy(poda.m_arrayPointer, v.data(), poda.m_arraySize * sizeof(T));
	}

	static void Append(PODArray<T>& poda, PODArray<T>& toAppend)
	{
		size_t originalSize = poda.m_arraySize;
		size_t newSize = poda.m_arraySize + toAppend.m_arraySize;
		PODArray::Resize(poda, newSize);
		memcpy(&poda.m_arrayPointer[originalSize], toAppend.m_arrayPointer, toAppend.m_arraySize * sizeof(T));
	}

	static void Resize(PODArray<T>& poda, size_t newSize)
	{
		if (newSize >= poda.m_capacity)
		{
			Reallocate(poda, 2 * poda.m_capacity);
		}

		for (size_t indexToClear = poda.m_arraySize; indexToClear > newSize; indexToClear--)
		{
			ZeroMemory(&poda.m_arrayPointer[indexToClear], sizeof(T));
		}
		poda.m_arraySize = newSize;
	}

	static void Free(PODArray<T>& poda)
	{
		if (poda.m_arrayPointer != nullptr)
		{
			delete[] poda.m_arrayPointer;
			poda.m_arraySize = 0;
		}
	}

	static const T* GetArrayPointer(PODArray& poda)
	{
		return poda.m_arrayPointer;
	}

	static size_t Size(PODArray<T>& poda)
	{
		return poda.m_arraySize;
	}

	T& operator[](size_t index)
	{
		if (index >= 0 && index < m_arraySize)
		{
			return m_arrayPointer[index];
		}
		else
		{
			throw std::out_of_range("Array index is out of range");
		}
	}

private:
	T* m_arrayPointer;
	size_t m_capacity;
	size_t m_arraySize;

	static void Reallocate(PODArray& poda, size_t newCapacity)
	{
		T* newArrayPointer = nullptr;
		if (newCapacity > 0)
		{
			newArrayPointer = new T[newCapacity];
		}

		size_t newArraySize = newCapacity < poda.m_arraySize ? newCapacity : poda.m_arraySize;
		if (newArraySize > 0)
		{
			memcpy(newArrayPointer, poda.m_arrayPointer, newArraySize * sizeof(T));
		}
		
		for (size_t newElementIndex = newArraySize; newElementIndex < newCapacity; newElementIndex++)
		{
			ZeroMemory(&newArrayPointer[newElementIndex], sizeof(T));
		}

		Free(poda);

		poda.m_capacity = newCapacity;
		poda.m_arraySize = newArraySize;
		poda.m_arrayPointer = newArrayPointer;
	}
};