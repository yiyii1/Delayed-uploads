// 大数相加
// 最大64位的十进制正整数的相加，输入为字符串，输出为字符串，溢出舍弃
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string addStrings(string num1, string num2) {
  string result;
  int carry = 0;
  int i = num1.size() - 1, j = num2.size() - 1;

  while (i >= 0 || j >= 0 || carry) {
    int sum = carry;
    if (i >= 0) sum += num1[i--] - '0';
    if (j >= 0) sum += num2[j--] - '0';
    result.push_back((sum % 10) + '0');
    carry = sum / 10;
  }
  // 溢出舍弃，如果超过64位舍弃高位，如果有前导0，舍弃
  if (result.size() > 64) {
    result = result.substr(0, 64);
  }
  while(result.size() > 1 && result.back() == '0') {
    result.pop_back();
  }
  if(result.empty()) {
    return "0";
  }
  reverse(result.begin(), result.end());
  return result;
}

int main() {
  string num1, num2;
  //多组输入输出，直到输入结束
  while (cin >> num1 >> num2) {
    cout << addStrings(num1, num2) << endl;
  }
  return 0;
}