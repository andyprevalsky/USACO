#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    private:
        int N;
        int count = 0;
        vector<vector<int> > arr;
    public:
        void readIn() {
            ifstream fin ("sort.in");
            fin >> N;
            int a;
            for (int i = 0; i < N; i++) {
                fin >> a;
                arr.push_back({a, i});
            }
            sort(arr.begin(), arr.end());
            int place = 0;
            for (auto &i: arr) {
                i[0] = place++;
            }
            sort(arr.begin(), arr.end(), [](vector<int> a, vector<int>b){return a[1]<b[1];});
        }

        void main() {
            readIn();
            ofstream fout ("sort.out");
            int min = 2000000000;
            for (int i = 0; i < arr.size(); i++) {
                if (i-arr[i][0] > count) count = i-arr[i][0];
            }
            fout << count+1;
        }
};

int main() {
    Solution s;
    s.main();
}