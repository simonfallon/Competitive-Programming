//Educational DP-contest: Problem B - Frog 2
//https://atcoder.jp/contests/dp/tasks/dp_a

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


using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
const double PI = atan(1)*4;
const int MAXN = 1e5+20;
const int INF = 1<<30;
const double EPS = 1e-9;
ll dp[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int n,k;
    cin>>n>>k;
    ll h[n];
    forn(i,n){
        cin>>h[i];
    }
    fill(dp,dp+n, INF);
    dp[0]=0;
    for1(i,n-1){
        for1(j, min(k,i)){
            dp[i]=min(dp[i-j]+abs(h[i]-h[i-j]),dp[i]);
        }
    }
    cout<<dp[n-1];
}
