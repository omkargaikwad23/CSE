#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int>vi;
#define test ll tt; cin>>tt; while(tt--)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define loop(i, b) for (ll i = 0; i < b; i++)
#define iterate(x) for(auto itr=x.begin(); itr != x.end(); ++itr)
#define printarr(a) for(auto i : a) cout<<i<<' ';cout<<endl;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define mod 1000000007
bool isPrime(ll n){if(n <= 1)return false;if(n <= 3)return true;if(n%2 == 0 || n%3 == 0)return false;for(ll i=5; i*i<=n; i=i+6)if(n%i == 0 || n%(i+2) == 0)return false;return true;}
ll nextPrime(ll N){if(N<=1)return 2;ll prime = N;bool found = false;while(!found){prime++;if(isPrime(prime))found=true;}return prime;}

int n = 1001, m = 1001;
vector<vector<char>>grid;
vector<vector<bool>>vis;
vector<vector<pii>>parent;
pii start, dest;
string ans = "1";

// R, L, U, D
vector<pii>dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool bfs(pii start){
    queue<pii>q;
    q.push(start);
    parent[start.first][start.second] = {start.first, start.second};

    while(!q.empty()){
        int i = q.front().first, j = q.front().second;
		q.pop();

        for(auto d : dir){
            int new_i = i + d.first;
            int new_j = j + d.second;

            if(new_i<0 || new_j<0) continue;
            if(new_i>=n || new_j>=m) continue;
            if(vis[new_i][new_j] || grid[new_i][new_j]=='#') continue;

            vis[new_i][new_j] = true;
            parent[new_i][new_j] = {i, j};
            q.push({new_i, new_j});
            if(grid[new_i][new_j]=='B') return true;
        }
    }
    return false;
}

void solve(){
    bfs(start);

    loop(i, n){
        loop(j, m){
            cout << "(" << parent[i][j].first << "," << parent[i][j].second << "\t";
        }
        cout <<"\n";
    }
    
    int i = dest.first, j = dest.second;
    vector<pii>path;
    path.push_back({i, j});
    while(1){
        cout << i << " " << j << " "  << grid[i][j] << endl;
        i = parent[i][j].first;
        j = parent[i][j].second;
        path.push_back({i, j});
        if(grid[i][j]=='A') break;
    }

    for(int k=0; k<path.size(); k++){
        int xi = path[k+1].first - path[k].first;
        int xj = path[k+1].second - path[k].second;

        if(xi==1 && xj==0){
            ans += 'D';
        }else if(xi==-1 && xj==0){
            ans += 'U';
        }
        else if(xi==0 && xj==1){
            ans += 'L';
        }
        else if(xi==0 && xj==-1){
            ans += 'R';
        }
    }

    cout << ans << endl;
}

int main()
{
    IOS
    cin >> n >> m;
    grid.resize(n, vector<char>(m));
    vis.resize(n, vector<bool>(m));
    parent.resize(n, vector<pii>(m));

    loop(i, n){
        loop(j, m){
            cin >> grid[i][j];
            if(grid[i][j]=='A'){
                start = {i, j};
            }
            if(grid[i][j]=='B'){
                dest = {i, j};
            }
        }
    }
    solve();
    
    return 0;
}