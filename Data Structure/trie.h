//
// Created by youssef on 28/02/23.
//

#ifndef DATA_STRUCTURE_TRIE_H
#define DATA_STRUCTURE_TRIE_H
#include <bits/stdc++.h>
using namespace std;
class trie{
private:
    static const int MAX_CHAR = 26;
    map<char,trie*> child;
    bool isLeaf{};
public:
    trie(){
    }

    void insert(const string& str,int idx = 0){
        if(str.size() == idx)
            isLeaf = 1;
        else{
            char cur = str[idx];
            if(!child.count(cur))
                child[cur] = new trie();
            child[cur]->insert(str,idx+1);
        }
    }

    void insert_itr(const string& str){
        trie* cur = this;
        for (int i = 0; i < str.size(); ++i) {
            if(!cur->child.count(str[i]))
                cur->child[str[i]] = new trie();
            cur = cur->child[str[i]];
        }
        cur->isLeaf = true;
    }

    bool word_exist_itr(const string& str){
        trie* cur = this;
        for (auto &i : str) {
            if(!cur->child.count(i))
                return false;
            cur = cur->child[i];
        }
        return cur->isLeaf;
    }

    bool word_exist(const string& str,int idx = 0){
        if(idx == str.size())
            return isLeaf;

        if(!child.count(str[idx]))
            return false;
        return child[str[idx]]->word_exist(str,idx+1);
    }

    bool prefix_exist(const string& str, int idx = 0){
        if(idx == str.size())
            return true;

        char cur = str[idx];
        if(!child[cur])
            return false;
        return child[cur]->prefix_exist(str,idx+1);
    }

    string first_word_prefix(const string &str){
        string ans;
        trie* cur = this;
        for (int i = 0; i < str.size(); ++i) {
            if(!cur->child[str[i]])
                return str;
            ans+=str[i];
            if((cur->child[str[i]]->isLeaf))
                return ans;
            cur = cur->child[str[i]];
        }
        return str;
    }

    void get_all_strings(vector<string> &vec,string s = ""){
        if(isLeaf)
            vec.push_back(s);
        for(auto i : child){
            i.second->get_all_strings(vec, s + i.first);
        }
    }

    void auto_complete(const string &str, vector<string>&res){
        auto cur = this;
        for(auto &i : str){
            cur = cur->child[i];
        }
        cur->get_all_strings(res,str);
    }

    bool word_exist_with_1_change(const string str){
        vector<string> sup;
        get_all_strings(sup);
        for (int i = 0; i < sup.size(); ++i) {
            int cnt = 0;
            for (int j = 0; j < str.size(); ++j) {
                if(str[j] != sup[i][j])
                    cnt++;
                if(cnt > 1)
                    break;
            }
            if(cnt == 1)
                return 1;
        }
        return 0;
    }

    void print_all_sub(const string &s,int pos = 0){
        auto cur = this;
        for (int i = pos; i < s.size(); ++i) {
            if(!cur->child[s[i]])
                return;
            cur = cur->child[s[i]];
            if(cur->isLeaf)
                cout<<s.substr(pos, i - pos + 1)<<endl;
        }
    }
};

void list_substrs2(const string& str, vector<string> &queries){
    trie tree;
    for (int i = 0; i < queries.size(); ++i) {
        tree.insert(queries[i]);
    }
    for (int i = 0; i < str.size(); ++i) {
        tree.print_all_sub(str,i);
    }
}

void list_substrs(const string& str, vector<string> &queries){
    trie tree;
    for (int i = 0; i < str.size(); ++i) {
        tree.insert(str,i);
    }
    for (int i = 0; i < queries.size(); ++i) {
        if(tree.prefix_exist(queries[i]))
            cout<<queries[i]<<endl;
    }
}

class trie2 {
private:
    map<string , trie2*> child;
    bool isLeaf{};
public:
    trie2() {
    }

    void insert(const vector<string> & vec){
        auto cur = this;
        for (auto &i : vec) {
            cur = insert(i,cur);
        }
    }

    trie2* insert(const string &str,trie2* parent) {
        if (!parent->child.count(str))
            parent->child[str] = new trie2();
        return parent->child[str];
    }

    bool subpath_exist(const vector<string> &vec){
        auto cur = this;
        for (auto &i : vec) {
            if(!cur->child.count(i))
                return false;
            cur = cur->child[i];
        }
        return true;
    }
};
#endif //DATA_STRUCTURE_TRIE_H
