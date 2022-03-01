#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
#define test   \
    ll tt;     \
    cin >> tt; \
    while (tt--)
#define IOS                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
#define loop(i, b) for (ll i = 0; i < b; i++)
#define printarr(a)       \
    for (auto i : a)      \
        cout << i << ' '; \
    cout << endl;
#define all(x) (x).begin(), (x).end()
#define mod 1000000007

struct projects
{
    string projectName;
    int daysToComplete;
    float scoreAwarded;
    int bestBefore;
    int contributorsCount;
    float fact;
    int index;
    vector<pair<string, int>> skills;
};
map<string, vector<pair<string, int>>> cbs;
int c, p = 10e5+5, cur_day, total_score;
vector<projects> arr(p);


bool cmpByFact(projects& p1, projects& p2){
    return p1.fact > p2.fact;
}

void inputCbs(){
    cin >> c >> p;

    string name, skill_name;
    int skill_count, skill_level;
    for (int i = 0; i < c; i++)
    {
        cin >> name;
        cin >> skill_count;

        for (int j = 0; j < skill_count; j++)
        {
            cin >> skill_name;
            cin >> skill_level;
            // cin.ignore();
            cbs[name].push_back({skill_name, skill_level});
        }
    }

    // cout << c << " " << p << endl;
    // for (auto &it : cbs)
    // {
    //     // cout << c << " " << p << endl;
    //     cout << it.first << " " << it.second.size() << endl;
    //     for (auto &ele : it.second)
    //     {
    //         cout << ele.first << " " << ele.second << endl;
    //     }
    // }
}

void inputPj(){
    for (int i = 0; i < p; i++)
    {
        cin >> arr[i].projectName;
        cin >> arr[i].daysToComplete;
        cin >> arr[i].scoreAwarded;
        cin >> arr[i].bestBefore;
        cin >> arr[i].contributorsCount;
        arr[i].fact = (float)(arr[i].scoreAwarded / arr[i].contributorsCount);
        vector<pair<string, int>> skillsReq(arr[i].contributorsCount);
        for (int j = 0; j < arr[i].contributorsCount; j++)
        {
            string skill;
            int level;
            cin >> skill;
            cin >> level;
            arr[i].skills.push_back({skill, level});
        }
    }
}

bool canPossible(){
    for(auto pj : arr){
        
        for(auto con : cbs){

        }
    }
}

int main()
{
    IOS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    inputCbs();
    inputPj();
    
    sort(all(arr), cmpByFact);

    
    for (int i = 0; i < p; i++)
    {
        cout << arr[i].projectName << " " << arr[i].daysToComplete << " " << arr[i].scoreAwarded << " " << arr[i].bestBefore << " " << arr[i].contributorsCount << " " << arr[i].fact << endl;
        for (int j = 0; j < arr[i].contributorsCount; j++)
        {
            cout << arr[i].skills[j].first << " " << arr[i].skills[j].second << endl;
        }

        
    }

    
    return 0;
}