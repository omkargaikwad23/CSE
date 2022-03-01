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

// n<=100 && w<=1000
int knapsack(int wt[], int val[], int weight, int n){
    int table[102][1002];
    memset(table, -1, sizeof(table));
    
    if(n==0 || weight==0) 
      return 0;
    if(table[n][weight]!=-1) 
      return table[n][weight];

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

int knapsack_itr(int wt[], int profit[], int weight, int n){
  vector<vector<ll>>dp(n+1, vector<ll>(weight+1, 0));
    
  for(int i=1; i<=n; i++){
      for(int j=0; j<=weight; j++){
          if(wt[i-1]>j){
              dp[i][j] = dp[i-1][j];
          }
          else{
              dp[i][j] = max((profit[i-1]+dp[i-1][j-wt[i-1]]), dp[i-1][j]);
          }
      }
  }
  return dp[n][weight];
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
      cin >> wt[i] >> val[i];
    }
    // loop(i, 0, n){
    //   cin >> val[i]; 
    // }

    int profit = knapsack_itr(wt, val, weight, n);
    
    cout << profit << endl;
  }
  return 0;
}