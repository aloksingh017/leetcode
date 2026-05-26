#include <bits/stdc++.h>
using namespace std;

class LRUCache {
public:
  class Node {
  public:
    int key;
    int value;
    Node *next;
    Node *prev;
    Node(int key, int value) {
      this->key = key;
      this->value = value;
    }
  };

  Node *head = new Node(-1, -1);
  Node *tail = new Node(-1, -1);
  int cap;
  unordered_map<int, Node *> mp;

  LRUCache(int capacity) {
    cap = capacity;
    head->next = tail;
    tail->prev = head;
  }
  void addNode(Node *newNode) {
    Node *temp = head->next;
    newNode->next = temp;
    temp->prev = newNode;
    head->next = newNode;
    newNode->prev = head;
  }
  void deleteNode(Node *delNode) {
    Node *delPrev = delNode->prev;
    Node *delNext = delNode->next;
    delPrev->next = delNext;
    delNext->prev = delPrev;
  }
  int get(int key) {
    if (mp.find(key) != mp.end()) {
      Node *resNode = mp[key];
      int res = resNode->value;
      deleteNode(resNode);
      addNode(resNode);
      mp[key] = head->next;
      return res;
    }
    return -1;
  }

  void put(int key, int value) {
    if (mp.find(key) != mp.end()) {
      Node *existingNode = mp[key];
      mp.erase(key);
      deleteNode(existingNode);
    }
    if (mp.size() >= cap) {
      mp.erase(tail->prev->key);
      deleteNode(tail->prev);
    }
    addNode(new Node(key, value));
    mp[key] = head->next;
  }
};
