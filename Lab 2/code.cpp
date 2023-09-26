#include <bits/stdc++.h>
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

/* 

Helper Functions

*/


/*

Graph function 

*/

struct GraphMatrix{
	vvi matrix;
	int size;
	GraphMatrix(int n){
		size=n;
		matrix.resize(n);
		F(i,0,n) {
			vi v;
			v.assign(n, 0);
			matrix[i]=v;
		}
	}

	void set_connection(){
		int n;
		cin >> n;
		int a,b,c;
		while (n--){
			cin >> a >> b >> c;
			matrix[a][b] = c;	
			matrix[b][a] = c;
		}
	}

	int smallest_node(vi & d, vi & s){
		int tmp = INF, node = -1;
		F(i,0,size)	{
			if (d[i] < tmp && s[i] == 0){
				tmp = d[i];
				node = i;
			}
		}
		return node;
	}

	vi djikstra(int source){
		int u;
		vi d, pi, s;
		d.assign(size, INF);
		pi.assign(size, -1);
		s.assign(size, 0);

		d[source] = 0;

		while (u=smallest_node(d, s), u != -1){
			s[u] = 1;
			F(i,0,size){
				if (matrix[u][i] != 0 && s[i] == 0 && (matrix[u][i] + d[u]) < d[i]){
					d[i] = d[u] + matrix[u][i];
					pi[i] = u;
				}	
			}
		}
		
		return d;
		 	
	} 

	void print_graph(){
		cout << "Graph Matrix" << endl;
		F(i,0,size) cout << matrix[i] << endl;
		cout << endl;
	}
};


struct GraphAdj{
	vector<vector<ii>> adj;
	int size;

	GraphAdj(int n){
		size=n;
		adj.resize(n);
	}

	void set_connection(){
		int n;
		cin >> n;
		int a,b,c;
		while (n--){
			cin >> a >> b >> c;
			adj[a].pb(mp(c, b));	
			adj[b].pb(mp(c, a));
		}
	}


	vi djikstra(int source){
		int u;
		vi d, pi, s;
		priority_queue<ii, vector<ii>, greater<ii>> pq;
		d.assign(size, INF);
		pi.assign(size, -1);
		s.assign(size, 0);

		d[source] = 0;
		pq.push(mp(0, source));

		while (!pq.empty()){
			ii node = pq.top();
			pq.pop();
			s[node.se] = 1;
			for (ii con: adj[node.se]){
				if (s[con.se] == 0 && d[con.se] > d[node.se] + con.fi){
					pq.push(mp(d[node.se] + con.fi, con.se));
					d[con.se] = d[node.se] + con.fi;
					pi[con.se] = node.se;
				}
			}
			
		}
		
		return d;
		 	
	} 

	void print_graph(){
		F(i,0,size){
			cout << i << ": ";
			F(j,0,adj[i].size()){
				cout << adj[i][j].se << " -> ";
			}
			cout << endl;
		}

	}
};



int32_t main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);



	int n;
	cin >> n;

	GraphAdj gm(n);
	gm.set_connection();
	gm.print_graph();


	cout << "Shortest Distance" << endl;
	printV(gm.djikstra(0));

	return 0;

}
