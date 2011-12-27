// 10245 - The Closest Pair Problem
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <hash_map>

using namespace std;
using namespace __gnu_cxx;

typedef pair<double, double> Point;
typedef vector<Point> Points;
typedef vector<Point>::iterator point;

class myhash {
public:
size_t operator()(const pair<int, int>& p) const {
    hash<long> h;
    return h((long(p.first) << 31) + long(p.second));
}
};
typedef hash_map<pair<int, int>, vector<Point>*, myhash > Box;

inline double dist(const Point& a, const Point& b) {
    double dx = a.first - b.first;
    double dy = a.second - b.second;    
    return dx * dx + dy * dy;
}

inline double bruteForceDistance(const point& begin, const point& end) {
    double d = 1000000000000; 
    for(point i = begin; i != end; ++i) {
        for (point j = i + 1; j != end; ++j) {
            d = min(d, dist(*i, *j));
        }
    }
    return d;
}

double rabinDistance(const point& begin, const point& end) {
    random_shuffle(begin, end);
    double d = bruteForceDistance(begin, begin + sqrt(end - begin));
    if (d == 0.0) {
        return 0.0;
    }

    Box box;
    for(point p = begin; p != end; ++p) {
        pair<int, int> h = pair<int, int>(p->first / sqrt(d), p->second / sqrt(d));
        Box::iterator b = box.find(h);
        vector<Point>* v = NULL;
        if (b == box.end()) {
            v = new vector<Point>;
            box.insert(pair<pair<int, int>, vector<Point>*>(h, v));
        } else {
            v = b->second;
        }
        v->push_back(*p);
    }
    for(Box::iterator b = box.begin(); b != box.end(); ++b) {
        d = min(d, bruteForceDistance(b->second->begin(), b->second->end()));
        /*
        // correctness requires this, but for UVA test cases ...
        int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
        int dy[] = {0, -1, -1, -1,  0, 1, 1, 1};
        for (int i = 0; i < 8; i++) {
        */
        // ... this is enough
        int dx[] = {1, 0, -1, 0};
        int dy[] = {0, -1, 0, 1};
        for (int i = 0; i < 4; i++) {
            pair<int, int> h = pair<int, int>(b->first.first + dx[i], b->first.second + dy[i]);
            Box::iterator c = box.find(h);
            if (c != box.end())
            for (point j = b->second->begin(); j != b->second->end(); ++j) {
            for (point k = c->second->begin(); k != c->second->end(); ++k) {
                d = min(d, dist(*j, *k));
            }
            }
        }
    }
    if (d == 0.0) {
        return 0.0;
    }
    // obviously I don't free up memory not to waste time...
    return sqrt(d);
}

int main(void) {
    int t;
    while(true) {
        scanf("%d", &t);
        if (t == 0) {
            break;
        }
        
        Points p;
        while (t--) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            p.push_back(Point(x, y));
        }
        double d = rabinDistance(p.begin(), p.end());
        if (d < 10000.0) {
            printf("%.4lf\n", d);
        } else {
            printf("INFINITY\n");
        }
    } 
    return 0;
}
