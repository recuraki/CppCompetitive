#include <bits/stdc++.h>
#include <cassert>
//#include <chrono>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

// #include <atcoder/all>
using namespace std;
//using namespace __gnu_pbds;
using ll = long long int;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)

#define FASTIO() cin.tie(0); ios::sync_with_stdio(false)
#define FASTIOpre() cin.tie(0); ios::sync_with_stdio(false); cout << fixed << setprecision(20);

using namespace std;

struct Point{
    long double x, y;
    Point operator+(const Point &other){ return (Point){x + other.x, y + other.y}; }
    Point operator-(const Point &other){ return (Point){x - other.x, y - other.y}; }
    bool operator==(const Point &other){ return (x == other.x && y == other.y); }
    Point operator/(const long double a){ return (Point){x / a, y / a}; }
};
ostream& operator<<(ostream &os, const Point &p){ // Pointのcout << ダンプ。
    os << "{" << p.x << ", " << p.y << "}";
    return os;
}

long double PointDist(Point a, Point b){
    return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 重心座標を求め x, y を返す。O(|points|)
Point gravity(vector<Point> &points){
    Point ans = {0, 0};
    for(auto &p: points) ans = ans + p;
    ans = ans / points.size();
    return ans;
}

// 全ての点をPointずらす
// 重心に対して-x, -yをずらせば、0,0が重心となる
void PointShift(vector<Point> &points, Point shift){
    for(auto &p: points) p = p + shift;
};

// x,yをrad回した時の座標は
// newx = xcos(rad) - y sin(rad)
// newy = xsin(rad) + y cos(rad)
Point PointRot(Point p, long double rad){
    return {p.x * cos(rad) - p.y * sin(rad),
            p.x * sin(rad) + p.y * cos(rad)};
};

// 点p1 と 点p2で結ばれる線分に対して y軸 = yの直線の交点が存在するかを識別し、交点座標を返す
pair<bool, Point> isCrossY(long double y, Point p1, Point p2){
    if(p1.y == p2.y) return(make_pair(false, (Point){0, 0}));
    if(p1.y > p2.y) swap(p1, p2);
    auto cx = (p1.x * (p2.y - y) + p2.x * (y - p1.y)) / (p2.y - p1.y);
    if(p1.y <= y && y <  p2.y) return(make_pair(true, (Point){cx, y}));
    return(make_pair(false, (Point){0, 0}));
}

// 3点が同一線上にあるか？ p3を原点にいどうして　判定する。
// Verify: https://atcoder.jp/contests/abc181/tasks/abc181_c
bool sameLine3Point(const Point &p1, const Point &p2, const Point &p3){
    return( (p1.x - p3.x) * (p2.y - p3.y) == (p2.x - p3.x) * (p1.y - p3.y));
}

// 2つの直線が交わるかの判定 p=[x,y]のp1-p2を繋ぐ線とp3-p4を繋ぐせんを調べる
bool intersect(Point p1, Point p2, Point p3, Point p4){
    auto tc1 = (p1.x - p2.x) * (p3.y - p1.y) + (p1.y - p2.y) * (p1.x - p3.x);
    auto tc2 = (p1.x - p2.x) * (p4.y - p1.y) + (p1.y - p2.y) * (p1.x - p4.x);
    auto td1 = (p3.x - p4.x) * (p1.y - p3.y) + (p3.y - p4.y) * (p3.x - p1.x);
    auto td2 = (p3.x - p4.x) * (p2.y - p3.y) + (p3.y - p4.y) * (p3.x - p2.x);
    return (tc1*tc2 < 0) && (td1*td2 < 0);
}

// ある点が凸多角形内に存在するかを判定する
// p = (x, y)の座標
// poly = [(x1, y1), (x2, y2)...]
// http://uchigle.cocolog-nifty.com/blog/2008/11/post-3a38.html
// http://www.not-enough.org/abe/manual/argo/poly-naibu.html
bool isPointInPolygon(Point p, vector<Point> poly){
    bool ans = false;
    auto lp = poly[poly.size() - 1];
    for(auto cp: poly){
        auto [flag, pCross] = isCrossY(p.y, lp, cp);
        if(flag && pCross.x > p.x) ans = !ans;
        lp = cp;
    }
    return ans;
}


long double eps = 0.000001; // 1e-6
long double eps2 = 0.00000001; // 1e-8

// C - Collinearity
// https://atcoder.jp/contests/abc181/tasks/abc181_c
void abc181c(){
    int n; cin >> n;
    vector<Point> p(n);
    REP(i, n) cin >> p.at(i).x >> p.at(i).y;
    REP(a, n){
        FOR(b, a+1, n){
            FOR(c, b+1, n){
                if(sameLine3Point(p.at(a), p.at(b), p.at(c))){
                    cout << "Yes" << "\n";
                    return;
                }
            }
        }
    }
    cout << "No" << "\n";
    return;
}


// D - Congruence Points
// https://atcoder.jp/contests/abc207/tasks/abc207_d
int abc207d() {
    int n; cin >> n;
    vector<Point> s(n), t(n);
    REP(i, n) {
        cin >> s.at(i).x >> s.at(i).y;
    }
    REP(i, n) {
        cin >> t.at(i).x >> t.at(i).y;
    }
    // 0,0 を回避したいので全てに+epsする
    auto gras = gravity(s);
    auto grat = gravity(t);
    PointShift(s, {-gras.x, -gras.y});
    PointShift(t, {-grat.x, -grat.y});
    PointShift(s, {eps2, eps2});
    PointShift(t, {eps2, eps2});
    //for(auto &p: s) cout << p << "\n";
    //for(auto &p: t) cout << p << "\n";

    if(n == 1){
        cout << "Yes" << "\n";
        return 0;
    }

    // 多分、s[0]が原点だとつらい。条件より、重心は複数ないので
    if(s.at(0).x < eps && s.at(0). y) swap(s.at(0), s.at(1));
    // s[0]に対してt[i]が対応すると仮定する
    auto radS = atan2(s.at(0).y, s.at(0).x); // atan2(y, x)
    REP(i, n){
        auto radT = atan2(t.at(i).y, t.at(i).x);
        // もし、S=45, T=30 とすると、Tをrot +15しないといけない。
        auto radDelta = radS - radT;
        // 全ての点の評価を行う
        bool allok = true;
        REP(a, n){ // s[a]
            bool thisok = false;
            REP(b, n){ // t[b]
                auto deltap = PointRot(t.at(b), radDelta) - s.at(a);
                //cout << deltap << "\n";
                if(abs(deltap.x) > eps) continue;
                if(abs(deltap.y) > eps) continue;
                thisok = true;
                break;
            }
            if(!thisok) allok = false;
        }
        if(allok){
            cout << "Yes" << "\n";
            return 0;
        }
    }
    cout << "No" << "\n";
    return 0;
}

void TESTisCrossY(){
    cerr << "isCrossY:" << "\n";

    pair<bool, Point> t;

    t = isCrossY(0.5, Point{1,2}, Point{1,0});
    assert(t.first == true);
    assert((t.second == Point{1.0, 0.5}));

    t = isCrossY(0.5, Point{0, 1}, Point{1,0});
    assert(t.first == true);
    assert((t.second == Point{0.5, 0.5}));

    t = isCrossY(0.5, Point{0, 2}, Point{1,0});
    assert(t.first == true);
    assert((t.second == Point{0.75, 0.5}));

    t = isCrossY(3, Point{0, 2}, Point{0,0});
    assert(t.first == false);

    t = isCrossY(0, Point{-100, -100}, Point{100, -100});
    assert(t.first == false);
}

void testIntersect(){
    cout << "testIntersect\n";
    assert(intersect(Point{0,0}, Point{0,1}, Point{-1, 0.5}, Point{1, 0.5}));
    assert(intersect(Point{0, 0}, Point{0,1}, Point{0,0}, Point{0, 1}) == false);

}
void testisPointInPolygon(){
    cout << "testisPointInPolygon\n";
    vector<Point> poly;
    poly.push_back({-100, -100});
    poly.push_back({+100, -100});
    poly.push_back({+100, +100});
    poly.push_back({-100, +100});
    assert(isPointInPolygon(Point{0, 0}, poly));
    assert(isPointInPolygon(Point{99,99}, poly));
    assert(isPointInPolygon(Point{0, -100}, poly));
    assert(!isPointInPolygon(Point{101, 101}, poly));
    assert(!isPointInPolygon(Point{80, -101}, poly));
}

void test(){
    TESTisCrossY();
    testIntersect();
    testisPointInPolygon();
}
int main(){
    test();
    //abc207d();
    //abc181c();
}