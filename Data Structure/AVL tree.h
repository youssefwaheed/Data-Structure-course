//
// Created by youssef on 27/02/23.
//

#ifndef DATA_STRUCTURE_AVL_TREE_H
#define DATA_STRUCTURE_AVL_TREE_H
#include <bits/stdc++.h>
using namespace std;
class AVLTree{
private:
    struct BinaryNode{
        int data{};
        int height{};
        int count{1};
        BinaryNode* left{};
        BinaryNode* right{};
        BinaryNode(int data):data(data){}
        int ch_height(BinaryNode* node){
            if(!node)
                return -1;
            return node->height;
        }
        int ch_count(BinaryNode* node) {	// child height
            if (!node)
                return 0;
            return node->count;
        }
        int update_height(){
            return height = 1 + max(ch_height(left), ch_height(right));
            count = 1 + ch_count(left) + ch_count(right);
        }
        int balance_factor(){
            return (ch_height(left) - ch_height(right));
        }
    };
    BinaryNode* root{};
public:
    BinaryNode* left_rotation(BinaryNode* node){
        cout << "left_rotation " << node->data << "\n";
        BinaryNode* right_tree = node->right;
        node->right = right_tree->left;
        right_tree->left = node;
        node->update_height();
        right_tree->update_height();
        return right_tree;
    }

    BinaryNode* right_rotation(BinaryNode* node){
        cout << "right_rotation " << node->data << "\n";
        BinaryNode* left_tree = node->left;
        node->left = left_tree->right;
        left_tree->right = node;
        node->update_height();
        left_tree->update_height();
        return left_tree;
    }

    BinaryNode* balance(BinaryNode* node){
        if(node->balance_factor() == 2){
            if(node->left->balance_factor() == -1)
                node->left = left_rotation(node->left);
            node = right_rotation(node);
        }
        else if(node->balance_factor() == -2){
            if(node->right->balance_factor() == 1)
                node->right = right_rotation(node->right);
            node = left_rotation(node);
        }
        return node;
    }

    bool is_bst(BinaryNode* node,int mx = INT_MAX , int mn = INT_MIN){
        bool state = node->data > mn && node->data < mx;
        if(!state)
            return state;
        bool left_tree = !node->left || is_bst(node->left,node->data,mn);
        if(!left_tree)
            return 0;
        bool right_tree = !node->right || is_bst(node->right,mx,node->data);
        return right_tree;
    }

    void verify() {
        assert(abs(root->balance_factor()) <= 1);
        assert(is_bst(root));
    }

    void insert_value(int val){
        root = insert_node(val,root);
        verify();
    }

    BinaryNode* insert_node(int val,BinaryNode* node){
        if(!node)
            return new BinaryNode(val);

        if(val < node->data){
            if(node->left)
                node->left = insert_node(val,node->left);
            else
                node->left = new BinaryNode(val);
        }
        else{
            if(node->right)
                node->right = insert_node(val,node->right);
            else
                node->right = new BinaryNode(val);
        }
        node->update_height();
        return balance(node);
    }

    void level_order_traversal() {
        if (!root)
            return;

        queue<BinaryNode*> nodes_queue;
        nodes_queue.push(root);

        int level = 0;
        while (!nodes_queue.empty()) {
            int sz = nodes_queue.size();

            cout << "Level " << level << ": ";
            while (sz--) {
                BinaryNode*cur = nodes_queue.front();
                nodes_queue.pop();

                cout << cur->data << " ";
                if (cur->left)
                    nodes_queue.push(cur->left);
                if (cur->right)
                    nodes_queue.push(cur->right);
            }
            level++;
            cout<<"\n";
        }
        cout << "\n******************\n";
    }

    BinaryNode* successor(BinaryNode* node){
        if(node->left)
            return successor(node->left);
        return node;
    }

    void delete_val(int val){
        if(root){
            root = delete_node(val,root);
            verify();
        }
    }

    BinaryNode* delete_node(int val,BinaryNode* node){
        if(!node)
            return nullptr;
        if(val > node->data)
            node->right = delete_node(val,node->right);
        else if(val < node->data)
            node->left = delete_node(val,node->left);
        else{
            BinaryNode* temp = node;
            if(!node->left && !node->right){
                delete node;
                node = nullptr;
            }
            else if(!node->left)
                node = node->right;
            else if(!node->right)
                node = node->left;
            else{
                BinaryNode* mn = successor(node->right);
                node->data = mn->data;
                node->right = delete_node(node->data,node->right);
                temp = nullptr;
            }
            if(temp){
                delete temp;
                temp = nullptr;
            }
        }
        if(node) {
            node->update_height();
            node = balance(node);
        }
        return node;
    }

    pair<bool, int> lower_bound(int target){
        auto res = lower_bound_(target,root);
        if(res == -1)
            return make_pair(0,target);
        return make_pair(1, res);
    }

    int lower_bound_(int target,BinaryNode* node){
        if(!node)
            return -1;
        if(target == node->data)
            return target;
        if(target < node->data) {
            if(node->left && node->left->data > target)
                return lower_bound_(target, node->left);
            else
                return node->data;
        }
        else if(target > node->data)
            return lower_bound_(target,node->right);
    }

    pair<bool, int> upper_bound(int target){
        auto res = upper_bound_(target,root);
        if(res == -1)
            return make_pair(0,target);
        return make_pair(1, res);
    }

    int upper_bound_(int target,BinaryNode* node){
        if(!node)
            return -1;
        if(target < node->data){
            int ans = upper_bound_(target,node->left);
            if(ans != -1)
                return ans;
            return node->data;
        }
        return upper_bound_(target,node->right);
    }

    int upper_bound_count(int target,BinaryNode* node){
        if(!node)
            return 0;
        if(target < node->data){
            int sum = 0;
            if(node->right)
                sum+=node->right->count;
            return sum + upper_bound_count(target,node->left);
        }
        return upper_bound_count(target,node->right);
    }

    int count_inversion(const vector<int>& vec) {
        int sum = 0;
        for (int i = 0; i < (int) vec.size(); ++i) {
            insert_value(vec[i]);
            sum += upper_bound_count(vec[i], root);
        }
        return sum;
    }

    long long min_nodes(int h){
        if(h == 0)
            return 1;
        if(h == 1)
            return 2;
        return 1 + min_nodes(h-1) + min_nodes(h-2);
    }

    long long min_nodes_iter(int h){
        long long start = 0;
        long long second = 0;
        long long ans = 0;
        for (int i = 0; i <= h; ++i) {
            ans = start + second + 1;
            start = second;
            second = ans;
        }
        return ans;
    }
};
void test_lower() {
    AVLTree tree;

    vector<int> v { 10, 5, 20, 15, 50, 70, 2, 13, 40 };
    // 2, 5, 10, 13, 15, 20, 40, 50, 70

    for (int i = 0; i < v.size(); ++i) {
        tree.insert_value(v[i]);
        // tree.level_order_traversal();
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); ++i)
        cout << v[i]+1<< " " << tree.lower_bound(v[i]+1 ).second << "\n";
}

void test_upper() {
    AVLTree tree;

    vector<int> v { 10, 5, 20, 15, 50, 70, 2, 13, 40 };

    for (int i = 0; i < v.size(); ++i)
        tree.insert_value(v[i]);

    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i)
        cout << v[i]<< " " << tree.upper_bound(v[i]).second << "\n";
}

#endif //DATA_STRUCTURE_AVL_TREE_H
