#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution {
    private:
        int N;
        vector<int> nums;
        unordered_map<int, int> prefix;
        int longest = 0;
    public:
        void readIn() {
            ifstream fin ("div7.in");
            fin >> N;
            int a;
            for (int i = 0; i < N; i++) {
                fin >> a;
                nums.push_back(a);
            }
        }

        void main() {
            readIn();
            ofstream fout ("div7.out");
            
            long long total = 0;
            for (int i = 0; i < nums.size(); i++) {
                total += nums[i];
                if (total == 0) continue;
                prefix[total%7] = i;
            }

            total = 0;
            if (prefix.find(0) != prefix.end()) {
                longest = prefix[0]+1;
            }
            for (int i = 0; i < nums.size(); i++) {
                total += nums[i];
                int currSum = total%7;
                int j = currSum;
                if (prefix.find(j) != prefix.end()) {
                    if (prefix[j]-i > longest) longest = prefix[j] - i;
                }
            }

            fout << longest;

        }
};

int main() {
    Solution s;
    s.main();
}