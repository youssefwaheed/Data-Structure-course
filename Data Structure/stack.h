//
// Created by youssef on 12/12/22.
//
#include<bits/stdc++.h>
using namespace std;
#ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H
class Stack2 {
private:
    int size{};
    int top_front{};
    int top_end{};
    int *arr{};
public:
    explicit Stack2(int size) : top_front(-1), size(size) {
        arr = new int[size];
        top_end = size;
    }

    void push(int id,int val){
        if(id == 1){
            if(isFullFront()){
                cout<<"stack is full"<<endl;
                return;
            }
            arr[++top_front] = val;
        }
        else{
            if(isFullEnd()){
                cout<<"stack is full"<<endl;
                return;
            }
            arr[--top_end] = val;
        }
    }

    int peak(int id)const{
        if(id == 1){
            if(isEmptyFront()){
                cout<<"stack is empty"<<endl;
                return INT_MAX;
            }
            else return arr[top_front];
        }
        else {
            if(isEmptyEnd()){
                cout<<"stack is empty"<<endl;
                return INT_MAX;
            }
            else return arr[top_end];
        }
    }

    bool isFullFront()const{
        return (top_front + 1 >= top_end);
    }

    bool isFullEnd()const{
        return (top_front >= top_end - 1);
    }

    bool isEmptyFront()const{
        return (top_front == -1);
    }

    bool isEmptyEnd()const{
        return (top_end == size);
    }

    void pop(int id){
        if(id == 1){
            if(isEmptyFront()){
                cout<<"stack is empty"<<endl;
                return;
            }
            --top_front;
        }
        else{
            if(isFullEnd()){
                cout<<"stack is empty"<<endl;
                return;
            }
            ++top_end;
        }
    }

    void display()const{
        for (int i = top_front; i >= 0 ; --i) {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
        for (int i = top_end; i < size ; ++i) {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};

class Stack{
private:
    int size{};
    int top{};
    int* arr{};
public:
    explicit Stack(int size):top(-1),size(size){
        arr = new int[size];
    }
    void push(int val){
        if(isFull()){
            cout<<"stack is full\n";
            return;
        }
        arr[++top] = val;
    }

    int peek()const{
        if(isEmpty()){
            cout<<"stack is empty.\n";
            return INT_MAX;
        }
        return arr[top];
    }

    void pop(){
        if(top == -1){
            cout<<"stack is empty.\n";
            return;
        }
        --top;
    }

    bool isEmpty()const{
        return (top == -1);
    }

    bool isFull()const{
        return (top >= size - 1);
    }

    void display()const{
        for (int i = top; i >= 0 ; --i) {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }

    void reverse_subword(string& str){
        Stack stk((int)str.size());
        for (int i = 0; i < (int)str.size(); ++i) {
            int j = i;
            while (j < str.size() && str[j] != ' ')stk.push(str[j++]);
            while (!stk.isEmpty()){
                str[i] = (char)stk.peek();
                stk.pop();
                ++i;
            }
        }
        cout<<str<<endl;
    }

    void insertEnd(int val){
        if(isFull()){
            cout<<"stack is full"<<endl;
            return;
        }
        if(isEmpty())
            push(val);
        else {
            int cur = peek();
            pop();
            insertEnd(val);
            push(cur);
        }
    }

    void reverse(){
        if(isEmpty())
            return;
        int cur = peek();
        pop();
        reverse();
        insertEnd(cur);
    }
};

template <typename type>

class Stack3{
private:
    struct node{
        type value{};
        node* next{};
        node(type val){
            value = val;
        }
    };
    node* head = nullptr;
public:
    void push(type val){
        node* newNode = new node(val);
        newNode->next = head;
        head = newNode;
    }
    type pop(){
        assert(!isEmpty());
        node* newHead = head->next;
        type val = head->value;
        delete head;
        head = newHead;
        return val;
    }
    type peek()const{
        assert(!isEmpty());
        return head->value;
    }
    bool isEmpty()const{
        return head == nullptr;
    }
};

int priority(char ch){
    if(ch == '+' || ch == '-')
        return 1;
    else if(ch == '*' || ch == '/')
        return 2;
    else if(ch == '^')
        return 3;
    return 0;
}

string InfixToPostfix(string &infix){
    string expression;
    stack<char> stk;
    int n = (int)infix.size();
    for (int i = 0; i < n; ++i) {
        char ch = infix[i];
        if(ch == '(') stk.push('(');
        else if(ch == ')'){
            while (!stk.empty() && stk.top()!='('){
                expression+=stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else if(isdigit(ch) || isalpha(ch)) expression+=ch;
        else if(!stk.empty() && stk.top() == '^' && ch == '^') stk.push('^');
        else{
            while (!stk.empty() && priority(ch) <= priority(stk.top())){
                expression+=stk.top();
                stk.pop();
            }
            stk.push(ch);
        }
    }
    while (!stk.empty()) {
        expression+=stk.top();
        stk.pop();
    }
    return expression;
}

string infixToPrefix(string infix){
    string expression;
    reverse(infix.begin(),infix.end());
    stack<char> stk;
    int n = (int)infix.size();
    for (int i = 0; i < n; ++i) {
        char ch = infix[i];
        if(ch == ')') stk.push(')');
        else if(ch == '('){
            while (!stk.empty() && stk.top()!=')'){
                expression+=stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else if(isdigit(ch) || isalpha(ch)) expression+=ch;
        else if(!stk.empty() && stk.top() == '^' && ch == '^') expression+='^';
        else{
            while (!stk.empty() && priority(ch) < priority(stk.top())){
                expression+=stk.top();
                stk.pop();
            }
            stk.push(ch);
        }
    }
    while (!stk.empty()) {
        expression+=stk.top();
        stk.pop();
    }
    std::reverse(expression.begin(), expression.end());
    return expression;
}
double res(double fir,double sec,char opera){
    switch (opera) {
        case '+':
            return fir + sec;
        case '-':
            return fir - sec;
        case '*':
            return fir * sec;
        case '/':
            if(sec == 0) return -1;
            else return fir / sec;
        case '^':
            return pow(fir,sec);
        default:
            return -1;
    }
}

double evaluate_postfix(string &postfix){
    Stack3<double> stk;
    double ans = 0;
    int n = (int)postfix.size();
    for (int i = 0; i < n; ++i) {
        char ch = postfix[i];
        if(isdigit(ch)) stk.push(ch-'0');
        else{
            stk.push(res(stk.pop(),stk.pop(),ch));
        }
    }
    return stk.pop();
}

string remove_brackets(string s){
    Stack3<char> stk;
    int n = (int)s.size();
    string ans;
    for (int i = 0; i < n; ++i) {
        char ch = s[i];
        if(ch == '(' && i == 0)
            continue;
        else if(ch == '(')stk.push(ans[ans.size()-1]);
        else if(ch == ')')stk.pop();
        else {
            if(stk.isEmpty()) ans+=ch;
            else{
                ans.erase(ans.size(),1);
                if(isdigit(ch))ans+=ch;
                else if((stk.peek() == '-' && ch == '+' )||(stk.peek() == '+' && ch == '-'))ans+='-';
                else ans+='+';
            }
        }
    }
    return ans;
}
#endif //LINKED_LIST_STACK_H
