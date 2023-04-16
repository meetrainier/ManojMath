// Returns length of shortest chain to reach 'target' from 'start'
// using minimum number of adjacent moves.  D is dictionary
// C++ program to find length of the shortest chain
// transformation from source to target
//#include<bits/stdc++.h>
#include "all_std.h" 
#include "GenericGraphHeader.h"

using namespace std;

// To check if strings differ by exactly one character
bool isadjacent(string& a, string& b)
{
	int count = 0;  // to store count of differences
	auto n = a.length();

	// Iterate through all characters and return false
	// if there are more than one mismatching characters
	for (int i = 0; i < n; i++)
	{
		if (a[i] != b[i]) 
			count++;
		if (count > 1)
			return false;
	}
	return count == 1 ? true : false;
}

// A queue item to store word and minimum chain length
// to reach the word.
struct QItem
{
	string word;
	int len;
};

int shortestChainLen1(string& start, string& target, set<string> &D)
{
	// Create a queue for BFS and insert 'start' as source vertex
	queue<QItem> Q;
	QItem item = { start, 1 };  // Chain length for start word is 1
	Q.push(item);

	// While queue is not empty
	while (!Q.empty())
	{
		// Take the front word
		QItem curr = Q.front();
		Q.pop();

		// Go through all words of dictionary
		for (auto it = D.begin(); it != D.end(); )
		{
			// Process a dictionary word if it is adjacent to current
			// word (or vertex) of BFS
			string temp = *it;
			if (isadjacent(curr.word, temp))
			{
				// Add the dictionary word to Q
				item.word = temp;
				//toon -> poon -> poin -> poie -> plie -> plee ->plea //for debugging 
				item.len = curr.len + 1;
				if (temp == target)
					return item.len;
				Q.push(item);

				// Remove from dictionary so that this word is not
				// processed again.  This is like marking visited
				it = D.erase(it);//mnj  added it= 

				// If we reached target
				
			}
			else { it++; }
		}
	}
	return 0;
}


int shortestChainLen(string& start, string& target, set<string> &D)
{
	// Create a queue for BFS and insert 'start' as source vertex
	queue<QItem> Q;
	QItem item = { start, 1 };  // Chain length for start word is 1
	Q.push(item);

	// While queue is not empty
	while (!Q.empty())
	{
		// Take the front word
		QItem curr = Q.front();
		Q.pop();

		// Go through all words of dictionary
		for (auto it = D.begin(); it != D.end(); it++)
		{
			// Process a dictionary word if it is adjacent to current
			// word (or vertex) of BFS
			string temp = *it;
			if (isadjacent(curr.word, temp))
			{
				// Add the dictionary word to Q
				item.word = temp;
				item.len = curr.len + 1;
				Q.push(item);

				// Remove from dictionary so that this word is not
				// processed again.  This is like marking visited
				D.erase(temp);
				
				// If we reached target
				if (temp == target)
					return item.len;
			}
		}
	}
	return 0;
}
void TestshortestChainLen2() {

	set<string> D;
	D.insert("toon");
	D.insert("poon");
	D.insert("plee");
	D.insert("same");
	D.insert("poie");
	D.insert("plie");
	D.insert("poin");
	D.insert("plea");

	D.insert("pine");
	D.insert("peas");
	D.insert("pale");

	// toon -> poon -> poin -> poie -> plie -> plee ->plea 
	string start = "toon";
	string target = "plea";
	int l = shortestChainLen1(start, target, D);
	cout << l << endl;
	assert(7 == l);

}

void TestshortestChainLen1(){
	
	set<string> D;
	D.insert("toon");
	D.insert("poon");
	D.insert("plee");
	D.insert("same");
	D.insert("poie");
	D.insert("plie");
	D.insert("poin");
	D.insert("plea");
	// toon -> poon -> poin -> poie -> plie -> plee ->plea 
	string start = "toon";
	string target = "plea";
	int l = shortestChainLen1(start, target, D); 
	cout << l << endl; 
	assert(7 == l);

}

void TestshortestChainLen() {
	TestshortestChainLen1(); 
	TestshortestChainLen2();
}