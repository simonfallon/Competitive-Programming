//Educational DP-contest: Problem C - Vacation
//https://atcoder.jp/contests/dp/tasks/dp_c

#include <bits/stdc++.h>
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
const int MAXN = 1e5+20;
const double EPS = 1e-9;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int n;
    cin>>n;
    ll a[n], b[n], c[n], maxA[n], maxB[n], maxC[n];
    forn(i,n){
        cin>>a[i]>>b[i]>>c[i];
    }
    maxA[0]=a[0];
    maxB[0]=b[0];
    maxC[0]=c[0];
    for1(i,n-1){
        maxA[i]=max(maxB[i-1],maxC[i-1])+a[i];
        maxB[i]=max(maxA[i-1],maxC[i-1])+b[i];
        maxC[i]=max(maxB[i-1],maxA[i-1])+c[i];
    }
    cout<<max(maxA[n-1],max(maxB[n-1],maxC[n-1]))<<el;
}
