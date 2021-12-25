#include <bits/stdc++.h>
using namespace std;

typedef double D;
typedef long long ll;
typedef long long lli;
typedef long double ld;
typedef unsigned int ui;
typedef unsigned long long ull;

#define F first
#define S second
#define C continue
#define mp make_pair
#define pf push_front
#define pb push_back
#define nl "\n"

#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vll vector<ll>
#define vs vector<string>

#define pii pair<int, int>

#define loop(i, a, b) for (int i = a; i < b; i++)

lli arr[200001];

void fillArr(int n)
{
  priority_queue<pair<int, pair<int, int>>> q; // {5, {1, 5}}

  q.push({n, {-1, -n}});
  int count = 1;

  while (!q.empty())
  {
    int L = -q.top().S.F;
    int R = -q.top().S.S;
    q.pop();

    int mid = (L + R) / 2;
    arr[mid] = count++;

    if (L == R)
      continue;

    if (L < mid)
      q.push({mid - L, {-L, -(mid - 1)}});

    if (mid < R)
      q.push({R - mid, {-(mid + 1), -R}});
  }
}

int main()
{
  int T;
  cin >> T;
  while (T--)
  {
    lli n;
    cin >> n;

    fillArr(n);

    loop(i, 1, n + 1)
      cout<< arr[i] << " ";

    cout << nl;
  }
  return 0;
}