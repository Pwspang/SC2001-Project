import random
import time


"""
Global Variables
"""
n_comp=0

"""
Helper Functions 
"""


def comp(a, b):
    global n_comp
    n_comp += 1
    if a < b:
        return 1
    elif a > b:
        return -1
    else:
        return 0


def generate_lst(size):
    return [random.randint(1, 10000) for i in range(size)]


def time_function(func, s, v):
    global n_comp
    n_comp = 0
    start = time.perf_counter_ns()
    func(v, s)
    return n_comp, time.perf_counter_ns()-start


"""
Sorting Functions
"""


def insertionSort(v):
    for i in range(1, len(v)):
        for j in range(i, 0, -1):
            if comp(v[j-1], v[j]) == -1:
                v[j-1], v[j] = v[j], v[j-1]
            else:
                break


def hybridSort(v, s):
    if len(v) <= s:
        insertionSort(v)
    else:
        m = len(v)//2
        L = v[m:]
        R = v[:m]
        hybridSort(L, s)
        hybridSort(R, s)

        i = j = k = 0
        #Merge out of place
        tmp_lst = []
        while i < len(L) and j < len(R):
            cmp = comp(L[i], R[j])
            if cmp > 0:
                v[k] = L[i]
                i += 1
                k += 1
            elif cmp < 0:
                v[k] = R[j]
                j += 1
                k += 1
            else:
                v[k] = R[j]
                k += 1
                j += 1
                v[k] = L[i]
                k += 1
                i += 1

        while i < len(L):
            v[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            v[k] = R[j]
            j += 1
            k += 1
"""
Part i

Fixed S = 16

Variable N to measure the time complexity 

Goal understand: The time complexity of the hybridsort algorithm

To Do:

1) Plot n vs comparison, O(n^2), O(nlogn)
2) Curve should lie within O(nlogn) and O(n^2)

"""


def part_1():
    i = 100
    f = open("part1.csv", "w")
    print("n,n_comp,time")
    f.write("n,n_comp,time\n")
    while i < 10000000:
        v = generate_lst(i)
        c, t = time_function(hybridSort, 16, list(v))
        f.write("{},{},{}\n".format(i, c, t))
        print("{},{},{}".format(i, c, t))
        i *= 2

    f.close()

"""
Part ii

Fixed n = 100000

Goal: To understand how number of comparisons increases with respect to S

*Important note: Try to explain the sharp jump in key comparisons 

To Do: 

From the data identify S "shape" key comparisons increased

12 -> 24 -> 48 -> 96 

Can see that every x2 will have aa sharp increase in number of key comparisons

Explaination: Try to link back to time complexity log2(n/k)

"""

def part_2():
    f = open("part2.csv", "w")
    print("s,n_comparison,cpu_burst(ns)")
    f.write("s,n_comparison,cpu_burst(ns)\n")
    v = generate_lst(100000)
    for s in range(1, 101):
        c, t = time_function(hybridSort, s, list(v))
        print("{},{},{}".format(s, c, t))
        f.write("{},{},{}\n".format(s, c, t))

    f.close()

"""
Part iii

Varying input of dataasets 

Goal: Determine an optimal value of S for the best performance of the hybrid algorithm 

How to do it? 
- To find a point where insertion is faster than mergesort
- Since insertion sort more efficient than merge sort on smaller array size
- Why not look at key_comparisons only? merge_sort -> recursive call -> OS need to create a stack for subsequent functions -> potentially more time needed 
- Therefore, we look at both key comparisons and cpu burst time to determine the optimal value of s
** Important for mergeSort optimality we choose multiples of 2 for S (For every multiple the key comp sharply increases)

*We Chose S=8
"""


def part_3():
    f = open("part3.csv", "w")
    print("n,n_comparison_insertion,cpu_burst_insertion(ns),n_comparison_merge,cpu_burst_merge(ns),percentage faster insertion(%)")
    f.write("n,n_comparison_insertion,cpu_burst_insertion(ns),n_comparison_merge,cpu_burst_merge(ns),percentage faster insertion(%)\n")
    for n in range(2, 101):
        v = generate_lst(n)
        c1, t1 = time_function(hybridSort, n, list(v))
        c2, t2 = time_function(hybridSort, 1, list(v))
        print("{},{},{},{},{},{:.2f}%".format(n, c1, t1, c2, t2, (t2-t1)/t2*100))
        f.write("{},{},{},{},{},{:.2f}%\n".format(n, c1, t1, c2, t2, (t2-t1)/t2*100))
    f.close()


def part_d():
    f = open("partd.csv", "w")
    v = generate_lst(10000000)

    f.write("n_comparison,cpu_burst(ns)\n")
    print("n_comparison,cpu_burst(ns)")
    c1, t1 = time_function(hybridSort, 1, list(v))
    c2, t2 = time_function(hybridSort, 8, list(v))

    print("{},{}".format(c1, t1))
    print("{},{}".format(c2, t2))
    f.write("{},{}\n".format(c1, t1))
    f.write("{},{}\n".format(c2, t2))


def main():
    #part_1()
    #part_2()
    #part_3()
    part_d()
    pass



if __name__ == "__main__":
    main()
