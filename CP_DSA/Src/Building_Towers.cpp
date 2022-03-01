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
        ll x, m;
        cin >> x >> m;

        ll curr_sz = 1;
        ll len = 0;
        ll ops = 0;

        while(len < x){
            len+=curr_sz;
            curr_sz = len;
            ops++;
        }

        cout<<max(0ll, m-ops+1)<<'\n';
        

    }
    
    return 0;
}