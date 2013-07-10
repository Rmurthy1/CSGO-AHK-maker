#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

// load input file and create output file
// input file is in plaintext format, no need to cut anything off

void outputWriter(string, fstream &, int);

int main()
{
		fstream inputFile;
		fstream outputFile;
		string input;
		int counter;
		counter = 0;
		while (true)
		{
			cout << "Enter your input file's name [ex: input.txt]: ";
			getline(cin, input);
			inputFile.open(input.c_str(), ios::in);
			if (inputFile.fail())
			{
				cout << "Invalid file!" << endl;
			}
			if (inputFile.good())
			{
				cout << "Processing file!" << endl;
				break;
			}
		}
		cout << "Writing output to file: \"AHKoutput.txt\"" << endl;
		outputFile.open("AHKoutput.txt", ios::out);
		// write header data
		outputFile << "#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases\n; #Warn  ; Enable warnings to assist with detecting common errors\nSendMode Input  ; Recommended for new scripts due to its superior speed and reliability\nSetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory\n; \nVar:= 0\n^F1::\n";
		

		while(true)
		{
			if(!inputFile.good())
			{
				break;
			}
			string fullLine;
			getline(inputFile, fullLine);
			if (fullLine.length() > 1)
			{
				outputWriter(fullLine, outputFile, counter);
				counter++;
			}
		}
		// write ending data
		outputFile << "else\n{\nVar:= -1\n}\nVar++\nSend {Enter}\nreturn" << endl;
		outputFile.close();
		return 0;
}

void outputWriter(string fullLine, fstream &outputFile, int counter)
{
	// change the fullLine to a fullLine inserted with `% for %
	
	
	for (int i = 0; i < fullLine.length(); i++)
	{
		if (fullLine.at(i) == '%' || fullLine.at(i) == '`')
		{
			fullLine.insert(i, 1, '`');
			i++;
		}
	}
	
	float totalLength;
	totalLength = fullLine.length();
	float totalLines;
	totalLines = totalLength / 127;
	totalLines = ceil(totalLines);
	int intTotalLines = totalLines;
	if (counter == 0)
	{
		outputFile << "if(Var = " << counter << ")" << endl;
	}
	else
	{
		outputFile << "else if(Var = " << counter << ")" << endl;
	}
	outputFile << "{" << endl;
	outputFile << "Send y" << endl;
	outputFile << "Sleep, 900" << endl;
	
	if (totalLines > 1)
	{
		string *temp = new string[intTotalLines];
		for (int i = 0; i < totalLines; i++)
		{
			temp[i].assign(fullLine, (i * 127), 127);
		}
		for (int i = 0; i < totalLines; i++)
		{
			outputFile << "Send " << temp[i] << endl;
			if (i == (totalLines - 1))
			{
				break;
			}
			outputFile << "Send {Enter}" << endl;
			outputFile << "Sleep, 900" << endl;
			outputFile << "Send y" << endl;
			outputFile << "Sleep, 900" << endl;
			cout << temp[i] << endl;
		}
		delete [] temp;
	}
	else
	{
		outputFile << "Send " << fullLine << endl;
	}
	outputFile << "}" << endl;
	
}