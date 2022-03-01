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

vector<vector<int>> g(10e5+5);
vector<bool> vis(10e5+5, false);

// O(E+V)
void solve(int u){
    vis[u] = true;
    for(auto v : g[u]){
        if(!vis[v]){
            solve(v);
        }
    }
}

int main()
{
    IOS
    test{
        int n;
        cin >> n;
        int arr[n];
        for(int i=0; i<=n; i++){
            vis[i] = false;
            g[i].clear();
        }

        vector<pii> sorted;
        loop(i, n){ 
            cin >> arr[i];
            sorted.push_back({arr[i], i});
        }

        sort(all(sorted));

        /*
        i<j if and only if pi>pj.
        2 1 4 3 5

        sorted: 
        (1, 1), (2, 0), (3, 3), (4, 2), (5, 4)
        
        i = 0; u = 2
        v = 1;
        */
        
        int maxi = 0;
        for(int i=0; i<n; i++){
            int u = arr[i];

            if(u > maxi) maxi = u;
            else continue;

            for(auto v : sorted){
                if(v.first < u && v.second > i){
                    // cout << u << " " << v.first << endl;
                    g[u].push_back(v.first);
                    g[v.first].push_back(u);
                }else if(v.first >= u){
                    break;
                }
            }
        }

        int ans = 0;
        for(int i=0; i<n; i++){
            if(!vis[arr[i]]){
                ans++;
                solve(arr[i]);
            }
        }
        cout << ans << "\n";

    }
    
    return 0;
}