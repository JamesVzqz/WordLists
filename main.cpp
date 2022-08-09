
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif



/* Main functions
*
*	I'm using preprocessor directives to layout different mains to test
*	various functions. I have 5 example mains. Better than 
*	commenting/uncommenting blocks of code.
*
*/

// Choose which run to compile
#define RUN5 //RUN0 RUN1 RUN2 RUN3 RUN4 RUN5


#ifdef RUN1 

#include<iostream>
using std::cout;
using std::endl;

#include<cstring>
using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

int main() {

	int max = 5, // Keep track of the max number words	
		num = 0; // Number of words we can currently store
	//Allocate rows, to point to words
	char ** testlist = new char*[max];
	// for each row, allocate space for words
	for (int i = 0; i < max; i++) {
		testlist[i] = new char[20];
	}
	
	// Initialize words
	strcpy(testlist[0], "harry");
	strcpy(testlist[1], "ron");
	strcpy(testlist[2], "hermione");
	num = 3;	// Must be consistent with intended state, 
				// e.g. there are three currently three words.

	return 0;
}

#elif defined RUN1  //Test constructor 


#define MAKE_MEMBERS_PUBLIC // This constant will be checked in worlist.h

#include"wordlist.h"
#include<iostream>

#include<assert.h>
using std::cout;
using std::endl;

int main() {

	WordList wordlist(5);

	// Assuming we made our member variables public:
	cout << "Count: " << wordlist.n_words << endl; // Expect 0

	cout << "Capacity: " << wordlist.capacity << endl; // Expect 5


	return 0;
} 

#elif defined RUN2 


#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"


#include<assert.h>

// Same as above but using asserts instead of cout
//
// asserts are a way to check conditions, they will gracefully crash
// the program if the condition is not met.  
//
// Effective programmers have in mind test cases prior to 
// implmentation.  Should know what the end state should be after
// any function call.

int main() {
	WordList *wordlist = new WordList(5);

	// Assuming we made our member variables public:
	// If we failed to set our member variables correctly 
	// These assertions will fail
	assert(wordlist->n_words == 0);
	assert(wordlist->capacity == 5);
	

	return 0;
}

#elif defined RUN3

#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"
#include<iostream>
using std::cout;
using std::endl;

// Test insert: Both Constructor and insert must be
// implmented prior to running this code, otherwise
// it will crash.
int main() {
	WordList *wordlist = new WordList(5);
	wordlist->insert("harry");
	wordlist->insert("ron");
	wordlist->insert("hermione");

	// Assuming we made our member variables public:
	cout  << wordlist->words_list[0][2] << endl; // Expect 'r'

	cout  << wordlist->words_list[1] << endl; // Expect "ron"

	return 0;
}

#elif defined RUN4

#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"
#include<assert.h>
#include<cstring>

using std::strcmp;

// Test insert: same as RUN3 but with asserts. Both Constructor and insert 
// must be implmented prior to running this code, otherwise it will crash.
int main() {

	WordList *wordlist = new WordList(5);
	wordlist->insert("harry");
	wordlist->insert("ron");
	wordlist->insert("hermione");
	
	// Assuming we made our member variables public:
	assert(wordlist->words_list[0][2] == 'r' ); // Individual character, can use == 

	assert(strcmp(wordlist->words_list[1], "ron") == 0); // cstring, must use strcmp
	
	return 0;
}

#elif defined RUN5

#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"
#include<iostream>
using std::cout;
using std::endl;

// Test insert: Both Constructor and insert must be
// implmented prior to running this code, otherwise
// it will crash.
int main() {


	// 1. Testing constructor: Working
	WordList* wordlist = new WordList(5);

	/*
	// 2 & 3. Testing Copy Constructor & Destructor: Working & Working
	WordList existingList(5);
	if (0 == 0) {
		WordList newList(existingList); // Copy Constructor
	}
	*/


	// 4. Testing Insert: Working
	wordlist->insert("snape"); // 6
	wordlist->insert("voldemord"); // 5
	wordlist->insert("dumbledore"); // 4
	wordlist->insert("toby"); // 3
	wordlist->insert("hermione"); // 2
	wordlist->insert("ron"); // 1
	wordlist->insert("harry"); // 0


	// Comment or Uncomment blocks of text to test different parts

	
	// 5. Testing Print (turn on Insert): Working
	int retval = wordlist->print();
	cout << "total words in wordlist: " << retval << endl;


	/*
	// 6. Testing Get (turn on Insert): Working
	char* word = wordlist->get(1);
	if (word != nullptr)
		cout << word << endl;
	*/

	/*
	// 7. Testing Count (turn on Insert): Working
	for (int i = 0; i < wordlist->count(); i++) {
		cout << wordlist->get(i) << " ";
	}
	int wordamt = wordlist->count();
	cout << "total words in wordlist: " << wordamt << endl;
	*/

	/*
	// 8. Testing Erase (turn on Insert): Working
	wordlist->print();
	wordlist->erase("toby");
	wordlist->print();
	*/

	/*
	// 9. Testing Assignment operator (turn on Insert): Working

	WordList ben(5); // WordList can store 5 words
	//... Some WordList operations
	if (0 == 0) {
		WordList ann(4);
		ann = ben;
	} // Should not results in undefined behavior
	ben = ben;
	*/

	/*
	// 10. Testing Search (turn on Insert): Working
	wordlist->insert("Waldo"); // 2
	wordlist->insert("Is"); // 1
	wordlist->insert("Where"); // 0
	int retval = wordlist->search("Waldo");
	if (retval < 0)
		cout << "Not found" << endl;
	cout << "return value: " << retval << endl;
	int retval2 = wordlist->search("wawldo");
	if (retval2 < 0)
		cout << "Not found" << endl;
	cout << "return value: " << retval2 << endl;
	*/
	
	/*
	// 11. Testing Sort (turn on Insert): Working
	WordList neverwhere(5);
	neverwhere.insert("Richard");
	neverwhere.insert("Door");
	neverwhere.insert("Carabas");
	neverwhere.insert("Islington");
	neverwhere.insert("Abbot");
	neverwhere.sort(true);
	neverwhere.print(); // prints "Abbot Carabas Door Islington Richard\n"
	*/

	/*
	// 11. Testing Prepend (turn on Insert): Working
	WordList wordlist1(0);
	wordlist1.insert("mia");
	wordlist1.insert("susannah"); // num 2, max 2
	WordList wordlist2(4);
	wordlist2.insert("dean");
	wordlist2.insert("holmes");
	wordlist2.insert("odetta"); // num 3, max 4
	int retval = wordlist2.prepend(&wordlist1);
	wordlist2.print(); // print “susannah mia odetta holmes dean\n”
	// Assuming member variables are public
	cout << retval << " " << wordlist2.n_words << " " << wordlist2.capacity;
	//prints 2 5 5
	*/
	

	return 0;
}

#else

// Playing with memory tracer.  For this to work uncomment
// #include"debugmem.h" in wordlist.h to have the memory tracer included
// into the project.
//
// Assumes the Constructor, insert are correctly implemented.  Note if there is 
// undefined behavior in any of your code then all bets are off, your code 
// may "appear" correct, may crash, may generate nonesense, all are equally 
// incorrect.  
// 
#define MAKE_MEMBERS_PUBLIC
#include"debugmem.h"
#include"wordlist.h"

#include<iostream>
using std::cout;
using std::endl;
#include<assert.h>

int main() {

	WordList * existinglist = DEBUG_NEW WordList(5); // WordList can store 5 words

	//... Some WordList operations
	existinglist->insert("harry");
	existinglist->insert("ron");
	existinglist->insert("hermione");

	GETMEMORYREPORT();
	cout << "------------------------" << endl;
	if (true) {
		WordList newList(*existinglist); // Copy Constructor
		GETMEMORYREPORT();

	} // Should not result in memory leaks or undefined behavior 


	delete existinglist; 
	GETMEMORYREPORT();
	cout << "------------------------" << endl;
	return 0;
}

#endif