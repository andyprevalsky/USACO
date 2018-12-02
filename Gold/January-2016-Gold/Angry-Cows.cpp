#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
    private:
        int N;
        set<int> haybales;
    public:
        void prepData() {
            ifstream fin ("angry.in");
            fin >> N;
            int a;
            for (int i = 0; i < N; i++) {
                fin >> a;
                haybales.insert(a*2);
            }           
        }

        bool leftMet(int pos, int power) {
            while (pos > *haybales.begin()) {
                if (power <= 0) return false;
                int next = *haybales.lower_bound(pos-power);
                if (pos == next) return false;
                pos = next;
                power -= 2;
            }
            return true;
        }

        bool rightMet(int pos, int power) {
            while (pos < *(--haybales.end())) {
                if (power <= 0) return false;
                int next = *(--haybales.upper_bound(pos+power));
                if (pos == next) return false;
                pos = next;
                power -= 2;
            }
            return true;
        }



        void main() {
            prepData();
            ofstream fout ("angry.out");
            
            int minPow = 0;
            int maxPow = 1000000000;
            int midPow; 

            while (minPow < maxPow) {
                midPow = minPow + (maxPow-minPow)/2;
                int l = *haybales.begin();
                int r = *(--haybales.end());
                int m;

                while (l < r) {
                    m = l + (r-l)/2 + 1;
                    if (leftMet(m, midPow)) l = m;
                    else r = m-1;
                }

                if (rightMet(m, midPow)) maxPow = midPow;
                else minPow = midPow+1;
            }

            fout << minPow / 2 << "." << ((minPow % 2 == 0) ? 0 : 5) << endl;
        }
};

int main() {
    Solution s;
    s.main();
}