// Homework 4 for Data Structures
//
// Using doubly linked list. Creates one and then will go through checking for
//any data that is an even number and will delete it.
//
// Usage: Run from console with User Input
//
// Programmer: Ryan Shoemake
//
// 7/6/2018 - Start and Finish
// 
//
// Some changes from HomeWork2 are the addition of a doubly linked list instead
//and cleaned up useless comments and debugging statements. Plus a lot of commented code.
// 7/6/2018 - Changed curr variable in DeleteFunction to = Head->next. Caused rare crash before.
//
/////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

struct Node {
	int data;
	Node *next;
	Node *prev;
};

bool GetUserInput(int &Size);
void CreateFile(int Size);
int InsertNormal(Node *&);
void PrintReverse(Node *);
void DeleteEven(Node *);

string InFile = "Numbers.txt";


int main() {
	int Size;

	//Do a validity check to see if the program should continue. This is another layer of checking. The function
	// will check input as well.
	if (GetUserInput(Size)) {
		struct Node *Head = NULL;
		Head = new Node;
		Head->next = NULL;
		Head->prev = NULL;
		//This is the second function in the first part of the homework. 
		// It's a simplistic function to write "Size" number of random variables
		// to a file.
		CreateFile(Size);

		InsertNormal(Head);
		DeleteEven(Head);
		PrintReverse(Head);

	}
	else {
		cout << "Invalid Input. Get out." << endl;
	}
	system("pause");
	return 0;
}

bool GetUserInput(int &Size) {
	string denied;		// This is to catch ANY input the user gives
	bool done = false;

	while (!done) {
		//Prompt the user for input. Try to be as clear as possible....
		cout << "Please enter a size for the linked list.\nThe size must be an integer between 20 and 100.\n20 and 100 ARE valid choices.\n";
		cin >> denied;
		Size = atoi(denied.c_str());
		if (Size >= 20 && Size <= 100) {
			done = true;
			return true;
		}
		else {
			cout << "You tried to pass " << denied << " ?\nThat's just ridiculous..\n";
			done = false;
		}
	}
}

void CreateFile(int Size) {
	//Seeding the random to be able to create different random integers.
	srand(time(NULL));
	//Output file is called Numbers.txt as instructed.
	ofstream fout("Numbers.txt");

	//Randomly generate numbers to send to Numbers.txt. I usually randomize numbers around 1-100 for easy debugging
	for (int i = 0; i < Size; i++) {
		fout << rand() % 100 + 1 << endl;
	}
	fout.close();
}

int InsertNormal(Node *&Head) {
	//Opening up the input file and declaring a holder variable.
	ifstream fin(InFile.c_str());
	int x;

	//Create a while loop to grab the values from the InFile. This will continue to move and add
	// new nodes as long as we are pulling information from the file.
	Node *curr = Head;
	Node *prev;
	curr = Head;
	prev = curr;
	while (fin >> x) {
		curr->next = new Node;
		curr->next->prev = curr;
		curr = curr->next;
		curr->data = x;
		curr->next = NULL;
	}
	cout << endl;
	fin.close();
	return 0;
}

void PrintReverse(Node *Head) {
	Node *curr = Head;
	Node *q = curr;
	while (curr != NULL) {
		q = curr;
		curr = curr->next;
	}
	int counter = 1;
	while (q != NULL) {
		if(q->prev != NULL)
			cout << q->data << "\t";
		q = q->prev;
		counter++;
		if (counter % 5 == 0) {
			cout << endl;
			counter = 0;
		}
	}
	cout << endl;
}

void DeleteEven(Node *Head) {
	Node *curr;
	Node *temp;

	//CHANGED this to head->next because of rare error that would cause
	//the program to crash.
	curr = Head->next;
	
	while (curr->next != NULL) {
		if (curr->data % 2 == 0) {
			temp = curr;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			curr = temp->next;
			delete temp;
		}
		else
			curr = curr->next;
	}
	//curr->next is NULL but curr could be a value that needs to be deleted.
	if (curr->data % 2 == 0) {
		curr->prev->next = NULL;
		delete curr;
	}

}
