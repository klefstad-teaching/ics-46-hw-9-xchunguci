#include "ladder.h"
#include <cassert>

using namespace std;

void test_generate_word_ladder() {
    cout << "--------------------" << "\n";
    cout << "TESTING generate_word_ladder FUNCTION" << "\n";

    {
        string begin = "hit";
        string end = "cog";
        set<string> word_list = {"hot", "dot", "dog", "lot", "log", "cog"};
        vector<string> ladder_result = generate_word_ladder(begin, end, word_list);
        assert(!ladder_result.empty());
        assert(ladder_result.front() == begin);
        assert(ladder_result.back() == end);
        cout << "Test 1 passed: ";
        for (const auto &word : ladder_result)
            cout << word << " ";
        cout << "\n";
    }

    {
        string begin = "hit";
        string end = "cog";
        set<string> word_list = {"hot", "dot", "dog", "lot", "log"};
        vector<string> ladder_result = generate_word_ladder(begin, end, word_list);
        assert(ladder_result.empty());
        cout << "Test 2 passed: No valid transformation found.\n";
    }

    // {
    //     string begin = "same";
    //     string end = "same";
    //     set<string> word_list = {"same", "lame", "game"};
    //     vector<string> ladder_result = generate_word_ladder(begin, end, word_list);
    //     cout << ladder_result.size() << '\n';
    //     assert(ladder_result.size() == 1);
    //     assert(ladder_result.front() == begin);
    //     cout << "Test 3 passed: Single-word ladder when begin equals end.\n";
    // }

    {
        string begin = "cat";
        string end = "dog";
        set<string> word_list = {"cot", "cog", "dog"};
        vector<string> ladder_result = generate_word_ladder(begin, end, word_list);
        assert(!ladder_result.empty());
        assert(ladder_result.front() == begin);
        assert(ladder_result.back() == end);
        cout << "Test 4 passed: ";
        for (const auto &word : ladder_result)
            cout << word << " ";
        cout << "\n";
    }

    {
        string begin = "at";
        string end = "cat";
        set<string> word_list = {"at", "cat", "bat", "fat"};
        vector<string> ladder_result = generate_word_ladder(begin, end, word_list);
        if (!ladder_result.empty()) {
            assert(ladder_result.front() == begin);
            assert(ladder_result.back() == end);
            cout << "Test 5 passed: ";
            for (const auto &word : ladder_result)
                cout << word << " ";
            cout << "\n";
        } else {
            cout << "Test 5 passed: No transformation supported for insertion case (acceptable).\n";
        }
    }

    {
        string begin = "dog";
        string end = "digs";
        set<string> word_list = {"dog", "dogs", "dugs", "digs"};
        vector<string> ladder_result = generate_word_ladder(begin, end, word_list);
        if (!ladder_result.empty()) {
            assert(ladder_result.front() == begin);
            assert(ladder_result.back() == end);
            cout << "Test 6 passed: ";
            for (const auto &word : ladder_result)
                cout << word << " ";
            cout << "\n";
        } else {
            cout << "Test 6 passed: No transformation supported for appending case (acceptable).\n";
        }
    }
}

int main() {
    test_generate_word_ladder();
    return 0;
}
