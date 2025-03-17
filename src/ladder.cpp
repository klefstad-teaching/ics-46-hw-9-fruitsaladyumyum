#include "ladder.h"



int strcmpignorecase(const string& word1, const string& word2) {
    if (word1.size() != word2.size())
        return -1;

    size_t word1_idx = 0;
    size_t word2_idx = 0;
    for (; word1_idx < word1.size() && word2_idx < word2.size(); ++word1_idx, ++word2_idx) {
        if (tolower(word1[word1_idx]) != tolower(word2[word2_idx]))
            return tolower(word1[word1_idx])-tolower(word2[word2_idx]);
    }
    return 0;
};


string strtolower(const string& word) {
    string lowercase_word = word;
    for (size_t i=0; i<lowercase_word.size(); ++i) {
        lowercase_word[i] = tolower(lowercase_word[i]);
    }
    return lowercase_word;
};


void error(string word1, string word2, string msg) {
    cerr << "[ERROR] The words [" << word1 << ", " << word2 << "] produced the following message: " << msg << endl;
};


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    /*
    Basically only computes the Longest Common Subsequence
    */
    //compute the length difference and ensure it's positive
    int len_diff = str1.size()-str2.size();
    if (len_diff < 0)
        len_diff *= -1;

    //evalute the edit distance
    if (len_diff > d)
        return false;
    else {
        int num_edits = 0;
        size_t str1_idx = 0;
        size_t str2_idx = 0;
        //for each character in both words
        for (; (str1_idx < str1.size()) && (str2_idx < str2.size()) && (num_edits < d+1); ++str1_idx, ++str2_idx)
            //if the two current chars are inequal
            if (tolower(str1[str1_idx]) != tolower(str2[str2_idx])) {
                //if the next char in a word matches the current char of the other word, 
                //then they are differing by at least one insertion/deletion
                if (str1_idx < str1.size()-1 && tolower(str1[str1_idx+1]) == tolower(str2[str2_idx]))
                    ++str1_idx;
                else if (str2_idx < str2.size()-1 && tolower(str2[str2_idx+1]) == tolower(str1[str1_idx]))
                    ++str2_idx;
                //otherwise, a substitution is required
                else {
                    ; }
                ++num_edits;
            }
        if (num_edits > d || (str1_idx+(d-num_edits)) < str1.size() || (str2_idx+(d-num_edits)) < str2.size())
            return false;
        else
            return true;
    }
};


bool is_adjacent(const string& word1, const string& word2) {
    //check that the two words differ in length only by <= 1 chars.
    if (!edit_distance_within(word1, word2, 1))
        return false;
    else
        return true;

    /*
    //if the two words are equivalent in size
    else if (word1.size() == word2.size()) {
        //then they must differ by only substitutions
        int num_diff_chars = 0;
        //for each character in both words
        for (size_t i = 0; (i < word1.size()) && (num_diff_chars < 2); ++i)
            if (tolower(word1[i]) != tolower(word2[i]))
                ++num_diff_chars;
        if (num_diff_chars > 1)
            return false;
        else
            return true;
    }

    //otherwise, they are inequal in size
    else {
        //then they must differ by only a single insertion/deletion
        int num_inserts_and_deletes = 0;
        size_t word1_idx = 0;
        size_t word2_idx = 0;
        //for each character in both words
        for (; (word1_idx < word1.size()) && (word2_idx < word2.size()) && (num_inserts_and_deletes < 2); ++word1_idx, ++word2_idx)
            //if the two current chars are inequal
            if (tolower(word1[word1_idx]) != tolower(word2[word2_idx])) {
                //if the next char in a word matches the current char of the other word, 
                //then they are differing by at least one insertion/deletion
                if (word1_idx < word1.size()-1 && tolower(word1[word1_idx+1]) == tolower(word2[word2_idx]))
                    ++word1_idx;
                else if (word2_idx < word2.size()-1 && tolower(word2[word2_idx+1]) == tolower(word1[word1_idx]))
                    ++word2_idx;
                //otherwise, then they have two consecutive chars that don't match, making the words non-adjacent
                else
                    return false;
                ++num_inserts_and_deletes;
            }
        if (num_inserts_and_deletes > 1 || (word1_idx+1) < word1.size() || (word2_idx+1) < word2.size())
            return false;
        else
            return true;
    }
    */
};


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    string lowercase_begin_word = strtolower(begin_word);
    string lowercase_end_word = strtolower(end_word);
    //check the inputs
    if (lowercase_begin_word == lowercase_end_word) {
        error(begin_word, end_word, "Start and end word cannot be the same word!");
        vector<string> empty_ladder;
        return empty_ladder;
    }
    if (!word_list.contains(lowercase_end_word)) {
        error(begin_word, end_word, "End word must be in the dictionary!");
        vector<string> empty_ladder;
        return empty_ladder;
    }
    queue<vector<string>> ladder_queue;
    vector<string> beginning_ladder = {lowercase_begin_word};
    ladder_queue.push(beginning_ladder);
    set<string> visited;
    visited.insert(lowercase_begin_word); //the ladder shall contain only lowercase words
    //for each ladder in the ladder queue
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        //for each word in the dictionary
        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (!visited.contains(word)) { //TODO: do we need to ignore casing for this??
                    visited.insert(word);
                    vector<string> new_ladder = ladder; //make a copy of the ladder
                    new_ladder.push_back(word);
                    if (word == lowercase_end_word) { //ignore case
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    vector<string> empty_ladder;
    return empty_ladder;
};


void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; (in >> word); ) {
        word_list.insert(strtolower(word)); //make the dictionary contain only lowercase words
    }
    in.close();
};


void print_word_ladder(const vector<string>& ladder) {
    size_t curr_idx = 0;
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    }
    else {
        cout << "Word ladder found: ";
        for (string word : ladder) {
            cout << word << " ";
            ++curr_idx;
        }
        cout << endl;
    }
};


void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
};