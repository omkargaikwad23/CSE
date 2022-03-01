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

// min index of array element not less than given one
int solve(int arr[], int n, int x){
    int last = n-1, first = 0, mid;

    while(first <= last) {
        mid = first + (last - first + 1)/2;
        if(arr[mid] < x) {
            first = mid + 1;
        } else {
            last = mid - 1;
        }
    }
    return first;
}

int main()
{
    IOS
    int n, q; cin >> n >> q;

    int arr[n], queries[q];
    loop(i, n) {
        cin >> arr[i];
    }
    loop(i, q) {
        cin >> queries[i];
    }
    
    loop(i, q){
        int ele = queries[i];
        cout << solve(arr, n, ele) + 1  << "\n";
    }
    return 0;
}