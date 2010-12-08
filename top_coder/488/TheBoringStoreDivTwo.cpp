#include <iostream>
#include <cstring>

using namespace std;

#define VISITED(l) visited[(l).level][(l).pos]
#define VISIT(l) VISITED(l)=true
#define UNVISIT(l) VISITED(l)=false
#define LETTER(l) (((l).level == 0) ? (J[(l).pos]) : (B[(l).pos]))

char text[16];
int pos=0;
string result="";
int level=0;

class TheBoringStoreDivTwo {
public:
    struct iterator {
        int pos, level, max0, max1;
        bool first;
        iterator() {}
        iterator(int pos, int level, const string& J, const string& B) : pos(pos), level(level), first(true), max0(J.length()), max1(B.length()) {}
        static iterator end() {
            return iterator(-1, -1, "", "");
        }
        iterator(const iterator& i) : pos(i.pos), level(i.level), first(true), max0(i.max0), max1(i.max1) {}
        iterator& operator++() {
           if (level==-1) {
               *this=end();
           } else if (first) {
               pos++;
               first = false;
           } else if (level == 0) {
               pos=0;
               level=1;
           } else {
               pos++;
           }
           if (level==0 && pos==max0) {
               pos=0;
               level=1;
           }
           if (level==1 && pos==max1) {
               *this=end();
           }
           return *this;
        }
        bool operator!=(const iterator& i) {
            return pos != i.pos || level != i.level;
        }
        friend ostream& operator<<(ostream& os, iterator& it) {
            return os << it.pos << "@" << it.level	;
        }
    };
    static iterator stackleft[16];
    static iterator stackright[16];

    void visit(iterator& left, iterator& right) {
        level++;
        for (iterator l=left; l != iterator::end(); ++l) {
            if (VISITED(l))
                continue;
            VISIT(l);
            text[pos++]=LETTER(l);
            text[pos]=0;
            stackleft[pos++]=l;
            stackleft[pos]=iterator::end();
            stackright[pos]=iterator::end();
            for (iterator r=right; r != iterator::end(); ++r) {
                if (pos==1 && (r.level==1 || l.level==1))
                    continue;
                cout << l << " | " << r << " | " << text << " ";
                for (int i=0;i<level;i++) cout << " ";
                if (LETTER(l) != LETTER(r)) {
                    cout << "LETTER " << LETTER(l) << " vs " << LETTER(r) << endl;
                } else if (VISITED(r)) {
                    cout << "VISITED" << endl;
                } else {
                cout << "V I S I T" << endl;
               stackright[pos-1]=r;
                if (l.level == r.level && l.level == 1) {	
                    if (pos > result.length())
                        result = text;
                    else if (pos == result.length())
                        result = (text < result ) ? text : result;
                    cout << result << " xx " << J << " xx " << B << endl;
                    for(int i=0; i<pos;i++) {
                        cout << stackleft[i] << ", ";
                    }
                    cout << endl;
                    for(int i=0; i<pos;i++) {
                        cout << stackright[i] << ", ";
                    }
                    cout << endl;
                }
                VISIT(r);
                visit(l, r);
                UNVISIT(r);
                for (int i=0;i<level;i++) cout << " ";
                cout << l << " | " << r << " | " << text << "UNVISIT" << endl;
                }
            }
            cout << text << " MINUS ";
            text[--pos]=0;
            stackleft[pos]=iterator::end();
	    stackright[pos]=iterator::end();
            cout << text << endl;
            UNVISIT(l);
         }
        level--;
    }

   string find(string a, string b) {
        J=a;
        B=b;
        bzero(visited, sizeof(visited));
        pos=0;
        text[0]=0;
        result="";
        for (int i=0; i<J.length(); ++i) {
            for (int j=0; j<J.length(); ++j) {
                iterator left=iterator(i, 0, J, B);
                iterator right=iterator(j, 0, J, B);
                visit(left, right);
            }
        }    
        return result;
    }

private:
    bool visited[2][15];
    string J;
    string B;
};

TheBoringStoreDivTwo::iterator TheBoringStoreDivTwo::stackleft[16]={TheBoringStoreDivTwo::iterator::end()};
TheBoringStoreDivTwo::iterator TheBoringStoreDivTwo::stackright[16]={TheBoringStoreDivTwo::iterator::end()};

int main(void) {
    TheBoringStoreDivTwo store;
//    cout << store.find("StoreOfJohn", "StoreOfBrus") << endl;
  //  cout << store.find("JohnAndJohn", "John") << endl;
    cout << store.find("JohnPlaysGames", "BrusAlsoPlays") << endl;
//    cout << store.find("abacaba", "abacabadabacaba") << endl;
    return 0;
}
/*
    string find(string a, string b) {
        J=a;
        B=b;
        bzero(visited, sizeof(visited));
        for (int i=0; i<J.length()-1; ++i) {
            for (int j=i+1; j<J.length(); ++j) {
                if (J[i] != J[j])
                    continue;
                iterator left=iterator(i, 0, J, B);
                iterator right=iterator(j, 0, J, B);
                visit(left, right);
            }
        }    
        return result;
    }

private:
    bool visited[2][15];
    string J;
    string B;
};

int main(void) {
    TheBoringStoreDivTwo store;
//    cout << store.find("StoreOfJohn", "StoreOfBrus") << endl;
  //  cout << store.find("JohnAndJohn", "John") << endl;
    cout << store.find("JohnPlaysGames", "BrusAlsoPlays") << endl;
    //for (TheBoringStoreDivTwo::iterator i(0,0); TheBoringStoreDivTwo::iterator::end()!=i; ++i) {
     //  cout << i << endl;
    //}
    return 0;
}*/
