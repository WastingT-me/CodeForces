#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <tuple>
#include <algorithm>
 
using namespace std;
 
vector<int> min_operations_to_sort_substrings(int t, const vector<tuple<int, int, string, string, vector<pair<int, int>>>>& test_cases) {
    vector<int> results;
    results.reserve(t * 100); // Reserve space based on expected number of queries
 
    for (const auto& case_data : test_cases) {
        int n, q;
        string a, b;
        vector<pair<int, int>> queries;
        tie(n, q, a, b, queries) = case_data;
 
        // Initialize prefix sum arrays for frequencies of each character
        vector<vector<int>> freq_a(26, vector<int>(n + 1, 0));
        vector<vector<int>> freq_b(26, vector<int>(n + 1, 0));
 
        // Fill prefix sum arrays
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 26; ++j) {
                freq_a[j][i + 1] = freq_a[j][i];
                freq_b[j][i + 1] = freq_b[j][i];
            }
            freq_a[a[i] - 'a'][i + 1]++;
            freq_b[b[i] - 'a'][i + 1]++;
        }
 
        // Process each query
        for (const auto& query : queries) {
            int l, r;
            tie(l, r) = query;
            int changes = 0;
 
            for (int i = 0; i < 26; ++i) {
                int count_a = freq_a[i][r] - freq_a[i][l - 1];
                int count_b = freq_b[i][r] - freq_b[i][l - 1];
                changes += abs(count_a - count_b);
            }
 
            results.push_back(changes / 2);
        }
    }
 
    return results;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    vector<tuple<int, int, string, string, vector<pair<int, int>>>> test_cases;
    test_cases.reserve(t);
 
    for (int i = 0; i < t; ++i) {
        int n, q;
        string a, b;
        cin >> n >> q >> a >> b;
        
        vector<pair<int, int>> queries(q);
        for (int j = 0; j < q; ++j) {
            int l, r;
            cin >> l >> r;
            queries[j] = {l, r};
        }
        
        test_cases.emplace_back(n, q, a, b, queries);
    }
 
    vector<int> results = min_operations_to_sort_substrings(t, test_cases);
    for (int result : results) {
        cout << result << "\n";
    }
 
    return 0;
}