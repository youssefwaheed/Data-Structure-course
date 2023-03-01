//
// Created by youssef on 02/11/22.
//

#ifndef LINKED_LIST_DOUBLE_LINKED_LIST_H
#define LINKED_LIST_DOUBLE_LINKED_LIST_H
#include <bits/stdc++.h>
using namespace std;
#define node Node
class node{
public:
    node* next{};
    node* prev{};
    int data{};
    node(int data):
        data(data){}
};

class LinkedList{
private:
    Node *head { };
    Node *tail { };
    int length = 0;

    // let's maintain how many nodes

    vector<Node*> debug_data;	// add/remove nodes you use

    void debug_add_node(Node* node) {
        debug_data.push_back(node);
    }
    void debug_remove_node(Node* node) {
        auto it = std::find(debug_data.begin(), debug_data.end(), node);
        if (it == debug_data.end())
            cout << "Node does not exist\n";
        else
            debug_data.erase(it);
    }

public:
    LinkedList() {
    }
    LinkedList(const LinkedList&) = delete;
    LinkedList &operator=(const LinkedList &another) = delete;

    void delete_node(Node* node) {
        debug_remove_node(node);
        --length;
        delete node;
    }

    void add_node(Node* node) {
        debug_add_node(node);
        ++length;
    }

    void print() {
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    void print_reversed()  {
        for (Node* cur = tail; cur; cur = cur->prev)
            cout << cur->data << " ";
        cout << "\n";
    }

    void insert_end(int val){
        node* new_node = new node(val);

        if(length == 0)
            head = tail = new_node;
        else{
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        add_node(new_node);
        tail->next = nullptr;
        head->prev = nullptr;
    }

    void insert_front(int val){
        node* new_node = new node(val);
        new_node->prev = nullptr;
        if(!head){
            head = tail = new_node;
            tail->next = nullptr;
        }
        else {
            head->prev = new_node;
            new_node->next = head;
            head = new_node;
        }
        add_node(new_node);
    }

    void delete_front(){
        if(!head)
            return;

        node* new_head = head->next;
        delete_node(head);
        head = new_head;
        if(head) {
            new_head->prev = nullptr;
        }
        if(length == 1) {
            tail = head;
            tail->next = nullptr;
        }
        if(length == 0)
            tail = head = nullptr;
        debug_verify_data_integrity();
    }

    void delete_end(){
        if(!head)
            return;

        node* new_tail = tail->prev;
        delete_node(tail);
        tail = new_tail;
        tail->next = nullptr;

        if(length == 0)
            tail = head = nullptr;
    }

    void link(node* node1,node* node2){
        if(node1) node1->next = node2;
        if(node2) node2->prev = node1;
    }

    void merge_2sorted_lists(LinkedList& list){
        if(!list.length){
            return;
        }
        node* cur1 = head;
        node* cur2 = list.head;
        if(head){
            node* last {};
            head = nullptr;
            while (cur1 && cur2){
                node* next{};
                if(cur1->data <=  cur2->data){
                    next = cur1;
                    cur1 = cur1->next;
                }else{
                    next = cur2;
                    cur2 = cur2->next;
                }
                link(last,next);
                last = next;
                if(!head)
                    head = last;

            }
            if (cur2) {	// our tail is from 2nd
                tail = list.tail;
                link(last, cur2);
            } else if (cur1) {
                link(last, cur1);
            }
        } else {	// use its data
            head = list.head;
            tail = list.tail;
        }
    length += list.length;
    debug_data.insert(debug_data.end(), list.debug_data.begin(), list.debug_data.end());	// add other nodes
    list.head = list.tail = nullptr;
    list.length = 0;
    list.debug_data.clear();
    debug_verify_data_integrity();
}

    node* delete_and_link(node* cur){
        node* pre = cur->prev;
        link(cur->prev , cur->next);
        delete_node(cur);
        return pre;
    }

    void delete_all_nodes_with_key(int value){
        if(!length)
            return;
        for(node* cur = head; cur;){
            if(cur->data == value){
                if(cur == head) {
                    delete_front();
                    cur =  head;
                    continue;
                }
                cur = delete_and_link(cur);
                if(!cur->next)
                    tail = cur;
            }
            cur = cur->next;
        }
        debug_verify_data_integrity();
    }

    void delete_even_positions(){
        if(!length)
            return;

        for(node* cur = head; cur->next ;cur = cur->next){
            cur = delete_and_link(cur->next);
            if(!cur->next) {
                tail = cur;
                break;
            }
        }
        debug_verify_data_integrity();
    }

    void delete_odd_positions(){
        if(!length)
            return;
        insert_front(-1);
        delete_even_positions();
        delete_front();
        debug_verify_data_integrity();
    }

    bool is_palindrome(){
        if(!length)
            return false;
        int i = 0;
        for(node* front = head,* back = tail ;i < length/2 ; i++, front = front->next,back = back->prev){
            if(front->data != back->data)
                return false;
        }
        return true;
    }

    void get_middle(){
        if(length <= 2)
            return;
        for(node* cur = head,*pre = tail; cur && pre ; cur = cur->next,pre = pre->prev){
            if(cur == pre){
                cout<<cur->data<<endl;
                break;
            }
            else if(cur->next == pre){
                cout<<cur->data<<" "<<pre->data<<endl;
                break;
            }
        }
    }

    void get_middle2(){

        if(length <= 2)
            return;
        int pre = 0;
        for(node* cur = head; cur ;cur = cur->next){
            int after_ = 0;
            ++pre;
            for(node* after = cur->next; after ; after = after->next){
                ++after_;
                if(after_ - pre > 1)
                    break;
            }
            if(pre == after_) {
                cout << cur->data << " " << cur->next->data << endl;
                return;
            }
            else if(pre - after_ == 1) {
                cout << cur->data << endl;
                return;
            }
        }
    }

    node* get_nth(int nth) const{
        for (node* node = head; nth > 0 && node != nullptr ; nth-- ,node = node->next) {
            if(nth == 1)
                return node;
        }
        return nullptr;
    }

    /*void swap_kth(int kth){

        if(kth > length)
            return;
        int kth_back = length - kth + 1;
        if(kth > kth_back)
            swap(kth,kth_back);

        node* first = get_nth(kth);
        node* second = get_nth(kth_back);

        node* first_prev = first->prev;
        node* first_next = first->next;

        node* second_prev = second->prev;
        node* second_next = second->next;
        if(kth == kth_back)
            return;

        if(kth +1 == kth_back){//1 2 3 4
            link(first_prev,second);
            link(second,first);
            link(first,second_next);
        }
        else{
            link(first_prev,second);
            link(second,first_next);
            link(second_prev,first);
            link(first,second_next);
        }
        if(kth == 1)
            swap(head,tail);
        debug_verify_data_integrity();
    }*/

    node* get_nth_back(int nth) const{
        for (node* node = tail; nth > 0 && node != nullptr ; nth-- ,node = node->prev) {
            if(nth == 1)
                return node;
        }
        return nullptr;
    }

    void swap_kth(int kth){
        node* first = get_nth(kth);
        node* second = get_nth_back(kth);

        if(first == second)
            return;

        node* first_prev = first->prev;
        node* first_next = first->next;

        node* second_prev = second->prev;
        node* second_next = second->next;

        if(first->next == second){//1 2 3 4
            link(first_prev,second);
            link(second,first);
            link(first,second_next);
        }
        else{
            link(first_prev,second);
            link(second,first_next);
            link(second_prev,first);
            link(first,second_next);
        }
        if(kth == 1)
            swap(head,tail);

        debug_verify_data_integrity();
    }

    void reverse(){
        if(length < 2)
            return;
        for(node* cur = tail; cur; cur = cur->next){
            swap(cur->next,cur->prev);
        }
        swap(head,tail);
        debug_verify_data_integrity();
    }
//////////////////////////////////////______DEBUGGING______/////////////////////////////////////////

    void debug_print_address() {
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur << "," << cur->data << "\t";
        cout << "\n";
    }

    void debug_print_node(Node* node, bool is_seperate = false) {
        if (is_seperate)
            cout << "Sep: ";
        if (node == nullptr) {
            cout << "nullptr\n";
            return;
        }

        if (node->prev == nullptr)
            cout << "X\t";
        else
            cout << node->prev->data << "\t";

        cout << " <= [" <<node->data << "]\t => \t";

        if (node->next == nullptr)
            cout << "X\t";
        else
            cout << node->next->data << "\t";

        if (node == head)
            cout << "head\n";
        else if (node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }

    void debug_print_list(string msg = "") {
        if (msg != "")
            cout << msg << "\n";
        for (int i = 0; i < (int) debug_data.size(); ++i)
            debug_print_node(debug_data[i]);
        cout << "************\n" << flush;
    }

    string debug_to_string() {
        if (length == 0)
            return "";
        ostringstream oss;
        for (Node* cur = head; cur; cur = cur->next) {
            oss << cur->data;
            if (cur->next)
                oss << " ";
        }
        return oss.str();
    }

    void debug_verify_data_integrity() {
        if (length == 0) {
            assert(head == nullptr);
            assert(tail == nullptr);
        } else {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!head->prev);
            assert(!tail->next);
        }
        int len = 0;
        for (Node* cur = head; cur; cur = cur->next, len++) {
            if (len == length-1)	// make sure we end at tail
                assert(cur == tail);
        }

        assert(length == len);
        assert(length == (int )debug_data.size());

        len = 0;
        for (Node* cur = tail; cur; cur = cur->prev, len++) {
            if (len == length-1)	// make sure we end at head
                assert(cur == head);
        }
        cout << "\n";
    }

};

#endif //LINKED_LIST_DOUBLE_LINKED_LIST_H
