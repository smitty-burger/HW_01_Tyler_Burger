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
//
//Input:
//	Ordered_Deck.txt
//			
//Output:
//  Shuffled_Deck_(#).txt
//===========================================================================

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <cassert>
#include <random>

using namespace std;

//function prototypes
//void Ordered_Deck_Load();		//Load in a .txt file with a precompiled ordered list of cards.
int Welcome_Screen();			//Display a welcome screen on the console and prompt user for
								//the number of decks to be created and shuffled.
void Menu();					//Display main menu on welcome screen.
void line();					//Output separator line in console.
int Decks_to_be_Shuffled(int deck_num);	//Verify with the user on how many decks are to be shuffled.

//===========================================================================					MAIN

int main()
{
	//Menu selection variable
	int deck_num;

	//Display welcome screen and obtain number of decks to be shuffled
	deck_num = Welcome_Screen();
	
	//Confirm number of decks with user
	deck_num = Decks_to_be_Shuffled(deck_num);

    return 0;
}

//===========================================================================					Welcome_Screen

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

void Menu()
{
	//show menu options
	cout << "\n\n\t\t       Welcome to the Deck Shuffler\n\n\n"
		<< "\t\tHow many decks would you like to shuffle?\n\n\n\n\n\n";
	return;
}

//===========================================================================					Line

void line()
{
	//divider
	cout << "\n\n============================================================\n\n";
}

//===========================================================================					Decks_to_be_Shuffled

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