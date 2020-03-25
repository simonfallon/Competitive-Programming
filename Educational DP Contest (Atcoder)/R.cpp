//Educational DP-contest: Problem R - Walk
//https://atcoder.jp/contests/dp/tasks/dp_r

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
typedef vector<ll> vi;
const int MOD = 1e9+7;
const double PI = atan(1)*4;
const int MAXN = 55;
const double EPS = 1e-9;
int n;
vector<vi> m1, m2, res, mat;
ll k, ans;

vector<vi> multiply(vector<vi> m1, vector<vi> m2){
    int dim = m1[0].size();
    vector<vi> res (dim);
    forn(i,dim){
        res[i].resize(dim);
    }
    forn(i, dim){
        forn(j,dim){
            res[i][j]=0;
            forn(k, dim){
                res[i][j] += m1[i][k]*m2[k][j];
                res[i][j] %= MOD;
            }
        }
    }
    return res;
}

vector<vi> binPow(vector<vi> m, ll e){
    if(e==1){
        return m;
    }
    if(e%2){
        return multiply(m, binPow(multiply(m,m), e/2));
    } else{
        return binPow(multiply(m,m), e/2);
    }
}

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    cin>>n>>k;
    m1.resize(n);
    forn(i,n){
        m1[i].resize(n);
        forn(j,n){
            cin>>m1[i][j];
        }
    }
    mat = binPow(m1, k);
    forn(i,n){
        forn(j,n){
            ans += mat[i][j];
            ans %= MOD;
        }
    }
    cout<<ans<<el;
}
