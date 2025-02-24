// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); i++) {
        int num = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > num) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = num;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f) {
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if (low < high) {
        if (flag == 0) {
            int i = Partition(data, low, high);
            QuickSortSubVector(data, low, i - 1, flag);
            QuickSortSubVector(data, i + 1, high, flag);
        }
        else if (flag == 1) {
            int i = RandomizedPartition(data, low, high);
            QuickSortSubVector(data, low, i - 1, flag);
            QuickSortSubVector(data, i + 1, high, flag);
        }
    }
    
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high) {
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int random = rand() % (high - low + 1) + low;
    swap(data[random], data[high]);
    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int base = data[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (data[j] < base) {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data) {
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if ((high - low) >= 1) {
        int middle1 = (high + low) / 2;
        int middle2 = middle1 + 1;
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftIndex = low;
    int rightIndex = middle2;
    int combinedIndex = low;
    vector<int> combined(data.size());
    while (leftIndex <= middle1 && rightIndex <= high) {
        if (data[leftIndex] > data[rightIndex]) {
            combined[combinedIndex] = data[rightIndex];
            rightIndex++;
            combinedIndex++;
        }
        else {
            combined[combinedIndex] = data[leftIndex];
            leftIndex++;
            combinedIndex++;
        }
    }
    if (leftIndex == middle2) {
        while (rightIndex <= high) {
            combined[combinedIndex] = data[rightIndex];
            rightIndex++;
            combinedIndex++;
        }
    }
    else {
        while (leftIndex <= middle1) {
            combined[combinedIndex] = data[leftIndex];
            leftIndex++;
            combinedIndex++;
        }
    }
    for (int i = low; i <= high; i++) {
        data[i] = combined[i];
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int max_index = root;
    if (left < heapSize && data[left] > data[max_index]) {
        max_index = left;
    }
    if (right < heapSize && data[right] > data[max_index]) {
        max_index = right;
    }
    if (max_index != root) {
        swap(data[root], data[max_index]);
        MaxHeapify(data, max_index);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        MaxHeapify(data, i);
    }
}
