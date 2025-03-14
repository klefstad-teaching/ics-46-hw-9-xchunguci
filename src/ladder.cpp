#include "ladder.h"
#include <unordered_map>
#include <climits>

void error(string word1, string word2, string msg) {
  std::cout << word1 << " and " <<  word2 << " " << msg;
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream infile(file_name);
    if (!infile) {
        std::cout << "Failed to read file.";
        return;
    }
    
    string word;
    while (infile >> word) {
        for (char& c : word) {
            c = tolower(c);
        }
        word_list.insert(word);
    }
}


void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        std::cout << "No word ladder found.\n";
        return;
    }

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i] << ' ';
    }
    cout << '\n';
}

void my_assert(bool condition) {
    if (condition)
        cout << "Test passed, yo!" << endl;
    else
        throw "Test failed.";
}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}

static bool edit_distance_equal_length_within(const string& s1, const string& s2, int d) {
    int diff = 0;
    for (size_t i = 0; i < s1.size(); i++) {
        if (s1[i] != s2[i]) {
            diff++;
            if (diff > d)
                return false;
        }
    }
    return diff <= d;
}

static bool edit_distance_length_diff_one_within(const string& shorter, const string& longer) {
    int i = 0, j = 0;
    bool diffFound = false;
    while (i < static_cast<int>(shorter.size()) && j < static_cast<int>(longer.size())) {
        if (shorter[i] != longer[j]) {
            if (diffFound)
                return false;
            diffFound = true;
            j++; // skip one char in longer
        } else {
            i++; j++;
        }
    }
    return true;
}

static bool dp_edit_distance_within(const string& str1, const string& str2, int d) {
    int n = str1.size(), m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;
    for (int i = 1; i <= n; i++) {
        int rowMin = INT_MAX;
        for (int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
            rowMin = min(rowMin, dp[i][j]);
        }
        if (rowMin > d)
            return false;
    }
    return dp[n][m] <= d;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int n = str1.size();
    int m = str2.size();
    if (abs(n - m) > d)
        return false;
    if (d == 0)
        return str1 == str2;
    if (d == 1) {
        if (n == m)
            return edit_distance_equal_length_within(str1, str2, 1);
        else {
            const string& shorter = (n < m ? str1 : str2);
            const string& longer  = (n < m ? str2 : str1);
            return edit_distance_length_diff_one_within(shorter, longer);
        }
    }
    return dp_edit_distance_within(str1, str2, d);
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2)
        return true;
    
    return edit_distance_within(word1, word2, 1);
}

static vector<string> get_candidates(const string &last_word, const unordered_map<int, vector<string>>& words_by_length) {
    vector<string> candidates;
    for (size_t len = last_word.size() - 1; len <= last_word.size() + 1; ++len) {
        if (words_by_length.find(len) != words_by_length.end()) {
            for (const string &w : words_by_length.at(len))
                candidates.push_back(w);
        }
    }
    sort(candidates.begin(), candidates.end(), [last_word](const string &a, const string &b) {
        int diffA = abs((int)a.size() - (int)last_word.size());
        int diffB = abs((int)b.size() - (int)last_word.size());
        if (diffA == diffB)
            return a < b;
        return diffA < diffB;
    });
    return candidates;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word)
        return vector<string>{};

    unordered_map<int, vector<string>> words_by_length;
    for (const string& word : word_list)
        words_by_length[word.size()].push_back(word);

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        vector<string> candidates = get_candidates(last_word, words_by_length);
        for (const string &word : candidates) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return vector<string>();
}