// 合并n个升序数组
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

vector<int> mergeKArrays(vector<vector<int>> &arrays) {
  using Element = tuple<int, int, int>;          //值，数组索引，元素索引
  priority_queue<Element, vector<Element>, greater<Element>> pq;
  for (int i = 0; i < arrays.size(); i++) {     //每个数组第一个元素入堆
    if (!arrays[i].empty())
      pq.emplace(arrays[i][0], i, 0);
  }
  vector<int> result;
  while (!pq.empty()) {
    auto [val, arrIdx, elemIdx] = pq.top();
    pq.pop();
    result.push_back(val);

    if (elemIdx + 1 < arrays[arrIdx].size())
      pq.emplace(arrays[arrIdx][elemIdx + 1], arrIdx, elemIdx + 1);
  }
    return result;
}

int main() {
  vector<vector<int>> arrays = {{1, 4, 5}, {1, 3, 4}, {2, 6}};
  vector<int> merged = mergeKArrays(arrays);
  for (int num : merged) {
    cout << num << " ";
  }
  cout << endl;
  return 0;
}