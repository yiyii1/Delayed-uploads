// 质数的几种求解方法
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

typedef long long ll;

// 方法1：暴力法
bool isPrime1(ll n) {
  if (n <= 1)
    return false;
  for (ll i = 2; i * i <= n; ++i) {
    if (n % i == 0)
      return false;
  }
  return true;
}

// 方法2：暴力法优化
bool isPrime2(ll n) {
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;
  for (ll i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false; // 所有质数都可以表示为6k ± 1的形式
  }
  return true;
}

// 方法3：埃拉托斯特尼筛法
// 从2开始，依次将每个质数的倍数标记为非质数，直到sqrt(n)，最后剩下的未被标记的数就是质数
// 适用于求解范围内所有质数
vector<ll> isPrime3(ll n) {
  vector<bool> isPrime(n + 1, true);
  isPrime[0] = isPrime[1] = false;
  for (ll i = 2; i * i <= n; ++i) {
    if (isPrime[i]) {
      for (ll j = i * i; j <= n; j += i) {
        isPrime[j] = false;
      }
    }
  }
  vector<ll> primes;
  for (ll i = 2; i <= n; ++i) {
    if (isPrime[i])
      primes.push_back(i);
  }
  return primes;
}

// 方法4: Miller-Rabin 素数测试
// 适用于大数的质数测试，概率性算法
// 快速幂取模
ll mod_mul(ll a, ll b, ll n) { return (ll)((__int128)a * b % n); }

ll power(ll a, ll d, ll n) {
  ll res = 1;
  a = a % n;
  while (d > 0) {
    if (d & 1)
      res = mod_mul(res, a, n);
    a = mod_mul(a, a, n);
    d >>= 1;
  }
  return res;
}

bool millerTest(ll d, ll n, ll a) {
  ll x = power(a, d, n);
  if (x == 1 || x == n - 1)
    return true;
  while (d != n - 1) {
    x = mod_mul(x, x, n);
    d <<= 1;
    if (x == 1)
      return false;
    if (x == n - 1)
      return true;
  }
  return false;
}

// Miller-Rabin 素数测试主函数
bool isPrime4(ll n) { // k 是测试的轮数
  if (n <= 1)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0)
    return false;

  ll d = n - 1;
  while (d % 2 == 0)
    d /= 2;

  ll bases[] = {2, 3, 5, 7, 11, 13, 17, 19}; // 确定性底数，适用于64位整数
  for (ll a : bases) {
    if (!millerTest(d, n, a))
      return false;
  }
  return true;
}

int main() {
  mt19937_64 gen(steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<ll> dis(1, 1e12);
  ll testNum = dis(gen);
  //   ll testNum = 402730253881; // 已知的一个大质数

  cout << "测试随机数: " << testNum << "\n\n";

  auto test = [&](string name, bool (*func)(ll)) {
    auto start = high_resolution_clock::now();
    bool result = func(testNum);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "[" << name << "]\n";
    cout << "结果: " << (result ? "质数" : "合数") << "\n";
    cout << "耗时: " << duration.count() << " 微秒\n\n";
  };

  test("平方根优化 O(sqrt(N))", isPrime1);
  test("6k +/- 1 优化", isPrime2);
  test("Miller-Rabin 确定性底数", isPrime4);

  return 0;
}
