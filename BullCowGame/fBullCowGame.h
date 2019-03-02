#pragma once
#include <string>
#include <map>

// to make it unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

constexpr int32 MAX_TRIES = 10;

/* This represents the scoring system of the game, bulls
is the number of correct letters in the right place, while 
cows are the correct letters in the wrong place
*/
struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

/* Enum describing the status of a guess
*/
enum class EGuessStatus 
{
	INVALID,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE
};

/* Main game-logic class, containing the bulls and cows
game, and keeping the variables. No view code or direct
user interaction. The game is a simple guess the word
game based on mastermind.
*/
class FBullCowGame 
{
public:
	FBullCowGame();

	int32 getCurrentTry() const { return myCurrentTry; }
	int32 getHiddenWordLength() const { return myHiddenWord.length(); }
	FString getHiddenWord() const { return myHiddenWord; }
	int32 getMaxTries() const;
	bool isGameWon() const;

	void reset();
	EGuessStatus checkGuessValidity(FString guess);
	// Returns bulls and cows and increasing currentTries. Assumes valid guess
	FBullCowCount submitValidGuess(FString guess);

private:
	bool bCorrectWordGuessed;
	int32 myCurrentTry;
	FString myHiddenWord;

	bool isIsogram(FString word) const;
	bool isLowerCase(FString word) const;
};