#include <iostream>
#include <vector>
using namespace std;

  double findMaxAverage(vector<int> & nums, int k) {
    int ans = 0, ave = 0;
    for (int i = 0; i < k; i++) {
      ans += nums[i];
    }
    for (int i = k; i < nums.size(); i++) {
      ans = max(ans, ans + nums[i] - nums[i - k]);
    }
    double aveans = (double)ans / k;
    return aveans;
  }
int main() {

  vector<int> tp = {0, 1, 1, 3, 3};
  int k = 4;
  double ans = findMaxAverage(tp, k);
  cout << ans;
}