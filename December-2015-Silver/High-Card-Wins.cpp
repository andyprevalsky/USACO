#include <fstream>
#include <functional>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
    private:
        int N;
        vector<int> Bessie;
        vector<int> Elsie;
        unordered_set<int> inElsie;
        int res = 0;
    public:
        void readIn() {
            ifstream fin ("highcard.in");
            fin >> N;
            int a;
            for (int i = 0; i < N; i++) {
                fin >> a;
                Elsie.push_back(a);
                inElsie.insert(a);
            }
            for (int i = 1; i <= 2*N; i++) {
                if (inElsie.find(i) == inElsie.end()) Bessie.push_back(i);
            }
            sort(Elsie.begin(), Elsie.end(), greater<int>());
            sort(Bessie.begin(), Bessie.end(), greater<int>());
        }
        
        void main() {
            ofstream fout ("highcard.out");
            readIn();
            int E, B;
            while(!Bessie.empty()) {
                E = Elsie.back();
                B = Bessie.back();
                if (B > E) {
                    Elsie.pop_back();
                    Bessie.pop_back();
                    res++;
                } else {
                    Bessie.pop_back();
                }
            }
            fout << res;
        }
};

int main() {
    Solution s;
    s.main();
}