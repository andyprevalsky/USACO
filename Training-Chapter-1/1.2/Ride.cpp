/*
ID: andypre1
LANG: C++11
PROB: ride
*/

#include <fstream>
#include <string>
using namespace std;

class Solution { 
    public:
        string main() {
            ifstream fin ("ride.in");
            string comet, group;
            fin >> comet >> group;
            int cometV = 1;
            int groupV = 1;
            for (auto i = comet.begin(); i != comet.end(); i++) {
                cometV *= (int(*i)-64);
            }
            for (auto i = group.begin(); i != group.end(); i++) {
                groupV *= (int(*i)-64);
            }
            if (cometV % 47 == groupV % 47) return "GO\n";
            else return "STAY\n";
        }
};

int main() {
    ofstream fout ("ride.out");
    Solution s;
    fout << s.main();
}