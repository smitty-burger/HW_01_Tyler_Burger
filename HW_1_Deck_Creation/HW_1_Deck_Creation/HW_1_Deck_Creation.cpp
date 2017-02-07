//===========================================================================
//HW_1_Deck_Creation.cpp
//This program creates a user defined number of decks of cards. After the 
//decks have been created, the user will be prompted to choose if the decks
//should be shuffled. The order of the shuffled decks will then be saved
//as a .txt file.

//ME493 Card Shuffler
//History:	    Date		Resp. Eng.			Modification
//              _______		_________________	_____________
//				2/1/17		Tyler Burger		initial 
//				2/4/17		Tyler Burger		add deck creation 
//				2/5/17		Tyler Burger		create shuffling algorithm
//				2/6/17		Tyler Burger		add file output
//				2/6/17		Tyler BUrger		TestA and TestB added, function briefs added --STABLE
//
//Input:
//	N/A
//			
//Output:
//  Shuffled_Deck.txt		---->	Please edit file path in 'file_output' function before running
//
//===========================================================================

/*
DEBUG HELPER

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
int chkpnt = 0;
cout << "checkpoint " << chkpnt << endl;
chkpnt++;
//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
cout << "checkpoint " << chkpnt << endl;
chkpnt++;
//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

*/

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cassert>
#include <random>
#include <vector>

using namespace std;

//function prototypes
int Welcome_Screen();			//Display a welcome screen on the console and prompt user for
								//the number of decks to be created and shuffled.
void Menu();					//Display main menu on welcome screen.
void line();					//Output separator line in console.
int Decks_to_be_Shuffled(int deck_num);	//Verify with the user on how many decks are to be shuffled.
void Deck_Creator(int deck_num, vector<int> &d_num, vector<int> &d_suit);	//Create the two vectors that hold the data for the decks
void Deck_Shuffler(vector<int> &d_num, vector<int> &d_suit, vector<int> &nd_num, vector<int> &nd_suit);	//shuffle deck vectors and create two 
																										//new vectors that contain a shuffled deck
void file_output(int deck_num, vector<int> nd_num, vector<int> nd_suit);
void TestA(int deck_num, vector<int> nd_num, vector<int> nd_suit);	//When shuffling a single deck, no card is duplicated
void TestB(int deck_num, vector<int> nd_num, vector<int> nd_suit);	//When shuffling n decks together, the first card in the deck appears a
														//total of n times.

//===========================================================================					MAIN

int main()
{
	//Menu selection variable
	int deck_num;

	//Display welcome screen and obtain number of decks to be shuffled
	deck_num = Welcome_Screen();
	
	//Confirm number of decks with user
	deck_num = Decks_to_be_Shuffled(deck_num);

	//Create ordered deck(s)
	vector<int> d_num(deck_num * 52);	//Vector for card numbers
	vector<int> d_suit(deck_num * 52);	//Vector for card suits
	Deck_Creator(deck_num, d_num, d_suit);

	//Shuffle Deck(s)
	vector<int> nd_num;
	vector<int> nd_suit;
	Deck_Shuffler(d_num, d_suit, nd_num, nd_suit);

	//Write shuffled deck to file
	file_output(deck_num, nd_num, nd_suit);

	//Perform Test A
	TestA(deck_num, nd_num, nd_suit);

	//Perform Test B
	TestB(deck_num, nd_num, nd_suit);

    return 0;
}

//===========================================================================					Welcome_Screen
/*	||	Brief	||
Displays a screen to introduce the program to the user and to obtain and check
correct number of decks. Maximum number of decks allowed is 10.
*/
int Welcome_Screen()
{
	//choose menu choice
	int choice;
	Menu();
	cin >> choice;

	//check choice
	while (choice < 0 || choice > 10)
	{
		cout << "\t\t    ***" << choice << " is not a valid deck number***\n\n\n\n\n " <<
			"Please Pick a new number of decks\n\n\n\n\n\n" << endl;
		cin >> choice;
	}
	return choice;
}

//===========================================================================					Menu
/*	||	Brief	||
Displays a screen to introduce the program to the user.
*/
void Menu()
{
	//show menu options
	cout << "\n\n\t\t       Welcome to the Deck Shuffler\n\n\n"
		<< "\t\tHow many decks would you like to shuffle?\n\n\n\n\n\n";
	return;
}

//===========================================================================					Line
/*	||	Brief	||
Displays a line break of "="
*/
void line()
{
	//divider
	cout << "\n\n============================================================\n\n";
}

//===========================================================================					Decks_to_be_Shuffled
/*	||	Brief	||
Confirms with the user the number of decks to be shuffled. If the user chooses
to change the number they will be prompted to enter in a new numnber. This 
number of decks will then be chacked for validity. The maximum number of decks
allowed is 10.
*/
int Decks_to_be_Shuffled(int deck_num)
{
	char letter;
	int pass;
	pass = 0;

	//Confirm choice
	do
	{
		cout << "\t\tDo you wish to shuffle " << deck_num << " deck";
		if (deck_num <= 1)
		{
			cout << "?\t(Y/n)\n";
		}
		else
		{
			cout << "s?\t(Y/n)\n";
		}

		cin >> letter;
		switch (letter)
		{
			//Number of decks is good. Proceed to initializing decks
		case 'Y':
			pass = 1;
			break;
		case 'y':
			pass = 1;
			break;
			//Number of decks is NOT good. Get new number of decks
		case'N':
		case'n':
			cout << "\t\tHow many decks would you like to shuffle?\n\n";
			cin >> deck_num;
			//check choice
			while (deck_num < 0 || deck_num > 10)
			{
				cout << "\t\t    ***" << deck_num << " is not a valid deck number***\n\n" <<
					"Please Pick a new number of decks\n\n" << endl;
				cin >> deck_num;
			}
			break;
		}
	} while (pass == 0);
	return deck_num;
}

//===========================================================================					Deck_Creator
/*	||	Brief	||
Create an ordered deck conisting of the standard 52 card french deck.
*/
void Deck_Creator(int deck_num, vector<int> &d_num, vector<int> &d_suit)
{
	//Create Loop Variables
	int card_num = 0;
	int i;
	int j;
	int k;

	for (i = 0; i < deck_num; i++)
	{
		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 13; k++)
			{
				d_num[card_num] = k;
				d_suit[card_num] = j;
				card_num++;
			}
		}
	}
}

//===========================================================================					Deck_Shuffler
/*	||	Brief	||
Ordered deck is shuffled randomly to create a new order of the cards.
*/
void Deck_Shuffler(vector<int> &d_num, vector<int> &d_suit, vector<int> &nd_num, vector<int> &nd_suit)

{
	//Get System Time
	unsigned seed = time(0);
	//Seed Random Number Generator
	srand(seed);

	int len = d_num.size();
	int i = 0;
	int remove;

	do
	{
		//Use rand to get an element to place and remove
		remove = rand() % d_num.size();

		//set removal element to ith element in shuffled deck
		int temp = d_num[remove];
		nd_num.push_back(temp);
		temp = d_suit[remove];
		nd_suit.push_back(temp);

		//increment to next card
		i++;

		//erase the previously used card from the ordered deck
		d_num.erase(d_num.begin() + remove);
		d_suit.erase(d_suit.begin() + remove);

		//check to see if both vectors match in length
		assert(nd_num.size() == nd_suit.size());

		
	} while (i < len);

}

//===========================================================================					file_output
/*	||	Brief	||
Creates a file name and writes the shuffled deck to the file. The user will
be notified after the sve has been completed.
*/
void file_output(int deck_num, vector<int> nd_num, vector<int> nd_suit)
{
	//Create output file
	ofstream output_file;
	output_file.open("C:\\Users\\Tyler\\Desktop\\Shuffled_Deck.txt");							//file path for .txt shuffled deck output

	//User console update
	cout << "Now Writing Data To File\n\n\n" << endl;

	//Write to file
	output_file << "Card\tSuit" << endl;

	for (int card_num = 0; card_num < 52 * deck_num; card_num++)
	{
		output_file << nd_num[card_num] << '\t' << nd_suit[card_num] << endl;
	}

	//Close output file
	output_file.close();

	//User console update
	cout << "Data Has Been Written To File\n\n\n" << endl;
}

//===========================================================================					TestA
/*	||	Brief	||
Test the deck to make sure no card shows up more than it is supposed to.
*/
void TestA(int deck_num, vector<int> nd_num, vector<int> nd_suit)
{
	//Create Loop Variables
	int card_num = 0;
	int i = 0;
	int j;
	int k;

	for (j = 0; j < 4; j++)
	{
		for (k = 0; k < 13; k++)
		{
			i = 0;
			for (int card_num = 0; card_num < 52 * deck_num; card_num++)
			{
				if (k == nd_num[card_num] && j == nd_suit[card_num])
				{
					i++;
				}
			}
			assert(i == deck_num);
		}
	}
	cout << "\n\tTest A ---- Passed" << endl;
}

//===========================================================================					TestB
/*	||	Brief	||
Test the deck to ensure that every card shows up the appropriate number of
times. (For purposes of the assignment, TestB is a duplicate of TestA as they
both accomplish the same task with a single algorithm).
*/
void TestB(int deck_num, vector<int> nd_num, vector<int> nd_suit)
{
	//Create Loop Variables
	int card_num = 0;
	int i = 0;
	int j;
	int k;

	for (j = 0; j < 4; j++)
	{
		for (k = 0; k < 13; k++)
		{
			i = 0;
			for (int card_num = 0; card_num < 52 * deck_num; card_num++)
			{
				if (k == nd_num[card_num] && j == nd_suit[card_num])
				{
					i++;
				}
			}
			assert(i == deck_num);
		}
	}
	cout << "\n\tTest B ---- Passed" << endl;
}

//===========================================================================					COMMENTED
//===========================================================================					DEBUGGING HELP

/*//from main	
	//Test ordered deck compilation
	int card_num;
	cout << '\n';
	for (card_num = 0; card_num < 52*deck_num; card_num++)
	{
		cout << card_num << '\t' << d_num[card_num] << '\t' << d_suit[card_num] << endl;
	}
*/

/*//from main
	//Test shuffled deck compilation
	cout << '\n';
	for (card_num = 0; card_num < 52 * deck_num; card_num++)
	{
	cout << card_num << '\t' << nd_num[card_num] << '\t' << nd_suit[card_num] << endl;
	}
*/