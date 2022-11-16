//tbd: Move this out of MnjGraph module 
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <sstream> 
#include <string>

using namespace std;

int findMissingNumber1(const string& numString, int maxNum, const char delim) {
	//Algo: if s1 = sum of all number upto maxNum 
	//   s2 = sum of all given numbers 
	// then missingNumber = s1 -s2 


	// // initialize return value to sum of all #s, 
	// we will deprecate it down to missing number 
	// Note: this assumes only one number is missing
	int missingNum = 0;

	for (int i = 1; i <= maxNum; i++) {
		missingNum += i;
	}

	istringstream iss(numString);
	string num = "";

	while (getline(iss, num, delim)) {

		try { // boost lexical cast could be nice here, but goin' old school
			missingNum -= atoi(num.c_str());

		}
		catch (const exception& e) {
			// silently skipping non-numerics, 
			// would want to ask client how to handle
			// e.g. log it, re-throw, etc. 
			std::cout << e.what() << std::endl;
		}

	};

	return missingNum;

}

int TestFindMissingNumber1()
{
	cout << "Hello World" << endl;
	cout << findMissingNumber1(string("2,3"), 3, ',') << endl;
	cout << findMissingNumber1(string("1,3"), 3, ',') << endl;
	cout << findMissingNumber1(string("1,2"), 3, ',') << endl;

	assert(1 == findMissingNumber1(string("2,3"), 3, ','));
	assert(2 == findMissingNumber1(string("1,3"), 3, ','));
	assert(3 == findMissingNumber1(string("1,2"), 3, ','));

	return 0;
}

