#include <iostream>
using namespace std;
int main(void) {
    int d[10000];
    int z[10000];
    int n,tc;
    cin >> tc;
    for (int t=0;t<tc;t++) {
        cin >> n;

        int m=0;
        for (int i=0;i<n;i++)
        {
            cin >> z[i];
            cin >> d[i];
            m+=d[i];
        }

        m/=2;


        long long ZP, ZL, DP, DL, CP, CL;
        int p;
        ZP=ZL=DP=DL=CP=CL=p=0;

        
        ZP=z[0];
        while (DP+d[p]<=m) {
            DP+=d[p];
            p++;
            ZP+=z[p];
            CP+=DP*z[p];
        }

        int l=n;

        while (l-1>p) {
            l--;
            DL+=d[l];
            ZL+=z[l];
            CL+=DL*z[l];
        }

        long long min_cost=CL+CP;

        for (int b=0;b<n-1;b++) {
            int zb=z[b];
            int db=d[b];
            ZP-=zb;
            DP-=db;
            CP-=db*ZP;
            while (d[p]+DP<=m) {
                DP+=d[p];
                p=l;
                int zp=z[p];
                int dp=d[p];
                ZP+=zp;
                CP+=zp*DP;
                CL-=zp*DL;
                DL-=dp;
                ZL-=zp;
                l=(l+1)%n;
            }
            ZL+=zb;
            DL+=db;
            CL+=db*ZL;
            min_cost=min(min_cost, CL+CP);
        }       
        cout << min_cost << endl;
    }

    return 0;
}

