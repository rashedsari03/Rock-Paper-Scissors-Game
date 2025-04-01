// This is my solution::

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

enum enWinner
{
    Player = 1,
    Computer = 2,
    Draw = 3
};

enum enChoices
{
    Stone = 1,
    Paper = 2,
    Scissor = 3
};

struct stRoundInfo
{
    short RoundNumber;
    enWinner Winner;
    enChoices PlayerCh;
    enChoices ComCh;
};

int RandomNumber(int From, int To)
{
    // Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

int ReadRoundsNumber()
{
    int Number = 1;
    do
    {
        cout << "How many rounds 1 to 10 ? " << endl;
        cin >> Number;
    } while (Number <= 0 || Number > 10);
    return Number;
}

string WinnerName(enWinner user)
{
    string Winner = "";
    switch (user)
    {
    case Player:
        Winner = "Player";
        break;
    case Computer:
        Winner = "Computer";
        break;
    case Draw:
        Winner = "No Winner";
        break;
    default:
        break;
    }
    return Winner;
}

string ChoiceName(enChoices ch)
{
    string Choice = "";
    switch (ch)
    {
    case Stone:
        Choice = "Stone";
        break;
    case Scissor:
        Choice = "Scissor";
        break;
    case Paper:
        Choice = "Paper";
        break;
    default:
        break;
    }
    return Choice;
}

// enChoices ReturnChoice(enChoices choice)
//{
//     switch (choice)
//     {
//     case Stone:
//         return enChoices::Stone;
//     case Paper:
//         return enChoices::Paper;
//     case Scissor:
//         return enChoices::Scissor;
//     }
// }

enChoices PlayerChoice()
{
    short choice = -1;
    do
    {
        cout << "\nYour choice: [1]:Stone, [2]:Paper, [3]:Scissor ? ";
        cin >> choice;
    } while (choice > 3 || choice < 1);
    return enChoices(choice);
}

enChoices ComputerChoice()
{
    return enChoices(RandomNumber(1, 3));
}

enWinner WhoIsWin(enChoices playerCh, enChoices comCh)
{
    if (playerCh == comCh)
        return enWinner::Draw;

    if (enChoices::Paper == playerCh)
    {
        if (enChoices::Stone == comCh)
            return enWinner::Player;
        return enWinner::Computer;
    }

    if (enChoices::Scissor == playerCh)
    {
        if (enChoices::Paper == comCh)
            return enWinner::Player;
        return enWinner::Computer;
    }

    if (enChoices::Stone == playerCh)
    {
        if (enChoices::Scissor == comCh)
            return enWinner::Player;
        return enWinner::Computer;
    }
}

short NumberOfWins(stRoundInfo Round[], enWinner user, short NumberOfRounds)
{
    short count = 0;
    for (int i = 0; i <= NumberOfRounds; i++)
    {
        if (Round[i].Winner == user)
            count++;
    }
    return count;
}

void ChangeScreenColor(enWinner WhoIsWinner)
{
    switch (WhoIsWinner)
    {
    case Player:
        system("color 2F");
        break;
    case Computer:
        cout << "\a";
        system("color 4F");
        break;
    case Draw:
        system("color 6F");
        break;
    default:
        system("color 0F");
        break;
    }
}

void ShowRoundResults(stRoundInfo Round)
{
    ChangeScreenColor(Round.Winner);
    cout << "\n------------- Round [" << Round.RoundNumber << "]-------------" << endl;
    cout << "Player 1 Choice: " << ChoiceName(Round.PlayerCh) << endl;
    cout << "Computer Choice: " << ChoiceName(Round.ComCh) << endl;
    cout << "Round Winner   : [" << WinnerName(Round.Winner) << "]";
    cout << "\n------------------------------------" << endl;
}

enWinner FinalWinner(short p1Wins, short comWins, short draw)
{
    if (p1Wins >= comWins && p1Wins >= draw)
    {
        return enWinner::Player;
    }
    else if (comWins >= p1Wins && comWins >= draw)
    {
        return enWinner::Computer;
    }
    else
    {
        return enWinner::Draw;
    }
}

void ShowGameResults(stRoundInfo Round[], short NumberOfRounds)
{
    short player1Wins = NumberOfWins(Round, enWinner::Player, NumberOfRounds);
    short ComputerWins = NumberOfWins(Round, enWinner::Computer, NumberOfRounds);
    short DrawTimes = NumberOfWins(Round, enWinner::Draw, NumberOfRounds);

    cout << "\n\t\t-----------------------------------------------------";
    cout << "\n\t\t\t\t  +++  Game Over  +++";
    cout << "\n\t\t-----------------------------------------------------";
    cout << "\n\t\t--------------------[ Game Result ]--------------------" << endl;
    cout << "\t\t Game Rounds        : " << NumberOfRounds << endl;
    cout << "\t\t Player1 won times  : " << player1Wins << endl;
    cout << "\t\t Computer won times : " << ComputerWins << endl;
    cout << "\t\t Draw times         : " << DrawTimes << endl;
    cout << "\t\t Final Winner       : " << WinnerName(FinalWinner(player1Wins, ComputerWins, DrawTimes)) << endl;
}

void PlayGame(short NumberOfRounds)
{
    stRoundInfo roundInfo[10];
    enChoices PlayerCh;
    for (int i = 1; i <= NumberOfRounds; i++)
    {
        cout << "\n Round [" << i << "] begins:" << endl;
        ;
        roundInfo[i].PlayerCh = PlayerChoice();
        roundInfo[i].ComCh = ComputerChoice();
        roundInfo[i].RoundNumber = i;
        roundInfo[i].Winner = WhoIsWin(roundInfo[i].PlayerCh, roundInfo[i].ComCh);

        ShowRoundResults(roundInfo[i]);
    }
    ShowGameResults(roundInfo, NumberOfRounds);
}

void startGame()
{
    char PlayAgain = 'Y';
    do
    {
        system("color 0F");
        system("cls");
        PlayGame(ReadRoundsNumber());
        cout << "\n\t\tDo you want paly again? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    startGame();

    return 0;
}