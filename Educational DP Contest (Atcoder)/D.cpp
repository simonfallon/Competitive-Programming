//Educational DP-contest: Problem D - Knapsack 1
//https://atcoder.jp/contests/dp/tasks/dp_d

#include <bits/stdc++.h>
#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,r,l) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define INF (1LL<<62)

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
const double PI = atan(1)*4;
const double EPS = 1e-9;
const int MAXN = 101;
const int MAXW = 1e9+5;
unordered_map<ii,int> pos;
int n, W,nuevas,tam;
int w[MAXN], v[MAXN];
vector<ii> dp;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    cin>>n>>W;
    for1(i,n){
        cin>>w[i]>>v[i];
    }
    pos[ii(W-w[1],v[1])]=1;
    pos[ii(W,0)]=0;
    dp.pb(ii(W,0));
    dp.pb(ii(W-w[1],v[1]));
    int ans = v[1];
    fore(i,2,n){
        nuevas=0;
        tam = dp.size();
        forn(j, tam){
            ii con = ii(dp[j].fi-w[i], dp[j].se+v[i]);
            if(con.fi>=0&&pos[con]==0){
                pos[con]=tam+nuevas;
                nuevas++;
                dp.pb(con);
                ans = max(ans, con.se);
            } else if(con.fi>=0&&dp[pos[con]].se<con.se){
                dp[pos[con]]=ii(con.fi, con.se);
                ans=max(ans,con.se);
            }
        }
    }
    cout<<ans<<el;
}
