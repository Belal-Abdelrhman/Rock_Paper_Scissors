
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};


struct stGameResults
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;

	enWinner GameWinner;
	string WinnerName;
};

/*Random Number*/

short HowManyRounds()
{
	short Rounds = 1;
	do
	{
		cout << "How Many Rounds From 1 To 10 ? ";
		cin >> Rounds;

	} while (Rounds < 1 || Rounds > 10);
	return Rounds;
}

/*Get Computer Choice*/

enGameChoice ReadPlayerChoice()
{
	short Choice = 1;

	do
	{
		cout << "Your Choice:  [1]:Stone , [2]:Paper , [3]:Scissor ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice >3);

	return (enGameChoice)Choice;
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player;
}


enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{

	if (PlayerWinTimes < ComputerWinTimes)
	{
		return enWinner::Computer;
	}
	else if (PlayerWinTimes > ComputerWinTimes)
	{
		return enWinner::Player;
	}
	else
	{
		return enWinner::Draw;
	}

}

/*Choice Name*/

// mostafa taha WinnerName
string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player" , "Computer" , "No Winner" };
	return arrWinnerName[Winner - 1];
}


void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{

	case enWinner::Player:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	case enWinner::Draw:
		system("color 6F");
		break;

	}
}

string Tabs(short NumberOfTabs)
{
	string t = "";

	for (short i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n________________Round[" << RoundInfo.RoundNumber << "]________________\n" << endl;
	cout << "Player Choice     : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice   : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner      : " << RoundInfo.WinnerName << endl;
	cout << "\n_____________________________________________\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}


void ResetScreen()
{
	system("cls");
	system("color 0F");
}

stGameResults FillGameResults(short GameRound, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRound;
	GameResults.PlayerWinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}


void ShowGameOverScreen()
{
	cout << Tabs(2) << "-------------------------------------------\n" << endl;
	cout << Tabs(2) << "        ++++ G a m e O v e r ++++                \n" << endl;
	cout << Tabs(2) << "-------------------------------------------\n" << endl;

}

void ShowFinalGameResults(stGameResults GameResults)
{

	cout << Tabs(2) << "----------------[ Game Results ]------------------" << endl;
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player Win Times   : " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer Win Times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "---------------------------------------------------" << endl;

	SetWinnerScreenColor(GameResults.GameWinner);

}


stGameResults PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "\nRound [ " << GameRound << " ] begins : \n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);


		if (RoundInfo.Winner == enWinner::Player)
		{
			PlayerWinTimes++;
		}
		else if (RoundInfo.Winner == enWinner::Computer)
		{
			ComputerWinTimes++;
		}
		else
		{
			DrawTimes++;
		}

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRound, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}


void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults  GameResults = PlayGame(HowManyRounds());

		ShowGameOverScreen();
		ShowFinalGameResults(GameResults)
			;
		cout << endl << Tabs(3) << "Do you want play again ? (Y/N) :";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}


int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}