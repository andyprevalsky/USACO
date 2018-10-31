#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
    private:
        int N;
    public:
        void Barn() {
            ifstream fin ("cbarn.in");
            ofstream fout ("cbarn.out");
            fin >> N;
            int q;
            int front = 0;
            vector<int> doors;
            for (int i = 0; i < N; i++) {
                fin >> q;
                doors.push_back(q);
            }
            for (int i = 0; i <= N; i++) {
                int j = i-1;
                if (j < 0) j = N-1;
                int spots = 0;
                int cows = 0;
                while (j != i) {
                    spots += 1;
                    cows += doors[j];
                    j -= 1;
                    if (j < 0) j = N-1;
                    if (cows > spots) break;
                    if (j == i) {
                        front = i;
                        break;
                    }
                }
            }
            vector<int> ordoors;
            int i = front;
            int j = i+1;
            if (j == N) j = 0;
            ordoors.push_back(doors[i]);  
            while (j != i) {
                ordoors.push_back(doors[j]);
                j++;
                if (j == N) j = 0;
            }    
            int energy = 0;
            for (int i = ordoors.size()-2; i >= 0; i--) {
                while(ordoors[i] > 0 && ordoors[i+1] == 0) {
                    int e = 0;
                    for (int j = i; j < ordoors.size()-1; j++) {
                        if (ordoors[j+1] != 0) break;
                        ordoors[j] -= 1;
                        ordoors[j+1] += 1;
                        e += 1;
                    }
                    energy += e*e;
                }
            }
            fout << energy;
        }
};

int main() {
    Solution s;
    s.Barn();

}