//Educational DP-contest: Problem H - Grid 1
//https://atcoder.jp/contests/dp/tasks/dp_h


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
typedef pair<long long,long long> pll;
typedef tuple<long double,int,int> tdii;
const double PI = atan(1)*4;
const int MAXN = 1e3 + 10;
const int MOD = 1e9+7;
const double EPS = 1e-9;
int dp[MAXN][MAXN];
int h, w, u, v, ans;
bool seen[MAXN];
char g[MAXN][MAXN];

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>>h>>w;
    for1(i,h){
        for1(j,w){
            cin>>g[i][j];
        }
    }
    g[0][0] = '.';
    forn(i,h+1){
        g[0][i] = g[i][0] = '.';
    }
    dp[1][1] = 1;
    for1(i,h){
        for1(j,w){
            if(i==1 && j==1) continue;
            if(g[i][j]=='.') dp[i][j] = (g[i-1][j]=='.' ? dp[i-1][j] : 0) +(g[i][j-1]=='.' ? dp[i][j-1] : 0 );
            dp[i][j] %= MOD;
        }
    }
    cout<<dp[h][w]<<el;

}
