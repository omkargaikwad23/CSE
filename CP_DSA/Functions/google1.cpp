#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long int lli;
typedef long double ld;
typedef unsigned int ui;
typedef unsigned long long ull;
#define ff first
#define ss second
#define cc continue
#define mp make_pair
#define pf push_front
#define pb push_back
#define nl "\n"
#define minArr(a)  *min_element(arr(a))
#define minVec(a)  *min_element(vec(a))
#define maxArr(a)  *max_element(arr(a))
#define maxVec(a)  *max_element(vec(a))
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vll vector<ll>
#define vs vector<string>
#define pii pair<int, int>
#define loop(i, a, b) for (int i = a; i < b; i++)
#define printarr(a)     for(auto i : a) cout<<i<<' ';cout<<"\n";
bool isPrime(ll n){if(n <= 1)return false;if(n <= 3)return true;if(n%2 == 0 || n%3 == 0)return false;for(ll i=5; i*i<=n; i=i+6)if(n%i == 0 || n%(i+2) == 0)return false;return true;}
ll nextPrime(ll N){if(N<=1)return 2;ll prime = N;bool found = false;while(!found){prime++;if(isPrime(prime))found=true;}return prime;}

int main()
{
  int T;
  cin >> T;
  while (T--)
  {
    int n;
    cin >> n;
    char arr[n];
    unordered_map<int, char>ump;
    loop(i, 0, n){ 
      cin >> arr[i];
      if(arr[i]=='1'){
        ump[i+1]++;
      }
    }
    int dis = 0;
    for(int i=0; i<n; i++){
      if(arr[i]=='0'){
        int min = INT_MAX;
        for(auto j:ump){
          if(abs(j.first-(i+1))<min){
            min = abs(j.first-(i+1));
          }
        }
        dis+=min;
      }
    }
    cout << dis << nl;
  }
  return 0;
}