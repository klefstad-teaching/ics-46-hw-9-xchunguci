#include "ladder.h"


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
        std::cout << "No word ladder found.\n" << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
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

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int n = str1.size();
    int m = str2.size();

    if (abs(n - m) > d) return false;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; 
            } else {
                // choose min cost
                dp[i][j] = 1 + min({ dp[i - 1][j],      // deletion
                                     dp[i][j - 1],      // insertion
                                     dp[i - 1][j - 1] }); // substitution
            }
        }
    }
    
    return dp[n][m] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2)
        return true;
    
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    
    if (begin_word == end_word) return vector<string>{begin_word};

    queue<vector<string>> ladder_queue;
    

    ladder_queue.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = ladder.back();
        
        for (const string &word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    
    return vector<string>();
}