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

/*
1 3 2 4 5

*/

bool bubbleSort(int a[], int n)
{
	int i, j;
	for(i=0;i<n;i++)
	{
		for(j=0; j<(n-i-1); j++)
		{   
            
			if(a[j] > a[j+1] )
			{
                if((a[j]+a[j+1])%2!=1){
                    return false;
                }
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
    return true;
}

int main()
{
    IOS
    test{
        int n;
        cin >> n;
        int arr[n];
        loop(i, n) cin >> arr[i];

        bool temp = bubbleSort(arr, n);

        cout << (temp ? "Yes" : "No") << "\n";
    }
    
    return 0;
}