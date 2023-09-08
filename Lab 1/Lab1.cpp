#include <bits/stdc++.h>
#include "headers/benchmark.hpp"
using namespace std;
using namespace bm;

#define bit(x,i) (x&(1<<i))  //select the bit of position i of x
#define lowbit(x) ((x)&((x)^((x)-1))) //get the lowest bit of x
#define hBit(msb,n) asm("bsrl %1,%0" : "=r"(msb) : "r"(n)) //get the highest bit of x, maybe the fastest
#define max(a,b) (a<b?b:a)
#define min(a,b) (a>b?b:a)
#define abs(x) (x<0?(-x):x) // big bug here if "-x" is not surrounded by "()"
#define IN(i,l,r) (l<i&&i<r) //the next for are for checking bound
#define LINR(i,l,r) (l<=i&&i<=r)
#define LIN(i,l,r) (l<=i&&i<r)
#define INR(i,l,r) (l<i&&i<=r)
#define F(i,L,R) for (int i = L; i < R; i++) //next four are for "for loops"
#define FE(i,L,R) for (int i = L; i <= R; i++)
#define FF(i,L,R) for (int i = L; i > R; i--)
#define FFE(i,L,R) for (int i = L; i >= R; i--)
#define getI(a) scanf("%d", &a) //next three are handy ways to get ints, it's also force you to use '&' sign
#define getII(a,b) scanf("%d%d", &a, &b)
#define getIII(a,b,c) scanf("%d%d%d", &a, &b, &c)
#define wez(n) int (n); scanf("%d",&(n)) //handy if the input is right after the definition of a variable
#define wez2(n,m) int (n),(m); scanf("%d %d",&(n),&(m))
#define wez3(n,m,k) int (n),(m),(k); scanf("%d %d %d",&(n),&(m),&(k))
#define TESTS wez(testow)while(testow--) //for multilple cases problems
#define whileZ int T; getI(T); while(T--) // the same as above
#define getS(x) scanf("%s", x) //get a char* string
#define clr(a,x) memset(a,x,sizeof(a)) //set elements of array to some value
#define char2Int(c) (c-'0')
#define lastEle(vec) vec[vec.size()-1]
#define SZ(x) ((int)((x).size()))
#define REMAX(a,b) (a)=max((a),(b)) // set a to the maximum of a and b
#define REMIN(a,b) (a)=min((a),(b));
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++) // traverse an STL data structure
#define ALL(c) (c).begin(),(c).end() //handy for function like "sort()"
#define PRESENT(c,x) ((c).find(x) != (c).end())
#define CPRESENT(c,x) (find(ALL(c),x) != (c).end())
#define ll long long //data types used often, but you don't want to type them time by time
#define ull unsigned long long
#define ui unsigned int
#define us unsigned short
#define IOS ios_base::sync_with_stdio(0); //to synchronize the input of cin and scanf
#define INF 1001001001
#define PI 3.1415926535897932384626
//for map, pair
#define mp make_pair
#define fi first
#define se second
// for debug
inline void pisz(int n) { printf("%d\n",n); }
#define DBG(vari) cerr<<#vari<<" = "<<(vari)<<endl;
#define printA(a,L,R) FE(i,L,R) cout << a[i] << (i==R?'\n':' ')
#define printV(a) printA(a,0,a.size()-1)
#define MAXN 10000
//for vectors
#define pb push_back
typedef int elem_t;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
// directions
const int fx[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
const int fxx[8][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
template<typename T,typename TT> ostream& operator<<(ostream &s,pair<T,TT> t) {return s<<"("<<t.first<<","<<t.second<<")";}
template<typename T> ostream& operator<<(ostream &s,vector<T> t){F(i,0,SZ(t))s<<t[i]<<" ";return s; }

/*

Helper Functions

Preset seed in main function will cause all thread to generate the same vector array.

*/

int rand_num(){
	return rand()%10000+1;
}

/*

Hybrid Sort class 

If s=1: Merge Sort

If n=s: Insertion Sort

Else: Hybrid Sort

*/

class HybridSort{
public:
	ull n_comp=0;
	vi v;

	void operator()(int n, int s, vector<ull> & ans, int pos){
		srand(1000);
		generate_vector(n);
		mergeSort(0,n-1,s);
		ans[pos]=n_comp;
	}

	int comp(int a, int b){
		n_comp++;
		if (a < b) return 1;
		else if (a > b) return -1;
		else return 0;
	}

	void generate_vector(int n){
		v.resize(n);
		generate(v.begin(), v.end(), rand_num);
	}

	void insertionSort(int l, int r){
		FE(i,l+1,r){
			for (int j=i; j > l; j--){
				if (comp(v[j-1], v[j])==-1) swap(v[j], v[j-1]);
				else break;	
			}
		}
	}

	void mergeSort(int l, int r, int s){
		if (l==r) return;
		if (r-l+1 <= s) insertionSort(l,r);
		else {
			int m=(l+r)/2;
			mergeSort(l,m,s);
			mergeSort(m+1,r,s);
			//inplace merge 
			int a=l, b=m+1, i, cmp, tmp;
			while (a <= m && b <= r){
				cmp = comp(v[a], v[b]);
				if (cmp > 0){
					a++;
				} else if (cmp < 0){
					tmp = v[b++];
					for (i=++m; i > a; i--) v[i] = v[i-1];
					v[a++] = tmp;
				} else {
					if (a==m && b==r) break;
					tmp = v[b++];
					a++;
					for(i=++m; i > a; i--) v[i] = v[i-1];
					v[a++] = tmp;
				}
			}
		}
	}

};




/*

Part i

Fixed S = 16

Variable N to measure the time complexity 

Goal understand: The time complexity of the hybridsort algorithm

To Do:

1) Plot n vs comparison, O(n^2), O(nlogn)
2) Curve should lie within O(nlogn) and O(n^2)



*/

void part_1(){
	vector<thread> vt;
	vector<ull> ans(9);
	int arr[] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};

	//using multithreading to speed up runtime
	ofstream file;
	file.open("part1.csv");	

	cout << "n,n_comparison" << endl;
	file << "n,n_comparison" << endl;

	F(i,0,9){
		vt.pb(thread(HybridSort(), arr[i], 16, ref(ans), i));
	}

	F(i,0,9){
		vt[i].join();
		cout << arr[i] << "," << ans[i] << endl;
		file << arr[i] << "," << ans[i] << endl;
	}

	file.close();

}



/*

Part ii

Fixed n = 100000

Goal: To understand how number of comparisons increases with respect to S

*Important note: Try to explain the sharp jump in key comparisons 

To Do: 

From the data identify S "shape" key comparisons increased

12 -> 24 -> 48 -> 96 

Can see that every x2 will have aa sharp increase in number of key comparisons

Explaination: Try to link back to time complexity log2(n/k)

Using "benchmark.hpp" libary only measures the CPU burst time 

*/

void part_2(){
	ofstream file;
	file.open("part2.csv");	

	cout << "s,n_comparison,cpu_burst(ns)" << endl;
	file  << "s,n_comparison,cpu_burst(ns)" << endl;

	vector<ull> ans(101);

	for (int i=1; i <=81; i+=20){
		F(j,i,i+20) {
			auto ns = Bench::mark(HybridSort(), 100000, j, ref(ans), j);
			cout << j << "," << ans[j] << "," << ns.as_nanoseconds() << endl;
			file << j << "," << ans[j] << "," << ns.as_nanoseconds() << endl;
		}
	}
	file.close();
}

/*

Part iii

Varying input of dataasets 

Goal: Determine an optimal value of S for the best performance of the hybrid algorithm 

How to do it? 
- To find a point where insertion(CPU burst time) = merge(CPU burst time)
- Since insertion sort more efficient than merge sort on smaller array size
- Why not look at key_comparisons only? merge_sort -> recursive call -> OS need to create a stack for subsequent functions -> potentially more time needed 
- Therefore, we look at both key comparisons and cpu burst time to determine the optimal value of s
** Important for mergeSort optimality we choose multiples of 2 for S

*Same array will be generated since the srand seed is the same 

*We Chose S=16 

*/

void part_3(){
	ofstream file;
	file.open("part3.csv");
	vector<ull> ans_ins(101),ans_merge(101);

	cout << "n,n_comparison_insertion,cpu_burst_insertion(ns),n_comparison_merge,cpu_burst_merge(ns)" << endl;
	file << "n,n_comparison_insertion,cpu_burst_insertion(ns),n_comparison_merge,cpu_burst_merge(ns)" << endl;

	FE(n, 1, 100){
		cout << n << ",";
		file << n << ",";

		auto ns = Bench::mark(HybridSort(), n, n, ref(ans_ins), n);
		cout << ans_ins[n] << "," << ns.as_nanoseconds() << ",";
		file << ans_ins[n] << "," << ns.as_nanoseconds() << ",";

		ns = Bench::mark(HybridSort(), n, 1, ref(ans_merge), n);
		cout << ans_merge[n] << "," << ns.as_nanoseconds() << endl;
		file << ans_merge[n] << "," << ns.as_nanoseconds() << endl;
		
	}


	file.close();
}

/*

Part D: Compare with original Mergesort 

Compare S=1 with S=16


*/

void part_d(){
	vector<ull> ans(2);

	cout << "n_comparison, cpu_burst(s)" << endl;

	auto ns = Bench::mark(HybridSort(), 10000000, 1, ref(ans), 0);
	cout << ans[0] << "," << ns.as_seconds() << endl;

	ns = Bench::mark(HybridSort(), 10000000, 16, ref(ans), 1);
	cout << ans[1] << "," << ns.as_seconds() << endl;

}





int32_t main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	// srand(unsigned(std::time(nullptr)));



	// part_1();
	// part_2();
	// part_3();
	// part_d();

	
	return 0;

}
