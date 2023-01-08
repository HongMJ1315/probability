#include<bits/stdc++.h>
using namespace std;
#define mxn 100
#define iter 10000

int main(){
    random_device rd;
    mt19937 gen(rd());
    int all = 0;
    cin >> all;
    for(int i = 0; i < all; i++){
        double a = gen(), b = gen();
        if(b > a) swap(a, b);
        if(a <= 1e-8){
            i--;
            continue;
        }
        double p = b / a;
        p = p - ((p * 10.0 - double(int(p * 10))) / 10.0);
        binomial_distribution<> d(mxn, p);
        vector<int> mem(mxn + 1, 0);
        for(int i = 0; i <= iter; i++){
            int ran = d(gen);
            mem[d(gen)]++;
        }
        cout << fixed << setprecision(10) << p << endl;
        for(int i = 0; i <= mxn; i++)
            cout << mem[i] << " ";
        cout << endl;

    }
    return 0;

}