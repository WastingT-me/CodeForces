#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
 
int calculate_time(const string& s) {
    int time = 2;  
    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] == s[i - 1]) {
            time += 1;
        } else {
            time += 2;
        }
    }
    return time;
}

string insert_best_letter(const string& s) {
    int max_time = -1;
    string best_string;
 
    // Пробуем вставить букву в каждую позицию от 0 до len(s)
    for (size_t i = 0; i <= s.size(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            string new_s = s.substr(0, i) + c + s.substr(i);
            int current_time = calculate_time(new_s);
            if (current_time > max_time) {
                max_time = current_time;
                best_string = new_s;
            }
        }
    }
    return best_string;
}

void run_tests() {
    vector<pair<string, string>> test_cases = {
        {"a", "wa"},  // Один возможный вариант вставки w перед a
        {"aaa", "aada"},  // Вставка d между любыми двумя a увеличивает время
        {"abb", "abcb"},  // Вставка c между b увеличивает время
        {"password", "pastsword"}  // Вставка s после pa
    };
    
    bool passed = true;
    for (size_t i = 0; i < test_cases.size(); ++i) {
        const string& s = test_cases[i].first;
        const string& expected = test_cases[i].second;
        string result = insert_best_letter(s);
        if (calculate_time(result) != calculate_time(expected)) {
            passed = false;
            cout << "Test case " << i + 1 << " failed: input(" << s 
                 << "), expected(" << expected << "), got(" << result << ")" << endl;
        } else {
            cout << "Test case " << i + 1 << " passed: input(" << s 
                 << "), expected(" << expected << "), got(" << result << ")" << endl;
        }
    }
 
    if (passed) {
        cout << "All test cases passed!" << endl;
    } else {
        cout << "Some test cases failed." << endl;
    }
}
 
int main() {
    int t;
    cin >> t;
    vector<string> results(t);
    for (int i = 0; i < t; ++i) {
        string s;
        cin >> s;
        results[i] = insert_best_letter(s);
    }
 
    for (const string& result : results) {
        cout << result << endl;
    }
 
    return 0;
}