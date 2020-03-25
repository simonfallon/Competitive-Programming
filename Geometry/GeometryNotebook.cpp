//This  file contains a list of methods related to Geometry in Competitive Programming. 
//Most of them were taken from https://vlecomte.github.io/cp-geo.pdf

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


struct pt { ld x,y;           
    pt() {x = y = 0.0; }           // DEFAULT CONSTRUCTOR
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

typedef pair<pt,pt> wall;
ostream& operator<<(ostream& os, pt p){
    return os <<"("<<p.x<<","<<p.y<<")";
}

ostream& operator<<(ostream& os, ii p){
    return os <<"("<<p.fi<<","<<p.se<<")";
}

template <typename T> int sgn(T x){
    return (T(0)<x) - (x<T(0));
}

struct circle  {
    ld x,y,r;
    circle() {x = y = r = 0.0; }           // DEFAULT CONSTRUCTOR
    circle(ld _x, ld _y, ld _r) : x(_x) , y(_y), r(_r) {}
    circle operator- (circle c) {
        circle res = { x-c.x, y-c.y, r };
        return res;
    }
};

ld sq(pt p){
    return p.x*p.x + p.y*p.y;
}

ld abs(pt p){
    return sqrt(sq(p));
}

ld dist(pt p1, pt p2){
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

pt scale(pt p, ld factor, pt c) { // nonnegative s = [<1 .. 1 .. >1]
    return c+(p-c)*factor;
} // shorter.same.longer

pt translate(pt p, pt v) { // translate p according to v
    return p+v;
}

pt rotO(pt p, ld theta){                //ROTATE RESPECT TO THE ORIGIN - ANGLE IN RAD
    return pt(p.x*cos(theta) - p.y*sin(theta),
                 p.x*sin(theta) + p.y*cos(theta));
}

pt rotP(pt p1, pt p2, ld theta){               //ROTATE RESPECT TO A POINT P2 - ANGLE IN RAD
    p1.x-=p2.x;
    p1.y-=p2.y;
    pt p3 (p1.x*cos(theta) - p1.y*sin(theta) + p2.x,
              p1.x*sin(theta) + p1.y*cos(theta) + p2.y);
    return p3;
}

pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq){
    pt pq = q-p, num{pq.cross(fq-fp), pq.dot(fq-fp)};
    return fp+ pt{(r-p).cross(num), (r-p).dot(num)}/pq.sq();
}

ld cross(pt p1, pt p2){
    return p1.x*p2.y-p1.y*p2.x;
}

ld dot(pt p1, pt p2){
    return p1.x*p2.x + p1.y*p2.y;
}

pt perp(pt p){
    return {-p.y, p.x};
}

bool isPerp (pt v, pt w){
    return dot(v,w)==0;
}

ld orient (pt a, pt b, pt c){
    return cross(b-a,c-a);
}

ld angle(pt v, pt w){
    double cosTheta = dot(v,w)/v.abs()/w.abs();
    return acos(max(-1.0, min(1.0, cosTheta)));
}

bool inAngle(pt a, pt b, pt c, pt p){
    assert(orient(a,b,c) != 0);
    if(orient(a,b,c)<0) swap(b,c);
    return orient(a,b,p)>=0 && orient(a,c,p)<=0;
}

ld orientedAngle(pt a, pt b, pt c){
    if(orient(a,b,c)>0) return angle(b-a, c-a);
    else{
        return 2*PI-angle(b-a, c-a);
    }
}

struct line{
    pt v; ld c;
    // FROM DIRECTION VECTOR V, OFFSET C
    line(pt v, ld c) : v(v), c(c) {}
    // FROM EQUATION AX+BY=C
    line(ld a, ld b, ld c) : v({b,-a}), c(c) {}
    // FROM POINTS P->Q
    line(pt p, pt q) : v(q-p), c(cross(v,p)) {}

    ld side(pt p){return cross(v,p)-c;} // LEFT SIDE: >0. ON THE LINE: =0, RIGHT SIDE: <0
    ld dist(pt p) {return abs(side(p)) / abs(v);} //DIST FROM P TO L
    ld sqDist(pt p) {return side(p)*side(p) / sq(v);}
    line perpTrough(pt p){return {p, p + perp(v)};} // PERPENDICULAR TO L TROUGH P
    bool cmpProj(pt p, pt q){return dot(v,p)<dot(v,q);} // TO SORT POINTS(OR ORTHOGONAL PROJECTIONS) ALONG L
    line translate(pt t){return {v, c + cross(v,t)};}
    line shiftLeft(double delta){return {v, c + delta*abs(v)};}
    pt proj(pt p){return p - perp(v)*side(p)/sq(v);}
    pt refl(pt p){return p - perp(v)*2*side(p)/sq(v);}

};

bool lineInter(line l1, line l2, pt &out){
    ld d = cross(l1.v, l2.v);
    if(d==0) return false;
    out = (l2.v*l1.c - l1.v*l2.c) / d;
    return true;
}

line bisector(line l1, line l2, bool interior){
    assert(cross(l1.v, l2.v) != 0); //PARALLEL CHECK
    ld sign = interior ? 1 : -1;
    return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
            l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}

bool inDisk(pt a, pt b, pt p){
    return dot(a-p, b-p)<=0;
}

bool onSegment(pt a, pt b, pt p){
    return orient(a,b,p)==0 && inDisk(a,b,p);
}

bool properInter(pt a, pt b, pt c, pt d, pt &out){
    ld oa = orient(c,d,a),
       ob = orient(c,d,b),
       oc = orient(a,b,c),
       od = orient(a,b,d);

       if(oa*ob<0 && oc*od<0){
            out = (a*ob - b*oa) / (ob-oa);
            return true;
       }
       return false;
}

struct cmpX {
    bool operator()(pt a, pt b){
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
};

//set<pt,cmpX> inters(pt a, pt b, pt c, pt d){
//    pt out;
//    if(properInter(a,b,c,d,out)) return {out};
//    set<pt,cmpX> s;
//    if(onSegment(c,d,a)) s.insert(a);
//    if(onSegment(c,d,b)) s.insert(b);
//    if(onSegment(a,b,c)) s.insert(c);
//    if(onSegment(a,b,d)) s.insert(d);
//    return s;
//}

ld segPoint(pt a, pt b, pt p){  //DISTANTCE FROM P TO SEGMENT AB
    if(a!=b){
        line l(a,b);
        if(l.cmpProj(a,p) && l.cmpProj(p,b)) return l.dist(p);
    }
    return min(abs(p-a), abs(p-b));
}

ld segSegDist(pt a, pt b, pt c, pt d){  //DISTANCE FROM SEG. AB TO SEG. CD
    pt temp;
    if(properInter(a,b,c,d,temp)) return 0;
    return min({segPoint(a,b,c),segPoint(a,b,d),
                segPoint(c,d,a), segPoint(c,d,b)});
}

ld areaTriangle(pt a, pt b, pt c){
    return abs(cross(b-a, c-a))/2.0;
}

ld areaPol(vector<pt> P){
    ld area = 0.0;
    int n = P.size();
    forn(i,n)
        area += cross(P[i], P[(i+1)%n]);
    return abs(area)/2.0;
}

bool above(pt a, pt p){
    return p.y >= a.y;
}

bool crossesRay(pt a, pt p, pt q){ //CHECK IF [PQ] CROSSES RAY FROM A
    return (above(a,q) - above(a,p)) * orient(a,p,q) >0;
}

bool inPolygon(vector<pt> P, pt a, bool strict = true){  //IF STRICT RETURNS TRUE WHEN A IS ON THE BOUNDARY
    int numCross = 0, n = P.size();
    forn(i,n){
        if(onSegment(P[i], P[(i+1)%n],a))
            return !strict;
        numCross += crossesRay(a, P[i], P[(i+1)%n]);
    }
    return numCross & 1; //ODD:TRUE , EVEN:FALSE
}

double angleDist(pt a, pt p, pt q){
    ld ampli = angle(p-a, q-a);
    if(orient(a,p,q) > 0) return ampli;
    else return -ampli;
}

bool inter1(long long a, long long b, long long c, long long d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

bool check_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
        return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
           sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}

int insideCircle(pt p, circle c) {
    ld dx = p.x - c.x, dy = p.y - c.y;
    ld Euc = dx * dx + dy * dy, rSq = c.r * c.r;
    return Euc < rSq ? 0 : Euc == rSq ? 1 : 2;
} //0 inside/ 1 border/ 2 outside

ld areaHeron(pt p1, pt p2, pt p3){
    ld a = dist(p1, p2);
    ld b = dist(p2, p3);
    ld c = dist(p3, p1);
    ld s= (a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

ld perimeter (pt a, pt b, pt c){
    return dist(a,b)+dist(b,c)+dist(c,a);
}

ld rInCircle(pt a, pt b, pt c) {
    return areaHeron(a, b, c) / (0.5 * perimeter(a, b, c));
}

ld rCircumCircle(pt p1, pt p2, pt p3) {
    ld a = dist(p1, p2);
    ld b = dist(p2, p3);
    ld c = dist(p3, p1);
    return a * b * c / (4.0 * areaHeron(p1, p2, p3));
}


bool circleCircleInt(pt c1, ld r1, pt c2, ld r2, pt &p1, pt &p2){
    ld d = dist(c1,c2);
    if(d < abs(r2-r1)|| d > r1+r2)  //TRIANGLE INEQUALITIES
        return false;
    ld alpha = acos((d*d + r1*r1 - r2*r2)/(2*d*r1));
    pt rad = (c2-c1)/d*r1; //RESIZE VECTOR C1C2 TO LENGTH D
    p1 = c1+rotO(rad, -alpha);
    p2 = c1+rotO(rad, alpha);
    return true;
}


bool half(pt p){
    assert(p.x!=0 || p.y!=0);
    return p.y>0 || (p.y==0 && p.x<0);
}

bool halfA(pt p){
    return p.y>0 && (p.y==0 && p.x<0);
}


bool halfV(pt v, pt p){
    return cross(v,p) <0 || (cross(v,p)==0 && dot(v,p) < 0);
}

void polarSort(vector<pt> &P){ //CUADRANTES 3,4,1,2 (-PI, PI]
    sort(P.begin(), P.end(), [](pt v, pt w){
        return make_tuple(half(v), 0, v.sq()) <
                make_tuple(half(w), cross(v,w), w.sq());
    });
}

void polarSortV(vector<pt> &P, pt &vec){ //CUADRANTES 3,4,1,2 (-PI, PI]
    sort(P.begin(), P.end(), [&vec](pt v, pt w){
        return make_tuple(halfV(vec, v), 0, v.sq()) <
                make_tuple(halfV(vec, w), cross(v,w), w.sq());
    });
}


void polarSortAround(pt &o, vector<pt> &P){
    sort(P.begin(), P.end(), [&o](pt v, pt w) {
        return make_tuple(half(v-o), 0, (v-o).sq()) <
                make_tuple (half(w-o), cross(v-o, w-o), (w-o).sq());
    });
}

ANGLES


struct angl {
    pt d; int t = 0; //DIRECTION , # OF FULL TURNS
    angl t180(){return{-d, t+halfA(d)};}
    angl t360(){return{d,t+1};}
    bool operator < (angl other) const {
    return make_tuple(t, halfA(d), 0) <
           make_tuple(other.t, halfA(other.d), cross(d, other.d));
    }
};


angl moveTo(angl a, pt newD){
    assert(!onSegment(a.d, newD, {0,0}));

    angl b{newD, a.t};
    if(a.t180() < b)
        b.t--;
    if(b.t180() < a)
        b.t++;
    return b;
}

int windingNumber2(vector<pt> P, pt a){
    angl alpha {P.back()};
    for(pt d : P)
        alpha = moveTo(alpha,d);
    return alpha.t;
}


//CIRCLES

pt circumCenter(pt a, pt b, pt c){
    b = b-a, c = c-a;
    assert(cross(b,c) != 0);
    return a + perp(b*sq(c) - c*sq(b))/cross(b,c)/2;
}

int circleLine(pt o, ld r, line l, pair<pt,pt> &out){
    ld h2  = r*r - l.sqDist(o);
    if(h2>=0){
        pt p = l.proj(o);
        pt h = l.v*sqrt(h2)/abs(l.v);
        out = {p+h, p-h};
    }
    return 1 + sgn(h2);
}

int circleCircle(pt o1, ld r1, pt o2, ld r2, pair<pt,pt> &out){
    pt d = o2-o1; ld d2 = sq(d);
    if(d2==0) {assert (r1 != r2); return 0;}
    ld pd = (d2 + r1*r1 -r2*r2) / 2;
    ld h2 = r1*r1 - pd*pd/d2;
    if(h2>=0){
        pt p = o1 + d*pd/d2 , h = perp(d)*sqrt(h2/d2);
        out = {p+h, p-h};
    }
    return 1 + sgn(h2);


bool sortx1(wall w1, wall w2){
    if(w1.fi.x==w2.fi.x){
        return w1.se.x>w2.se.x;
    }
    else return w1.fi.x<w2.fi.x;
}

bool sortx2(wall w1, wall w2){
    if(w1.se.x==w2.se.x){
        return w1.fi.x>w2.fi.x;
    }
    else return w1.se.x<w2.se.x;
}

bool sorty(wall w1, wall w2){
    if(w1.fi.y==w2.fi.y){
        return w1.se.y>w2.se.y;
    }
    else return w1.fi.y<w2.fi.y;
}

bool sorty2(wall w1, wall w2){
    if(w1.se.y==w2.se.y){
        return w1.fi.y>w2.fi.y;
    }
    else return w1.se.y<w2.se.y;
}

int main (){

}
