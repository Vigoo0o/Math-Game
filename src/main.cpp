#include <iostream>
using namespace std;

// Data Member

enum enQuestionLevil 
{
    Easy = 1, 
    Medium = 2, 
    Hard = 3, 
    MixQuestion = 4
};

enum enOprationType 
{
    Addition = 1,
    Subtraction = 2,
    Multiplication = 4,
    Division = 3,
    MixOpration = 5
};

struct stFinalResult
{
    int NumberOfQuestion;
    enQuestionLevil QuestionLevel;
    enOprationType OprationType;
    int NumberOfRightAnswer;
    int NumberOFWrongAnswer;
};

// Function Member

string OprationToChar(int OprationType)
{
    string ArrOprations[] {"+", "-", "*", "/", "Mix"};
    return ArrOprations[OprationType - 1];
}

string NameOfQuestionsLevel(enQuestionLevil QuestionLevel)
{
    string ArrQuestionsLevel[] {"Easy", "Medium", "Hard", "Mix"};
    return ArrQuestionsLevel[QuestionLevel - 1];
}


void PrintFinallResult(stFinalResult FinalResult)
{
    cout << "Number Of Questions    : " << FinalResult.NumberOfQuestion << endl;
    cout << "Questions Level        : " << NameOfQuestionsLevel(FinalResult.QuestionLevel) << endl;
    cout << "Opration Type          : " << OprationToChar((int)FinalResult.OprationType) << endl;
    cout << "Number Of Right Answer : " << FinalResult.NumberOfRightAnswer << endl;
    cout << "Number Of Wrong Answer : " << FinalResult.NumberOFWrongAnswer << endl;
    cout << "\n\n______________________________\n\n";

}

void PrintHeadOfFinallResult(int NumberOfRightAnswer, int NumberOfWrongAnswer)
{
    string FinalReult = "";

    if(NumberOfRightAnswer < NumberOfWrongAnswer)
        FinalReult = "Fail";
    else
        FinalReult = "Pass";

    cout << "\n\n______________________________\n\n";
    cout << "Final Result Is " << FinalReult << endl;
    cout << "\n______________________________\n\n";
}

stFinalResult FillFinalResult(int NumberOfQuestion, enQuestionLevil QuestionLevil, enOprationType OprationType, int NumberOfRightAnswer, int NumberOfWrongAnswer)
{
    stFinalResult FinalResult;

    FinalResult.NumberOfQuestion = NumberOfQuestion;
    FinalResult.QuestionLevel = QuestionLevil;
    FinalResult.OprationType = OprationType;
    FinalResult.NumberOfRightAnswer = NumberOfRightAnswer;
    FinalResult.NumberOFWrongAnswer = NumberOfWrongAnswer;

    return FinalResult;
}

void PrintTrueOrFalse(bool TrueOfFalse)
{
    if(TrueOfFalse)
        cout << "Right Answer :-)\n";
    else
        cout << "Wrong Answer :-(\n";
}

bool IsAnswerTrue(int Number1, int Number2, enOprationType OprationType, int Answer)
{
    int RealAnswer = 0;

    if(OprationType == enOprationType::Addition)
        RealAnswer = Number1 + Number2;
    else if(OprationType == enOprationType::Subtraction)
        RealAnswer = Number1 - Number2;
    else if(OprationType == enOprationType::Multiplication)
        RealAnswer = Number1 * Number2;
    else if(OprationType == enOprationType::Division)
        RealAnswer = Number1 / Number2;

    return RealAnswer == Answer;
}

int ReadAnswar()
{
    int Answer = 0;

    cin >> Answer;

    return Answer;
}



int RandomNumber(int From, int To)
{
    int RandomNumber = rand() % (To - From + 1) + From;
    return RandomNumber;
}

void GenerateQuestion(enQuestionLevil QuestionLevel, enOprationType OprationType, int& RightAnswer, int& WrongAnswer)
{
    int QuestionLeveleNumber = (int)QuestionLevel;
    int OprationTypeNumber = (int)OprationType;
    int QuestionNumber1 = 0, QuestionNumber2 = 0;
    int Answer = 0;

    if(QuestionLevel == enQuestionLevil::MixQuestion)
    {
        QuestionLeveleNumber = RandomNumber(1, 4);
    }
    if(OprationType == enOprationType::MixOpration)
    {
        OprationTypeNumber = RandomNumber(1, 5);
    }

    if(QuestionLevel == enQuestionLevil::Easy)
    {
        QuestionNumber1 = RandomNumber(1, 10);
        QuestionNumber2 = RandomNumber(1, 10);
    }
    else if(QuestionLevel == enQuestionLevil::Medium)
    {
        QuestionNumber1 = RandomNumber(10, 20);
        QuestionNumber2 = RandomNumber(10, 20);
    }
    else if(QuestionLevel == enQuestionLevil::Hard)
    {
        QuestionNumber1 = RandomNumber(30, 40);
        QuestionNumber2 = RandomNumber(30, 40);
    }

    cout << QuestionNumber1 << endl;
    cout << QuestionNumber2 << OprationToChar(OprationTypeNumber) << endl;
    cout << "____________\n";
    Answer = ReadAnswar();
    bool RightOrWrong = IsAnswerTrue(QuestionNumber1, QuestionNumber2, OprationType, Answer);
    PrintTrueOrFalse(RightOrWrong);

    if(RightOrWrong)
        RightAnswer++;
    else
        WrongAnswer++;

}

enOprationType ReadOprationType()
{
    short OprationType = 0;

    do
    {
        cout << "Enter Opration Type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix: ";
        cin >> OprationType;
    } while (OprationType > 5 || OprationType < 1);

    return (enOprationType)OprationType;
}

enQuestionLevil ReanQuestionLevel()
{
    short QuestionLevel = 1;

    do
    {
        cout << "Enter Question Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix? ";
        cin >> QuestionLevel;
    } while (QuestionLevel > 5 || QuestionLevel < 1);
    
    return (enQuestionLevil)QuestionLevel;
}

int HowManyQuestion()
{
    int QuestionNumber = 0;

    do
    {
        cout << "How Many Questions Do You Want? ";
        cin >> QuestionNumber;
    } while (QuestionNumber <= 0);
    
    return QuestionNumber;
}

stFinalResult PlayGame(enOprationType OprationType, enQuestionLevil QuestionLevil, int HowManyQuestion)
{
    int NumberOfRightAnswer = 0, NumberOfWrongAnswer = 0;

    for(int QuestionNumber = 1; QuestionNumber <= HowManyQuestion; QuestionNumber++)
    {
        cout << "\n\nQuestion [" << QuestionNumber << "/" << HowManyQuestion << "]\n\n";
        GenerateQuestion(QuestionLevil, OprationType, NumberOfRightAnswer, NumberOfWrongAnswer);
    }
    return FillFinalResult(HowManyQuestion, QuestionLevil, OprationType, NumberOfRightAnswer, NumberOfWrongAnswer);
}

string Tabs(int NumberOfTaps)
{
    string T = "";

    for(int i = 0; i < NumberOfTaps; i++)
    {
        T += "\t";
    }

    return T;
}

void DifinitionGame()
{
    cout << Tabs(5) << "+++ Math Game +++\n";
}

void StartGame()
{
    char PlayAgein = 'n';

    do
    {
        DifinitionGame();
        stFinalResult FinalResult = PlayGame(ReadOprationType(), ReanQuestionLevel(), HowManyQuestion());
        PrintHeadOfFinallResult(FinalResult.NumberOfRightAnswer, FinalResult.NumberOFWrongAnswer);
        PrintFinallResult(FinalResult);
    } while (PlayAgein == 'Y' || PlayAgein == 'y');
    
}

int main()
{
    StartGame();
    return 0;
}