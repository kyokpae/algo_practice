#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pos;

class AlphabetPath {
public:
    
    const pos findA(const vector<string>& letterMaze) {
        for (int j=0; j<letterMaze.size(); j++) {
            for (int i=0; i<letterMaze[j].size(); i++) {
                if (letterMaze[j][i] == 'A') {
                    return pos(j, i);
                }
            }
        }
        return pair<int, int>(-1, -1);
    }
    
    bool scanXY(const vector<string>& letterMaze, pos p, char letter) {
        if (p.first < 0) return false;
        if (p.second < 0) return false;
        if (p.first >= letterMaze.size()) return false;
        if (p.second >= letterMaze[0].size()) return false; 
        return (letterMaze[p.first][p.second] == letter);
    }
    
    const pos scan(const vector<string>& letterMaze, pos current, char letter) {
        pos left = pos(current.first-1, current.second);
        pos right = pos(current.first+1, current.second);
        pos top = pos(current.first, current.second-1);
        pos bottom = pos(current.first, current.second+1);
        if (scanXY(letterMaze, left, letter)) return left;
        if (scanXY(letterMaze, right, letter)) return right;
        if (scanXY(letterMaze, top, letter)) return top;
        if (scanXY(letterMaze, bottom, letter)) return bottom;
        return pos(-1, -1);
    }

    string doesItExist(vector<string> letterMaze) {
        pos current = findA(letterMaze);        
        for (int i=1; i<26; i++) {            
            pos next = scan(letterMaze, current, 'A'+i);            
            if (next.first == -1) {
                return "NO";
            }
            current = next;
        }
        return "YES";
    }
};

