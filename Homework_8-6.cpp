// COURSE:      COP 2334 - Intro to C++ Programming
// ASSIGNMENT:  Homework 8-6
// DATE:        10-13-2019
// NAME:        Mark Darling

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

int main()
{
	// DEFINE VARIABLES
	char answerKey[20];
	char studentID[8];
	char studentAnswers[20];
	string temp;
	double studentScore;
	double studentPercentage;
	
	const int CORRECT = 2;
	const int INCORRECT = -1;
	const int NOANSWER = 0;
	const double FULLCREDIT = 40;
	
	// OPEN FILE FOR READING
	ifstream testResults;
	testResults.open("Ch8_Ex6Data.txt");
	
	// PROCESS THE ANSWER KEY
	// ON THE FIRST LINE OF FILE
	cout<<"Reading the answer key...\n";
	for (int i=0; i<20; i++)
	{
		// READ ANSWER KEY INTO ARRAY answerKey[i]
		testResults >> answerKey[i];
	}
/*
	// DEBUG:
	// MAKE SURE ANSWER KEY WAS PROCESSED CORRECTLY
	
	cout<<"Displaying the answer key...\n";
	for (int i=0; i<20; i++)
	{
		cout<<"answerKey["<<i<<"]: "<<answerKey[i]<<endl;
	}
*/
	
	// READ IN TEST RESULTS FROM FILE
	// ONE LINE AT A TIME AND PROCESS
	// EACH LINE AS WE GO THROUGH THE FILE
	cout<<"Processing test results...\n\n";

/*    
	// DEBUG:
	int counter = 0;
*/    
	// CONTINUE PROCESSING THE FILE WHILE WE
	// THERE ARE STILL LINES BEING READ IN
	while (getline(testResults, temp))
	{   
		studentScore = 0;
		
/*
		// DEBUG:
		counter++;
		cout<<"Counter is: "<<counter<<endl;
*/      
		
		// RESET studentAnswers[] ARRAY
		// BEFORE EACH LINE WE PROCESS
		for (int i=0; i<20; i++)
		{
			studentAnswers[i] = ' ';
		}
		
		// READ THE FIRST LINE OF
		// STUDENT RESULTS INTO A STRING
		getline(testResults, temp);
		
		// PROCESS STRING INTO MEANINGFUL RESULTS BY
		// EXAMINING EACH CHARACTER IN STRING ONE BY ONE
		for (int i=0; i<temp.length(); i++)
		{
			cout<<temp[i];    // DEBUG LINE
			
			// READ CHARACTERS 1 THRU 8 OF EACH LINE
			// INTO THE studentID[] VARIABLE
			if (i < 8)
			{
				studentID[i] = temp[i];
			}
			
			// SKIP CHARACTER 9 AND READ CHARACTERS 10-29
			// INTO OUR studentAnswers[] VARIABLE
			if (i >= 9)
			{
				 studentAnswers[(i-9)] = temp[i];
			}
		}
		cout<<endl;
		
		// PROCESS THE STUDENT'S SCORE
		for (int i=0; i<(strlen(studentAnswers)-2); i++)
		{   
			// ALLOCATE POINTS BASED ON STUDENT
			// ANSWER COMPARED TO ANSWER KEY
			if (studentAnswers[i] == answerKey[i])
				studentScore = studentScore + CORRECT;
			else if (studentAnswers[i] == ' ')
				studentScore = studentScore + NOANSWER;
			else if (studentAnswers[i] != answerKey[i])
				studentScore = studentScore + INCORRECT;
			
			// DEBUG BLOCK
			cout<<"studentAnswers["<<i<<"]: "<<studentAnswers[i]<<"    ";
			cout<<"answerKey["<<i<<"]: "<<answerKey[i]<<"    ";
			cout<<"studentScore: "<<studentScore<<"    ";
			cout<<"strlen(studentAnswers): "<<strlen(studentAnswers)<<endl;
		}
		//cout<<endl<<" "<<studentScore<<" ";	// DEBUG
		
		studentPercentage = ((studentScore/FULLCREDIT)*100);
		cout<<endl<<" "<<studentPercentage<<" ";
		if (studentPercentage >= 90)
			cout<<"A";
		else if (studentPercentage <= 89.99 && studentPercentage >= 80)
			cout<<"B";
		else if (studentPercentage <= 79.99 && studentPercentage >= 70)
			cout<<"C";
		else if (studentPercentage <= 69.99 && studentPercentage >= 60)
			cout<<"D";
		else if (studentPercentage <= 59.99 && studentPercentage >= 0)
			cout<<"F";
		
		cout<<endl<<endl;
	}
	
	// DEBUG:
	cout<<endl<<endl;
	for (int i=0; i<8; i++)
	{
		cout<<"studentID["<<i<<"]: "<<studentID[i]<<endl;
	}
	for (int i=0; i<20; i++)
	{
		cout<<"studentAnswers["<<i<<"]: "<<studentAnswers[i]<<"    ";
		cout<<"answerKey["<<i<<"]: "<<answerKey[i]<<endl;
	}
	
	// CLOSE FILE AND END PROGRAM
	testResults.close();
	return 0;
}
