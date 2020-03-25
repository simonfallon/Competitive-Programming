//Educational DP-contest: Problem I - Coins
//https://atcoder.jp/contests/dp/tasks/dp_i


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
const int MAXN = 3e3 + 10;
const int MOD = 1e9+7;
const double EPS = 1e-9;
int n;
double p[MAXN], q[MAXN], coins[MAXN], ans;

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout << setprecision(20)<< fixed;
    cin>>n;
    forn(i,n){
        cin>>p[i];
        q[i] = 1-p[i];
    }
    coins[0] = q[0];
    coins[1] = p[0];
    for1(i, n-1){
        coins[i+1] = coins[i] * p[i];
        fored(j, i, 1){
            coins[j] = coins[j]*q[i] + coins[j-1]*p[i];
        }
        coins[0] *= q[i];
    }
    fore(i, (n+1)/2, n){
        ans += coins[i];
    }
    cout<<ans<<el;
}
