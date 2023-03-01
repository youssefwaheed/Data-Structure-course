//
// Created by youssef on 2/19/23.
//

#ifndef DATA_STRUCTURE_BINARYSEARCHTREE_H
#define DATA_STRUCTURE_BINARYSEARCHTREE_H
#include <bits/stdc++.h>
using namespace std;
/*lass BinarySearchTree{
private:
    int data{};
    BinarySearchTree* right{};
    BinarySearchTree* left{};
    BinarySearchTree* parent{};
public:

    BinarySearchTree();

    BinarySearchTree(int root){
        data = root;
    }

    BinarySearchTree(int root, BinarySearchTree* left, BinarySearchTree* right):
        data(root),left(left),right(right){}

   *//* BinarySearchTree(deque<int> &preorder):BinarySearchTree(preorder, get_next_greater(preorder)){*//**//*
        this->data = preorder[0];
        for (int i = 1; i < preorder.size(); ++i) {
                insert(preorder[i]);
        }*//**//*
    }
    BinarySearchTree(deque<int> &preorder,const deque<int> &next_greater,int start = 0,int end = -1){
        if(end == -1){
            end = preorder.size() - 1;
        }
        data = preorder[start];
        int split = next_greater[start];
        if(split > end)
            split = end + 1;

        if(start + 1 <= split - 1)
            left = new BinarySearchTree(preorder,next_greater,start+1,split - 1);
        if(split <= end)
            right = new BinarySearchTree(preorder,next_greater,split,end);
    }
    *//*
    BinarySearchTree(deque<int> &preorder,int mn = 0,int mx = 10001){
        bool state = preorder.front() > mn && preorder.front() < mx;
        if(!state)
            return;
        data = preorder.front();
        preorder.pop_front();
        if(!preorder.empty() && preorder.front() < data) {
            BinarySearchTree*left_tree = new BinarySearchTree(preorder, mn, data);
            if(left_tree->data != 0)
                left = left_tree;
        }
       if(!preorder.empty() && preorder.front() > data) {
           BinarySearchTree *right_tree = new BinarySearchTree(preorder, data, mx);
           if(right_tree->data != 0)
               right = right_tree;
       }
    }


    deque<int> get_next_greater(deque<int> &preorder){
        stack<int> stk;
        deque<int> ans(preorder.size());
        for(int i = 0 ; i< preorder.size() ; i++){
            while (!stk.empty() && preorder[i] >= preorder[stk.top()]){
                ans[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
        while (!stk.empty()){
            ans[stk.top()] = preorder.size();
            stk.pop();
        }
        return ans;
    }
    void insert(int val){
        if(val < data){
            if(left)
                left->insert(val);
            else left = new BinarySearchTree(val);
            left->parent = this;
        }
        else {
            if(right)
                right->insert(val);
            else right = new BinarySearchTree(val);
            right->parent = this;
        }
    }

    bool search_iterative(int target){
        BinarySearchTree* cur = this;
        while (cur){
            if(target == cur->data)
                return 1;
            if(target > cur->data){
                cur = cur->right;
            }
            else {
                cur = cur->left;
            }
        }
        return 0;
    }

    string print_inorder(){
        string str;
        if(left)
            str+=left->print_inorder();
        str+= to_string(data)+" ";
        if(right)
            str+=right->print_inorder();
        return str;
    }

    bool is_bst1(int mx = INT_MAX , int mn = INT_MIN){
        bool state = data > mn && data < mx;
        if(!state)
            return state;
        bool left_tree = !left || left->is_bst1(data,mn);
        if(!left_tree)
            return 0;
        bool right_tree = !right || right->is_bst1(mx,data);
        return right_tree;
    }

    bool is_bst2(){
        string s = print_inorder();
        int x = s[0]-'0';
        for (int i = 1; i < s.size() ; ++i) {
            if(s[i] == ' ')continue;
            int y = s[i] - '0';
            if(y < x)
                return 0;
            x = y;
        }
        return 1;
    }

    BinarySearchTree* build_balanced_bst_tree(vector<int> &values,int left_ = 0,int right_ = -100){
        if(right_ == -100)
            right_ = (int)values.size() -1;
        if(right_ < left_)
            return nullptr;
        int mid = (left_ + right_) / 2;
        BinarySearchTree* left_tree = build_balanced_bst_tree(values,left_,mid - 1);
        BinarySearchTree* right_tree = build_balanced_bst_tree(values,mid + 1,right_);
        BinarySearchTree* root = new BinarySearchTree(values[mid],left_tree,right_tree);
        return root;
    }

    int kth_smallest(int &k) {
        if (k == 0)
            return -1234;
        if (left) {
            int res = left->kth_smallest(k);
            if (k == 0)
                return res;
        }
        k--;
        if (k == 0)
            return data;

        if (right)
            return right->kth_smallest(k);
        return -1234;
    }

    int lca(int x,int y){
        if(x < data && y < data)
            return left->lca(x,y);
        if(x > data && y > data)
            return right->lca(x,y);
        return data;
    }

    int min_value(){
        if(left)
            return left->min_value();
        return data;
    }

    BinarySearchTree* min_node(){
        if(left)
            return left->min_node();
        return this;
    }

    BinarySearchTree* max_node(){
        if(right)
            return right->max_node();
        return this;
    }

    void delete_value(int targer){
        delete_node_v3(targer,this);
    }

    void special_delete(BinarySearchTree* child){
        ///اضطرينا نضحي بالجنين عشان الام نعيش
        data = child->data;
        left = child->left;
        right = child->right;
        delete child;
    }

    BinarySearchTree* delete_node(int target,BinarySearchTree* node){
        if(!node)
            return nullptr;
        if(target < node->data)
            node->left = delete_node(target,node->left);
        else if(target > node->data)
            node->right = delete_node(target,node->right);
        else{
            BinarySearchTree* temp = node;
            if(!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
            else if(!node->left)
                node->special_delete(node->right);
            else if(!node->right)
                node->special_delete(node->left);
            else{
                BinarySearchTree* mn = node->right->min_node();
                node->data = mn->data;
                node->right = delete_node(node->data,node->right);
                temp = nullptr;
            }
            if(temp){
                temp = nullptr;
            }
        }
        return node;
    }
    BinarySearchTree* delete_node_v2(int target,BinarySearchTree* node){
        if(!node)
            return nullptr;
        if(target < node->data)
            node->left = delete_node_v2(target,node->left);
        else if(target > node->data)
            node->right = delete_node_v2(target,node->right);
        else{
            BinarySearchTree* temp = node;
            if(!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
            else if(!node->left)
                node->special_delete(node->right);
            else if(!node->right)
                node->special_delete(node->left);
            else{
                //BinarySearchTree* mn = node->right->min_node();
                BinarySearchTree* mx = node->left->max_node();
                node->data = mx->data;
                node->left = delete_node_v2(node->data,node->left);
                temp = nullptr;
            }
            if(temp){
                temp = nullptr;
            }
        }
        return node;
    }
    BinarySearchTree* delete_node_v3(int target,BinarySearchTree* node){
        if(!node)
            return nullptr;
        if(target < node->data)
            node->left = delete_node(target,node->left);
        else if(target > node->data)
            node->right = delete_node(target,node->right);
        else{
            BinarySearchTree* temp = node;
            if(!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
            else if(!node->left)
                node->special_delete(node->right);
            else if(!node->right)
                node->special_delete(node->left);
            else{
                BinarySearchTree* mn = node->right->min_node();
                node->data = mn->data;
                BinarySearchTree* cur = node->right;
                BinarySearchTree* previous = node;
                while (cur != mn){
                    previous = cur;
                    cur = cur->left;
                }
                previous->left = cur->right;
                delete cur;
                cur = nullptr;
                temp = nullptr;
            }
            if(temp){
                temp = nullptr;
            }
        }
        return node;
    }

    int max_value(){
        if(right)
            return right->min_value();
        return data;
    }

    bool find_chain(vector<BinarySearchTree*> &ancestors,int target){
        ancestors.push_back(this);
        if(target == data)
            return true;

        if(target < data)
            return left && left->find_chain(ancestors,target);
        return right && right->find_chain(ancestors,target);
    }

    BinarySearchTree* get_next(vector<BinarySearchTree*> &ancestors){
        if(ancestors.empty())
            return nullptr;
        BinarySearchTree* cur = ancestors.back();
        ancestors.pop_back();
        return cur;
    }

    pair<bool,int> successor(int target){
        vector<BinarySearchTree*> bath;

        if(!find_chain(bath,target))
            return make_pair(0,-1);

        BinarySearchTree* child = get_next(bath);
        if(child->right)
            return make_pair(1, child->right->min_value());

        BinarySearchTree* parent = get_next(bath);
        while (parent && child == parent->right)
            child = parent,parent = get_next(bath);

        if(parent)
            return make_pair(1,parent->data);
        return make_pair(0,-1);
    }

    pair<bool,int> successor2(int target){
        BinarySearchTree* child = this;

        while (child && child->data != target){
            if(target > child->data && right)
                child = child->right;
            else if(target < child->data && left)
                child = child->left;
            else
                break;
        }
        if(!child || child->data != target)
            return make_pair(0,-1);

        if(child->right)
            return make_pair(1,child->right->min_value());

        BinarySearchTree* parent_ = child->parent;
        while (parent_ && parent_->right == child)
            child = parent_ , parent_ = child->parent;

        if(parent_)
            return make_pair(1,parent_->data);
        return make_pair(0,-1);
    }

    pair<bool,int> successor3(int target){
        if(target == data){
            if(right)
                return make_pair(1,right->min_value());
            else{
                return make_pair(0,data);
            }
        }
        pair<bool,int> res;
        if(target > data && right){
            res = right->successor3(target);
            if(!res.first) {
                if (data > res.second)
                    return make_pair(1, data);
            }
           return res;
        }
        else if(target < data && left){
            res = left->successor3(target);
            if(!res.first) {
                if (data > res.second)
                    return make_pair(1, data);
            }
            return res;
        }
        return make_pair(1,-1);
    }

    void print_preorder(){
        cout<<data<<" ";
        if(left)
            left->print_preorder();
        if(right)
            right->print_preorder();
    }

    void get_inorder(vector<int>& values) {
        if (left)
            left->get_inorder(values);
        values.push_back(data);
        if (right)
            right->get_inorder(values);
    }
};

bool is_degenerate(vector<int> &preorder){
   int sz = (int)preorder.size();
   if(sz <= 2)
       return true;

   int mn = 1;
   int mx = 1000;
    for (int i = 1; i < sz; ++i) {
        if(preorder[i] > mx || preorder[i] < mn)
            return 0;

        if(preorder[i] > preorder[i-1])
            mn = preorder[i-1] + 1;
        else
            mx = preorder[i-1] - 1;
    }
    return true;
}

BinarySearchTree* GetTree1() {
    BinarySearchTree* tree = new BinarySearchTree(50);
    tree->insert(20);
    tree->insert(60);
    tree->insert(15);
    tree->insert(45);
    tree->insert(70);
    tree->insert(35);
    tree->insert(73);

    tree->insert(14);
    tree->insert(16);
    tree->insert(36);
    tree->insert(58);
    return tree;
}


void test1() {
    BinarySearchTree* tree = GetTree1();

    vector<int> inorder;
    tree->get_inorder(inorder);

    for (int i = 0; i < (int)inorder.size(); ++i) {
        if(inorder[i] == 50)
            continue;	// root

        vector<int> inorder_v2;
        BinarySearchTree* tree = GetTree1();
        tree->delete_value(inorder[i]);
        tree->get_inorder(inorder_v2);

        vector<int> inorder_cpy = inorder;
        inorder_cpy.erase(find(inorder_cpy.begin(), inorder_cpy.end(), inorder[i]));
        assert(inorder_cpy == inorder_v2);
    }
}
*/class BinarySearchTree{
private:
    struct BinaryNode{
        int data{};
        BinaryNode* left{};
        BinaryNode* right{};
        BinaryNode(int data):data(data){}
    };
    BinaryNode* root{};
public:
    void link(BinaryNode* node){
        BinaryNode* cur = root;
        while (cur){
            if(node->data > cur->data){
                if(cur->right){
                    cur = cur->right;
                }
                else{
                    cur->right = node;
                    break;
                }
            }
            else{
                if(cur->left){
                    cur = cur->left;
                }
                else{
                    cur->left = node;
                    break;
                }
            }
        }
    }
    void insert_value(int val){
        if(!root) {
            root = new BinaryNode(val);
            return;
        }
        BinaryNode* new_node = new BinaryNode(val);
        link(new_node);
    }
    void print_preorder(){
        print_preorder(root);
    }
    void print_preorder(BinaryNode*& node)const{
        if(!node)
            return;
        cout<<node->data<<" ";
        print_preorder(node->left);
        print_preorder(node->right);
    }
    void print_inorder(){
        stack<pair<BinaryNode*,bool>> s;
        s.push(make_pair(root,false));
        while (!s.empty()){
            auto cur = s.top();
            s.pop();
            if(cur.second)
                cout<<cur.first->data<<' ';
            else{
                if(cur.first->right)
                    s.push(make_pair(cur.first->right,false));
                s.push(make_pair(cur.first,true));
                if(cur.first->left)
                    s.push(make_pair(cur.first->left, false));
            }
        }
    }
    void delete_value(int val){
        delete_node(val,root);
    }
    BinaryNode* min_node(BinaryNode* node) {
        if(node->left)
            return min_node(node->left);
        return node;
    }
    BinaryNode* delete_node(int target,BinaryNode* &node){
        if(!node)
            return nullptr;
        if(target < node->data)
            node->left = delete_node(target,node->left);
        else if(target > node->data)
            node->right = delete_node(target,node->right);
        else{
            BinaryNode* temp = node;
            if(!node->left && !node->right) {
                delete node;
                temp = nullptr;
                node = nullptr;
            }
            else if(!node->left) {
                node = node->right;
            }
            else if(!node->right){
                node = node->left;
            }
            else{
                BinaryNode* mn = min_node(node->right);
                node->data = mn->data;
                node->right = delete_node(node->data,node->right);
                temp = nullptr;
            }
            if(temp){
                delete temp;
                temp = nullptr;
            }
        }
        return node;
    }

};
#endif //DATA_STRUCTURE_BINARYSEARCHTREE_H
