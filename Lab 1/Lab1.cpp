#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;
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


vi v;
ull n_comp=0;
ll i_comp=0, m_comp=0;

int comp(int a, int b, int c){
	if (c) i_comp++;
	else m_comp++;
	n_comp++;
	if (a < b) return -1;
	else if (a > b) return 1;
	else return 0;
}

void insertionSort(int l, int r){
	FE(i,l+1,r){
		for (int j=i; j > l; j--){
			if (comp(v[j-1], v[j],1)==1) swap(v[j], v[j-1]);
			else break;
		}
	}
}

void mergeSort(int l, int r, int s){
	// ending
	if(r-l <= 0) return;
	if (r-l+1 <= s) insertionSort(l,r);
	else {
		int m=(l+r)/2;
		mergeSort(l,m,s);
		mergeSort(m+1,r,s);
		// Do inplace merging
		int a=l, b = m+1, i, cmp, tmp;
		while (a <= m && b <= r){
			cmp = comp(v[a], v[b],0);
			if (cmp > 0){
				tmp = v[b++];
				for (i=++m; i > a; i--)
					v[i] = v[i-1];
				v[a++] = tmp;
			} else if (cmp < 0){
				a++;
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

int rand_num(){
	return rand()%10000+1;
}

void s_comp(int n){
	FILE * pFile = fopen ("sn_comp.txt" , "w");
	FE(s,1,100){
		generate(v.begin(), v.end(), rand_num);
		// printV(v);
		mergeSort(0, n-1, s);
		fprintf(pFile, "%d %llu\n", s, n_comp);
		cout << s << " " << n_comp << " " << i_comp << " " << m_comp << endl;
		// printV(v);
		n_comp=0;
		i_comp=0;
		m_comp=0;
	}
	
	fclose(pFile);
}


int32_t main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int n;

	cout << "Enter size: ";
	cin >> n;
	v.resize(n);
	// srand(unsigned(std::time(nullptr)));

	s_comp(n);
	
	return 0;

}