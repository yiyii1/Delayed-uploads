// 合并K个有序链表
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

// 方法一： 归并排序，两两合并
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
  ListNode dummy(0);
  ListNode *head = &dummy;
  while (l1 && l2) {
    if (l1->val < l2->val) {
      head->next = l1;
      l1 = l1->next;
    } else {
      head->next = l2;
      l2 = l2->next;
    }
    head = head->next;
  }
  head->next = l1 ? l1 : l2;
  return dummy.next;
}

ListNode *mergeKLists(vector<ListNode *> &lists) {
  if (lists.empty())
    return nullptr;
  int interval = 1;
  while (interval < lists.size()) {
    for (int i = 0; i + interval < lists.size(); i += interval * 2) {
      lists[i] = mergeTwoLists(lists[i], lists[i + interval]);
    }
    interval *= 2;
  }
  return lists[0];
}

// 方法二： 优先队列 最小堆
ListNode *mergeKListsPQ(vector<ListNode *> &lists) {
  auto cmp = [](ListNode *a, ListNode *b) { return a->val > b->val; };
  priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> pq(cmp);
  for (auto node : lists) {
    if (node)
      pq.push(node);
  }
  ListNode dummy(0);
  ListNode *head = &dummy;
  while (!pq.empty()) {
    ListNode *node = pq.top();
    pq.pop();
    head->next = node;
    head = head->next;
    if (node->next) //
      pq.push(node->next);
  }
  return dummy.next;
}

int main() {
  ListNode *l1 = new ListNode(1);
  l1->next = new ListNode(4);
  l1->next->next = new ListNode(5);
  l1->next->next->next = new ListNode(11);

  ListNode *l2 = new ListNode(1);
  l2->next = new ListNode(3);
  l2->next->next = new ListNode(4);

  ListNode *l3 = new ListNode(2);
  l3->next = new ListNode(6);
  l3->next->next = new ListNode(0);
  l3->next->next->next = new ListNode(15);

  ListNode *l4 = new ListNode(8);
  l4->next = new ListNode(9);

  ListNode *l5 = new ListNode(7);
  l5->next = new ListNode(10);

  vector<ListNode *> lists = {l1, l2, l3, l4, l5};
  // ListNode *merged = mergeKListsPQ(lists);
  ListNode *merged = mergeKLists(lists);
  while (merged) {
    cout << merged->val << "->";
    merged = merged->next;
  }
  cout << endl;

  return 0;
}