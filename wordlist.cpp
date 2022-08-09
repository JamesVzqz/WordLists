/* WordList  file
*
*
*	This file will contain the function definitions
*
*	Topics to research: Multilevel Pointers, Dynamic Allocation, Classes
*
*/
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif

#include"wordlist.h"
#include<iostream>
#include<cstring>

using std::cout;
using std::endl;

using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

/* Function: Wordlist Constructor  
*/
WordList::WordList(const int cap):words_list(nullptr), n_words(0), capacity(cap){

	if (capacity < 1) {
		words_list = nullptr;
	} else {
		words_list = new char* [capacity];
		for (int i = 0; i < capacity; i++) {
			words_list[i] = new char[MAX_WORD_SIZE];
		}
	}

}

/* Function: Wordlist Copy Constructor
*/
WordList::WordList(const WordList &src) {

	// Edge cases
	if (src.words_list == nullptr) {
		capacity = 0;
		n_words = 0;
		words_list = nullptr;
	}
	else {
		n_words = src.n_words;
		capacity = src.capacity;
		words_list = new char* [capacity];
		for (int i = 0; i < capacity; i++){
			words_list[i] = new char[MAX_WORD_SIZE];  // Setting up its own dynamically allocated memory
			// QUESTION: how to copy each string without copying each character from each row?
			strcpy(words_list[i], src.words_list[i]);  
			// QUESTION: does strcpy does a deep copy? I thought about doing it char by char w another for loop but remember we will not deal with individual characters
			/*
			// not sure if strcpy will do a deep copy in case it doesn't, must copy each char manually
			for (int j = 0; j < 20; j++) {
				words_list[i][j] = src.words_list[i][j];
			}
			*/
		}
	}

}


/* Function: Wordlist Destructor
*/
WordList::~WordList() {

	for (int i = 0; i < n_words; i++)
		delete[] words_list[i];
	delete[] words_list;

}

/* Function: printList
*/
int	WordList::print() const {

	int index = 0;
	if (n_words > 0) {
		cout << words_list[index++];
		while (index < n_words) {
			cout << " " << words_list[index++];
		}
		cout << "\\n" << endl;
		return index;
	}
	else {
		return -2;
	}

}


/* Function: get
*/
char* WordList::get(const int index) const {

	if ((index < 0) || (index >= n_words)) {
		return nullptr;
	}
	return words_list[index];

}


/* Function: count
*/
int	WordList::count() const {

	return n_words;

}


/* Function: insert
*/
int	WordList::insert(const char word[]) {

	char** templist;

	// n_words starts with value 0;
	if (word[0] == '\0') { // if word is empty
		// do nothing, return -1
		return -1;
	} 
	if (words_list == nullptr) {
		// create a new empty list with enough space dynamically allocated for more capacity (resize)
		templist = new char* [capacity + 1];
		for (int i = 0; i < capacity + 1; i++) {
			templist[i] = new char[MAX_WORD_SIZE];
		}
		for (int i = n_words; i > 0; i--) {
			// copy first word of original into second of temp
			strcpy(templist[i], words_list[i - 1]);
		}
		// clean up old list 
		for (int i = 0; i < n_words; i++)
			delete[] words_list[i];

		// update pointer to point new one
		words_list = templist;
		// add the word to the first row
		strcpy(words_list[0], word);
		// increment n_words each time a word is added
		n_words++;
		capacity++;

		// return -2
		return -2;
	}
	if (n_words < capacity) { // if space is available (n_words < capacity)
		// move everything down by one
		for (int i = n_words; i > 0; i--) {
			strcpy(words_list[i], words_list[i-1]);
		}
		// add the word to the first row
		strcpy(words_list[0], word);
		// increment n_words each time a word is added
		n_words++;
		// return 0
		return 0;
	} 
	else if (n_words == capacity) { // if not more space available (n_words == capacity)
		// create a new empty list with enough space dynamically allocated for more capacity (resize)
		templist = new char* [capacity + 1];
		for (int i = 0; i < capacity + 1; i++) {
			templist[i] = new char[MAX_WORD_SIZE];
		}
		for (int i = n_words; i > 0; i--) {
			// copy first word of original into second of temp
			strcpy(templist[i], words_list[i-1]);
		}
		// clean up old list 
		for (int i = 0; i < n_words; i++)
			delete[] words_list[i];

		// update pointer to point new one
		words_list = templist;
		// add the word to the first row
		strcpy(words_list[0], word);
		// increment n_words & capacity each time a word is added
		n_words++;
		capacity++;

		// return 1
		return 1;
	}

}


/* Funtion: erase
*/
int	WordList::erase(const char word[]) {

	int count = 0;

	if (words_list == nullptr) {
		// do nothing, return 2
		return -2;
	}
	else {
		for (int i = n_words - 1; i >= 0; i--) {
			if (strcmp(words_list[i], word) == 0) {
				count++;
				// move word upwards (eliminate previous word)
				for (int j = i + 1; j < n_words; j++) {
					strcpy(words_list[j - 1], words_list[j]);
				}
				// substract from n_words
				n_words--;
			}
		}
	}

	return count;

}


/* Funtion: prepend
*/
int	WordList::prepend(const WordList* src) {

	char** templist;
	int total_words = n_words + src->n_words;
	int max = total_words;
	int src_num = src->n_words;

	if (src == nullptr) { // if *src is nullptr or empty, does nothing
		// does nothing, return 0
		return 0;
	}
	if (words_list == nullptr) { // if words_list == nullptr, everything applies except returns -2
		// set capacity equal to total_words
		capacity = total_words;

		// create a new empty list with enough space dynamically allocated for more capacity (resize)
		templist = new char* [capacity + 1];
		for (int i = 0; i < capacity + 1; i++) {
			templist[i] = new char[MAX_WORD_SIZE];
		}
		for (int i = max - 1; i > 1; i--) {
			// copy first each word of original into temp (leaving src->n_words amount of spaces)
			strcpy(templist[i], words_list[src_num]);
			src_num--;
		}
		// clean up old list 
		for (int i = 0; i < n_words; i++)
			delete[] words_list[i];

		// update pointer to point new one
		words_list = templist;

		// for the amount of new words
		int k = 0;
		for (int j = (src->n_words); j > 0; j--) {
			// add the n word to the k row (initial to last available)
			strcpy(words_list[j - 1], src->words_list[j - 1]);
			k++;
			n_words++;
		}

		// return -2
		return -2;
	}
	if (total_words <= capacity) { // if space is available (total_words <= capacity)
		
		// move everything down by one, x amount of times
		for (int x = src->n_words; x > 0; x--) {
			for (int i = max; i > 0; i--) {
				strcpy(words_list[i], words_list[i - 1]);
			}
		}

		// for the amount of new words
		int k = 0;
		for (int j = (src->n_words); j > 0; j--) {
			// add the n word to the k row (initial to last available)
			strcpy(words_list[j-1], src->words_list[j-1]);
			k++;
			n_words++;
		}

		// return number of words prepended
		return k;
	}
	else if (total_words > capacity) { // if not more space available (total_words > capacity)
		// set capacity equal to total_words
		capacity = total_words;

		// create a new empty list with enough space dynamically allocated for more capacity (resize)
		templist = new char* [capacity + 1];
		for (int i = 0; i < capacity + 1; i++) {
			templist[i] = new char[MAX_WORD_SIZE];
		}
		for (int i = max-1; i > 1; i--) {
			// copy first each word of original into temp (leaving src->n_words amount of spaces)
			strcpy(templist[i], words_list[src_num]);
			src_num--;
		}
		// clean up old list 
		for (int i = 0; i < n_words; i++)
			delete[] words_list[i];

		// update pointer to point new one
		words_list = templist;

		// for the amount of new words
		int k = 0;
		for (int j = (src->n_words); j > 0; j--) {
			// add the n word to the k row (initial to last available)
			strcpy(words_list[j - 1], src->words_list[j - 1]);
			k++;
			n_words++;
		}

		// return number of words prepended
		return k;
	}

}


/* Funtion: search
*/
int WordList::search(const char word[]) const {

	if (words_list == nullptr) {
		// do nothing, return 2
		return -2;
	}
	else if (words_list != nullptr) {
		for (int i = 0; i < n_words; i++) {
			// iterate to find the word
			if (strcmp(words_list[i], word) == 0) {
				// return the index of the word
				return i;
				cout << i << endl;
			}
		}
		return -1;
	}

}


/* Funtion: sort
*/
int	WordList::sort(bool asc) {

	if (words_list == nullptr) {
		return -2;
	} else if (n_words == 1) {	
		return 1;
	} else if (asc == true) {		
		int min = 0;
		for (int i = 0; i < n_words; i++) {
			min = i;												
			for (int j = i + 1; j < n_words; j++) {
				if (strcmp(words_list[j], words_list[min]) < 0) {		
					min = j;										
				}
			}
			if (min != i) {										
				char* temp = new char[MAX_WORD_SIZE];
				strcpy(temp, words_list[i]);
				words_list[i] = new char[MAX_WORD_SIZE];
				strcpy(words_list[i], words_list[min]);
				words_list[min] = new char[MAX_WORD_SIZE];
				strcpy(words_list[min], temp);
				delete[] temp;
			}

		}
		return 0;
	} else if (asc == false) {												
		int max = 0;
		for (int i = 0; i < n_words; i++) {
			max = i;
			for (int j = i + 1; j < n_words; j++) {
				if (strcmp(words_list[j], words_list[max]) > 0) {
					max = j;
				}
			}
			if (max != i) {
				char* temp = new char[MAX_WORD_SIZE];
				strcpy(temp, words_list[i]);
				words_list[i] = new char[MAX_WORD_SIZE];
				strcpy(words_list[i], words_list[max]);
				words_list[max] = new char[MAX_WORD_SIZE];
				strcpy(words_list[max], temp);
				delete[]temp;
			}
		}

		return 0;
	}
	
}


/* Funtion: Assignment Operator  
*/
WordList& WordList::operator=(const WordList &src) {

	// check for self-assignment
	if (this == &src) {
		return *this;
	}
	// clean up
	delete[] words_list;
	// no inheritance

	// check for edge cases
	if (src.words_list == nullptr) {
		capacity = 0;
		n_words = 0;
		words_list = nullptr;
		return *this;
	}
	else {
		n_words = src.n_words;
		capacity = src.capacity;
		words_list = new char* [capacity]; // (re)allocate
		for (int i = 0; i < capacity; i++) {
			words_list[i] = new char[MAX_WORD_SIZE];  // Setting up its own dynamically allocated memory
			strcpy(words_list[i], src.words_list[i]);
		}
	}
	// return myself
	return *this;

}

