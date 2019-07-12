/*
Author: Snickeen.
Email : ff@snickeen.com
Date  : 2019.07.09 Tur.

If you find out any bugs, please tell me. Thank you.


//
Generate testcases' data for SPOC2019PA1_1-3-3.

*/

#include<iostream>
#include<random>
#include<time.h>
using namespace std;

const int MAXN = 4e6+7;

char s[MAXN],op,lr,c;
int n,m;

int Limit = 30;
int Rand(int LIMIT){
    return rand()%LIMIT+1;
}

signed main()
{
    //freopen("SPOC2019PA1_1-3-3.gen.in","w",stdout);
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    srand(time(0));
    n = Rand(Limit)%10+1;
    // 初始的字符串
    for(int i=0;i<n;i++){
        char c = 'a' + Rand(26) - 1;
        cout<<c;
    }
    cout<<endl;
    // 操作数
    m = Rand(Limit);
    cout<< m+1 << endl; //多一个操作，最后是Show
    while(m--){
        int op = Rand(6);
        if(op<5){
            char cursor = Rand(2)&1?'L':'R';
            if(op<=2){
                cout<<(op&1?'<':'>')<<" "<<cursor<<endl;
            }
            else if(op==3){
                char c = 'a' + Rand(26) - 1;
                cout<<"I"<<" "<<cursor<<" "<<c<<endl;
            }
            else if(op==4){
                cout<<"D"<<" "<<cursor<<endl;
                //m++;
            }
        }
        else if(op==5){
            cout<<"R"<<endl;
        }
        else if(op==6){
            cout<<"S"<<endl;
        }
    }
    cout<<"S"<<endl; //最后加一个show

    return 0;
}



/*



*/
