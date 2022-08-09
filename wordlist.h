/* WordList header file
*
*	This file contains the class definition for the WordList.  
*
*	Topics: Multilevel Arrays, Pointers, Dynamic Allocation, Classes
*
*/
#ifndef WORDLIST_H
#define WORDLIST_H

// Uncomment this if you want to play with memory tracer
//#include"debugmem.h" 

/* Globally defined constants
*/
// All words are at most 19 characters + '\0'
const int MAX_WORD_SIZE = 20;

/* Word List ADT
*/
class WordList {

public:
	WordList(const int cap);
	WordList(const WordList &src);
	~WordList();

	int		print() const; 

	char*	get(const int index) const;

	int		count() const;

	int		insert(const char word[]);

	int		erase(const char word[]); 

	int		prepend(const WordList* src);

	int		search(const char word[]) const;
	
	int		sort(const bool asc);

	WordList& operator=(const WordList &src);

#ifndef MAKE_MEMBERS_PUBLIC 
// If this macro is defined prior to including this header file
// it will ignore the private access specifier, and the member
// variables will be follow the above public specifier.
private:
#endif
	int		n_words;		// Number of words currently in list
	int		capacity;	// The total size of the list.
	char**	words_list;		// The list storing the words
};

#endif