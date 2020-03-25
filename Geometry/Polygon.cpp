// This file contains some basic algorithms on Polygons and sets of points. 
// Checking whether a polygon is convex, Computing the area of a polygon 
// checking whether a point lies inside a convex polygon, and finding the convex Hull
// of a set of points. Most of them were taken from https://vlecomte.github.io/cp-geo.pdf

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
const int MAXN = 1e5+20;
const double EPS=1e-9;

double dist(pt p1, pt p2){
    return hypot(p1.x-p2.x, p1.y-p2.y);
}

double signed_area_parallelogram(pt p1, pt p2, pt p3) {
    return (p2 - p1).cross(p3 - p2);
}

double triangle_area(pt p1, pt p2, pt p3) {
    return abs(signed_area_parallelogram(p1, p2, p3)) / 2.0;
}

int intCcw(pt p, pt q, pt r) {
    if(crossV(toVec(p, q), toVec(p, r)) > 0){
        return 1;       //R A LA IZQUIERDA DE PQ
    } else if(fabs(crossV(toVec(p, q), toVec(p, r))) < EPS){
        return 0;       // PQR COLINEALES
    } else {
        return -1;      //R A LA DERECHAA DE PQ
    }
}

bool collinear(pt p, pt q, pt r) {
    return fabs(crossV(toVec(p, q), toVec(p, r))) < EPS;
}

bool cw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

bool isConvex(vector<pt> puntos){
    bool hasPos=false, hasNeg=false;
    int n = p.size();
    forn(i, n){
        int or = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
        if(or>0) hasPos=true;
        if(or<0) hasNeg=true;
    }
    return !(hasPos && hasNeg);
}

double areaP1(vector<pt> fig) {
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        pt p = i ? fig[i - 1] : fig.back();
        pt q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return fabs(res) / 2;
}

double areaP2(vector <pt> puntos){
    int n=puntos.size();
    double x,y, area=0;
    forn(i, n){
        x += puntos[i].x; y += puntos[i].y;
    }
    x/=n; y/=n;
    pt center = pt(x,y);
    for1(i, n){
        area+=triangle_area(center, puntos[i], puntos[(i+1)%n]);
    }
    return fabs(area);
}

bool lexComp(const pt & l, const pt & r){
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

int sgn(long long val){
    return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

vector<pt> seq;
int n;

bool pointInTriangle(pt a, pt b, pt c, pt point){
    long long s1 = abs(a.cross(b, c));
    long long s2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));
    return s1 == s2;
}

void prepare(vector<pt> & points){
    n = points.size();
    int pos = 0;
    for(int i = 1; i < n; i++){
        if(lexComp(points[i], points[pos]))
            pos = i;
    }
    rotate(points.begin(), points.begin() + pos, points.end());

    n--;
    seq.resize(n);
    for(int i = 0; i < n; i++)
        seq[i] = points[i + 1] - points[0];
}

bool pointInConvexPolygon(pt point){
    if(fabs(seq[0].cross(point)) > EPS && sgn(seq[0].cross(point)) != sgn(seq[0].cross(seq[n - 1])))
        return false;
    if(fabs(seq[n - 1].cross(point)) > EPS && sgn(seq[n - 1].cross(point)) != sgn(seq[n - 1].cross(seq[0])))
        return false;

    if(seq[0].cross(point) == 0)
        return seq[0].sqrLen() >= point.sqrLen();

    int l = 0, r = n - 1;
    while(r - l > 1){
        int mid = (l + r)/2;
        int pos = mid;
        if(seq[pos].cross(point) >= 0)l = mid;
        else r = mid;
    }
    int pos = l;
    return pointInTriangle(seq[pos], seq[pos + 1], pt(0, 0), point);
}

void convex_hull(vector<pt>& a) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end());
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}

int main (){

}
