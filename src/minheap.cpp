#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>

template <typename T>
class MinHeap
{
private:
    std::vector<T> heap;

    void heapify_up(int i)
    {
        if (i && heap[parent(i)] > heap[i])
        {
            std::swap(heap[i], heap[parent(i)]);
            heapify_up(parent(i));
        }
    }

    void heapify_down(int i)
    {
        int left = left_child(i);
        int right = right_child(i);
        int smallest = i;

        if (left < size() && heap[left] < heap[i])
            smallest = left;

        if (right < size() && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i)
        {
            std::swap(heap[i], heap[smallest]);
            heapify_down(smallest);
        }
    }

    int parent(int i) { return (i - 1) / 2; }
    int left_child(int i) { return (2 * i + 1); }
    int right_child(int i) { return (2 * i + 2); }

public:
    unsigned int size() { return heap.size(); }
    bool empty() { return size() == 0; }

    void push(T key)
    {
        heap.push_back(key);
        int index = size() - 1;
        heapify_up(index);
    }

    void pop()
    {
        if (size() == 0)
            throw std::out_of_range("Heap is empty");

        heap[0] = heap.back();
        heap.pop_back();

        heapify_down(0);
    }

    T top()
    {
        if (size() == 0)
            throw std::out_of_range("Heap is empty");

        return heap.front();
    }

    template <typename Predicate>
    T extract(Predicate pred)
    {
        auto it = std::find_if(heap.begin(), heap.end(), pred);
        if (it == heap.end())
            throw std::out_of_range("Element not found");

        std::swap(*it, heap.back());
        T value = heap.back();
        heap.pop_back();
        if (heap.size() > 1 && it != heap.end())
            heapify_down(it - heap.begin());
        // T value = *it;
        // heap.erase(it);
        return value;
    }

    void List()
    {
        for (auto i : heap)
        {
            std::cout << i << std::endl;
        }
        std::cout << std::endl;
    }
};