/*
ID: andypre1
LANG: C++11
PROB: gift1
*/

#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
    private:
        int NP;
    public:
        void main() {
            ifstream fin ("gift1.in");
            ofstream fout ("gift1.out");
            unordered_map<string, int> banks;
            vector<string> order;
            fin >> NP;
            string temp;
            for (int i = 0; i < NP; i++) {
                fin >> temp;
                order.push_back(temp);
                banks[temp] = 0;
            }
            int giving, numPeople;
            for (int i = 0; i < NP; i++) {
                fin >> temp;
                fin >> giving >> numPeople;
                if (numPeople != 0)
                    banks[temp] += (giving%numPeople)-(giving);
                else
                    banks[temp] += giving;
                for (int j = 0; j < numPeople; j++) {
                    fin >> temp;
                    banks[temp] +=  giving/numPeople;
                }
            }
            int pos = 0;
            for (auto i = banks.begin(); i != banks.end(); i++) {
                fout << order[pos] << " " << banks[order[pos]] << endl;
                pos++;
            }
        }
        
};

int main() {
    Solution s;
    s.main();
}