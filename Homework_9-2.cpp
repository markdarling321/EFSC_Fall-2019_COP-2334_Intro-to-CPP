// COURSE:      COP 2334 - Intro to C++ Programming
// ASSIGNMENT:  Homework 9-2
// DATE:        10-17-2019
// NAME:        Mark Darling

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// STRUCTURE DEFINITION
struct studentType
{
    string studentFName;
    string studentLName;
    int testScore;
    char grade;
};

// FUNCTION PROTOTYPES
void getData(ifstream& inFile, studentType sList[], int CLASS_SIZE);
void calculateGrade(studentType sList[], int CLASS_SIZE);
int highestScore(const studentType sList[], int CLASS_SIZE);
void printResult(ofstream& outFile, const studentType sList[], int CLASS_SIZE);

// BEGIN MAIN PROGRAM
int main()
{
    // DECLARE VARIABLES
    const int CLASS_SIZE = 20;
    const string inFileName = "Ch9_Ex2Data.txt";
    const string outFileName = "Ch9_Ex2Out.txt";
    ifstream inFile;
    ofstream outFile;
    studentType sList[CLASS_SIZE];    // CREATE STRUCTURED ARRAY
    
    // OPEN FILES FOR READING & WRITING
    inFile.open(inFileName);
    outFile.open(outFileName);
    
    // READ STUDENT NAMES & TEST SCORES
    getData(inFile, sList, CLASS_SIZE); // READ FILE DATA
    calculateGrade(sList, CLASS_SIZE);  // CALCULATE LETTER GRADES
    
    // OUTPUT STUDENT NAMES & TEST SCORES SORTED BY GRADE
    printResult(outFile, sList, CLASS_SIZE);

    // CLOSE FILES BEFORE ENDING PROGRAM
    inFile.close();
    outFile.close();
    
    // END OF MAIN PROGRAM
    return 0;
}

void getData(ifstream& inFile, studentType sList[], int CLASS_SIZE)
{
    for (int i = 0; i < CLASS_SIZE; i++)
    {
        //cin.get(inFile, sList.studentFName[i]);
        //inFile.get(sList.studentFName[i]);
        inFile>>sList[i].studentFName;
        
        //cin.get(inFile, sList.studentLName[i]);
        //inFile.get(sList.studentLName[i]);
        inFile>>sList[i].studentLName;
        
        //cin.get(inFile, sList.testScore[i]);
        //inFile.get(sList.testScore[i]);
        inFile>>sList[i].testScore;
        
        //sList.grade[i] = calculateGrade(sList[], CLASS_SIZE);
    }
}

void calculateGrade(studentType sList[], int CLASS_SIZE)
{
    for (int i = 0; i < CLASS_SIZE; i++)
    {
        if (sList[i].testScore >= 90)
            sList[i].grade = 'A';
        else if (sList[i].testScore >= 80)
            sList[i].grade = 'B';
        else if (sList[i].testScore >= 70)
            sList[i].grade = 'C';
        else if (sList[i].testScore >= 60)
            sList[i].grade = 'D';
        else
            sList[i].grade = 'F';
    }
}

int highestScore(const studentType sList[], int CLASS_SIZE)
{
    int highestScore = 0;
    
    for (int i = 0; i < CLASS_SIZE; i++)
    {
        if (sList[i].testScore > highestScore)
            highestScore = sList[i].testScore;
    }
    
    return highestScore;
}

void printResult(ofstream& outFile, const studentType sList[], int CLASS_SIZE)
{
    // CREATE A TEMPORARY STRUCT TO COPY ORIGINAL STRUCT TO
    studentType tempList[CLASS_SIZE];
    
    for (int i = 0; i < CLASS_SIZE; i++)
    {
        tempList[i].studentFName =  sList[i].studentFName;
        tempList[i].studentLName =  sList[i].studentLName;
        tempList[i].testScore =  sList[i].testScore;
        tempList[i].grade =  sList[i].grade;
        //cout<<tempList[i].studentFName<<endl<<tempList[i].studentLName<<endl<<tempList[i].testScore<<endl<<tempList[i].grade<<endl<<endl;
    }
    
    // SORT THE STRUCT BY GRADE
    //int i = 0;
    //while (i < (CLASS_SIZE-1) )
    for (int i = 0; i < (CLASS_SIZE-1); i++) // CHECK TWO ELEMENTS AT A TIME AND DETERMINE WHICH SCORE IS HIGHER
    {       //   LOWER SCORE      <      HIGHER SCORE
        if (tempList[i].testScore < tempList[i+1].testScore)
        {
            string tempFName = tempList[i].studentFName;
            string tempLName = tempList[i].studentLName;
            int tempScore = tempList[i].testScore;
            char tempGrade = tempList[i].grade;
            
            tempList[i].studentFName = tempList[i+1].studentFName;
            tempList[i].studentLName = tempList[i+1].studentLName;
            tempList[i].testScore = tempList[i+1].testScore;
            tempList[i].grade = tempList[i+1].grade;
            
            tempList[i+1].studentFName = tempFName;
            tempList[i+1].studentLName = tempLName;
            tempList[i+1].testScore = tempScore;
            tempList[i+1].grade = tempGrade;
            
            i = 0;                                               // RESET AND START FROM BEGINNING AGAIN
        }
        //i++;
    }
    
    for (int i = 0; i < (CLASS_SIZE-1); i++) // CHECK TWO ELEMENTS AT A TIME AND DETERMINE WHICH LName IS FIRST ALPHABETICALLY
    {
        string tempLName0 = tempList[i].studentLName;
        string tempLName1 = tempList[i+1].studentLName;
        int lenLName0 = tempLName0.length();
        int lenLName1 = tempLName1.length();
        
        int j = 0;
        while((j < lenLName0) && (j < lenLName1))
        {
            if (tempList[i].studentLName[j] > tempList[i+1].studentLName[j])
            {
                string tempFName = tempList[i].studentFName;
                string tempLName = tempList[i].studentLName;
                int tempScore = tempList[i].testScore;
                char tempGrade = tempList[i].grade;

                tempList[i].studentFName = tempList[i+1].studentFName;
                tempList[i].studentLName = tempList[i+1].studentLName;
                tempList[i].testScore = tempList[i+1].testScore;
                tempList[i].grade = tempList[i+1].grade;

                tempList[i+1].studentFName = tempFName;
                tempList[i+1].studentLName = tempLName;
                tempList[i+1].testScore = tempScore;
                tempList[i+1].grade = tempGrade;

                i = 0;                                               // RESET AND START FROM BEGINNING AGAIN
            }
            j++;
        }
    }
    
    
    int possibleGrades = 5;
    bool finishedSorting = false;
    while (!finishedSorting)
    {
        for (int i = 0; i < CLASS_SIZE; i++)
        {
            if (possibleGrades == 5 && tempList[i].grade == 'A')        // 1st PASS
            {
                outFile<<tempList[i].studentLName<<", "<<tempList[i].studentFName<<" "<<tempList[i].testScore<<" "<<tempList[i].grade<<endl;
            }
            else if (possibleGrades == 4 && tempList[i].grade == 'B')    // 2nd PASS
            {
                outFile<<tempList[i].studentLName<<", "<<tempList[i].studentFName<<" "<<tempList[i].testScore<<" "<<tempList[i].grade<<endl;
            }
            else if (possibleGrades == 3 && tempList[i].grade == 'C')    // 3rd PASS
            {
                outFile<<tempList[i].studentLName<<", "<<tempList[i].studentFName<<" "<<tempList[i].testScore<<" "<<tempList[i].grade<<endl;
            }
            else if (possibleGrades == 2 && tempList[i].grade == 'D')    // 4th PASS
            {
                outFile<<tempList[i].studentLName<<", "<<tempList[i].studentFName<<" "<<tempList[i].testScore<<" "<<tempList[i].grade<<endl;
            }
            else if (possibleGrades == 1 && tempList[i].grade == 'F')    // 5th PASS
            {
                outFile<<tempList[i].studentLName<<", "<<tempList[i].studentFName<<" "<<tempList[i].testScore<<" "<<tempList[i].grade<<endl;
            }
        }
        possibleGrades--;
        if (possibleGrades == 0)
            finishedSorting = true;
    }
}
