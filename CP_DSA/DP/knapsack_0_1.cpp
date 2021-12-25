#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long int lli;
typedef long double ld;
#define pii pair<int, int>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define endl "\n"

#define loop(i, a, b) for (int i = a; i < b; i++)
#define iterate(x) for(auto itr=x.begin(); itr != x.end(); ++itr)
bool isPrime(ll n){if(n <= 1)return false;if(n <= 3)return true;if(n%2 == 0 || n%3 == 0)return false;for(ll i=5; i*i<=n; i=i+6)if(n%i == 0 || n%(i+2) == 0)return false;return true;}
ll nextPrime(ll N){if(N<=1)return 2;ll prime = N;bool found = false;while(!found){prime++;if(isPrime(prime))found=true;}return prime;}
#define printarr(a)     for(auto i : a) cout<<i<<' ';cout<<endl;



// n<=100 && w<=1000
int knapsack(int wt[], int val[], int weight, int n){
    int table[102][1002];
    memset(table, -1, sizeof(table));
    
    if(n==0 || weight==0) return 0;
    if(table[n][weight]!=-1) return table[n][weight];

    if(wt[n-1]<=weight){
      int maxi = max(val[n-1] + knapsack(wt, val, weight-wt[n-1], n-1), knapsack(wt, val, weight, n-1));
      table[n][weight] = maxi;
      return maxi;
    }
    else if(wt[n-1]>weight){
      return knapsack(wt, val, weight, n-1);
    }
    // return table[n][weight];
}

int main()
{
  int T = 1, m, n, temp, weight;
  // cin >> T;
  while(T--)
  {
    
    cin >> n >> weight;
    int wt[n], val[n];

    loop(i, 0, n){
      cin >> wt[i]; 
    }
    loop(i, 0, n){
      cin >> val[i]; 
    }

    int profit = knapsack(wt, val, weight, n);
    
    cout << profit << endl;
  }
  return 0;
}