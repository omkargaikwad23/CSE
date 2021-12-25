#include <bits/stdc++.h>
using namespace std;

//Brute Force Approach
void primeFact(int n){
  for(int i=2; i<= n;i++)
  {
    if(n%i == 0){
      int cnt = 0;
      while(n%i == 0){
        cnt++, n/=i;
      }
      cout << i << "^" << cnt << endl;
    }
  }
}

//Optimized approach TC: O(sqrt(n))
void primeFact1(int n){
  for(int i=2; i*i<= n;i++)
  {
    if(n%i == 0){
      int cnt = 0;
      while(n%i == 0){
        cnt++, n/=i;
      }
      if(n>1)
        cout << i << "^" << cnt << endl;
    }
  }
}

//prime factorisation using sieve
int arr[1000001];
void sieve()
{
  int maxN = 1000000;
  for(int i=0; i<=maxN; i++){
    arr[i] = -1;
  }
  for(int i=2; i<=maxN; i++){
    if(arr[i]== -1){
      for(int j=i; j<=maxN; j+=i){
        if(arr[j]==-1){
          arr[j] = i;
        }
      }
    }
  }
}

int main()
{
  int n;
  cin >> n;
  primeFact(n);
  return 0;
}