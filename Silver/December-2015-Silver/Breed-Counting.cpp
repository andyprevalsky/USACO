#include <fstream>
#include <vector>
using namespace std;

class Solution {
    private:
        int N, Q;
        vector<int> cows;
        vector<vector<int> > prefixes;
        vector<vector<int> > queries;
    public:
        void readIn() {
            ifstream fin ("bcount.in");
            fin >> N >> Q;
            int a;
            for (int i = 0; i < N; i++) {
                fin >> a;
                cows.push_back(a);
            }
            int b;
            for (int i = 0; i < Q; i++) {
                fin >> a >> b;
                queries.push_back({a-1, b-1});
            }
        }

        int main() {
            readIn();
            ofstream fout ("bcount.out");
            int a = 0;
            int b = 0;
            int c = 0;
            prefixes.push_back({0, 0, 0});
            for (auto i: cows) {
                if (i == 1) a++;
                else if (i == 2) b++;
                else c++;
                prefixes.push_back({a, b, c});
            }

            for (auto i: queries) {
                fout << prefixes[i[1]+1][0]-prefixes[i[0]][0] << " " << prefixes[i[1]+1][1]-prefixes[i[0]][1] << " " << prefixes[i[1]+1][2]-prefixes[i[0]][2] << endl;
            }
        }
};

int main() {
    Solution s;
    s.main();
}