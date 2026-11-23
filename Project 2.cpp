#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "RandomNumber.h"
using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Subtract = 2, Multiply = 3, Divide = 4, MixOp = 5 };
struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	short CorrectAnswer = 0;
	short PlayerAnswer = 0;
	bool AnswerResult = false;
};
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberQuestion = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfRightQuestions = 0;
	short NumberOfWrongQuestions = 0;
	bool isPass = false;
};
short ReadNumberOfQuestions()
{
	short Num;
	do
	{
		cout << "How many Questions do you want to answer ? ";
		cin >> Num;

	} while (Num <= 0 || Num > 100);
	return Num;
}
int SimpleCalculator(short Num1, short Num2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Num1 + Num2;

	case enOperationType::Subtract:
		return Num1 - Num2;

	case enOperationType::Divide:
		return Num1 / Num2;

	case enOperationType::Multiply:
		return Num1 * Num2;
	
	default:
		return Num1 + Num2;
	}
}
enQuestionsLevel GetRandomQuestionLevel()
{
	return (enQuestionsLevel)RandomNumber(1, 3);
}
short GenerateNumberByLevel(enQuestionsLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case enQuestionsLevel::Easy:
		return RandomNumber(1, 10);

	case enQuestionsLevel::Med:
		return RandomNumber(10, 50);

	case enQuestionsLevel::Hard:
		return RandomNumber(50, 100);

	default:
		return RandomNumber(1, 10);
	}
}
enOperationType GetRandomOperationType()
{
	return (enOperationType)RandomNumber(1, 4);
}
enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "\nEnter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;
}
enOperationType ReadOperationType()
{
	short OpType = 0;
	do
	{
		cout << "\nEnter Operation Type [1] Add, [2] Subtract, [3] Multiply, [4] Division, [5] Mix ? ";
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);
	return (enOperationType)OpType;
}
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
	{
		QuestionLevel = GetRandomQuestionLevel();
	}
	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();
	}
	Question.OperationType = OpType;
	Question.QuestionLevel = QuestionLevel;
	Question.Number1 = GenerateNumberByLevel(QuestionLevel);
	Question.Number2 = GenerateNumberByLevel(QuestionLevel);
	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
	return Question;
}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short i = 0; i < Quizz.NumberQuestion; i++)
	{
		Quizz.QuestionList[i] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}
string GetOpTypeSymbol(enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return " + ";
	case enOperationType::Subtract:
		return " - ";
	case enOperationType::Multiply:
		return " * ";
	case enOperationType::Divide:
		return " / ";
	default :
		return " + ";
	}
}
void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberQuestion << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
	cout << "____________________\n";
}
short ReadQuestionAnswer()
{
	short Answer = 0;
	cin >> Answer;
	return Answer;
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongQuestions++;

		cout << "\nWrong Answer :-(\n";
		cout << "The right Answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
		system("color 4F");
		cout << "\a";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightQuestions++;
		cout << "\nRight Answer :-)\n";
		system("color 2F");
	}
	cout << endl;
}
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberQuestion; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.isPass = (Quizz.NumberOfRightQuestions >= Quizz.NumberOfWrongQuestions);
}
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}
string GetFinalResultsText(bool Pass)
{
	if (Pass)
	{
		return "PASS :-)";
	}
	else
	{
		return "Fail :-(";
	}
}
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "_________________________________\n\n";
	cout << " Final Results is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n_________________________________\n\n";

	cout << "Number of Question       : " << Quizz.NumberQuestion << endl;
	cout << "Questions Level          : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type           : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Correct Answer : " << Quizz.NumberOfRightQuestions << endl;
	cout << "Number of Wrong Answer   : " << Quizz.NumberOfWrongQuestions << endl;
	cout << "_________________________________\n";

	if (Quizz.isPass)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
	}
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberQuestion = ReadNumberOfQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "\nDo You Want To Play Again ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
