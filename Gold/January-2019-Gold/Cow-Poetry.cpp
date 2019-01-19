#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <math.h>
using namespace std;

#define MOD 1000000007

class Solution {
    private:
        int N, M, K;
        long long res = 1;
        vector<int> words[5001];
        map<int, int> syll; // maps syllables to numbers of words with said syllable
        map<char, int> scheme;
        vector<int> combos;
        vector<int> permutes;
        long long dp[5001] = {}; //number of combination with x syllables left
    public:
            long long modpow(long long a, long long b, long long n){
                long long x=1, y=a; 
                while (b > 0) {
                    if (b%2 == 1) {
                        x = (x*y) % n; // multiplying with base
                    }
                    y = (y*y) % n; // squaring the base
                    b /= 2;
                }
                return x % n;
            }
        void prepData() {
            ifstream fin ("poetry.in");
            fin >> N >> M >> K;
            int a, b;
            for (int i = 0; i < N; i++) {
                fin >> a >> b;
                syll[a] += 1;
                words[b].push_back(a);
            }
            char t;
            for (int i = 0; i < M; i++) {
                fin >> t;
                scheme[t] += 1;
            }
        }

        void main() {
            prepData();
            ofstream fout ("poetry.out");
            dp[0] = 1;
            int j = 0;

            while (j <= K) {
                for (auto i: syll) {
                    if (i.first > j) break;
                    dp[j] += (dp[j-i.first] * i.second%MOD)%MOD;
                    dp[j] %= MOD;
                } 
                j += 1;
            }

            for (int i = 1; i <= N; i++) {
                long long combo = 0;
                if (words[i].empty()) continue;
                for (auto j: words[i]) {
                    combo += dp[K-j];
                    combo %= MOD;
                    //if (combo > 1000000000)
                }
                combos.push_back(combo);
            }

            for (auto i: scheme) {
                long long p = 0;
                for (auto j: combos) {
                    p += modpow(j, i.second, MOD);
                    p %= MOD;
                }
                res = (res%MOD * p)%MOD;
            }
            fout << res << endl;
        }
};

int main() {
    Solution s;
    s.main();
    return 0;
}