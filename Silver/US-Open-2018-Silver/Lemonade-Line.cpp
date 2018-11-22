#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution {
    private:
        int N;
        vector<int> cows;
    public:
        void readIn() {
            ifstream fin ("lemonade.in");
            fin >> N;
            int a; 
            for (int i = 0; i < N; i++) {
                fin >> a;
                cows.push_back(a);
            }
            sort(cows.begin(), cows.end(), greater<int>());
        }
        void main() {
            readIn();
            ofstream fout ("lemonade.out");
            int count = 0;
            for (int i = 0; i < N; i++) {
                if (cows[i] < count) break;
                else count++;
            }
            fout << count;
        }
};

int main() {
    Solution s;
    s.main();
}