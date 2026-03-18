// 无重复字符的最长子串
// 给定一个字符串 s ，请你找出其中不含有重复字符的最长子串的长度。
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
int main() {
  string s;
  cin >> s;
  int l = 0, r = 1, ans = 0;
  unordered_set<char> st;
  st.emplace(s[l]);
  while (r < s.length()) {
    while (st.find(s[r]) != st.end()) {
      st.erase(s[l]);
      l++;
    }
    ans = max(r - l + 1, ans);
    st.emplace(s[r]);
    r++;
  }
  cout << ans;
  return 0;
}