#include "ladder.h"



void test_edit_distance_within() {
    my_assert(edit_distance_within("cars", "bars", 1) == true);
    my_assert(edit_distance_within("cars", "car", 1) == true);
    my_assert(edit_distance_within("car", "cars", 1) == true);
    my_assert(edit_distance_within("car12345", "car", 8) == true);
    my_assert(edit_distance_within("asdfasdf", "1", 1) == false);
}


void test_is_adjacent() {
    //happy cases
    //substitutions
    my_assert(is_adjacent("cars", "bars") == true);
    my_assert(is_adjacent("bars", "cars") == true);
    //insertion/deletion before/after word
    my_assert(is_adjacent("cars", "cars ") == true);
    my_assert(is_adjacent("cars ", "cars") == true);
    //insertion/deletion within word
    my_assert(is_adjacent("caars", "cars") == true);
    my_assert(is_adjacent("cars", "caars") == true);

    //edge cases
    my_assert(is_adjacent("cars", "c ars ") == false);
    my_assert(is_adjacent("sleep", "isle") == false);
    my_assert(is_adjacent("dis", "isle") == false);
    //ignore casing
    my_assert(is_adjacent("cars", "Cars ") == true);
    my_assert(is_adjacent("Cars", "cars ") == true);
    my_assert(is_adjacent("cbrs", "caRs") == true);
    my_assert(is_adjacent("caRs", "cbrs") == true);
}


void test_strcmpignorecase() {
    //reflexive property
    string a = "asdf";
    string b = "Asdf";
    my_assert(strcmpignorecase(a, b) == 0);
    my_assert(strcmpignorecase(b, a) == 0);
    //unable to get lowercase
    string c = " sdf";
    string d = " sDF";
    my_assert(strcmpignorecase(c, d) == 0);
    //inequivalent size
    string e = "a";
    string f = "ab";
    my_assert(strcmpignorecase(e, f) != 0);
}


void test_strtolower() {
    string a = "ASSff";
    string b = "assff";
    my_assert(strtolower(a) == b);
}


void test_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    //happy cases
    verify_word_ladder();
    //allow non-dictionary beginning words
    my_assert(generate_word_ladder("Marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("asdf", "car", word_list).size() == 0);
    //disallow non-dictionary end words
    my_assert(generate_word_ladder("car", "Carss", word_list).size() == 0);
    //disallow identical beginning and end words
    my_assert(generate_word_ladder("car", "car", word_list).size() == 0);
}


int main() {
    /*
    string a = "nums";
    vector<string> cars(20, a);
    print_word_ladder(cars);
    */
    test_edit_distance_within();
    test_is_adjacent();
    test_strcmpignorecase();
    test_strtolower();
    test_word_ladder();
    
    return 0;
}