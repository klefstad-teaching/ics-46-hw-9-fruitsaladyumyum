#include "ladder.h"

/*
3)  IMPLEMENT BFS USING A QUEUE TO STORE PARTIAL LADDERS THAT REPRESENT POSSIBILITIES TO EXPLORE. EACH PARTIAL LADDER
    IS A STACK, MEANING YOUR OVERALL COLLECTION MUST BE A QUEUE OF STACKS.

5)  Another subtle issue is that you must not reuse words that have been included in a previous shorter ladder. 
    For example, suppose that you have added the partial ladder cat → cot → cog to the queue. 
    Later on, if your code is processing ladder cat → cot → con, one neighbor of con is cog, 
    so you might want to examine cat → cot → con → cog. But doing so is unnecessary, 
    because your goal is to find the shortest valid word ladder, and you have already found one from cat to cog 
    without the unnecessary word con. So you should not enqueue the longer ladder in your algorithm.

    If you follow this rule properly, it will ensure that as soon as you've enqueued a ladder ending with a 
    specific word, you've found a minimum-length path from the starting word to the end word in the ladder, 
    so you will never have to enqueue that end word again. To implement this strategy, keep track of the set of 
    words that have already been used in any ladder, and ignore those words if they come up again.
*/
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
    else
        return true;
};


bool is_adjacent(const string& word1, const string& word2) {
    //check that the two words differ in length only by <= 1 chars.
    if (!edit_distance_within(word1, word2, 1))
        return false;

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
    for (string word : ladder) {
        cout << word;
        if (curr_idx < ladder.size()-1) {
            cout << " -> ";
        }
        else {
            cout << endl;
        }
        ++curr_idx;
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