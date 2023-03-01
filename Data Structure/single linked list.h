//
// Created by youssef on 02/11/22.
//

#ifndef LINKED_LIST_SINGLE_LINKED_LIST_H
#define LINKED_LIST_SINGLE_LINKED_LIST_H
#include <bits/stdc++.h>
using namespace std;
#define el endl
#define LinkedList linkedList

class node{
public:
    int data{};
    node* next{};
    node(int data):data(data){}
    ~node(){
        cout<<"deleted node with data "<<data<<" at address "<< this<<el;
    }
};

class LinkedList{
private:
    node* head{};
    node* tail{};
    int length{};
    vector<node*> debug_data;

    void debug_add_node(node* node){
        debug_data.emplace_back(node);
    }

    void debug_remove_node(node* node){
        auto it = std::find(debug_data.begin(), debug_data.end(),node);
        if(it == debug_data.end())
            cout<<"Not exist\n";
        else
            debug_data.erase(it);
    }

public:
    linkedList(){};

    linkedList(const linkedList&) = delete;
    linkedList &operator=(const linkedList &another) = delete;

    linkedList(initializer_list<int> list){
        auto it = list.begin();
        while (it != list.end()){
            insert_end(*it);
            it++;
        }
    }

    linkedList& operator=(const initializer_list<int> &list){
        auto it = list.begin();
        while (it != list.end()){
            insert_end(*it);
            ++it;
        }
        return *this;
    }

    template<typename type,typename ...all>
    linkedList(type val ,all...values){
        insert_end(val,values...);
    }

    template<typename type,typename ...all>
    void insert_end(type val ,all...values){
        insert_end(val);
        insert_end(values...);
    }

    void insert_end(int val){
        node* newNode = new node(val);
        add_node(newNode);

        if(!head)
            head = tail = newNode;
        else{
            tail->next = newNode;
            tail = newNode;
            tail->next = nullptr;
        }
    }

    void print()const{
        node* now = head;
        while (now != nullptr){
            cout<<now->data<<" ";
            now = now->next;
        }
        cout<<el;
    }

    int getLength()const{
        return length;
    }

    int getHead()const{
        if(!head)
            return -1;
        return head->data;
    }
    void delete_node(node* node) {
        debug_remove_node(node);
        --length;
        if(length == 1)
            tail = head;
        tail->next = nullptr;
        delete node;
    }

    void add_node(node* node) {
        debug_add_node(node);
        ++length;
    }

    node* get_nth_from_front(int nth) const{
        for (node* node = head; nth > 0 && node != nullptr ; nth-- ,node = node->next) {
            if(nth == 1)
                return node;
        }
        return nullptr;
    }

    int search(int val){
        int i = 0;
        for (node* node = head; node != nullptr ;i++,node = node->next) {
            if(node->data == val)
                return i;
        }
        return -1;
    }

    int improved_search(int val){
        int i = 0;
        for(node* cur = head,*pre = nullptr; cur != nullptr; pre = cur,cur = cur->next,i++){
            if(cur->data == val){
                if(!pre)
                    return i;
                else {
                    swap(cur->data,pre->data);
                    return i - 1;
                }
            }
        }
        return -1;
    }

    void insert_front(int val){
        node* newNode = new node(val);
        newNode->next = head;
        head = newNode;
        add_node(head);
        if(length == 1)
            tail = head;
    }

    void delete_front(){
        assert(length);
        node* newHead = head->next;
        delete_node(head);
        head = newHead;

        if(length <= 1)		// Fix
            tail = head;

        debug_verify_data_integrity();
    }

    node* get_nth_back(int nth){
        assert(length - nth >= 0);
        node* cur = head;
        int idx = length - nth;
        while (idx){
            cur = cur->next;
            idx--;
        }
        debug_verify_data_integrity();
        return cur;
    }

    void delete_nth_node(int nth){
        assert(length - nth >= 0);

        if(nth == 1){
            delete_front();
        }
        else{
            node* cur = get_nth_from_front(nth-1);
            node* temp = cur->next;
            cur->next = cur->next->next;
            if(temp == tail)
                tail = cur;
            delete_node(temp);
        }

        if(length == 1)
            tail = head;

        debug_verify_data_integrity();
    }

    bool is_same(const linkedList &list) const{
        node* curNode1 = head;
        node* curNode2 = list.head;

        /* if(length != list.length)
             return 0;*/

        while (curNode1 && curNode2){
            if(curNode1->data != curNode2->data)
                return 0;
            curNode1 = curNode1->next;
            curNode2 = curNode2->next;
        }
        return (curNode2 == curNode1);
    }

    void delete_node_with_key(int key){
        int idx = search(key) + 1;
        if(idx <= 0 ){
            cout<<"no such value\n";
            return;
        }
        delete_nth_node(idx);
        debug_verify_data_integrity();
    }

    void swap_pairs(){
        for(node* cur = head; cur!= nullptr; cur = cur->next->next){
            if(cur->next != nullptr)
                swap(cur->data,cur->next->data);
            else return;
        }
    }

    void reverse(){
        tail = head;
        node* prev  = nullptr;
        while (head){
            node* next_node = head->next;
            head->next = prev;

            prev = head;
            head = next_node;
        }
        head = prev;
        debug_verify_data_integrity();
    }

    void delete_even_positions(){
        node* prev = nullptr;
        for(node* cur = head; cur ;prev = cur, cur = cur->next,prev){
            if(cur->next){
                node* deleted_node = cur->next;
                cur->next = cur->next->next;
                delete_node(deleted_node);
            }
        }
        tail = prev;
        debug_verify_data_integrity();
    }

    void insert_sorted(int value){
        node* cur = head,*prev = nullptr;

        while( cur && value > cur->data) {
            prev = cur;
            cur = cur->next;
        }

        if(cur == head) insert_front(value);
        else if(!cur) insert_end(value);
        else{
            node* new_node = new node(value);
            add_node(new_node);
            new_node->next = cur;
            prev->next = new_node;
        }

        debug_verify_data_integrity();
    }

    void swap_head_tail(){
        if(length < 2)
            return;

        node* cur = head;
        node* prev = nullptr;
        while (cur->next){
            prev = cur;
            cur = cur->next;
        }
        prev->next = head;
        tail->next = head->next;
        head->next = nullptr;

        swap(head,tail);

        debug_verify_data_integrity();
    }

    void left_rotate(int k){
        if(!length || length == 1 || k % length == 0)
            return;

        int x = k % length;
        node* node = get_nth_from_front(x);

        tail->next = head;
        head = node->next;

        tail = node;
        tail->next = nullptr;

        debug_verify_data_integrity();
    }

    void remove_duplicates_from_not_sorted(){
        if(length == 1 || !length)
            return;
        int arr[(int)1e5] = {0};
        for(node* cur = head,*prev = nullptr; cur ; prev = cur,cur = cur->next){
            if(arr[cur->data]){
                prev->next = cur->next;
                delete_node(cur);
                cur = prev;
            }
            arr[cur->data]++;
        }
    }

    void delete_last_occurrence(int key){
        node* last = nullptr;
        node* prev = nullptr;

        if(key == head->data)
            last = head;

        for(node* cur = head; cur ; cur = cur->next){
            if(cur->next && cur->next->data == key){
                last = cur->next;
                prev = cur;
            }
        }

        if(last){
            if(last == head){
                node* temp = head->next;
                delete_node(head);
                head = temp;
            }
            else if(last == tail){
                delete_node(tail);
                prev->next = nullptr;
                tail = prev;
            }
            else{
                prev->next = last->next;
                delete_node(last);
            }
        }

        debug_verify_data_integrity();
    }

    void move_to_end(node* cur,node* prev){
        if(cur == head){
            node* temp = cur->next;
            tail->next = head;
            head->next = nullptr;
            tail = head;
            head = temp;
            return;
        }
        prev->next = cur->next;
        cur->next = nullptr;
        tail->next = cur;
        tail = cur;
    }

    void move_key_occurance_to_end(int key){
        if(!length)
            return;
        int len = length;
        for(node* cur = head,*prev = nullptr;len--;){
            if(cur->data == key){
                node* temp = cur->next;
                move_to_end(cur, prev);
                cur = temp;
            }
            else{
                prev = cur;
                cur = cur->next;
            }
        }
    }

    int max(node* node = nullptr,bool is_first = true){
        if(!head)
            return -1;
        if(is_first){
            return std::max(max(head,false),head->data);
        }
        if(!node)
            return 0;
        return std::max(max(node->next,false),node->data);
    }

    void odd_pos_even_pos(){
        int cnt = length/2;
        for(node* prev = head,*cur = head->next; cnt && cur; prev = prev->next,cur = prev->next,cnt--){
            move_to_end(cur,prev);
        }
        debug_verify_data_integrity();
    }

    void insert_alternate(LinkedList &another){
        node* cur = head;
        node* another_cur = another.head;

        if(length == 0) {
            while (!cur && another_cur) {
                insert_end(another_cur->data);
                another_cur = another_cur->next;
            }
            return;
        }
        node* next = head->next;
        while (cur && next && another_cur){
            cur->next = new node(another_cur->data);
            add_node(cur->next);
            cur->next->next = next;
            cur = next;
            next = next->next;
            another_cur = another_cur->next;
        }

        while (cur && another_cur){
            insert_end(another_cur->data);
            another_cur = another_cur->next;
        }

        debug_verify_data_integrity();
    }

    node* remove_from_to(node* from,node* to , node* pre = nullptr){

        for (node* cur = from,*prev = pre; cur != to  ;) {
            if(cur == head){
                node* next = cur->next;
                delete_node(cur);
                head = next;
                cur = head;
            }
            else{
                node* next = cur->next;
                prev->next = cur->next;
                delete_node(cur);
                cur = next;
            }
            if(length == 1)
                tail = head;
            else if(length == 0)
                head = tail = nullptr;
            if(tail) tail->next = nullptr;
        }
        return to;
    }

    void remove_all_repeated_from_sorted(){
        if(length <= 1)
            return;
        for(node* cur = head,*pre = nullptr; cur ;){
            int cnt = 0;
            node* temp = cur->next;
            for(; temp ; temp = temp->next){
                if(temp->data == cur->data)
                    cnt++;
                else break;
            }
            if(cnt) {
                cur = remove_from_to(cur, temp, pre);
            }
            else{
                pre = cur, cur = cur->next;
            }
            debug_verify_data_integrity();
        }
    }

    pair<node*,pair<node*,node*>> reverse_subchain(node* now,int k){
        k--;
        node* pre = now;
        node* cur_tail = now;
        node* cur = pre->next;
        while (cur && k--){
            node* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return {pre, {cur_tail,cur}};
    }

    void reverse_chains(int k){
        if(k == length){
            reverse();
            return;
        }
        assert(k);
        node* pre = head;
        node* last_tail = head = nullptr;
        while (pre){
            auto p = reverse_subchain(pre,k);
            node* chain_head = p.first;
            node* chain_tail = p.second.first;
            pre = p.second.second;
            if(!head)
                head = chain_head;
            else last_tail->next = chain_head;
            last_tail = chain_tail;
        }
        last_tail->next = nullptr;
        tail = last_tail;
        debug_verify_data_integrity();
    }
    /* ~list(){
         while (head){
             node* next = head->next;
             delete head;
             head = next;
         }
     }*/
//////////////////////////////////////______DEBUGGING______/////////////////////////////////////////
    bool debug_verify_data_integrity()const{
        if(length == 0) {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else{
            if(length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!tail->next);
        }

        int count = 0;
        for(node* cur = head;cur != nullptr; cur = cur->next)
            assert(count++ < 10000);

        assert(count == length);
        assert(length == (int)debug_data.size());
        return 1;
    }

    string debug_to_string() const{
        if (length == 0)
            return "";
        ostringstream oss;
        for (node* cur = head; cur; cur = cur->next) {
            oss << cur->data;
            if (cur->next)
                oss << " ";
        }
        return oss.str();
    }

    void print_debug_node(node* node,bool is_seperated = false )const{
        if(is_seperated)
            cout<<"seperated\n";
        if(!node){
            cout<<"nullptr\n";
            return;
        }
        cout<<node->data<<" ";
        if(!node->next)
            cout<<"X ";
        else
            cout<<node->next->data<<" ";
        if(node == head)
            cout<<"head";
        else if(node == tail)
            cout<<"tail";
        cout<<el;
    }

    void debug_print_list(const string& msg = ""){
        if(msg != "")
            cout<<msg<<el;
        for (auto & i : debug_data) {
            print_debug_node(i);
        }
        cout<<msg<<el;
    }

    void debug_print_address() {
        for (node* cur = head; cur; cur = cur->next)
            cout << cur << "," << cur->data << "\t";
        cout << "\n";
    }
};

class LinkedList2{
private:
    node* head{};
public:
    void add_element(int val){
        if(!head){
            head = new node(val);
            head->next = nullptr;
            return;
        }
        node* secondNode = head;
        head = new node(val);
        head->next = secondNode;
    }

    void print()const{
        node* cur = head;
        while (cur){
            cout<<cur->data<<" ";
            cur = cur->next;
        }
        cout<<el;
    }

    node* get_tail()const{
        if(!head)
            return nullptr;
        node* cur = head;
        while (cur->next){
            cur = cur->next;
        }
        return cur;
    }

};
#endif //LINKED_LIST_SINGLE_LINKED_LIST_H
