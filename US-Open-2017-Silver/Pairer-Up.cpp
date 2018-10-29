#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ifstream fin ("pairup.in");
    ofstream fout ("pairup.out");
    int N;
    fin >> N;
    vector<vector<long long int> > cows;
    long long int a, b;
    for (int i = 0; i < N; i++) {
        fin >> a >> b;
        cows.push_back({b, a});
    }
    sort(cows.rbegin(), cows.rend());
    int front = 0;
    long long int j1 = 0;
    int back = cows.size()-1;
    long long int j2 = cows[back][1];
    long total = cows[front][0] + cows[back][0];
    
    while((front != back || j1 != j2) && (front != back-1 || j1 != cows[front][1])) {
        if (j1 == cows[front][1]) {
            front += 1;
            j1 = 0;
        }
        if (j2 == 0) {
            back -= 1;
            j2 = cows[back][1];
        }
        if (cows[front][0] + cows[back][0] > total) {
            total = cows[front][0] + cows[back][0];
        }
        j1 += 1;
        j2 -= 1;
    }
    fout << total;
}