#include <bits/stdc++.h>
using namespace std;

class LRUCache {
public:
    class Node{
        public:
            int key;
            int value;
            Node* next;
            Node* prev;
            Node(int key, int value){
                this->key = key;
                this->value = value;
                next = nullptr;
                prev= nullptr;
            }
    };
    Node* head = new Node(-1,-1);
    Node* tail = new Node(-1,-1);
    int cap;
    unordered_map<int, Node*> mp;
    void addNode(Node* newNode){
        Node* temp= head->next;
        head->next = newNode;
        newNode->next = temp;
        temp->prev= newNode;
        newNode->prev= head;
    }
    void deleteNode(Node* delNode){
        Node* nextNode= delNode->next;
        Node* prevNode= delNode->prev;
        nextNode->prev = prevNode;
        prevNode->next = nextNode;
    }
    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev=head;
    }
    
    int get(int key) {
        if(mp.find(key)!= mp.end()){
            int res = mp[key]->value;
            Node* resNode = mp[key];
            deleteNode(resNode);
            addNode(resNode);
            return res;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(mp.find(key)!=mp.end()){
            Node* existingNode = mp[key];
            mp.erase(key);
            deleteNode(existingNode);
            delete existingNode;
        }
        if(mp.size()>=cap){
            Node* lru = tail->prev;
            mp.erase(lru->key);
            deleteNode(lru);
            delete lru;
        }
        addNode(new Node(key, value));
        mp[key]=head->next;
    }
};