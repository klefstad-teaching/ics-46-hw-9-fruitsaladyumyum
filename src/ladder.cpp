#include "ladder.h"

#define UNUSED(x) (void)(x) //TODO: DELETE LATER D/ELETE LA/TER DELETE L/ATER/ DELETE LATER DEL/ETE LATER DELETE LATER /DELETE LATER 


/*
1)  CHECK THE INPUT TO MAKE SURE THAT THE START AND END WORDS ARE NOT THE SAME

2)  INVALID INPUT SHOULD CAUSE AN ERROR MESSAGE TO BE PRINTED. USE words.txt FOR YOUR DICTIONARY OF WORDS, AND IGNORE
    LETTER CASES. One exception, the start word can be a non-dictionary word.

3)  IMPLEMENT BFS USING A QUEUE TO STORE PARTIAL LADDERS THAT REPRESENT POSSIBILITIES TO EXPLORE. EACH PARTIAL LADDER
    IS A STACK, MEANING YOUR OVERALL COLLECTION MUST BE A QUEUE OF STACKS.

4)  ALLOW WORD LADDERS BETWEEN WORDS OF DIFFERENT LENGTHS. SO you can add or remove a single letter from your string
    at each hop, and you can add/remove this single letter from ANY index of the string.
    Hint: the lengths are either the same or differ by one character between neighbor words.

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

void error(string word1, string word2, string msg) {
    cerr << "The words [" << word1 << ", " << word2 << "] produced the following message: " << msg << endl;
};


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {UNUSED(str1);UNUSED(str2);UNUSED(d);return false;};
bool is_adjacent(const string& word1, const string& word2) {UNUSED(word1);UNUSED(word2);return false;};
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {UNUSED(begin_word);UNUSED(end_word);UNUSED(word_list);vector<string> cars; return cars;};
void load_words(set<string> & word_list, const string& file_name) {UNUSED(word_list);UNUSED(file_name);};
void print_word_ladder(const vector<string>& ladder) {UNUSED(ladder);};


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