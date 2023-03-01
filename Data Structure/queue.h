//
// Created by youssef on 1/29/23.
//

#ifndef DATA_STRUCTURE_QUEUE_H
#define DATA_STRUCTURE_QUEUE_H
#include <bits/stdc++.h>
#include "single linked list.h"
//#include "double linked list.h"
using namespace std;
template <typename type>
class Queue{
protected:
    type* arr{};
    int size{};
    int front{};
    int rear{};
    int added_elements{};
public:
    void operator=(Queue<int>) = delete;
    Queue(){}
    Queue(int size):size(size){
        arr = new type[size];
        front = rear = 0;
        added_elements = 0;
    }
    void enqueue(type val){
        if(isFull()){
            cout<<"Queue is full\n";
            return;
        }
        arr[rear] = val;
        rear = next(rear);
        ++added_elements;
    }
    int next(int pos)const{
        return ++pos % size;
    }
    type dequeue(){
        if(isEmpty()){
            cout<<"Queue is empty\n";
            return  -1;
        }
        type val = arr[front];
        front = next(front);
        --added_elements;
        return val;
    }
    type queue_front(){
        if(isEmpty()){
            cout<<"Queue is empty\n";
            return  -1;
        }
        type val = arr[front];
        return val;
    }
    bool isEmpty()const{
        return added_elements == 0;
    }
    bool isFull()const{
        return added_elements == size;
    }
    void clear(){
        front = rear = 0;
        added_elements = 0;
    }
    void display() {
        cout << "Front " << front << " - rear " << rear << "\t";
        if (isFull())
            cout << "full";
        else if (isEmpty()) {
            cout << "empty\n\n";
            return;
        }
        cout << "\n";
        int size_ = added_elements;
        int front_  = front;
        while (size_--){
            cout<<arr[front_]<<" ";
            front_ = next(front_);
        }
        cout << "\n\n";
    }
    ~Queue(){
        delete[] arr;
    }
};
template <typename type>
class Queue2{
private:
    LinkedList list;
public:
    void enqueue(type val){
        if(isEmpty()){
            cout<<"Empty\n";
            return;
        }
        list.insert_end(val);
    }
    void dequeue(){
        if(isEmpty()){
            cout<<"Empty\n";
            return;
        }
        cout << list.getHead();
        list.delete_front();
    }
    bool isEmpty()const{
        return list.getLength() == 0;
    }
    void display()const{
        list.print();
    }
};
template <typename type>
class Dequeu:public Queue<type>{
public:
    Dequeu(int size):
            Queue<int>(size){}
    int prev(int pos){
        return (pos - 1 + this->size) % this->size;
    }
    void enqueue_rear(int value){
        Queue<type>::enqueue(value);
    }
    void enqueue_front(int value){
        assert(!Queue<type>::isFull());
        this->front = prev(this->front);
        this->arr[this->front] = value;
        this->added_elements++;
    }
    int dequeue_front(){
        return Queue<int>::dequeue();
    }
    int dequeue_rear(){
        assert(!this->isEmpty());
        this->rear = prev(this->rear);
        int val = this->arr[this->rear];
        this->added_elements--;
        return val;
    }
};
class Stack{
private:
    Queue<int> q{};
    int size{};
    int added_elements{};
    void add_front(int val){
        int sz = added_elements;
        q.enqueue(val);
        while (sz--)
            q.enqueue(q.dequeue());
        added_elements++;
    }
public:
    Stack(int size):size(size),q(size){
        added_elements  = 0;
    }
    void push(int val){
        add_front(val);
    }
    int pop(){
        assert(!isEmpty());
        return q.dequeue();
    }

    bool isFull() const{
        return q.isFull();
    }
    bool isEmpty()const {
        return q.isEmpty();
    }

    int peek(){
        return q.queue_front();
    }
};
class QueueStack{
private:
    int added_elements{};
    int size{};
    stack<int> s1;
    stack<int> s2;
    void reverse(){
        if(!s2.empty()) return;
        while (!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
    }
public:
    QueueStack(int size):size(size),added_elements(0){}
    void enqueue(int val){
        assert(!isFull());
        s1.push(val);
        added_elements++;
    }
    int dequeue(){
        assert(!isEmpty());
        if(s2.empty()) reverse();
        int val =  s2.top();
        s2.pop();
        added_elements--;
        return val;
    }
    bool isEmpty()const{
        return added_elements == 0;
    }
    bool isFull()const{
        return added_elements == size;
    }

};
class PriorityQueue{
private:
    Queue<int> q1{},q2{},q3{};
    int size{};
    int added_elements{};
public:
    PriorityQueue(int size):size(size),q1(size),q2(size),q3(size){
    }
    bool isFull(){
        return added_elements == size;
    }
    bool isEmpty(){
        return added_elements == 0;
    }

    void enqueue(int id,int priority){
        if(priority == 1 ) {
            assert(!q1.isFull());
            q1.enqueue(id);
        }
        else if(priority == 2) {
            assert(!q2.isFull());
            q2.enqueue(id);
        }
        else{
            assert(!q3.isFull());
            q3.enqueue(id);
        }
        added_elements++;
    }
    int dequeue(){
        added_elements--;
        if(!q3.isEmpty()){
            return q3.dequeue();
        }
        else if(!q2.isEmpty()){
            return q2.dequeue();
        }
        else if(!q1.isEmpty()) {
            return q1.dequeue();
        }
    }
    void display(){
        if(!q3.isEmpty()){
            cout<<"Priority #3 tasks: \n";
            q3.display();
        }
        if(!q2.isEmpty()){
            cout<<"Priority #2 tasks: \n";
            q2.display();
        }
        if(!q1.isEmpty()){
            cout<<"Priority #1 tasks: \n";
            q1.display();
        }
        cout<<"******************\n";
    }
};
class CircularQueue{
private:
    int front{};
    int rear{};
    int* arr;
    int size{};
public:
    CircularQueue(int size):size(size+1){
        arr = new int[size];
        front = rear = 0;
    }
    bool isEmpty()const{
        return front == rear;
    }
    bool isFull()const{
        return next(rear) == front;
    }
    void enqueue(int val){
        if(isFull()){
            cout<<"Queue is full\n";
            return;
        }
        arr[rear] = val;
        rear = next(rear);
    }
    int next(int pos)const{
        return (++pos) % size;
    }
    int dequeue(){
        if(isEmpty()){
            cout<<"Queue is empty\n";
            return  -1;
        }
        int val = arr[front];
        front = next(front);
        return val;
    }
    int queue_front(){
        if(isEmpty()){
            cout<<"Queue is empty\n";
            return  -1;
        }
        int val = arr[front];
        return val;
    }
    void clear(){
        front = rear = 0;
    }
    void display() {
        cout << "Front " << front << " - rear " << rear << "\t";
        if (isFull())
            cout << "full";
        else if (isEmpty()) {
            cout << "empty\n\n";
            return;
        }
        cout << "\n";
        int front_  = front;
        while (front_ != rear){
            cout<<arr[front_]<<" ";
            front_ = next(front_);
        }
        cout << "\n\n";
    }
    ~CircularQueue(){
        delete[] arr;
    }
};

class Last_k_numbers_sum_stream {
private:
    int k;
    int sum {};
    int added_elements{};
    Queue<int> q;
public:
    explicit Last_k_numbers_sum_stream(int k):k(k),q(k+1){
    }

    int next(int new_num) {
        q.enqueue(new_num);
        added_elements++;
        sum+=new_num;
        if(added_elements > k)sum-=q.dequeue();
        return sum;
    }
};

#endif //DATA_STRUCTURE_QUEUE_H
