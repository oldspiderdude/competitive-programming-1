/*
 * Convex Hull Trick is a technique used to determine efficiently, after preprocessing,
 * which member of a set of linear functions in which one variable attains an extremal value
 * for a given value of the independent variable.
 *
 * Suppose you have a set of lines yi = ai*x + bi and you want to find the smallest yi for given x.
 * Naively you could evaluate all yi for this x and choose the smallest one.
 * But if you want to evaluate a series of values for x, then you can determine where yi intersects
 * and then for each interval between the intersections determine which yi is the smallest.
 * Then, given any x, you choose the corresponding interval and only evaluate the yi that is smallest on that interval.
 *
 * Reference problem: IOI 2002 Batch Scheduling
 */

#include <bits/stdc++.h>

using namespace std;

#define SIZE 10005

int N, S;
int T[SIZE], F[SIZE];
int dp[SIZE], sumT[SIZE], sumF[SIZE];

deque<int> q;

inline double f (int k, int i) {
    return ((double)dp[k] - (double)dp[i])/((double)sumT[k] - (double)sumT[i]);
}
int main() {
    scanf("%d%d", &N, &S);
    for (int x = 0; x < N; x++)
        scanf("%d%d", &T[x], &F[x]);
    for (int i = N-1; i >= 0; i--) {
        sumT[i] = sumT[i+1] + T[i];
        sumF[i] = sumF[i+1] + F[i];
    }
    q.push_back(N);
    for (int i = N-1; i >= 0; i--) {
        while (q.size() >= 2 && f(q[0], q[1]) < (double)sumF[i])
            q.pop_front();

        int j = q.front();
        dp[i] = (dp[j] + (S + sumT[i] - sumT[j])*sumF[i]);
        while (q.size() >= 2 && f(q[q.size()-2], q[q.size()-1]) > f(q[q.size()-1], i)) {
            q.pop_back();
        }
        q.push_back(i);
    }
    printf("%d\n", dp[0]);
    return 0;
}

