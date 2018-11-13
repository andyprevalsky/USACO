#include <fstream>
#include <vector>
using namespace std;

class Solution {
    private:
        int res;
        int N;
        vector<vector<char> > input;
        vector<vector<char> > output;
    public:
        void main() {
            ifstream fin ("transform.in");
            ofstream fout ("transform.out");
            fin >> N;
            char c;
            for (int k = 0; k < 2; k++) {
                for (int j = 0; j < N; j++) {
                    vector<char> row;
                    for (int i = 0; i < N; i++) {
                        fin >> c;   
                        row.push_back(c);
                    }
                    if (k == 0) input.push_back(row);
                    else output.push_back(row);
                }
            }

            fout << res;
        }
};

int main() {
    Solution s;
    s.main();
}