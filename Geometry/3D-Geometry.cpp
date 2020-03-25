// This file contains the structs and methods related to 3D Geometry in Competitive Programming
// The structs provide a way to represent 3D objects such as Points, Planes, 
// alternative coordinates systems, and lines. Each of them has its own methods to compute
// and find important and frequently asked things such as distances, angles, projections, 
// reflections and so on. Most of them were taken from https://vlecomte.github.io/cp-geo.pdf

#include <bits/stdc++.h>
#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(ll i=1; i<= n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,r,l) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define deb(x) cout<< #x<< " " << x<<el
#define INF (1LL<<62)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef vector<ll> vi;
const double PI = atan(1)*4;
const int MAXN = 1e5+20;
const double EPS = 1e-9;

struct pt { ld x,y;           //Punto ld
    pt() {x = y = 0.0; }           // constructor default
    pt(ld _x, ld _y) : x(_x) , y(_y) {}
    bool operator < (pt other) const {
        if(fabs(x-other.x)>EPS)
            return x < other.x;
        return y < other.y;
    }
    bool operator == (pt other) const {
        return fabs(x-other.x)<EPS && fabs(y-other.y)<EPS;
    }
    bool operator != (pt other) const {return !(*this==other);}
    pt operator*(const ld& s) const {return pt(x*s,y*s);}
    pt operator/(const ld& s) const {return pt(x/s,y/s);}
    pt operator-(const pt& p) const { return pt(x - p.x, y - p.y); }
    pt operator-() const {return {-x,-y};}
    pt operator+(const pt& p) const { return pt(x + p.x, y + p.y); }
    ld cross(const pt& p) const { return x * p.y - y * p.x; }
    ld cross(const pt& a, const pt& b) const { return (a - *this).cross(b - *this); }
    ld dot(const pt& p) const { return(x * p.x + y * p.y);}
    void print() {cout<<"x = "<<x<<"   y = "<<y<<el;}
    ld sq() {return x*x + y*y; }
    ld abs() {return sqrt(x*x + y*y);}
};


//POINTS AND PRODUCTS

struct p3 {
    ld x, y, z;

    p3 operator+(p3 p) {return {x+p.x, y+p.y, z+p.z};}
    p3 operator-(p3 p) {return {x-p.x, y-p.y, z-p.z};}
    p3 operator*(ld s) {return {x*s, y*s, z*s};}
    p3 operator/(ld s) {return {x/s, y/s, z/s};}
    p3 operator-() const {return {-x,-y,-z};}

    bool operator==(p3 p) {return tie(x,y,z) == tie(p.x, p.y, p.z);}
    bool operator!=(p3 p) {return !operator==(p);}
};

p3 zero{0,0,0};

ld operator|(p3 v, p3 w) {
    return v.x*w.x + v.y*w.y + v.z*w.z;
}

p3 operator*(p3 v, p3 w){
    return {v.y*w.z - v.z*w.y,
            v.z*w.x - v.x*w.z,
            v.x*w.y - v.y*w.x};
}

ld sq(p3 v){
    return v|v;
}

ld abs(p3 v) {
    return sqrt(sq(v));
}

p3 unit(p3 v) {
    return v/abs(v);
}

double angle(p3 v, p3 w){
    double cosTheta  = (v|w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

ld orient (p3 p, p3 q, p3 r, p3 s){
    return (q-p)*(r-p)|(s-p);
}

ld orientN(p3 p, p3 q, p3 r, p3 n){
    return (q-p)*(r-p)|n;
}

//PLANES

struct plane {
    p3 n; ld d;
    //NORMAL AND OFFSET D
    plane(p3 n, ld d) : n(n), d(d) {}
    //FROM NORMAL AND POINT
    plane(p3 n, p3 p) : n(n), d(n|p) {}
    //FROM 3 NON-COL POINTS
    plane(p3 p, p3 q, p3 r) : plane((q-p)*(r-p), p) {}

    ld side(p3 p){return (n|p)-d;}
    ld dist(p3 p){return abs(side(p))/abs(n);}
    plane translate(p3 t){return plane(n, d+(t|n));}
    plane shiftUp(ld delta){return plane(n, d+delta*abs(n));}
    p3 proj(p3 p){return p - n*side(p)/sq(n);}
    p3 refl(p3 p){return p - n*2*side(p)/sq(n);}

};

struct coords{
    p3 o, dx, dy, dz;

    coords(p3 p, p3 q, p3 r) : o(p) {
        dx = unit(q-p);
        dz = unit(dx*(r-p));
        dy = dx*dz;
    }

    pt pos2d(p3 p){return {(p-o)|dx, (p-o)|dy};}
    p3 pos3d(p3 p){return{(p-o)|dx, (p-o)|dy, (p-o)|dz};}
};

//LINES

struct line3 {
    p3 d, o;
    //FROM TWO POINTS P,Q
    line3 (p3 p, p3 q) : d(q-p), o(p) {}
    //FROM TWO PLANES
    line3 (plane p1, plane p2){
        d = p1.n*p2.n;
        o = (p2.n*p1.d - p1.n*p2.d)*d/sq(d);
    }

    ld sqDist(p3 p){return sq(d*(p-o))/sq(d);}
    ld dist(p3 p){return sqrt(sqDist(p));}
    bool cmpProj(p3 p, p3 q){return (d|p) < (d|q);}

    p3 proj(p3 p){return o + d*(d|(p-o)/sq(d));}
    p3 refl(p3 p){return proj(p)*2-p;}
    p3 inter(plane p) {return o - d*p.side(o)/(d|p.n);}

};

ld dist(line3 l1, line3 l2){
    p3 n = l1.d*l2.d;
    if(n == zero) return l1.dist(l2.o);
    return abs((l2.o - l1.o)|n)/abs(n);
}

p3 closestOnL1(line3 l1, line3 l2){
    p3 n2 = l2.d*(l1.d*l2.d);
    return l1.o + l1.d*((l2.o-l1.o)|n2)/(l1.d|n2);
}

ld smallAngle(p3 v, p3 w){
    return acos(min(abs(v|w)/abs(v)/abs(w), ld(1.0)));
}

ld angle(plane p1, plane p2){
    return smallAngle(p1.n, p2.n);
}

bool isParallel(plane p1, plane p2){
    return p1.n*p2.n == zero;
}

bool isPerpendicular(plane p1, plane p2){
    return (p1.n|p2.n) == 0;
}

ld angle(line3 l1, line3 l2){
    return smallAngle(l1.d, l2.d);
}

bool isParallel(line3 l1, line3 l2){
    return l1.d*l2.d == zero;
}

bool isPerpendicular(line3 l1, line3 l2){
    return (l1.d|l2.d) == 0;
}

double angle(plane p, line3 l){
    return PI/2-smallAngle(p.n, l.d);
}

bool isParallel(plane p, line3 l){
    return (p.n|l.d) == 0;
}

bool isPerpendicular(plane p, line3 l){
    return p.n*l.d == zero;
}

line3 perpTrough(plane p, p3 o){
    return line3(o, o+p.n);
}

plane perpTrough(line3 l, p3 o){
    return plane(l.d, o);
}


//POLYHEDRONS
p3 vectorArea2(vector<p3> P){
    p3 S = zero;
    int n = P.size();
    forn(i, n)
        S = S + P[i]*P[(i+1)%n];
    return S;
}

ld area(vector<p3> P){
    return abs(vectorArea(P))/2.0;
}

int main (){

}
