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

class PriorityQueueMinHeap
{
public:
    // empty constructor
    PriorityQueueMinHeap(){};

    // get parent of i node
    int parent(int i) { return (i - 1) / 2; }

    // get left child of i node
    int left(int i) { return (2 * i + 1); }

    // get right child of i node
    int right(int i) { return (2 * i + 2); }

    // checks if i node is a leaf
    bool isLeaf(int i) { return 2 * i >= (_heap.size() - 1) && i < _heap.size(); }

    // checks if i node has left child
    bool hasLeft(int i) { return left(i) < _heap.size(); }

    // checks if i node has right child
    bool hasRight(int i) { return right(i) < _heap.size(); }

	// swap nodes at i and j
    void swap(int i, int j)
    {
        int tmp0 = _heap[i][0],
            tmp1 = _heap[i][1];

        _heap[i][0] = _heap[j][0];
        _heap[i][1] = _heap[j][1];

        _heap[j][0] = tmp0;
        _heap[j][1] = tmp1;
    }

    // sorts itself upwards from i
    void heapifyUp(int i)
    {
        // checks up parent distance is greater than current index
        while (i != 0 && _heap[parent(i)][1] > _heap[i][1])
        {
            // if so, swap and change current index to its parent since its shifted
            swap(i, parent(i));
            i = parent(i);
        }
    }

    // sorts itself downwards from i
    void heapifyDown(int i)
    {
        // keep swapping if node has children
        while (hasLeft(i))
        {
            int smallestChildIndex = -1;
            // if has children, it WILL have a left child
            if (hasLeft(i))
            {
                int leftChild = left(i);
                // it may not have a right child
                if (hasRight(i))
                {
                    int rightChild = right(i);
                    // get the smaller of the left and right children
                    smallestChildIndex = (_heap[leftChild][1] <= _heap[rightChild][1]) ? leftChild : rightChild;
                }
                // no right child
                else
                    smallestChildIndex = leftChild;
            }
            // no children at all
            else
                break;
            if (_heap[i][1] > _heap[smallestChildIndex][1])
            {
                swap(i, smallestChildIndex);
                i = smallestChildIndex;
            }
            // when the smallest child less or equals to i
            else
                break;
        }
    }

    // adds vertex and its distance from source into the priority queue
    void add(int vertex, int distance)
    {
        // inserts vertex, distance pair into heap
        int *tmp = new int[2]{vertex, distance};
        _heap.push_back(tmp);

        // sorts itself upwards
        heapifyUp(_heap.size() - 1);
    }

    // changes the distance of vertex from the source
    void edit(int vertex, int newDistance)
    {
        // loop through the queue to find the vertex and update the distance
        for (int i = 0; i < _heap.size(); i++)
        {
            if (_heap[i][0] == vertex)
            {
                int oldDistance = _heap[i][1];
                _heap[i][1] = newDistance;

                // if new distance if somehow larger than old distance,
                // no choice but to sort itself downwards
                if (newDistance > oldDistance)
                    heapifyDown(i);
                else
                    heapifyUp(i);
                break;
            }
        }
    }

    // returns [vertex, distance] of the shortest distance pair
    int *pop()
    {
        if (_heap.size() == 0)
            return NULL;

        int *smallest = new int[2]{_heap[0][0], _heap[0][1]};
        _heap.erase(_heap.begin());
        // edge case if size = 0 after erasing
        if (_heap.size() > 1)
        {
            swap(0, _heap.size() - 1);
            heapifyDown(0);
        }
        return smallest;
    }

	// returns whether heap is empty
    bool isEmpty()
    {
        return _heap.size() == 0;
    }

    // super useful for debugging heapify, prints heap
    void printHeap()
    {
        for (int i = 0; i < _heap.size(); i++)
        {
            int *tmp = _heap[i];
            cout << "(" << tmp[0] << "," << tmp[1] << ") ";
        }
        cout << endl;
    }

protected:
	// heap stores as vector instead of a tree structure
    vector<int *> _heap;
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
		ii u;
		vi d, pi, s;
		// 
		d.assign(size, INF);
		pi.assign(size, -1);
		s.assign(size, 0);

		d[source] = 0;

		//min Queue using Array/Vector
		vector<ii> pq;
		F(i,0,size) pq.pb(mp(d[i], i));

		// Outer Loop O(|V|)
		while (u=smallest_node(pq, s), u.se != -1){
			// O(|V|) to find the smallest node
			s[u.se] = 1;
			// O(|V|) to loop through matrix to find connected vertices
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

	vi djikstra(int source){
		// Time complexity should be O(( V + E )Log V)
		int u;
		vi d, pi, s;

		d.assign(size, INF);
		pi.assign(size, -1);
		s.assign(size, 0);

		d[source] = 0;
		PriorityQueueMinHeap pq= PriorityQueueMinHeap();
		F(i,0,size) pq.add(i, d[i]);

		// Outer Loop O(V)
		while (!pq.isEmpty()){
			// Extract Min O(Log(V))
			int * arr = pq.pop();
			ii node = mp(arr[1], arr[0]);
			s[node.se] = 1;
			// O(E) to loop through edges
			for (auto con: adj[node.se]){
				if (s[con.se] == 0 && (d[con.se] > node.fi + con.fi)){
					d[con.se] = node.fi + con.fi;
					pi[con.se] = node.se;
					// O(log(V)) to decrease key
					pq.edit(con.se, d[con.se]);
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

void tc3(string filename){
	ifstream myfile;
	ofstream outfile;
	vector<ull> v(501);
	
	myfile.open(filename);
	FE(i,100,500){
		GraphMatrix g = GraphMatrix(myfile);
		auto result = Bench::mark(mem_fn(&GraphMatrix::djikstra), &g, 0);
		v[i] = result.fi.as_nanoseconds();
	}
	myfile.close();
	myfile.open(filename);
	outfile.open("ga_tc3(1.0).csv");
	outfile << "|E|,Time_elapsed_GM(ns),Time_elapsed_GA(ns)" << endl;
	FE(i,100,500){
		GraphAdj g = GraphAdj(myfile);
		auto result = Bench::mark(mem_fn(&GraphAdj::djikstra), &g, 0);
		outfile << i << "," << v[i] << "," << result.fi.as_nanoseconds() << endl;
	}
	myfile.close();
	outfile.close();

}



int32_t main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	// gm_tc1();
	// gm_tc2();
	// ga_tc1();
	// ga_tc2();
	tc3("testcase3(1.0).txt");

	return 0;

}
