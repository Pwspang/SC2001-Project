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
#define F(i,L,R) for (int i = L; i < R; i++) //next four are for "for loops"
#define FE(i,L,R) for (int i = L; i <= R; i++)
#define FF(i,L,R) for (int i = L; i > R; i--)
#define FFE(i,L,R) for (int i = L; i >= R; i--)
#define getS(x) scanf("%s", x) //get a char* string
#define clr(a,x) memset(a,x,sizeof(a)) //set elements of array to some value
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
#define INF 1001001001
#define PI 3.1415926535897932384626
//for map, pair
#define mp make_pair
#define fi first
#define se second
// for debug
#define DBG(vari) cerr<<#vari<<" = "<<(vari)<<endl;
#define printA(a,L,R) FE(i,L,R) cout << a[i] << (i==R?'\n':' ')
#define printV(a) printA(a,0,a.size()-1)
#define MAXN 10000
//for vectors
#define pb push_back
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

struct Heap{
	//creating a min head instead of max heap
	vector<ii> heap;
	vi pos;
	int size;

	Heap(vector<ii> & v){
		size = v.size();
		heap.resize(size*2);
		pos.assign(size*2, -1);
		F(i,0,size) {
			heap[i] = v[i];
			//pos should be in order
			pos[i]=i;
		}
		heapifying(0);
	}

	// Heap Constructors
	void heapifying(int i){
		//if not leaf
		if (2*i+1 <= size-1){
			heapifying(2*i+1);
			heapifying(2*i+2);
			fixHeap(i, heap[i]);
		}
	}

	void fixHeap(int i, ii k){
		//check if leaf
		if (2*i+1 > size-1){
			// set pos 
			pos[k.se]=i;
			heap[i] = k;
		} else {
			//Check if right child exists
			int smaller=2*i+1;
			if (2*i+2 <= size-1) {
				smaller = heap[2*i+1].fi < heap[2*i+2].fi ? 2*i+1 : 2*i+2; 
			} 

			if (k.fi < heap[smaller].fi){
				//set pos
				pos[k.se]=i;
				heap[i] = k;
			} else {
				//swap pos
				swap(pos[heap[i].se], pos[heap[smaller].se]);
				swap(heap[i], heap[smaller]);
				fixHeap(smaller, k);
			}
			
		}
	}

	ii extractMin(){
		swap(heap[0], heap[size-1]);
		pos[heap[0].se] = 0;
		pos[heap[size-1].se] = -1;
		size--;
		heapifying(0);
		return heap[size];
	}

	void fixUp(int p){
		//iterative fixUp
		while (p != 0){
			int parent = (p-1)/2;
			if (heap[parent].fi < heap[p].fi) return;
			//swap 
			swap(heap[p], heap[parent]);
			swap(pos[heap[p].se], pos[heap[parent].se]);
			p = parent;
		}

	}


	void decreaseKey(ii k){
		//find key in O(1)
		int index = pos[k.se];
		heap[index].fi = k.fi;
		fixUp(index);
	} 

	// void insertNode(ii k){
	// 	heap[size]=k;
	// 	size++;
	// 	fixUp(size-1);
	// }

	// void deleteNode(int vertex){
	// 	//Find Vertex, using O(n) ensure that the node is inside the heap

	// 	int index=-1;
	// 	F(i,0,size){
	// 		if (heap[i].se == vertex){
	// 			index = i;
	// 			break;
	// 		}
	// 	}
	// 	//Same idea as extractMin 
	// 	if (index == size-1) size--;
	// 	else {
	// 		swap(heap[index], heap[size-1]);
	// 		size--;
	// 		heapifying(index);
	// 	}
	// }

	bool empty(){
		return size==0;
	}

	void print_heap(){
		F(i,0,size) cout << heap[i] << " ";
		cout << endl;
	}

};


/*

Graph function 

*/

struct GraphMatrix{
	vvi matrix;
	int size;
	GraphMatrix(ifstream&  myfile){
		myfile >> size;
		matrix.resize(size);
		F(i,0,size) {
			vi v;
			v.assign(size, 0);
			matrix[i]=v;
		}
		set_connection(myfile);
	}

	void set_connection(ifstream&  myfile){
		// Get input from user
		int n;
		myfile >> n;
		int a,b,c;
		while (n--){
			myfile >> a >> b >> c;
			matrix[a][b] = c;	
			matrix[b][a] = c;
		}
	}

	ii smallest_node(vector<ii> & pq, vi & s){
		//returns (-1,-1) if the queue is empty
		//Distance is -1 if item is not in the array
		ii smallest=mp(INF,-1);
		F(i,0,size){
			if (pq[i].fi < smallest.fi && pq[i].fi != -1 && s[i] != 1){
				smallest = pq[i];
			}
		}
		return smallest;
	}

	// To analyse time complexity, check V against time taken (Vary E to show that the number of edges of graph is not a factor)

	vi djikstra(int source){
		// Time complexity should be O(2|V|^2) -> O(|V|^2)
		// Time complexity for best case/average case/worst case should be the same
		ii u;
		vi d, pi, s;
		d.assign(size, INF);
		pi.assign(size, -1);
		s.assign(size, 0);

		d[source] = 0;

		//min Queue using Array/Vector
		//Could also use vector d and s only, but follow project definition
		vector<ii> pq;
		F(i,0,size) pq.pb(mp(d[i], i));

		// Outer Loop O(|V|)
		while (u=smallest_node(pq, s), u.se != -1){
			// O(|V|) to find the smallest node
			s[u.se] = 1;
			//O(|V|) to loop through matrix to find connected vertices
			F(i,0,size){
				if (matrix[u.se][i] != 0 && s[i] == 0 && (matrix[u.se][i] + u.fi) < d[i]){
					// updating pq vector O(1) update
					pq[i].fi  = u.fi + matrix[u.se][i];
					// updating the distance vector O(1) Update
					d[i] = u.fi + matrix[u.se][i];
					pi[i] = u.se;
				}	
			}
		}
		
		return d;
		 	
	} 

	void print_graph(){
		cout << "Graph Matrix" << endl;
		F(i,0,size){
			F(j,0,size) cout << std::setw(3) << matrix[i][j];
			cout << endl;
		}
		cout << endl;
	}
};


struct GraphAdj{
	vector<vector<ii>> adj;
	int size;

	GraphAdj(ifstream& myfile){
		myfile >> size;
		adj.resize(size);
		set_connection(myfile);
	}

	void set_connection(ifstream&  myfile){
		int a,b,c;
		int n;
		myfile >> n;
		while(n--){
			myfile >> a >> b >> c;
			adj[a].pb(mp(c, b));	
			adj[b].pb(mp(c, a));
		}
	}

	// vi djikstra(int source){
	// 	int u;
	// 	vi d, pi, s;
	// 	priority_queue<ii, vector<ii>, greater<ii>> pq;
	// 	d.assign(size, INF);
	// 	pi.assign(size, -1);
	// 	s.assign(size, 0);

	// 	d[source] = 0;
	// 	pq.push(mp(0, source));

	// 	while (!pq.empty()){
	// 		ii node = pq.top();
	// 		pq.pop();
	// 		if (s[node.se]==1) continue;
	// 		s[node.se] = 1;
	// 		for (ii con: adj[node.se]){
	// 			if (s[con.se] == 0 && d[con.se] > d[node.se] + con.fi){
	// 				pq.push(mp(d[node.se] + con.fi, con.se));
	// 				d[con.se] = d[node.se] + con.fi;
	// 				pi[con.se] = node.se;
	// 			}
	// 		}
			
	// 	}
		
	// 	return d;
		 	
	// } 

	vi djikstra(int source){
		// Time complexity should be O(V + E Log V)
		int u;
		vi d, pi, s;

		d.assign(size, INF);
		pi.assign(size, -1);
		s.assign(size, 0);

		d[source] = 0;
		//pq.push(mp(0, source));
		// Creating initial Heap
		vector<ii> tmp;
		F(i,0,size) tmp.pb(mp(d[i], i));
		Heap pq = Heap(tmp);

		// Outer Loop O(V)
		while (!pq.empty()){
			ii node = pq.extractMin();
			s[node.se] = 1;
			// O(E/V) to loop through the edges
			for (auto con: adj[node.se]){
				if (s[con.se] == 0 && (d[con.se] > node.fi + con.fi)){
					d[con.se] = node.fi + con.fi;
					pi[con.se] = node.se;
					pq.decreaseKey(mp(d[con.se], con.se));
				}
			}
			
		}
		return d;
		 	
	} 


	void print_graph(){
		cout << "Vertex: (Distance, Vertex)" << endl;
		F(i,0,size){
			cout << i << ": ";
			F(j,0,adj[i].size()){
				cout << adj[i][j] << " -> ";
			}
			cout << endl;
		}

	}
};

/*

Run Testcases using BM library 

*/

void gm_tc1(){
	ifstream myfile;
	ofstream outfile;
	outfile.open("gm_tc1.csv");
	myfile.open("testcase1.txt");
	outfile << "|V|,Time_elapsed(ns)" << endl;
	FE(i,200,1000){
		GraphMatrix g = GraphMatrix(myfile);
		auto result = Bench::mark(mem_fn(&GraphMatrix::djikstra), &g, 0);
		outfile << i << "," << result.fi.as_nanoseconds() << endl;
	}
	outfile.close();
	myfile.close();
}

void gm_tc2(){
	ifstream myfile;
	ofstream outfile;
	myfile.open("testcase2.txt");
	outfile.open("gm_tc2.csv");
	outfile << "|E|,Time_elapsed(ns)" << endl;
	FE(i,99,4950){
		GraphMatrix g = GraphMatrix(myfile);
		auto result = Bench::mark(mem_fn(&GraphMatrix::djikstra), &g, 0);
		outfile << i << "," << result.fi.as_nanoseconds() << endl;
	}
	outfile.close();
	myfile.close();

}

void ga_tc1(){
	ifstream myfile;
	ofstream outfile;
	outfile.open("ga_tc1_heap.csv");
	myfile.open("testcase1.txt");
	outfile << "|V|,Time_elapsed(ns)" << endl;
	FE(i,200,1000){
		GraphAdj g = GraphAdj(myfile);
		auto result = Bench::mark(mem_fn(&GraphAdj::djikstra), &g, 0);
		outfile << i << "," << result.fi.as_nanoseconds() << endl;
	}
	outfile.close();
	myfile.close();
}


void ga_tc2(){
	ifstream myfile;
	ofstream outfile;
	myfile.open("testcase2.txt");
	outfile.open("ga_tc2_heap.csv");
	outfile << "|E|,Time_elapsed(ns)" << endl;
	FE(i,99,4950){
		GraphAdj g = GraphAdj(myfile);
		auto result = Bench::mark(mem_fn(&GraphAdj::djikstra), &g, 0);
		outfile << i << "," << result.fi.as_nanoseconds() << endl;
	}
	outfile.close();
	myfile.close();

}


int32_t main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	// gm_tc1();
	// gm_tc2();
	// ga_tc1();
	// ga_tc2();



		
	return 0;

}
