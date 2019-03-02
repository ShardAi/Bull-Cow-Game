#pragma once
#include "fBullCowGame.h"

FString wordList[] = { "broch", "edict", "stamp", "audio", "guilt", "shrub", "grave", "lumpy", "guile", "short", "radar", "glory",
	   "shape", "rider", "roman", "wisla", "stale", "stern", "jaunt", "perky", "regal", "ample", "softy", "grunt", "hogan", "flora", "whole",
	   "saint", "squat", "daisy", "poesy", "bogus", "qaint", "brunt", "shape", "yacht", "magic", "drunk", "weigh", "smith", "swear", "hiker",
	   "horse", "study" };

FBullCowGame::FBullCowGame()
{
	reset();
}

int32 FBullCowGame::getMaxTries() const 
{ 
	TMap<int32, int32> wordLengthToMaxTries = { {1, 3}, {2, 3}, {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return wordLengthToMaxTries[myHiddenWord.length()]; 
}

bool FBullCowGame::isGameWon() const
{
	return bCorrectWordGuessed;
}

void FBullCowGame::reset()
{
	myHiddenWord = wordList[rand() % 44 + 1]; // This must be an isogram
	myCurrentTry = 1;
	bCorrectWordGuessed = false;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString guess)
{
	if (!isIsogram(guess)) // if guess isn't an isogram
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!isLowerCase(guess))// if guess isn't all lowercase
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (guess.length() != getHiddenWordLength())// if guess is wrong length
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//Receives valid guess, increments number of tries and returns bulls and cows count
FBullCowCount FBullCowGame::submitValidGuess(FString guess)
{
	myCurrentTry++;
	FBullCowCount bullCowCount;

	// Iterate through guess and hidden word, and compare characters. If they're in the
	// right spot, increment bulls, if they're equal but in wrong spot, increment cows.
	for (int32 i = 0; i < myHiddenWord.length(); i++)
	{
		for (int32 j = 0; j < guess.length(); j++)
		{
			if (myHiddenWord[i] == guess[j])
			{
				if (i == j)
					bullCowCount.bulls++;
				else
					bullCowCount.cows++;
			}
		}
	}

	// If it is all bulls the game is won.
	if (bullCowCount.bulls == getHiddenWordLength())
		bCorrectWordGuessed = true;

	return bullCowCount;
}

bool FBullCowGame::isIsogram(FString word) const
{
	// 0 or 1 letter words is by definition isograms
	if (word.length() <= 1)
		return true;

	TMap<char, bool> letterSeen;

	for (char letter : word)
	{
		letter = tolower(letter);
		if (letterSeen[letter])
			return false;
		else
			letterSeen[letter] = true;
	}

	return true;
}

bool FBullCowGame::isLowerCase(FString word) const
{
	for (char letter : word)
	{
		if (!islower(letter))
			return false;
	}
	return true;
}