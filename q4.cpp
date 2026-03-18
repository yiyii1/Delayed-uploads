// 缓存，支持get、put操作，有容量上限，操作复杂度o(1)
#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
  int key;
  int value;
  Node *prev;
  Node *next;
  Node(int k = 0, int v = 0) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
  int cap;
  unordered_map<int, Node *> cache;
  Node *head;
  Node *tail;

  void remove(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void addToHead(Node *node) {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
  }

public:
  LRUCache(int capacity) : cap(capacity) {
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (cache.find(key) == cache.end()) {
      return -1;
    }
    Node *node = cache[key];
    remove(node);
    addToHead(node);
    return node->value;
  }

  void put(int key, int value) {
    if (cache.find(key) != cache.end()) {
      remove(cache[key]);
      delete cache[key];
      cache.erase(key);
    }
    if (cache.size() == cap) {
      Node *lru = tail->prev;
      remove(lru);
      cache.erase(lru->key);
      delete lru;
    }
    Node *node = new Node(key, value);
    addToHead(node);
    cache[key] = node;
  }

  ~LRUCache() {
    Node *cur = head;
    while (cur) {
      Node *next = cur->next;
      delete cur;
      cur = next;
    }
  }
};

// 容量为3，执行如下操作 put(1,1), put(2,2), get(1), put(3,3), put(4,4),get(2),get(1), put(5,5), get(1), get(3), get(4), get(5)
int main() {
  LRUCache cache(3);
  cache.put(1, 1);
  cache.put(2, 2);
  cout << cache.get(1) << endl; // 返回 1
  cache.put(3, 3);
  cache.put(4, 4);
  cout << cache.get(2) << endl; // 返回 -1 (未找到)
  cout << cache.get(1) << endl; // 返回 1
  cache.put(5, 5);
  cout << cache.get(1) << endl; // 返回 -1 (未找到)
  cout << cache.get(3) << endl; // 返回 3
  cache.put(6, 6);
  cout << cache.get(4) << endl; // 返回 4
  cout << cache.get(5) << endl; // 返回 5

  return 0;
}