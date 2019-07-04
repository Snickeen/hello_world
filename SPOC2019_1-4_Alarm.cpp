#include <iostream>
using namespace  std;

typedef long long LL;
const LL MAX = 200005;
LL ans[MAX];// LL cnt;

struct Line{
	LL x,y;
	Line() {};
	Line(LL a, LL b) :x(a), y(b) {};
	void read(){
		cin >> x >> y;
	}
	bool on_the_right(LL x1, LL y1) {
		//叉积看是否在p0_p1右侧
		return((-x * y1) - (y * (x1 - x))) <= 0;
	}
	friend LL bin_search(LL lo, LL hi);
};

struct S{
	Line line[MAX];
	LL n,m;
	long long tem_x, tem_y;
	
	void read(){
		cin>>n>>m;
		for(LL i=1;i<=n;i++)line[i].read();
	}
	LL bin_search(LL lo, LL hi, LL tem_x, LL tem_y) {
		if (hi - lo < 0)return lo-1;
		LL mi = (lo + hi) >> 1;
	//  return lin[mi].on_the_right(tem_x, tem_y) ? bin_search(mi  , hi, tem_x, tem_y) : bin_search(lo, mi  , tem_x, tem_y);
		return line[mi].on_the_right(tem_x, tem_y) ? bin_search(mi+1, hi, tem_x, tem_y) : bin_search(lo, mi-1, tem_x, tem_y);
	}
	void solution(){
		read();
		while(m--){
			cin >> tem_x >> tem_y;
			cout << bin_search(1,n,tem_x,tem_y) <<"\n";
		}
	}
};
S s;
	
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	s.solution();
	
	/*
	// init action
	LL n, m; LL tem_x, tem_y;
	cin >> n >> m;
	for (LL i = 1; i <= n; i++)
	{

		cin >> tem_x >> tem_y;
		lin[i] = Line(tem_x, tem_y);
	}
	LL m2 = m;
	// m action
	while (m--)
	{
		cin >> tem_x >> tem_y;
		ans[cnt++] = bin_search(1, n, tem_x, tem_y);
	}
	for (LL i = 0; i < m2; i++)
	{
		cout << ans[i] << endl;
	}
	*/

}



/*

4 3
1 1
3 2
4 4
6 5
1 3
4 1
6 5

*/
