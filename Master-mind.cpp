
// HEADER FILES

#include	<iostream.h>
#include	<useful.h>
#include	<stdlib.h>

// GLOBAL FUNCTIONS

int			enter_int(char[]);		// Enter an integer

// GLOBAL VARIABLES

bool		err;			// Error Flag
char		ex;				// Variable for quit routine
int			levelA=0;		// Skill level A
int			levelB=0;		// Skill level B
int			seed=0;			// Seed for random functions
int			code[6];		// Select five random numbers
int			cc=0;			// Code Counter
int			gc=0;			// Guess Code Counter
int			guess[6][99];	// User's guesses (99 is the number of attempts)
int			black[99];		// Right code, right place
int			white[99];		// Right code, wrong place
bool		mark;			// Scoring flag				
int			go=0;			// Number of attempts
int			c=0;			// Counters for displaying results loop
int			w;				// This is a flag to ensure a white isn't scored twice

// MAIN FUNCTION

void main(void)
{
	do // Repeat program while the user wishes to use it 
	{

//  TITLE SCREEN

		clrscr();
		cout << "\n\t\t" << "\201\205\205\205\205\205\205\205\205\205\205\205\205\205\205"
				<< "\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205"
				<< "\205\205\205\205\205\205\205\205\205\205\205\205\205\205\187\n" <<
				"\t\t" <<	"\199 KCT - C++ Course                            \199\n" <<
				"\t\t" <<	"\204\205\205\205\205\205\205\205\205\205\205\205\205\205"
				<< "\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205"
				<< "\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205\185\n" <<
			    "\t\t" <<	"\199 File name    : Master-mind.cpp              \199\n" <<
			    "\t\t" <<	"\199 Project      : kct139                       \199\n" <<
				"\t\t" <<	"\199 Author       : Michael Gennery              \199\n" <<
				"\t\t" <<	"\199 Creation Date: 31-08-2001                   \199\n" <<
				"\t\t" <<	"\199 Ammend Date  : 14-09-2001                   \199\n" <<
				"\t\t" <<	"\199 Description  : Guess the random numbers     \199\n" <<				
				"\t\t" <<	"\200\205\205\205\205\205\205\205\205\205\205\205\205\205"
				<< "\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205"
				<< "\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205\205\188\n\n";

// MAIN PROGRAM
		
		cout	<< "Mastermind is a game of logical deduction where a user guesses the right"
				<< "\nsequence of up to five numbers.  One point in the black column is scored for a"
				<< "\nright number in the right place, and one point in the white column for a"
				<< "\nright number in the wrong place.\n\n";
		cout << "Enter 999 at anytime to exit.\n\n";
		
		do // Enter skill level A - The scope of each individual number
		{
			levelA=enter_int("Enter Skill level A (1-99).....: ");
			if (levelA==999) break; // Exit if the user enters 999
			if (((levelA<1) || (levelA>99)) && (levelA!=999)) cout << "\nInvalid range!\n";
		}while (((levelA<1) || (levelA>99)) && (levelA!=999));
		
		if (levelA==999) break; // Exit if the user enters 999
	
		do // Enter skill level B - The number of numbers the user will guess
		{
			levelB=enter_int("Enter Skill level B (1-5)......: ");
			if (levelB==999) break; // Exit if the user enters 999			
			if (((levelB<1) || (levelB>5)) && (levelB!=999)) cout << "\nInvalid range!\n";
		}while (((levelB<1) || (levelB>5)) && (levelB!=999));
		
		if (levelB==999) break; // Exit if the user enters 999

		seed=enter_int("\nEnter seed.....................: ");
		srand(seed);

		if (seed==999) break; // Exit if the user enters 999

		for (cc=1;cc<=levelB;cc++) 
		{
			code[cc]=rand()%levelA+1; // Select 5 random numbers
		}

		go=0;

		do // Keep asking the user until they get the right answer
		{
			go++;

			cout << "\nEnter 999 at anytime to exit.";
			
			cout << "\n\nEnter " << levelB << " numbers from 0 to " << levelA << ".\n\n";

			for (gc=1;gc<=levelB;gc++) // Obtain guess from user
			{	
				guess[gc][go]=0;
				do // keep asking the user until they enter a valid input
				{
					switch(gc)
					{
					case 1: guess[gc][go]=enter_int("Enter 1st number...............: ");break;				
					case 2: guess[gc][go]=enter_int("Enter 2nd number...............: ");break;				
					case 3: guess[gc][go]=enter_int("Enter 3rd number...............: ");break;				
					case 4: guess[gc][go]=enter_int("Enter 4th number...............: ");break;				
					case 5: guess[gc][go]=enter_int("Enter 5th number...............: ");break;
					}
					if ( ((guess[gc][go]<0) || (guess[gc][go]>levelA)) && (guess[gc][go]!=999))
					{
						cout << "You must enter a number between 0 and " << levelA << "!\n";
					}
				}while ( ((guess[gc][go]<0) || (guess[gc][go]>levelA)) && (guess[gc][go]!=999));

				if (guess[gc][go]==999) break; // Exit if the user enters 999
			}

			if (guess[gc][go]==999) break; // Exit if the user enters 999
			
			black[go]=0; // Reset scores to zero
			white[go]=0;

			if (guess[1][go]==code[1]) black[go]++;					// Mark the right answers
			if ((guess[2][go]==code[2]) && (levelB>1)) black[go]++;	// in the right place		
			if ((guess[3][go]==code[3]) && (levelB>2)) black[go]++;			
			if ((guess[4][go]==code[4]) && (levelB>3)) black[go]++;			
			if ((guess[5][go]==code[5]) && (levelB>4)) black[go]++;			
			
			w=0;
			mark=false;
			for (gc=1;gc<=levelB;gc++) // Mark the right answers, wrong place
			{
				for (cc=1;cc<=levelB;cc++)
				{
					if (guess[gc][go]==code[cc])
					{
						if ((gc!=cc) && (guess[gc][go]!=code[gc]))		// Right number, 
																		// wrong place and isn't 
																		// already a black
						{
							if (guess[cc][go]!=code[cc])					// This is to ensure
																			// the number hasn't already
																			// been scored as a black
							{
								if ((guess[gc][go]!=w) || (w=0))				// This routine is to
								{												// to ensure that
									w=guess[gc][go];							// a white
									white[go]++;								// is not scored again
									mark=true;									// if it has already appeared
								}
							}
						}
					}
					if (mark==true) break;	// This is to prevent 
											// number being scored twice						
				}
				mark=false; // Reset mark flag
			}

			// Print previous attempts and results

			clrscr();

			cout	<< "\nMASTER-MIND - LEVEL " << levelA << "/" << levelB
					<< "\n\nATTEMPT\t\t1st No.\t";
			if (levelB>1) cout << "2nd No.\t";
			if (levelB>2) cout << "3rd No.\t";
			if (levelB>3) cout << "4th No.\t";
			if (levelB>4) cout << "5th No.\t";
			cout << "\tBlack\tWhite";
			cout	<< "\n_____________________________________________________________________________\n\n";
			
			/*cout	<< "Correct\t" << "\t" << code[1] << "\t"
					<< code[2] << "\t" << code[3] << "\t" << code[4] << "\t" << code[5] << endl;*/

			for (c=1;c<=go;c++) // Print all attempts
			{
					cout << c << "\t\t" << guess[1][c] << "\t";
					if (levelB>1) cout << guess[2][c] << "\t";
					if (levelB>2) cout << guess[3][c] << "\t";
					if (levelB>3) cout << guess[4][c] << "\t";
					if (levelB>4) cout << guess[5][c] << "\t";
					cout << "\t" << black[c] << "\t" << white[c] << endl;
			}
				
			if (black[go]==levelB) 
				MessageBox(NULL,"\nCONGRATULATIONS! You've got them all right.","Master-mind",MB_OK);

		}while (black[go]<levelB);
				
		do // Ask user if they would like another go
		{	
			cout << "\nWould you like another go? (Y/N): ";			
			cin >> ex;
			ex=toupper(ex);
			err=false;
			if (ex!='Y' && ex!='N') 
			{
				cout << "\nInvalid option!";
				err=true;
			}			
			cin.clear();while(cin.get()!='\n');	// Clear the input
		}while (err==true);		// Ask again if they 
							// entered an invalid character

	}while (ex!='N'); // Repeat program if user eneterd Y	

}

// FUNCTION Enter an integer

int enter_int(char Q[])
{
	int X; // Value to be returned

	cout << Q; // Q is the question you want to ask
	while(!(cin>>X))
	{
		cin.clear();
		while(cin.get()!='\n');
		cout << "Invalid entry!\n" << Q;
	}

	return X; // Return entered value
}