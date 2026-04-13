// File: HeapKthlargestElementWhiting.cpp
// Name: Drew Whiting
// Course: COP3415.02I&T
// Date April 13, 2026

#include <iostream>
using namespace std;

const int MAX_HEAP_SIZE = 10000;

// Min heap implementation
class MinHeap {
private:
    int data[MAX_HEAP_SIZE]; // Array to store heap elements
    int size;                // Current number of elements in the heap

    // Helper: returns the index of the parent of node at index i
    int parent(int i) { return (i - 1) / 2; }

    // Helper: returns the index of the left child of node at index i
    int leftChild(int i) { return 2 * i + 1; }

    // Helper: returns the index of the right child of node at index i
    int rightChild(int i) { return 2 * i + 2; }

    // Moves a node up the heap until the min-heap property is restored
    void heapifyUp(int i) {
        // While not at root and parent is greater than current, swap upward
        while (i > 0 && data[parent(i)] > data[i]) {
            swap(data[parent(i)], data[i]);
            i = parent(i);
        }
    }

    // Moves a node down the heap until the min-heap property is restored
    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        // Find the smallest among current node, left child, and right child
        if (left < size && data[left] < data[smallest])
            smallest = left;
        if (right < size && data[right] < data[smallest])
            smallest = right;

        // If the smallest is not the current node, swap and continue down
        if (smallest != i) {
            swap(data[i], data[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Constructor: initializes an empty heap
    MinHeap() { size = 0; }

    // Returns the number of elements currently in the heap
    int getSize() { return size; }

    // Returns the minimum element (root) without removing it
    int getMin() { return data[0]; }

    // Inserts a new value into the heap
    void insert(int val) {
        // Place new element at the end and bubble it up
        data[size] = val;
        size++;
        heapifyUp(size - 1);
    }

    // Removes and returns the minimum element (root) from the heap
    int extractMin() {
        int minVal = data[0];

        // Move last element to root and shrink heap, then restore order
        data[0] = data[size - 1];
        size--;
        heapifyDown(0);

        return minVal;
    }
};

// Function to find the kth largest element in an array
// Parameters:
//   arr - input array of integers
//   n   - number of elements in arr
//   k   - the rank from the largest (1 = largest, 2 = second largest, etc.)
// Returns: the kth largest integer in arr
int findKthLargest(int arr[], int n, int k) {
    MinHeap heap;

    for (int i = 0; i < n; i++) {
        // Add the current element to the min-heap
        heap.insert(arr[i]);

        // If heap grows beyond k elements, remove the smallest
        // This ensures the heap always holds the k largest elements seen so far
        if (heap.getSize() > k) {
            heap.extractMin();
        }
    }

    // The root of the min-heap is the smallest of the k largest elements,
    // which is exactly the kth largest element overall
    return heap.getMin();
}

int main() {
    int arr[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};

    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    cout << "Kth largest element: " << findKthLargest(arr, n, k) << endl;

    return 0;
}