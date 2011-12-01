#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstring>
#include <climits>
#include <cstdlib>

using namespace std;

#define SET(a, n) memset(a, n, sizeof(a))
#define ZERO(a) SET(a, 0)

#define REPi(from, to) for (int i=from; i<to; i++)
#define REPj(from, to) for (int j=from; j<to; j++)
#define REPii(from, to) for (int ii=from; ii<to; ii++)
#define REPjj(from, to) for (int jj=from; jj<to; jj++)

class DropCoins {
public:

int getMinimum(vector<string>& board, int k) {
	int sat[31][31];

	const int h = board.size();
	const int w = board[0].size();

	ZERO(sat);
	REPi(1, h+1) REPj(1, w+1) {
	    int coin = (board[i-1][j-1] == 'o') ? 1 : 0;
	    sat[i][j] = coin + sat[i-1][j] + sat[i][j-1] - sat[i-1][j-1];
	}
	
	int mincost = INT_MAX;
    REPi(0, h+1) REPj(0, w+1) REPii(i, h+1) REPjj(j, w+1) {
        int area = sat[i][j] + sat[ii][jj] - sat[i][jj] - sat[ii][j];
        if (area == k) {            
            int costy[2] = {i, h-ii};
            int costx[2] = {j, w-jj};
            int miny = min(costy[0], costy[1]);
            int maxy = max(costy[0], costy[1]);
            int minx = min(costx[0], costx[1]);
            int maxx = max(costx[0], costx[1]);
            int cost = (minx + miny) * 2 + (maxx + maxy);
            if (cost < mincost) {
                mincost = cost;
            }                        
        }
    }
    return (mincost == INT_MAX) ? -1 : mincost;
}

};

int main(void) {
    vector<string> board;
    board.push_back(".....o");
    board.push_back("......");
    board.push_back("oooooo");
    board.push_back("oooooo");
    board.push_back("......");
    board.push_back("o.....");
    DropCoins dc;
    cout << dc.getMinimum(board, 12) << endl;   
    return 0;
}
