// marcin.olak@gmail.com
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define VISITED(l) visited[(l).level][(l).pos]
#define VISIT(l) VISITED(l)=true
#define UNVISIT(l) VISITED(l)=false
#define CHILDREN_LEFT g[left.level][left.pos][l]
#define CHILDREN_RIGHT g[right.level][right.pos][r]
#define LETTER(x) (x).letter(*this)

class TheBoringStoreDivTwo {
    struct node {
        node() : level(-1), pos(-1) {}
        node(char level, char pos) : level(level), pos(pos) {}
        char letter(TheBoringStoreDivTwo& store) const {
            return (level == 0) ? store.J[pos] : store.B[pos];
        }
        static node end() {
            return node();
        }
        bool operator!=(const node& n) {
            return n.level != level || n.pos != pos;
        }
        int level;
        int pos;
    };
public:
    string find(string a, string b) {
        J=a;
        B=b;
        buildGraph();
        memset(visited, 0, sizeof(visited));
        text[0]=0;
        text_len=0;
        result="";

        for (int i=0; i<J.length(); i++) {
            for (int j=0; j<J.length(); j++) {
                node left(0, i);
                node right(0, j);
                if (i!=j && LETTER(left) == LETTER(right)) {
                    visit(left, right);
                }
            }
        }
        return result;
    }

private:
    string J;
    string B;
    node g[2][15][17];
    bool visited[2][15];
    string result;
    char text[17];
    int text_len;
    

    void visit(const node& left, const node& right) {
        VISIT(left);
        VISIT(right);
        text[text_len++]=LETTER(left);
        text[text_len]=0;
        if (left.level==right.level && left.level==1) {
            if (text_len > result.length()) {
                result=text;
            } else if (text_len == result.length()) {
                result=(result < text) ? result : text;
            }
        }
        for (int r=0; CHILDREN_RIGHT != node::end(); r++) {
            if (VISITED(CHILDREN_RIGHT)) {
                continue;
            }
            for (int l=0; CHILDREN_LEFT != node::end(); l++) {
            	if (!(CHILDREN_LEFT != CHILDREN_RIGHT)) {
            		continue;
            	}
                if (LETTER(CHILDREN_LEFT) != LETTER(CHILDREN_RIGHT) || VISITED(CHILDREN_LEFT)) {
                    continue;
                }               
                visit(CHILDREN_LEFT, CHILDREN_RIGHT);
            }
        }
        text[--text_len]=0;
        UNVISIT(left);
        UNVISIT(right);
    }

    void buildGraph() {       
        for (int i=0; i<2; i++)
        for (int j=0; j<15; j++)
        for (int k=0; k<17; k++)
            g[i][j][k]=node::end();
        
        for (int j=0; j<J.length()-1; j++) {
            g[0][j][0].level=0;
            g[0][j][0].pos=j+1;
        }        
        for (int b=0; b<B.length(); b++) {
            for (int j=0; j<J.length(); j++) {
                int p=(j < J.length()-1) ? b+1 : b;
                g[0][j][p].level=1;
                g[0][j][p].pos=b;
            }
            if (b<B.length()-1) {
                g[1][b][0].level=1;
                g[1][b][0].pos=b+1;
            }
        }
    }
    friend class node;
};

int main(void) {
    TheBoringStoreDivTwo store;
    cout << store.find("StoreOfJohn", "StoreOfBrus") << endl;
    cout << store.find("JohnAndJohn", "John") << endl;
    cout << store.find("JohnPlaysGames", "BrusAlsoPlays") << endl;
    cout << store.find("aba", "abcab") << endl;
    cout << store.find("abcab", "abcdabc") << endl;
    cout << store.find("abacaba", "abacabadabacaba") << endl;
    cout << store.find("eeWW", "gg") << endl;
    return 0;
}

