#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

class Solution {
    private:
        int N;
        vector<int> E1;
        vector<int> E2;
        vector<int> B;
        int memo[100001] = {};
    public:
        void readIn() {
            ifstream fin ("cardgame.in");
            fin >> N;
            int a;
            for (int i = 0; i < N/2; i++) {
                fin >> a;
                memo[a] = 1;
                E1.push_back(a);
            }
            for (int i = 0; i < N/2; i++) {
                fin >> a;
                memo[a] = 1;
                E2.push_back(a);
            }
            for (int i = 1; i < 100001; i++) {
                if (i > 2*N) break;
                if (memo[i] == 0) B.push_back(i);
            }
            sort(E1.begin(), E1.end());
            sort(E2.begin(), E2.end(), greater<int>());
            sort(B.begin(), B.end());
        }

        int binSearch(int lowBound1, int lowBound2) {
            // if l2 is > l1 and nothing found, then pop the smallest card larger than l1
            // else: pop the largest card
            int lowBound = max(lowBound1, lowBound2);
            int l = 0;
            int r = B.size()-1;

            int min = B[r]+1;
            int mid = l + (r-l)/2;
            int index = r;
            
            while (l < r-1) {
                int mid = l + (r-l)/2;
                if (B[mid] < lowBound) l = mid;
                else {
                    r = mid;
                    if (B[mid] < min) {
                        min = B[mid];
                        index = mid;
                    }
                } 
            }
            if (B[r] < min && B[r] > lowBound) {
                min = B[r];
                index = r;
            }
            if (B[mid] < min && B[mid] > lowBound) {
                index = mid;
                min = B[mid];
            }
            if (B[l] < min && B[l] > lowBound) {
                index = l;
                min = B[l];
            }

            if (lowBound1 > lowBound2 && min == B[r]+1) min = B[r];
            else if (lowBound2 > lowBound1 && min == B[r]+1) return 0;
            // cout << "MIN: " <<  min << " LOWERBOUND: " << lowBound << endl;
            // for (auto i: B) {
            //     cout << i << endl;
            // }
            // cout << " ----- " << endl
            B.erase(B.begin()+index);

                
                
            // for (auto i: B) {
            //     cout << i << endl;
            // }
            // cout << endl << endl;
            return min;
        }

        void main() {
            readIn();
            ofstream fout ("cardgame.out");
            int points = 0;
            int j = 0;
            int i = 0;
            while (i != N/2 && j != N/2) {
                int res = binSearch(E1[i], E2[j]);
                if (res == 0) {
                    j++;
                    continue;
                }
                else if (res > E1[i]) points++;
                i++;
            }
            while (i < N/2) {
                int res = binSearch(E1[i], 0);
                if (res > E1[i]) points++;
                i++;
            }
            // cout << B.size() << endl;

            // cout << " " << B.size() << " " << N/2 << endl;
            // exit(1);
            sort(B.begin(), B.end(), greater<int>());
            j = 0;
            for (int i = 0; i < N/2; i++) {
                if (j == B.size()) {
                    fout << points << endl;
                    return;
                }               
                while(B[j] > E2[i]) {
                    j++;
                    if (j == B.size()) {
                        fout << points << endl;
                        return;
                    }
                }
                points++;
                j++;
            }
            fout << points << endl;
        }
        
};

int main() {
    Solution s;
    s.main();
}