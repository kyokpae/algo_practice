#include <iostream>
#include <map>
#include <cmath>
#include <cstdlib>
#include <cassert>

using namespace std;

int n;
int nums[100];
bool s[60001]={0};
int sum[120001]={0};
int nonzero=0;
map<int, int> mul;
map<int, int> sum_mul;

#define SET(x) s[(x)+30000]
#define SUMP(x) sum[(x)+60000]
#define SUM(x,y) sum[nums[(x)]+nums[(y)]+60000]

inline void inc_map(map<int, int>& object, int key, int inc) {
    map<int, int>::iterator it=object.find(key);
    if (it==object.end())
        object.insert(pair<int, int>(key, inc));
    else
        it->second+=inc;
}

int main(int argc, char** argv) {
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> nums[i];
        SET(nums[i])=true;
        if (nums[i]!=0)
            ++nonzero;
    }

    // oblicz wszystkie sumy i mnozenia
    for (int e=0; e<n; e++) {
        SUM(e, e)+=1;
        inc_map(mul, nums[e]*nums[e], 1);
        for (int f=e+1; f<n; f++) {
            SUM(e, f)+=2;
            inc_map(mul, nums[e]*nums[f], 2);
        }
    }
    // oblicz wszystkie mnozenia d przez wszystki sumy i zlicz ich ilosc
    for (int s=0; s<120001; s++) {
        int s_sum=sum[s];
        int num_s=s-60000;
        if (s_sum==0)
            continue;
        for (int d=0; d<n; d++) {
            if (nums[d]==0)
                continue;
            inc_map(sum_mul, nums[d]*num_s, s_sum);
        }
    }

    int result=0;
    for (map<int, int>::iterator it=mul.begin(); it!=mul.end(); it++) {
        int ab=it->first;
        int count=it->second;
        for (int c=0; c<n; c++) {
            int abc=ab+nums[c];
            map<int, int>::iterator it=sum_mul.find(abc);
            if (it!=sum_mul.end())
                result+=count*it->second;
        }
    }

    cout << result << endl;

    return 0;
}


