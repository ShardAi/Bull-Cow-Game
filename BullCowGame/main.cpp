/* This is the console executable, that makes use of the BullCow class.
This acts as the view in MVC Pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "fBullCowGame.h"

// to make it unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as we're outside a class
void printIntro();
void playGame();
FText getValidGuess();
bool askToPlayAgain();
void printGameSummary();

// initiate new game used across all playthroughs
FBullCowGame BCGame;

int main()
{
	do
	{
		printIntro();
		playGame();
	} 
	while (askToPlayAgain());
	return 0; // Exit the application
}

// Plays a single game to completion
void playGame()
{
	BCGame.reset();
	// Loop for the number of turns we're asking for guesses.
	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= BCGame.getMaxTries())
	{
		FText guess = getValidGuess();

		FBullCowCount BullCowCount = BCGame.submitValidGuess(guess);

		std::cout << "Bulls = " << BullCowCount.bulls << ". Cows = " << BullCowCount.cows << "\n\n";
	}

	printGameSummary();
}

void printIntro()
{
	// Introduce the game
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {             ___ " << std::endl;
	std::cout << "          (o o)            (o o) " << std::endl;
	std::cout << "   /-------\\ /              \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O                O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |                  |------|  * " << std::endl;
	std::cout << "    ^      ^                  ^      ^ " << std::endl << std::endl;
	std::cout << "Can you guess the " << BCGame.getHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
	return;
}

FText getValidGuess()
{
	FText guess = "";
	EGuessStatus status = EGuessStatus::INVALID;
	// Get a guess from the player and return it.
	do
	{
		std::cout << "Enter your guess " << BCGame.getCurrentTry() << "/" << BCGame.getMaxTries() << ": ";
		std::getline(std::cin, guess);

		// Check status and give feedback
		status = BCGame.checkGuessValidity(guess);

		switch (status)
		{
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter an isogram (a word with no duplicate letters).\n\n";
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter a guess with only lowercase letters.\n\n";
			break;
		case EGuessStatus::OK:
		default:
			// assume guess is valid
			break;
		}
	} while (status != EGuessStatus::OK); // keep looping until we get no errors
	return guess;
}

bool askToPlayAgain()
{
	std::cout << "Would you like to play again? [y/n]:";
	FText response = "";
	std::getline(std::cin, response);
	std::cout << "\n\n";
	return (response[0] == 'y' || response[0] == 'Y');
}

void printGameSummary()
{
	if (BCGame.isGameWon())
		std::cout << "Congratulations, you guessed that the word is: \"" << BCGame.getHiddenWord() << "\" and won the game! \n";
	else
		std::cout << "The hidden word was \"" << BCGame.getHiddenWord() << "\". Better luck next time.";
}
