
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void gameFunction(char *wordinFunction, char *userWordinFunction, int letterNumber);   //Function for checking the letter, incrementing counters etc.
void printUserWord(char * userWordinPrint,int letterNumber);			       //Function for printing the hanmgan figure
void printFigure(int failinFigure);						       //Function for printing the array of user

int main(void)
{
	FILE *fpointer;     //First, program reads from file
	fpointer = fopen("hangmanwords.txt", "r");

	if(fpointer== NULL)
	{
		printf("hangmanwords.txt couldn't found");
		return 0;
	}
	char readFromFile[300];

	while(!feof(fpointer))
	{
		fgets(readFromFile, 300, fpointer);
	}

	fclose(fpointer);

	srand(time(NULL));  //Seeding for random choices

	int restartGame= 1; //At the end, that variable's value can change so the game terminates
	while(restartGame==1)
	{
		int gameType;   //Program asks user to letter size
		printf(">->o-]   WELCOME TO HANGMAN!\n\nChoose a game\n1. Six Letters Game\n2. Seven Letters Game\n3. Random Game\n");
		scanf("%d", &gameType);

		while(gameType != 1 && gameType != 2 && gameType !=3)
		{
			system("cls");
			printf(">->o-]   WELCOME TO HANGMAN!\n\nChoose a game\n1. Six Letters Game\n2. Seven Letters Game\n3. Random Game\n");
			scanf("%d", &gameType);
		}

		system("cls");

		if(gameType == 3)
		{
			gameType = rand() % 2 + 1;
		}

		int categoryType; //Program asks user to category type
		printf("\n\nChoose a category\n1. Fruits and Vegetables\n2. Sports\n3. Technological Devices\n4. Countries\n5. Random Category\n");

		scanf("%d", &categoryType);

		while(categoryType != 1 && categoryType != 2 && categoryType != 3 && categoryType != 4 && categoryType != 5)
		{
			system("cls");
			printf("\n\nChoose a category\n1. Fruits and Vegetables\n2. Sports\n3. Technological Devices\n4. Countries\n5. Random Category\n");
			scanf("%d", &categoryType);
		}

		if(categoryType== 5)
		{
			categoryType= rand() % 4 + 1;
		}

		char askedWord[8];									//Array for holding the word
		char userWord[8]= {'_','_','_','_','_','_','_'};    //Array for user's true letters

		int randomer = rand()% 5;                           //Program writes appropriate random word to askedWord array from readed file

		if(categoryType == 1)      //Category for Fruits and Vegetables
		{
			if(gameType== 1)
			{
				for(int i= 0; i< 7; i++)
				{
					askedWord[i]= readFromFile[(35* 0)+ (randomer * 7)+ i];
				}

			}

			else
			{
				for(int i= 0; i< 7; i++)
				{
					askedWord[i]= readFromFile[(35* 1)+ (randomer * 7)+ i];
				}

			}
		}

		else if(categoryType == 2) //Category for Sports
		{
			if(gameType==1)
			{
				for(int i= 0; i< 7; i++)
				{
					askedWord[i]= readFromFile[(35* 2)+ (randomer * 7)+ i];
				}

			}

			else
			{
				for(int i= 0; i< 7; i++)
				{
					askedWord[i]= readFromFile[(35* 3)+ (randomer * 7)+ i];
				}

			}
		}

		else if(categoryType == 3) //Category for Technological Devices
		{
			if(gameType==1)
			{
				for(int i= 0; i< 7; i++)
				{
					askedWord[i]= readFromFile[(35* 4)+ (randomer * 7)+ i];
				}

			}

			else
			{
				for(int i= 0; i< 7; i++)
				{
					askedWord[i]= readFromFile[(35* 5)+ (randomer * 7)+ i];
				}

			}
		}

		else			        //Category for Countries
		{
			if(gameType==1)
			{
				for(int i= 0; i< 7; i++)
				{
					askedWord[i]= readFromFile[(35* 6)+ (randomer * 7)+ i];
				}

			}

			else
			{
				for(int i= 0; i< 7; i++)
				{
					askedWord[i]= readFromFile[(35* 7)+ (randomer * 7)+ i];
				}

			}
		}

		gameFunction(askedWord, userWord, (gameType+ 5));    //Program goes to gameFunction with neccessary arrays and lettter size

		printf("\n\nEnter 1 to restart game\nEnter any other number to exit\n");    //At the end of the game program asks user to replay or not
		scanf(" %d", &restartGame);
		system("cls");
	}
}

void gameFunction(char *wordinFunction, char *userWordinFunction, int letterNumber)      //Function for checking the letter, incrementing counters etc.
{
	int totalTrue= 0;			//Total number of true entered letters -if equals to letterNumber game is over-
	int totalFail= 0;			//Total number of fails -must be less than 9 or game is over-
	char scannedChar;

	while(totalFail< 9)
	{
		printFigure(totalFail);		//Program goes function to print the corresponding figure to fail
		printf("\n\n\n");
		printUserWord(userWordinFunction, letterNumber);     //Program goes function to print the user's array
		printf("\nEnter a character: ");
		scanf(" %c", &scannedChar);
		scannedChar= toupper(scannedChar);

		int letterAlreadyUsed= 1;			//Program checks whether the inputted letter is already found or not
		while(letterAlreadyUsed== 1)
		{
			for(int i=  0; i< letterNumber; i++)
			{
				if(userWordinFunction[i]!= scannedChar)
				{
					letterAlreadyUsed= 0;
				}

				else
				{
					letterAlreadyUsed= 1;
					printFigure(totalFail);
					printf("\n\n\n");
					printUserWord(userWordinFunction, letterNumber);
					printf("\nLetter already found!\nEnter a new character: ");
					scanf(" %c", &scannedChar);
					scannedChar= toupper(scannedChar);
					break;
				}
			}

		}

		int letterTrueCheck= 0;                        //This part checks every valid letter in order to understand...
		for(int i= 0; i< letterNumber; i++)			   //... it is a part of askedWord or not with counters
		{
			if(scannedChar== wordinFunction[i])		   //This part means that user entered a correct character
			{
				userWordinFunction[i]= wordinFunction[i];
				letterTrueCheck++;
				totalTrue++;
			}
		}

		if(letterTrueCheck== 0)						//This part means that user entered a wrong character
		{
			totalFail++;
		}

		if(totalTrue== letterNumber)                //This if statement works if you win the game and returns to main
		{
			printFigure(totalFail);
			printf("\n\n\n");
			printUserWord(userWordinFunction, letterNumber);
			printf("\n\nYOU WON!");
			return;
		}
	}

	printFigure(totalFail);	                         //This part works if you loose the game and returns to main
	printf("\n\n\n");
	for(int i= 0; i< letterNumber; i++)
	{
		printf("%c ", wordinFunction[i]);
	}
	printf("\n\nYOU LOST!");
	return;

}

void printUserWord(char *userWordinPrint,int letterNumber)    //This function basicly prints the array of user
{
	for(int i= 0; i< letterNumber; i++)
	{
		printf("%c ", userWordinPrint[i]);
	}
}

void printFigure(int failinFigure)    //This function clears the screen and prints the corresponding fail figure
{
	system("cls");

	switch(failinFigure)
	{
		case 0:
			printf("\n\n\n\n\n        \n        \n        \n     __|__");
			break;
		case 1:
			printf("\n\n\n\n\n       |\n       |\n       |\n     __|__");
			break;
		case 2:
			printf("  _ _ _\n       |\n       |\n       |\n       |\n       |\n       |\n       |\n     __|__ ");
			break;
		case 3:
			printf("  _ _ _  \n |     | \n |     | \n       |\n       |\n       |\n       |\n       |\n     __|__ ");
			break;
		case 4:
			printf("  _ _ _  \n |     | \n |     | \n( )    |\n       |\n       |\n       |\n       |\n     __|__ ");
			break;
		case 5:
			printf("  _ _ _  \n |     | \n |     | \n( )    |\n/      |\n       |\n       |\n       |\n     __|__ ");
			break;
		case 6:
			printf("  _ _ _  \n |     | \n |     | \n( )    |\n/ \\    |\n       |\n       |\n       |\n     __|__ ");
			break;
		case 7:
			printf("  _ _ _  \n |     | \n |     | \n( )    |\n/|\\    |\n |     |\n |     |\n       |\n     __|__ ");
			break;
		case 8:
			printf("  _ _ _  \n |     | \n |     | \n( )    |\n/|\\    |\n |     |\n |     |\n/      |\n     __|__ ");
			break;
		case 9:
			printf("  _ _ _  \n |     | \n |     | \n( )    |\n/|\\    |\n |     |\n |     |\n/ \\    |\n     __|__ ");
			break;
	}

	return;

}
