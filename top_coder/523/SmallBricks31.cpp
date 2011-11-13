#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

const long long prime = 1000000007;

class SmallBricks31 {
public:
    int countWays(int w, int h) {
        // generate structures
        generate("", w);
        flattenCounts();
        createGraph();

        for (int i = 1; i < h; i++) {
            for (int j = 0; j < structs.size(); j++) {
                trav[i].push_back(traverse(j, i));
            }
        }
        return traverse(0, h);
    }

    long long traverse(int from, int h) {
        long long count = counts[from];

        if (h == 0) {
            // zwroc ilosc kombinacji tego node'a
            return count;
        }

        if (trav[h].size() > from) {
            return (trav[h][from]);
        }
        long long mul = 1; // puste ...
        for (int to = 0; to < graph[from].size(); to++) {
            // ... albo dokladamy kolejny poziom
            mul += traverse(graph[from][to], h-1);
        }
        return (count * mul) % prime;
    }

    void addPattern(string& s) {
        map<string, int>::iterator it = patterns.find(s);
        if (it == patterns.end()) {
            patterns.insert(pair<string, int>(s, 1));
            structs.push_back(s);
        } else {
            it->second++;
        }
    }

    int patternCount(string& s) {
        map<string, int>::iterator it = patterns.find(s);
        return it->second;
    }

    void flattenCounts() {
        for (int i = 0; i < structs.size(); i++) {
            counts.push_back(patternCount(structs[i]));
        }
    }

    // rekurencyjnie wygeneruj możliwe struktury
    void generate(string s, int w) {
        if (w == 0) {
            addPattern(s);
        }
        // pusta przestrzen
        if (w > 0) {
            generate(s + ".", w-1);
        }
        // klocek 1
        if (w > 0) {
            generate(s + "X", w-1);
        }
        // klocek 2
        if (w > 1) {
            generate(s + "XX", w-2);
        }
        // klocek 3
        if (w > 2) {
            generate(s + "XxX", w-3);
        }
    }

    void createGraph() {
        graph = new vector<int>[structs.size()];
        for (int from = 0; from < structs.size(); from++) {
            for (int to = 0; to < structs.size(); to++) {
                if (edgeExists(from, to)) {
                    graph[from].push_back(to);
                }
            }
        }
    }

    bool structsCompatible(const string& from, const string& to) {
        for (int i = 0; i < from.size(); i++) {
            // docelowy pusty
            if (to[i] == '.') continue;
            // docelowy podparty
            if (to[i] == 'X' && from[i] != '.') continue;
            // docelowy niepusty i niepodparty

            // gdzies po srodku
            if (i > 0 && i < from.size() - 1) {
                // oraz srodkowy 3ki
                if (to[i] == 'x') {
                    // i podparty z bokow
                    if (from[i-1] != '.' && from[i+1] != '.') continue;
                }
            }

 //           cout << from << " -nie->" << to << endl;
            return false;
        }
        return true;
    }

    bool edgeExists(int from, int to) {
        // do 0 nigdzie
        if (to == 0) return false;
        // z 0 wszedzie
        if (from == 0) return true;
        // w to samo -> ok
        if (from == to) return true;
        return structsCompatible(structs[from], structs[to]);
    }

    vector<string> structs;
    vector<int>* graph;
    vector<int> counts;
    set<int> flats;
    map<string, int> patterns;
    vector<long long> trav[11];
};

int brick(int w, int h) {
    SmallBricks31 b;
    return b.countWays(w, h);
}

int main(void) {
    assert(587048789 == brick(6, 9));
    assert(170708663 == brick(6, 8));
    assert(237973525 == brick(5, 8));
    assert(24861902 == brick(6, 7));
    assert(81051310 == brick(6, 10));
    assert(21034400 == brick(5, 9));
    assert(82403180 == brick(5, 10));
    assert(9403676 == brick(10, 2));
    assert(301887 == brick(4, 5));
    assert(132976888 == brick(4, 9));
    assert(4 == brick(1, 3));
    assert(13 == brick(3, 1));
    assert(84 == brick(3, 2));
    assert(11676046 == brick(5, 5));
    assert(536794181 == brick(8, 9));

    {
        SmallBricks31 b;
        assert(b.structsCompatible("XXX", "XxX"));
        assert(b.structsCompatible("X.X", "XxX"));
        assert(b.structsCompatible("XxX", "X.."));
        assert(b.structsCompatible("XxX", ".X."));
        assert(b.structsCompatible("XxX", "..X"));
        assert(b.structsCompatible("XX.", "X.."));
        assert(b.structsCompatible("XX.", ".X."));
        assert(b.structsCompatible(".XX", "..X"));

        assert(!b.structsCompatible(".XX", "XxX"));
        assert(!b.structsCompatible("XX.", ".XX"));
        assert(!b.structsCompatible("XX.", "..X"));
        assert(!b.structsCompatible("X..", "XxX"));
    }
    return 0;
}
