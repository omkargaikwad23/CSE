#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int>vi;
typedef vector<ll>vl;
typedef vector<bool>vb;
#define test ll tt; cin>>tt; while(tt--)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define loop(i, b) for (ll i = 0; i < b; i++)
#define printarr(a) for(auto i:a) cout<<i<<' ';cout<<endl;
#define all(x) (x).begin(), (x).end()
#define mod 1000000007

void solve(){

}

int main()
{
    IOS
    test{
        string num;
        ll n, s;
        cin >> num >> s;
        ll initialSum = 0, l = num.size(), steps = 0ll;
        
        for(int i=0; i<l; i++){
            initialSum += num[i] - '0';
        }
        // cout << "\ninitial : " << initialSum << endl;

        ll mul = 1, carry = 0; l--;

        while(initialSum > s){
            ll digit = num[l]-'0' + carry;
            l--;
            initialSum -= digit; initialSum++;
            mul *= 10;
            carry = 1;
            steps += (mul - (digit*mul)/10);
            // cout << initialSum << " ->";
        }

        cout << steps << "\n";
    }
    
    return 0;
}