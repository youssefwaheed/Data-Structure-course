//
// Created by youssef on 2/12/23.
//

#ifndef DATA_STRUCTURE_BINARY_TREE_H
#define DATA_STRUCTURE_BINARY_TREE_H
#include <bits/stdc++.h>
using namespace std;
deque<int> inorder;
deque<int> preorder;
deque<pair<int,int>> new_preorder;
class BinarySearchTree{
private:
    BinaryTree* left{};
    BinaryTree* right{};
    int data{};
public:
    BinarySearchTree(int data):
            data(data){}

    BinarySearchTree(deque<int> &preorder, deque<int> &inorder){
        this->data = preorder.front();
        preorder.pop_front();
        if(inorder.size() == 1)
            return;
        int sz = (int)inorder.size();
        for (int i = 0; i < sz; ++i) {
            if(inorder[i] == data){
                if(i != 0) {
                    deque<int> left_inorder(inorder.begin(), inorder.begin() + i);
                    inorder.erase(inorder.begin(), inorder.begin() + i + 1);
                    left = new BinaryTree(preorder,left_inorder);
                }
                else inorder.pop_front();
                if(i != sz-1){
                    deque<int> right_inorder(inorder.begin(),inorder.end());
                    inorder.erase(inorder.begin(),inorder.end());
                    right = new BinaryTree(preorder,right_inorder);
                }
            }
        }
    }

    BinarySearchTree(deque<pair<int, int>>&preorder_queue){
        auto cur = preorder_queue.front();
        data = cur.first;
        preorder_queue.pop_front();
        if(cur.second)
            return;
        left = new BinaryTree(preorder_queue);
        right = new BinaryTree(preorder_queue);
    }

    void print_inorder(){
        if(left)
            left->print_inorder();
        cout<<data<<" ";
        inorder.push_back(data);
        if(right)
            right->print_inorder();
    }

    void print_preorder(){
        cout<<data<<" ";
        preorder.push_back(data);
        new_preorder.emplace_back(data,0);
        if(left)
            left->print_preorder();
        if(right)
            right->print_preorder();
        if(!left && !right)
            new_preorder.back().second = 1;
    }

    void print_inorder_iterative()  {
        stack<pair<BinaryTree*,bool>> stk;
        stk.push(make_pair(this,false));
        while (!stk.empty()){
            BinaryTree* cur = stk.top().first;
            bool done = stk.top().second;
            stk.pop();

            if(done)
                cout<<cur->data<<" ";
            else{
                if(cur->right)
                    stk.push(make_pair(cur->right,false));

                stk.push(make_pair(cur,true));

                if(cur->left)
                    stk.push(make_pair(cur->left,false));
            }

        }
        cout<<"\n";
    }

    void add(const vector<int> &values,const vector<char> &direction){
        assert(values.size() == direction.size());
        BinaryTree* cur = this;
        for (int i = 0; i <(int) direction.size(); ++i) {
            if(direction[i] == 'L') {
                if(!cur->left)
                    cur->left = new BinaryTree(values[i]);
                else
                    assert(cur->left->data == values[i]);
                cur = cur->left;
            }
            else{
                if(!cur->right)
                    cur->right = new BinaryTree(values[i]);
                else
                    assert(cur->right->data == values[i]);
                cur = cur->right;
            }
        }
    }

    int tree_max(){
        int max_ = data;
        if(left)
            max_ = max(left->tree_max(),max_);
        if(right)
            max_ = max(right->tree_max(),max_);
        return max_;
    }

    int tree_height(){
        int ans = 0;
        if(left)
            ans = 1 + left->tree_height();
        if(right)
            ans = max(ans,1 + right->tree_height());
        return ans;
    }

    int total_nodes(){
        int ans = 1;
        if(left)
            ans+=(left->total_nodes());
        if(right)
            ans+=(right->total_nodes());
        return ans;
    }

    int leafs_count(){
        int ans = !left && !right;
        if(left)
            ans+=left->leafs_count();
        if(right)
            ans+=right->leafs_count();
        return ans;
    }

    bool is_exists(int value){
        int ans = value == data;
        if(!ans && left)
            ans = left->is_exists(value);
        if(!ans && right)
            ans = right->is_exists(value);
        return ans;
    }

    bool is_perfect_formula(){
        int height = tree_height();
        long long ans = pow(2,height+1) - 1;
        return ans == total_nodes();
    }

    bool is_perfect(int h = -1){
        if(h == -1)
            h = tree_height();
        if(!left && !right)
            return h == 0;
        if(!left && right || left && !right)
            return false;
        return left->is_perfect(h-1) && right->is_perfect(h-1);
    }

    void clear(){
        if(!left && !right){
            return;
        }
        if(left) {
            left->clear();
            delete left;
            left = nullptr;
        }
        if(right) {
            right->clear();
            delete right;
            right = nullptr;
        }
    }

    ~BinarySearchTree(){
        clear();
    }

    void traverse_left_boundry(){
        cout<<data<<' ';
        if(left)
            left->traverse_left_boundry();
        else if(right)
            right->traverse_left_boundry();
    }

    int tree_diameter(){
        int res = 0 ;
        if(left && right)
            res = left->tree_height() + right->tree_height() + 2;
        else if(left)
            res = left->tree_height() + 1;
        else if(right)
            res = right->tree_height() + 1;

        if(left)
            res = max(res,left->tree_diameter());
        if(right)
            res = max(res,right->tree_diameter());
        return res;
    }

    void print_levels(){
        queue<BinaryTree*> queue;
        int cnt = 1;
        queue.push(this);
        while (cnt--){
            BinaryTree* cur = queue.front();
            cout<<cur->data<<" ";
            queue.pop();
            if(cur->left)
                queue.push(cur->left);
            if(cur->right)
                queue.push(cur->right);
            if(cnt == 0){
                cout<<"\n";
                cnt = (int)queue.size();
            }
        }
    }

    void print_levels_recursive(int h){
        if(h == 0)
            cout<<data<<" ";
        else{
            if(left)
                left->print_levels_recursive(h-1);
            if(right)
                right->print_levels_recursive(h-1);
        }
    }

    void  level_order_traversal_recursive(){
        int levels = tree_height();
        for (int i = 0; i <= levels; ++i) {
            cout<<"level"<<i<<":";
            print_levels_recursive(i);
            cout<<"\n";
        }
    }

    void level_order_traversal_recursive_v2(){
        queue<BinaryTree*> queue;
        queue.push(this);
        bfs(queue);
    }

    void  bfs(queue<BinaryTree*> &queue){
        if(queue.empty())
            return;
        BinaryTree* cur = queue.front();
        queue.pop();
        cout<<cur->data<<" ";
        if(cur->left)
            queue.push(cur->left);
        if(cur->right)
            queue.push(cur->right);
        bfs(queue);
    }

    void level_order_traversal_spiral(){
        deque<BinaryTree*> deque;
        deque.push_back(this);
        int level = 1;
        while (!deque.empty()){
            int sz = (int)deque.size();
            while (sz--){
                if(level & 1){
                    BinaryTree* cur = deque.front();
                    cout<<cur->data<<" ";
                    deque.pop_front();
                    if(cur->left)
                        deque.push_back(cur->left);
                    if(cur->right)
                        deque.push_back(cur->right);
                }
                else {
                    BinaryTree* cur = deque.back();
                    cout<<cur->data<<" ";
                    deque.pop_back();
                    if(cur->right)
                        deque.push_front(cur->right);
                    if(cur->left)
                        deque.push_front(cur->left);
                }
            }
            cout<<"\n";
            level++;
        }
    }

    bool is_perfect(){
        queue<BinaryTree*> queue;
        queue.push(this);
        int level = 0;
        while (!queue.empty()){
            int sz = (int)queue.size();
            if(sz != pow(2,level)){
                return 0;
            }
            while (sz--){
                BinaryTree* cur = queue.front();
                queue.pop();
                if(cur->left)
                    queue.push(cur->left);
                if(cur->right)
                    queue.push(cur->right);
            }
            level++;
        }
        return 1;
    }

    bool is_complete_v2(){
        queue<BinaryTree*> queue;
        queue.push(this);
        int level = tree_height();
        while (!queue.empty()){
            int sz = (int)queue.size();
            if(level == 1)break;
            while (sz--) {
                BinaryTree *cur = queue.front();
                queue.pop();
                if(cur->right && !cur->left) return 0;
                if (cur->left)
                    queue.push(cur->left);
                if (cur->right)
                    queue.push(cur->right);
            }
            level--;
        }
        while (!queue.empty()){
            BinaryTree *cur = queue.front();
            queue.pop();
            if(cur->right && !cur->left) return 0;
        }
        return 1;
    }

    bool is_complete(){
        queue<BinaryTree*> queue;
        queue.push(this);
        bool no_more_allowed = false;
        while (!queue.empty()){
            int sz = (int)queue.size();
            while (sz--) {
                BinaryTree *cur = queue.front();
                queue.pop();
                if (cur->left) {
                    if(no_more_allowed)return false;
                    queue.push(cur->left);
                }
                else no_more_allowed = true;
                if (cur->right) {
                    if (no_more_allowed)return false;
                    queue.push(cur->right);
                }
                else no_more_allowed = true;
            }
        }
        return true;
    }
    bool is_mirror(BinaryTree* first, BinaryTree* second){
        if((first && !second) || (!first && second))
            return 0;
        if(!first && !second)
            return 1;
        if(first->data != second->data)
            return 0;
        return is_mirror(first->left,second->right) && is_mirror(first->right,second->left);
    }
    bool is_symmetric(){
        /*return is_mirror(left,right);*/
        string left_tree = left ? left->parenthesize() : "";
        string right_tree = right ? right->parenthesize(false) : "";
        return left_tree == right_tree;
    }

    string parenthesize(bool left_ = true){
        string str;
        str+= to_string(data);
        if(left_){
            if(left)
                str+=left->parenthesize();
            else str+="()";
            if(right)
                str+=right->parenthesize();
            else str+="()";
        } else{
            if(right)
                str+= right->parenthesize(false);
            else str+="()";
            if(left)
                str+=left->parenthesize(false);
            else str+="()";
        }
        return str;
    }

    bool is_flip_equiv(BinaryTree* other){
        string cur_tree = parenthesize();
        string other_tree = other->parenthesize();
        std::sort(cur_tree.begin(), cur_tree.end());
        std::sort(other_tree.begin(), other_tree.end());
        return cur_tree == other_tree;
    }

    string parenthesize_canonical() {
        string repr = "(" + to_string(data);

        vector<string> v;

        if (left)
            v.push_back(left->parenthesize_canonical());
        else
            v.push_back("()");

        if (right)
            v.push_back(right->parenthesize_canonical());
        else
            v.push_back("()");

        sort(v.begin(), v.end());
        for (int i = 0; i < (int)v.size(); ++i)
            repr += v[i];

        repr += ")";

        return repr;
    }

    string all_duplicate_subtrees(map<string,int> &mp){
        string repr = "(" + to_string(data);

        vector<string> v;

        if (left)
            v.push_back(left->all_duplicate_subtrees(mp));
        else
            v.push_back("()");

        if (right)
            v.push_back(right->all_duplicate_subtrees(mp));
        else
            v.push_back("()");

        sort(v.begin(), v.end());
        int cnt = 0;
        for (int i = 0; i < (int)v.size(); ++i) {
            repr += v[i];
        }

        repr += ")";

        mp[repr]++;
        return repr;
    }

    void print_duplicate_subtrees(){
        map<string,int> mp;
        all_duplicate_subtrees(mp);
        auto it = mp.begin();
        while (it != mp.end()){
            int cnt = 0;
            if(it->second >= 2){
                for (auto &i: it->first) {
                    if (isdigit(i))cnt++;
                    if (cnt >= 2)break;
                }
                if(cnt >= 2)cout<<it->first<<endl;
            }
            it++;
        }
    }

};
class BinaryTree1{
private:
    struct Node{
        int data{};
        Node* left{};
        Node* right{};
        Node(int data):
                data(data){}
    };
    Node* root{};
    void PrintTree(Node* node)const{
        if(!node)
            return;
        PrintTree(node->left);
        cout<<node->data<<" ";
        PrintTree(node->right);
    }
public:
    BinaryTree1(int data):
            root(new Node(data)){}
    void print_inorder(){
        PrintTree(root);
        cout<<endl;
    }
    void add(const vector<int> &values,const vector<char> &direction){
        assert(values.size() == direction.size());
        Node* cur = root;
        for (int i = 0; i <(int) direction.size(); ++i) {
            if(direction[i] == 'L') {
                if(!cur->left)
                    cur->left = new Node(values[i]);
                else
                    assert(cur->left->data == values[i]);
                cur = cur->left;
            }
            else{
                if(!cur->right)
                    cur->right = new Node(values[i]);
                else
                    assert(cur->right->data == values[i]);
                cur = cur->right;
            }
        }
    }

};
class BinaryTree2{
private:
    BinaryTree2* left{};
    BinaryTree2* right{};
    char str{};
public:
    BinaryTree2(char str):str(str){
    }
    BinaryTree2(const string& postfix){
        stack<BinaryTree2*> stk;
        for (char i : postfix) {
            auto* new_tree = new BinaryTree2(i);
            if(!isdigit(i)) {
                new_tree->right = stk.top();
                stk.pop();
                new_tree->left = stk.top();
                stk.pop();
            }
            stk.push(new_tree);
        }
        BinaryTree2* new_tree = stk.top();
        this->str = new_tree->str;
        this->right = new_tree->right;
        this->left = new_tree->left;
    }
    bool is_just_number(){
        return !left && !right;
    }
    void print_inorder_expression(){
        if(left) {
            if(!left->is_just_number())cout<<"(";
            left->print_inorder_expression();
            if(!left->is_just_number())cout<<")";
        }
        cout<<str<<" ";
        if(right) {
            if(!right->is_just_number())cout<<"(";
            right->print_inorder_expression();
            if(!right->is_just_number())cout<<")";
        }
    }
};

#endif //DATA_STRUCTURE_BINARY_TREE_H
