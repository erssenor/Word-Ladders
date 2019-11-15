//
//Ethan Senor
//
//Project 3
//
//main.cc
#include <iostream>
#include <queue.h>
#include <list.h>
#include <fstream>
#include <string>
using namespace std;

struct Word {
	int ptr = -1;
	string word;
	LinearList<int> list;
};

void readWords(Word dict[]);
int sequentialSearch(string start, Word dict[]);
void Hamming(Word dict[]);
int HammingDist(string word1, string word2);
void genLadder(int w1, int w2, Word dict[]);
void findIndex(int &i, Word dict[]);


int main()
{
	//intput words
	string start, endword;
	int w1, w2;

	Word dict[5757];

	readWords(dict);

	//intput words
	cin >> start;
	cin >> endword;

	//search for the words in the list.
	//if not output and end program.
	int position = sequentialSearch(start, dict);
	
	if(position == -1) {
		cout << "first word not in list" << endl;
		return 0;
	}
	else {

		w1 = position;
	}
	
	position = sequentialSearch(endword, dict);

	if(position == -1) {
		cout << "second word not in list" << endl;
		return 0;
	}
	else {

		w2 = position;
	}
	//determine hamming distance with pairs of words
	Hamming(dict);

	genLadder(w1, w2, dict);

	return 0;
}





void readWords(Word dict[]) {

	ifstream textfile ("sgb-words.txt");
	if(textfile.is_open()) {
		for(int i = 0; i < 5757; i++) {
			textfile >> dict[i].word;
			dict[i].ptr = -1;
		}
	textfile.close();
	}
	else
		cout << "File does not open" << endl;
	
}



void Hamming(Word dict[]) {
	for(int i = 0; i < 5757; i++) {
		int position = 0;
		for(int j = 0; j < 5757; j++) {
			if(dict[i].word != dict[j].word && HammingDist(dict[i].word, dict[j].word) == 1) {
				dict[i].list.insert(position, j);
				position++;
			}
		}
	}
}

int HammingDist(string word1, string word2) {
	int count = 0;
	for(int i = 0; i < 5; i++) {
		if(word1[i] != word2[i])
			count++;
	}
	return count;
}




int sequentialSearch(string word, Word dict[]) {
	string key = word;

	for(int i = 0; i < 5757; i++) {
		if(dict[i].word == key) 			
			return i;
	}
	return -1;	
}




void genLadder(int w1, int w2, Word dict[]) {
	LinearList<int> S;
	S.clear();


	Queue<int> Q;

	Q.enqueue(w2);

	int w;
	

	while(!Q.isEmpty()) {
		w = Q.dequeue(); 
		
		for(int i = 0; i < dict[w].list.size(); i++) { 

			int v = dict[w].list[i];

			if(dict[v].ptr == -1 && dict[v].word != dict[w2].word) {
				dict[v].ptr = w;
				Q.enqueue(v);			
			}
		}		 
	}
	
	
	if(dict[w1].ptr != -1) {
		S.insert(0, w1);
		w = dict[w1].ptr;
		
		int i = 1;
		while (w != -1) {
			
			S.insert(i, w);
			w = dict[w].ptr;
			i++;
		}
	}

		
	if(S.isEmpty())
		cout << "No word ladder exists";
	else {
		for(int i = 0; i < S.size(); i++) {
			findIndex(S[i], dict);
		}
	}				
}


void findIndex(int &i, Word dict[]) {
	cout << dict[i].word << endl;
}









