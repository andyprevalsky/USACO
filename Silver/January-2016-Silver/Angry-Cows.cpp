#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;

class Solution {
    private:    
        int N, K;
        vector<int> cows;
        vector<vector<int> > gaps;
        vector<int> intervals;
    public:
        void readIn() {
            ifstream fin ("angry.in");
            fin >> N >> K;
            int a;
            for (int i = 0; i < N; i++) {
                fin >> a;
                cows.push_back(a);
            }
            sort(cows.begin(), cows.end());
        }

        bool validatePower(int power) {
            int total = 0;
            int length;
            int s = 0;
            int e = 0;
            for (int i = 0; i < K; i++) {
                length = power*2;
                while (cows[e]-cows[s] <= length) {
                    if (e == cows.size()-1) return true;
                    e++;
                }
                s = e;
            }
            return false;
            
        }

        void main() {
            readIn();
            ofstream fout ("angry.out");
            int l = 1;
            int r = cows[cows.size()-1];
            int mid;
            while (l < r-1) {
                mid = (l+r)/2;
                if (validatePower(mid)) r = mid;
                else l = mid;
            }
            if (validatePower(r)) fout << r << endl;
            else fout << l << endl;
        }
};

int main() {
    Solution s;
    s.main();
}