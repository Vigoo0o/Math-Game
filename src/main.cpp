#include <iostream>
using namespace std;

enum enQuestionLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };

enum enOprationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOprationType OprationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionLevel;
    enOprationType OprationType;
    short NumberOfRightAnswer;
    short NumberOfWrongAnswer;
    bool IsPass = false;
};

string GetOpTypeSymbol(enOprationType OprationType)
{
    string ArrOfOp[] { "+", "-", "*", "/", "Mix" };
    return ArrOfOp[OprationType - 1];
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string ArrOfQuestionLevelText[] { "Easy", "Mid", "Hard", "Mix" };
    return ArrOfQuestionLevelText[QuestionLevel - 1];
}

string GetFinalResultText(bool IsPass)
{
    return IsPass ? "Pass :-)" : "False :-(";
}

void PrintQuizzResult(stQuizz Quizz)
{
    cout << "\n";
    cout << "______________________________\n\n";
    cout << "Final Result Is " << GetFinalResultText(Quizz.IsPass);
    cout << "\n______________________________\n\n";

    cout << "Number Of Questions    : " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level        : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Opration Type          : " << GetOpTypeSymbol(Quizz.OprationType) << endl;
    cout << "Number Of Right Answer : " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number Of Wrong Answer : " << Quizz.NumberOfWrongAnswer << endl;
    cout << "______________________________\n";

}

void CorrectTheQuestionAnswer(stQuizz& Quizz, int QuestionNumber)
{
    if(Quizz.QuestionList[QuestionNumber - 1].PlayerAnswer == Quizz.QuestionList[QuestionNumber - 1].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber - 1].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;

        cout << "Right Answer :-)\n";
    }
    else
    {
        Quizz.QuestionList[QuestionNumber - 1].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;

        cout << "Wrong Answer :-(\n";
        cout << "The Right Answer Is: " << Quizz.QuestionList[QuestionNumber - 1].CorrectAnswer << endl;
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stQuizz Quizz, int QuestionNumber)
{
    cout << "Question [" << QuestionNumber << "/" << Quizz.NumberOfQuestions << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber - 1].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber - 1].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber - 1].OprationType);
    cout << "\n_________" << endl;
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
    for(int QuestionNumber = 1; QuestionNumber <= Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber - 1].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.IsPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}

int SimpleCalculator(int Number1, int Number2, enOprationType OprationType)
{
    switch (OprationType)
    {
    case enOprationType::Add:
        return Number1 + Number2;
    case enOprationType::Sub:
        return Number1 - Number2;
    case enOprationType::Mult:
        return Number1 * Number2;
    case enOprationType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

int RandomNumber(int From, int To)
{
    int RandomNumber = rand() % (To - From + 1) + From;
    return RandomNumber;
}

stQuestion GenarateQuestion(enQuestionLevel QuestionLevel, enOprationType OprationType) 
{
    stQuestion Question;

    if(QuestionLevel == enQuestionLevel::Mix)
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 4);

    if(OprationType == enOprationType::MixOp)
        OprationType = (enOprationType)RandomNumber(1, 4);

    Question.OprationType = OprationType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OprationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::Mid:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OprationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OprationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }

    return Question;
}

void GenarateQuizzQuestions(stQuizz& Quizz)
{
    for(int Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenarateQuestion(Quizz.QuestionLevel, Quizz.OprationType);
    }
}

enOprationType ReadOprationType()
{
    short OprationType = 0;

    do
    {
        cout << "Enter opration type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix: ";
        cin >> OprationType;
    } while (OprationType > 5 || OprationType < 1);

    return (enOprationType)OprationType;
}

enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel = 0;

    do
    {
        cout << "Enter question level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix? ";
        cin >> QuestionLevel;
    } while (QuestionLevel > 4 || QuestionLevel < 1);
    
    return (enQuestionLevel)QuestionLevel;
}

short HowManyQuestion()
{
    int NumberOfQuestions = 0;

    do
    {
        cout << "How many questions do you want from 1 to 10? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions > 10 || NumberOfQuestions < 1);
    
    return NumberOfQuestions;
}

void PlayGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = HowManyQuestion();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.OprationType = ReadOprationType();

    GenarateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswer(Quizz);
    PrintQuizzResult(Quizz);
}

void ResetScreen()
{
    system("clear");
}

void StartGame()
{
    char PlayAgein = 'N';

    do
    {
        ResetScreen();

        PlayGame();

        cout << "Do you want to play again? Y/N? ";
        cin >> PlayAgein;
    } while (PlayAgein == 'Y' || PlayAgein == 'y');
    
}

int main()
{
    StartGame();
    return 0;
}