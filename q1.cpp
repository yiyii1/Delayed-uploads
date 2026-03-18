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