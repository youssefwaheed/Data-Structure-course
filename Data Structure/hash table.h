//
// Created by youssef on 01/03/23.
//

#ifndef DATA_STRUCTURE_HASH_TABLE_H
#define DATA_STRUCTURE_HASH_TABLE_H
#include <bits/stdc++.h>
using namespace std;
int hash_string_lower_upper_digits(const string& str, int n = 65407){
    long long base = 2 * 26 + 10;
    long long sum = 0;
    long long nn = n;
    for (char i : str) {
        long long res = 0;
        if(islower(i))res = i - 'a';
        else if(isupper(i)) res = 26 + i - 'A';
        else if(isdigit(i))res =26 * 2 + i - '0';
        else
            assert(0);
        sum = (sum * base + res) % nn;
    }
    return sum % nn;
}

int hash_string_folding(string str, int n_ = 65407) {
    long long n = n_;
    long long sum = 0;
    for (int i = 0; i < (int)str.size(); i += 4) {
        string block = str.substr(i, 4);
        sum += hash_string_lower_upper_digits(block);
        sum %= n;
    }
    return sum;
}

struct SomeObject {
    const static int INTERNAL_LIMIT = 2147483647;
    string str1, str2;
    int number;

    int hash() {
        string s = str1 + str2 + to_string(number);
        return hash_string_lower_upper_digits(s,INTERNAL_LIMIT) % INTERNAL_LIMIT;
    }
};

struct PhoneEntry {
    const static int INTERNAL_LIMIT = 65407;
    string name;			// key
    string phone_number;	// data

    int hash() {
        return hash_string_lower_upper_digits(name, INTERNAL_LIMIT);
    }

    PhoneEntry(string name, string phone_number) :
            name(name), phone_number(phone_number) {
    }

    void print()const {
        cout << "(" << name << ", " << phone_number << ")  ";
    }

    bool operator<(const PhoneEntry& another)const{
        return name < another.name;
    }

    PhoneEntry& operator=(const PhoneEntry& another){
        if(this != &another){
            name = another.name;
            phone_number = another.phone_number;
        }
        return *this;
    }

};

class PhoneHashTable{
private:
    vector<vector<PhoneEntry>> table{};
    int table_size{};
public:
    PhoneHashTable(int size):
            table_size(size),table(vector<vector<PhoneEntry>>(size)){}

    bool get(PhoneEntry& phoneEntry){
        int hash = phoneEntry.hash() % table_size;
        for (auto & i : table[hash]) {
            if(i.name == phoneEntry.name){
                phoneEntry = i;
                return true;
            }
        }
        return false;
    }

    const PhoneEntry& operator[](const string& key) const{
        int hash = hash_string_lower_upper_digits(key, 65407) % table_size;
        for (auto & i : table[hash]) {
            if(i.name == key){
                return i;
            }
        }
        throw out_of_range("key not found\n");
    }

    string & operator[](const string& key){
        int hash = hash_string_lower_upper_digits(key, 65407) % table_size;
        for (auto & i : table[hash]) {
            if(i.name == key){
                return i.phone_number;
            }
        }
        table[hash].emplace_back(key,"");
        return table[hash].back().phone_number;
    }


    void put(PhoneEntry phoneEntry){
        int hash = phoneEntry.hash() % table_size;
        for (auto & i : table[hash]) {
            if(i.name == phoneEntry.name){
                i = phoneEntry;
                return;
            }
        }
        table[hash].emplace_back(phoneEntry);
    }


    bool remove(PhoneEntry phoneEntry){
        int hash = phoneEntry.hash() % table_size;
        for (auto & i : table[hash]) {
            if(i.name == phoneEntry.name){
                swap(i,table[hash].back());
                table[hash].pop_back();
                return true;
            }
        }
        return false;
    }

    void print_all() {
        for (int hash = 0; hash < table_size; ++hash) {
            if (table[hash].empty())
                continue;

            cout << "Hash " << hash << ": ";
            for (auto &phone : table[hash])
                phone.print();
            cout << "\n";
        }
    }
};

class PhoneHashTable2{
private:
    int table_size{};
    vector<PhoneEntry*> table{};
    int added_elements{};
    PhoneEntry *deleted {};
public:
    PhoneHashTable2(int size):table_size(size){
        table.resize(size);
        deleted = new PhoneEntry("","");
    }

    bool put(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < table_size; ++i) {
            if(table[idx] == deleted || !table[idx]){
                table[idx] = new PhoneEntry(phone.name,phone.phone_number);
                return true;
            }
            else if(table[idx]->name == phone.name) {
                table[idx]->phone_number = phone.phone_number;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }

    bool remove(PhoneEntry phone) {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < table_size; ++i) {
            if(!table[idx])
                break;
            if(table[idx]->name == phone.name) {
                delete table[idx];
                table[idx] = deleted;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }

    bool get(PhoneEntry &phone) {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < table_size; ++i) {
            if(!table[idx])
                break;
            if(table[idx]->name == phone.name) {
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }

    void print_all() {
        for (int hash = 0; hash < table_size; ++hash) {
            cout << hash << " ";
            if (table[hash] == deleted)
                cout << " X ";
            else if (!table[hash])
                cout << " E ";
            else
                table[hash]->print();
            cout << "\n";
        }
        cout << "******************\n";
    }
};

int count_anagram_substrings(const string &str){
    unordered_set<string> set;
    for (int start = 0; start < (int) str.size(); ++start) {
        for (int end = start; end < (int) str.size(); ++end) {
            string s = str.substr(start, end - start + 1);
            std::sort(s.begin(), s.end());
            set.emplace(s);
        }
    }
    return set.size();
}

#endif //DATA_STRUCTURE_HASH_TABLE_H
