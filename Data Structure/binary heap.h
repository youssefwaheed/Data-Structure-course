//
// Created by youssef on 2/26/23.
//

#ifndef DATA_STRUCTURE_BINARY_HEAP_H
#define DATA_STRUCTURE_BINARY_HEAP_H
#include <bits/stdc++.h>
using namespace std;
class MinHeap {
private:
    int *arr{};
    int size{};
    int capacity{};

    int parent(int node) {
        return node == 0 ? -1 : (node - 1) / 2;
    }

    int left(int node) {
        int idx = 2 * node + 1;
        if (idx >= size)
            return -1;
        return idx;
    }

    int right(int node) {
        int idx = 2 * node + 2;
        if (idx >= size)
            return -1;
        return idx;
    }

    void heapify_up(int child_pos) {
        int parent_pos = parent(child_pos);
        if (child_pos == 0 || arr[parent_pos] <= arr[child_pos])
            return;
        swap(arr[parent_pos], arr[child_pos]);
        heapify_up(parent_pos);
    }

    void heapify_down(int parent_pos) {
        int left_pos = left(parent_pos);
        int right_pos = right(parent_pos);
        if (left_pos == -1)
            return;

        if (right_pos != -1 && arr[right_pos] < arr[left_pos])
            left_pos = right_pos;

        if (arr[parent_pos] > arr[left_pos]) {
            swap(arr[parent_pos], arr[left_pos]);
            heapify_down(left_pos);
        }
    }

    void heapfiy() {
        for (int i = size / 2 - 1; i >= 0; --i) {
            heapify_down(i);
        }
    }

public:
    MinHeap() {
        size = 0;
        capacity = 1000;
        arr = new int[capacity];
    }

    MinHeap(vector<int> &vec) {
        capacity = 1000;
        assert(vec.size() <= capacity);
        arr = new int[capacity];
        size = vec.size();
        for (int i = 0; i < vec.size(); ++i) {
            arr[i] = vec[i];
        }
        heapfiy();
    }

    void push(int val) {
        assert(size + 1 <= capacity);
        arr[size++] = val;
        heapify_up(size - 1);
    }

    void pop() {
        assert(!isempty());
        arr[0] = arr[--size];
        heapify_down(0);
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            if (left(i) == -1)
                continue;
            cout << arr[i] << " " << arr[left(i)] << " " << arr[right(i)] << "\n";
        }
    }

    ~MinHeap() {
        delete[] arr;
        arr = nullptr;
    }

    int top() {
        assert(!isempty());
        return arr[0];
    }

    bool isempty() {
        return size == 0;
    }

    MinHeap &operator=(const MinHeap &other) {
        if (this != &other) {  // Check for self-assignment
            // Allocate new memory for the target object
            int *new_arr = new int[other.capacity];

            for (int i = 0; i < other.size; ++i) {
                new_arr[i] = other.arr[i];
            }
            delete[] arr;
            arr = new_arr;
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }

    void print_less_than(int val, int parent_pos = 0) {
        stack<int> s;
        s.push(parent_pos);
        while (!s.empty()) {
            int cur = s.top();
            s.pop();
            if (val > arr[cur]) {
                cout << arr[cur] << " ";
                if (left(cur) != -1)
                    s.push(left(cur));
                if (right(cur) != -1)
                    s.push(right(cur));
            }
        }
    }

    bool is_heap_array(int *p, int n) {
        for (int i = 0; i < n / 2; ++i) {
            if (p[i] > p[(i * 2) + 1])
                return 0;
            if ((i * 2) + 2 < n && p[i] > p[(i * 2) + 2])
                return 0;
        }
        return 1;
    }

    void heap_sort(int *p, int n){
        int* old_arr = arr;
        int old_size = size;
        size = n;
        arr = p;
        heapfiy();
        while (size--){
            swap(arr[0],arr[size]);
            heapify_down(0);
        }
        reverse(arr,arr+n);
        arr = old_arr;
        size = old_size;
    }
};
class MaxHeap {
private:
    int *arr{};
    int size{};
    int capacity{};

    int parent(int node) {
        return node == 0 ? -1 : (node - 1) / 2;
    }

    int left(int node) {
        int idx = 2 * node + 1;
        if (idx >= size)
            return -1;
        return idx;
    }

    int right(int node) {
        int idx = 2 * node + 2;
        if (idx >= size)
            return -1;
        return idx;
    }

    void heapify_up(int child_pos) {
        int parent_pos = parent(child_pos);
        if (child_pos == 0 || arr[parent_pos] >= arr[child_pos])
            return;
        swap(arr[parent_pos], arr[child_pos]);
        heapify_up(parent_pos);
    }

    void heapify_down(int parent_pos) {
        int left_pos = left(parent_pos);
        int right_pos = right(parent_pos);
        if (left_pos == -1)
            return;

        if (right_pos != -1 && arr[right_pos] > arr[left_pos])
            left_pos = right_pos;

        if (arr[parent_pos] < arr[left_pos]) {
            swap(arr[parent_pos], arr[left_pos]);
            heapify_down(left_pos);
        }
    }

    void heapfiy() {
        for (int i = size / 2 - 1; i >= 0; --i) {
            heapify_down(i);
        }
    }

public:
    MaxHeap() {
        size = 0;
        capacity = 1000;
        arr = new int[capacity];
    }

    MaxHeap(vector<int>&vec){
        capacity = 1000;
        assert(vec.size() <= capacity);
        arr = new int[capacity];
        size = vec.size();
        for (int i = 0; i < vec.size(); ++i) {
            arr[i] = vec[i];
        }
        heapfiy();
    }

    void push(int val) {
        assert(size + 1 <= capacity);
        arr[size++] = val;
        heapify_up(size - 1);
    }

    void pop() {
        assert(!isempty());
        arr[0] = arr[--size];
        heapify_down(0);
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            if (left(i) == -1)
                continue;
            cout << arr[i] << " " << arr[left(i)] << " " << arr[right(i)] << "\n";
        }
    }

    ~MaxHeap() {
        delete[] arr;
        arr = nullptr;
    }

    int top() {
        assert(!isempty());
        return arr[0];
    }

    bool isempty() {
        return size == 0;
    }

};
class MaxHeapRe{
private:
    MinHeap minHeap{};
public:
    MaxHeapRe():minHeap(){
    }
    MaxHeapRe(vector<int> &vec){
        for(auto &i : vec)
            i*=-1;
        minHeap = MinHeap(vec);
    }

    void push(int val) {
        minHeap.push(-val);
    }

    void pop() {
        assert(!isempty());
        minHeap.pop();
    }

    void print() {
        minHeap.print();
    }

    ~MaxHeapRe() {
    }

    int top() {
        assert(!isempty());
        return minHeap.top()*-1;
    }

    bool isempty() {
        return minHeap.isempty();
    }
};
void heap_sort() {
    const int SZ = 14;
    int arr[SZ] { 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
    MinHeap heap;

    heap.heap_sort(arr, SZ);

    for (int i = 0; i < SZ; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}
class KthNumberProcessor {
private:
    int k;
    priority_queue<int> q;

public:
    KthNumberProcessor(int k): k(k){
    }

    int next(int new_num) {
        if(q.size() < k){
            q.push(new_num);
            return q.top();
        }
        if(new_num < q.top()){
            q.pop();
            q.push(new_num);
        }
        return q.top();
    }
};
class PriorityQueue{
private:
    vector<pair<int,int>> arr;
    int size{};
    int capacity{};

    int parent(int node) {
        return node == 0 ? -1 : (node - 1) / 2;
    }

    int left(int node) {
        int idx = 2 * node + 1;
        if (idx >= size)
            return -1;
        return idx;
    }

    int right(int node) {
        int idx = 2 * node + 2;
        if (idx >= size)
            return -1;
        return idx;
    }

    void heapify_up(int child_pos) {
        int parent_pos = parent(child_pos);
        if (child_pos == 0 || arr[parent_pos].first >= arr[child_pos].first)
            return;
        swap(arr[parent_pos], arr[child_pos]);
        heapify_up(parent_pos);
    }

    void heapify_down(int parent_pos) {
        int left_pos = left(parent_pos);
        int right_pos = right(parent_pos);
        if (left_pos == -1)
            return;

        if (right_pos != -1 && arr[right_pos].first > arr[left_pos].first)
            left_pos = right_pos;

        if (arr[parent_pos].first < arr[left_pos].first) {
            swap(arr[parent_pos], arr[left_pos]);
            heapify_down(left_pos);
        }
    }

    void heapfiy() {
        for (int i = size / 2 - 1; i >= 0; --i) {
            heapify_down(i);
        }
    }

public:
    PriorityQueue() {
        size = 0;
        capacity = 1000;
        arr = vector<pair<int,int>> (capacity);
    }

    void enqueue(int val,int id) {
        assert(size + 1 <= capacity);
        arr[size].first = id;
        arr[size++].second = val;
        heapify_up(size - 1);
    }

    void pop() {
        assert(!isempty());
        arr[0] = arr[--size];
        heapify_down(0);
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            if (left(i) == -1)
                continue;
            cout << arr[i].second << " " << arr[left(i)].second << " " << arr[right(i)].second << "\n";
        }
    }

    ~PriorityQueue() {
    }

    int dequeue() {
        assert(!isempty());
        int val =  arr[0].second;
        pop();
        return val;
    }

    bool isempty() {
        return size == 0;
    }

};

#endif //DATA_STRUCTURE_BINARY_HEAP_H
