#include <vector>
#include <fstream>
#include <iostream>
#include <deque>
#include <map>
#include <list>
using namespace std;

class Solution {
    private:
        int N;
        deque<int> cows;
    public:
        void prepData() {
            ifstream fin ("sleepy.in");
            fin >> N;
            for (int i = 0; i < N; i++) {
                int a; fin >> a;
                cows.push_back(a);
            }
        }

        bool isSorted() {
            int prev = 0;
            for (auto i: cows) {
                if (i != prev+1) return false;
                prev = i;
            }
            return true;
        }

        void main() {
            prepData();
            ofstream fout ("sleepy.out");
            vector<int> ans;
            int count = 0;
            while (1) {
                int curr = cows.front();
                if (curr == 1 && isSorted()) break;
                cows.pop_front();
                int j = N;
                for (auto i = cows.rbegin(); i != cows.rend(); i++) {
                    if (curr > *i || (curr == 1 && *i == N)) {
                        cows.insert((i).base(), curr);
                        ans.push_back(j-1); 
                        break;
                    }
                    j -= 1;
                }
            }
            fout << ans.size() << endl;
            for (int i = 0; i < ans.size(); i++) fout << ans[i] << (i == ans.size()-1 ? "" : " ");
            for (auto i: ans) cout << i << endl;

        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}