#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ifstream fin ("maxcross.in");
    ofstream fout ("maxcross.out");
    int N, K, B;
    fin >> N >> K >> B;
    vector<int> signals (N);
    for (int i = 0; i < B; i++) {
        int b; 
        fin >> b;
        signals[b-1] = 1;
    }
    unordered_map<int, int> dp;
    int s = 0;
    int minWindow = 99999999;
    for (int i = 0; i < N; i++) {
        dp[i] = s;
        s += signals[i];
        if (i >= K-1) {
            int windowB = s-dp[i-K+1];
            if (windowB < minWindow)
                minWindow = windowB;
        }
    }
    fout << minWindow;
}