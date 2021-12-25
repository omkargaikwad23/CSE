#include <iostream>
using namespace std;

bool is_prime[1000001];

void sieve()
{
  int maxN = 1000000;
  for(int i=1; i<=maxN; i++) 
    is_prime[i] = true;

  is_prime[0] = is_prime[1] = false;

  for(int i=2; i*i<=maxN; i++){
    if(is_prime[i])
    {
      for(int j=i*i; j<=maxN; j+=i){
        is_prime[j] = false;
      }
    }
  }
}

int main(){
  // int n;
  // cin >> n;
  sieve();

  cout << "1:" << is_prime[1] << endl;
  cout << "2:" << is_prime[2] << endl;
  cout << "3:" << is_prime[3] << endl;
  cout << "4:" << is_prime[4] << endl;
  cout << "5:" << is_prime[5] << endl;
  cout << "6:" << is_prime[6] << endl;

}
