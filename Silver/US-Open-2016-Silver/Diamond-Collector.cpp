#include <fstream>
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    private:
        int N, K;
        vector<int> jewels;
        vector<int> bests;
        int best = 0;
    public:
        void readIn() {
            ifstream fin ("diamond.in");
            fin >> N >> K;
            int t;
            for (int i = 0; i < N; i++) {
                fin >> t;
                jewels.push_back(t);
            }
            sort(jewels.begin(), jewels.end());
        }

        void contInterval() {
            int i = 0;
            int count = 0;
            deque<int> cases;
            while (jewels[i] <= 2*K && i != jewels.size()) {
                cases.push_back(jewels[i]);
                count++;
                i++;
            }
            if (count > best) best = count;
            for (;i < jewels.size(); i++) {
                while (!cases.empty() && jewels[i] - cases.front() > 2*K) {
                    cases.pop_front();
                    count--;
                }
                cases.push_back(jewels[i]);
                count++;
                if (count > best) best = count;
            }
        }

        void distInterval() { 
            int i = 0;
            int count = 0;
            int best1 = 0;
            int count2 = 0;
            deque<int> cases;
            bests.push_back(0);
            for (;i < jewels.size(); i++) {
                while (!cases.empty() && jewels[i] - cases.front() > K) {
                    cases.pop_front();
                    count--;
                }
                cases.push_back(jewels[i]);
                count++;
                if (count > best1) best1 = count;
                bests.push_back(best1);
            }
            deque<int> cases2;
            i = jewels.size()-1;
            count = 0;
            for (;i >= 0; i--) {
                while (!cases2.empty() && -jewels[i] + cases2.front() > K) {
                    cases2.pop_front();
                    count--;
                }
                cases2.push_back(jewels[i]);
                count++;
                cout << count << " " << bests[i] << endl; 
                if (i == jewels.size()-1) continue;
                if (count + bests[i] > best) best = count + bests[i+1];
            }
        }

        void main() {
            readIn();
            ofstream fout ("diamond.out");
            contInterval();
            distInterval();
            fout << best;
        }
};

int main() {
    Solution s;
    s.main();
}
