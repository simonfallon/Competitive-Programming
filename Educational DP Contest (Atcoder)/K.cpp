//Educational DP-contest: Problem K - Stones
//https://atcoder.jp/contests/dp/tasks/dp_k

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
const int MAXN = 1e2 + 10;
const int MOD = 1e9+7;
const double EPS = 1e-9;
int n, k;
int dp[100005];
int moves[MAXN];

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout << setprecision(20)<< fixed;
    cin>>n>>k;
    forn(i,n){
        cin>>moves[i];
        dp[moves[i]]=1;
    }
    dp[0]=-1;
    for1(i,moves[0]-1){
        dp[i]=-1;
    }
    fore(i, moves[0]+1, k){
        if(dp[i]==0){
            forn(j,n){
                if(i-moves[j]>=0){
                    if(dp[i-moves[j]] == -1){
                        dp[i]=1;
                        break;
                    }
                }
                if(j==n-1) dp[i]=-1;
            }
        }
    }
    if(dp[k]==1) cout<<"First"<<el;
    else cout<<"Second"<<el;
}
