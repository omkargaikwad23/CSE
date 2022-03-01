#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long int lli;
typedef long double ld;
typedef unsigned int ui;
typedef unsigned long long ull;
#define minArr(a)  *min_element(arr(a))
#define minVec(a)  *min_element(vec(a))
#define maxArr(a)  *max_element(arr(a))
#define maxVec(a)  *max_element(vec(a))
#define pii pair<int, int>
#define loop(i, a, b) for (int i = a; i < b; i++)
bool isPrime(ll n){if(n <= 1)return false;if(n <= 3)return true;if(n%2 == 0 || n%3 == 0)return false;for(ll i=5; i*i<=n; i=i+6)if(n%i == 0 || n%(i+2) == 0)return false;return true;}
ll nextPrime(ll N){if(N<=1)return 2;ll prime = N;bool found = false;while(!found){prime++;if(isPrime(prime))found=true;}return prime;}
#define printarr(a)     for(auto i : a) cout<<i<<' ';cout<<"\n";

int main()
{
  string h1, temp;
  getline(cin, h1);
  string txt;
  getline(cin, txt);

  stringstream X(h1);
  stringstream Y(txt);

  map<char, int>mp1;
  map<char, int>mp2;

  while(getline(X, temp, ' ')){
    loop(i, 0, temp.length()){
      mp1[temp[i]]++;
    }
  }
  while(getline(Y, temp, ' ')){
    loop(i, 0, temp.length()){
      mp2[temp[i]]++;
    }
  }
  bool flag = true;
  map<char, int>::iterator itr;
  for(auto i: mp2){
    itr = mp1.find(i.first);
    //cout << itr->first << " " << i.first << endl;
    if(itr->second < i.second || itr == mp1.end()){
      flag = false;
    }
  }
  if(flag)
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
  
  return 0;
}