#include "stdafx.h"
#include <stdio.h>
#include <iostream>//read
#include <fstream>//write
#include <string>
#include <vector>

/*
	Alan Vuong
	Text Editor Program
	Created: December 20 2015
	Updated: December 30 2015
*/

//write or read to a text file that formated in a list format

//upcoming features: saving option, make code more structure like putting at the end of the main function

//main menu
void menuDisplay();
std::string pickingOptions(std::string *number, std::string name);
bool makeNewFile(bool isOpen);
bool findExistingFile(bool isOpen);
bool isAcceptableName(std::string fileName, std::string *number);
std::string choosingName(std::string input);
void isOpen(std::fstream& file);

//sub menu
void subMenuDisplay();
bool subMenu(std::string *number, std::fstream &file, std::string *fileNamePointer);
bool userAcceptChoice();
void readFile(std::fstream& file);
void addText(std::fstream& file);
void removeText(std::fstream& file, std::string fileName);
const std::vector<std::string> storeDesiredText(std::vector<std::string> desiredText, std::fstream &file);
void overrideTextFile(std::vector<std::string> desiredText, std::string fileName, std::fstream &file);
void renameFile(std::string fileName, std::fstream& file, std::string *fileNamePointer);
void deleteFile(std::string fileName, std::fstream &file);

//exit options
void displayQuittingText();
void confirmExit();

//display menu options
void menuDisplay()
{
	std::cout << "Enter the number option for the following options:\n" <<
		"1.New File\n" <<
		"2.Open File\n" <<
		"3.Exit Program\n";
}


//user type numbers to apply their option
std::string pickingOptions(std::string *number, std::string name)
{
	bool openingFile = true;

	//ends the loop if file is done trying to open the file
	while (openingFile)
	{
		getline(std::cin, *number);
		std::cout << "\n";

		if (*number == "1")
		{
			openingFile = makeNewFile(openingFile);
			name = choosingName(name);
		}
		else if (*number == "2")
		{
			openingFile = findExistingFile(openingFile);
			name = choosingName(name);
		}
		else if (*number == "3")
		{
			confirmExit();
		}
		else
		{
			std::cout << "Not a valid choice. I'm so so so sorry.\n";
		}
	}

	return name;
}

//first option of main menu
bool makeNewFile(bool isOpen)
{
	std::cout << "Creating...\n";
	isOpen = false;

	return isOpen;
}

//second option to main menu
bool findExistingFile(bool isOpen)
{
	std::cout << "Reopening...\n";
	isOpen = false;

	return isOpen;
}

//checks logic for creating a new or opening an existing file
bool isAcceptableName(std::string fileName, std::string *number)
{
	bool fileNotObtain = false;//a flag that ends while loop, when you successfully open or create a file

	std::ifstream inFile;
	inFile.open(fileName + ".txt");

	//you can't create a new file name that already exit
	if (!inFile.fail() && (*number == "1"))
	{
		std::cout << "The file existed already\n";
		fileNotObtain = true;
	}
	//you can't open an existing file name that doesn't exist
	else if (inFile.fail() && (*number == "2"))
	{
		std::cout << "The file doesn't exist\n";
		fileNotObtain = true;
	}

	return fileNotObtain;
}

//name the file
std::string choosingName(std::string input)
{
	std::cout << "Enter the name of the file\n";
	getline(std::cin, input);
	std::cout << "\n";

	return input;
}

//check if file is open
void isOpen(std::fstream& file)
{
	if (!file.is_open())
	{
		std::cout << "Error while opening the file\n";
	}
	else
	{
		std::cout << "File opened successfully\n";
		std::cout << "Writing to the file\n";
	}
}

//display menu affecting the picked file
void subMenuDisplay()
{
	std::cout << "Enter the number option for the following options:\n" <<
		"1.New File\n" <<
		"2.Open File\n" <<
		"3.Read File\n" <<
		"4.Add-User can add text to the file\n" <<
		"5.Remove-User can remove text of the file\n" <<
		"6.Rename\n" <<
		"7.Delete\n" <<
		"8.Exit\n";
}

//user can modify the file through the following options
bool subMenu(std::string *number, std::fstream &file, std::string name, std::string *fileNamePointer)
{
	bool fileNotChange = true;//decide whether to transition to main menu
	bool noChangeOnOption = true;//confirm user choice on sub menu

	//this confirms whether the user want to choose that number for the sub menu
	while (noChangeOnOption)
	{
		subMenuDisplay();
		getline(std::cin, *number);
		std::cout << "\n";

		noChangeOnOption = userAcceptChoice();
	}

	//returns to the main menu
	if (*number == "1")
	{
		fileNotChange = false;
	}
	//returns to the main menu
	else if (*number == "2")
	{
		fileNotChange = false;
	}
	//displays the text file in a list format
	else if (*number == "3")
	{
		readFile(file);
	}
	//adds a new text to the next line of the text file
	else if (*number == "4")
	{
		addText(file);
	}
	//deletes a targeted text and updates that information
	else if (*number == "5")
	{
		readFile(file);
		removeText(file, name);
		readFile(file);
	}
	//renames the file
	else if (*number == "6")
	{
		renameFile(name, file, fileNamePointer);
	}
	//return to back to main menu after deleting the file
	else if (*number == "7")
	{
		deleteFile(name, file);
		fileNotChange = false;

	}
	//quit the program
	else if (*number == "8")
	{
		confirmExit();
	}
	//any input besides these numbers doesn't work
	else
	{
		std::cout << "Invalid choice. Sorry. Seriously sorry.\n";
	}
	std::cout << "\n";

	return fileNotChange;//this affect whether to return back to the main menu
}

//give user a chance to confirm their sub menu choice
bool userAcceptChoice()
{
	std::string numberChoice;//user input a string
	bool denyChoice = true;//this method loops until the user accepts their sub menu option

	std::cout << "Are you sure about choosing that option?\n" <<
		"1.Yes\n" <<
		"2.No\n";
	getline(std::cin, numberChoice);
	
	if (numberChoice == "1")
	{
		denyChoice = false;
	}
	else if (numberChoice == "2")
	{
		;
	}
	else
	{
		std::cout << "I am trying my best, and I can't work with this data!\n";
	}
	std::cout << "\n";

	return denyChoice;
}

//allows user to read text file that list the text in a list
void readFile(std::fstream& file)
{
	file.seekg(0);
	std::cout << "Reading file\n" << "____________\n";
	std::string line;

	//files continues to list out each line until the end of the file
	while (file.good())
	{
		getline(file, line);
		std::cout << line << "\n";
	}

	file.clear();//require to read the file again
}

//add text at the end of the line of that selected file
void addText(std::fstream& file)
{
	std::string newText;//adds new text to the file

	readFile(file);//currently shows the orginal file

	std::cout << "\nEnter text to the text file\n";
	getline(std::cin, newText);
	std::cout << "\n";//prevents this prevents the new text from mashing older text in the same line
	file << newText + "\n";//adds new text to the file

	readFile(file);//the modified file with the new text
}

//removes text with user's string choice
void removeText(std::fstream& file, std::string fileName)
{
	std::vector<std::string> desiredText;//store text to keep in vector to override file
	
	file.seekg(0);
	desiredText = storeDesiredText(desiredText, file);
	overrideTextFile(desiredText, fileName, file);
}

//holds user desired text before overwritting the original file
const std::vector<std::string> storeDesiredText(std::vector<std::string> desiredText, std::fstream &file)
{
	std::string targetedText;//text the user wants to keep
	std::string excludeText;//the text the user wants to remove

	std::cout << "\nEnter text to remove from the text file\n";
	getline(std::cin, excludeText);
	std::cout << "\n";

	while (file.good())
	{
		getline(file, targetedText);
		//this stores each line into the vector except any matches with the targetedText
		if (excludeText != targetedText)
		{
			desiredText.push_back(targetedText + "\n");
		}
	}

	return desiredText;
}

//replace the original file with same file excluding the removed text
void overrideTextFile(std::vector<std::string> desiredText, std::string fileName, std::fstream &file)
{
	std::ofstream outFile;

	outFile.open(fileName + ".txt");
	//adds to the file with the vector carrying the desired text
	for (int j = 0; j < desiredText.size() - 1; ++j)//-1 prevents "\n" being added to vector
	{
		outFile << desiredText.at(j);
	}

	outFile.close();
	file.clear();//require to read the file again
}

void renameFile(std::string fileName, std::fstream &file, std::string *fileNamePointer)
{
	std::string fullFileName = fileName + ".txt";
	std::string newName;

	std::cout << "Enter the new name for your file:\n" << 
		"Current Name:" << fileName << "\n" <<
		"New Name:";

	getline(std::cin, newName);
	newName = newName + ".txt";

	file.close();//can't rename file being used without closing it

	if (rename(fullFileName.c_str(), newName.c_str()) == 0)
	{
		puts("File successfully renamed");
		*fileNamePointer = newName.substr(0, newName.length() - 4);//the last 4 element removes .txt
	}
	else
	{
		perror("Error renaming file");
	}

}

//user can delete the text there using at the moment
void deleteFile(std::string fileName, std::fstream &file)
{
	std::string fullFileName = fileName + ".txt";

	file.close();//can't delete file being used without closing it

	if (remove(fullFileName.c_str()) != 0)
	{
		perror("Error deleting file");
	}
	else
	{
		puts("File successfully deleted");
	}
}
//message to confirm user choice to exit program
void displayQuittingText()
{
	std::cout << "Exiting...\n";
	std::cout << "Are you want to exit?\n" <<
		"1.yes\n" <<
		"2.no\n";
}

//third choice to exit program in the main menu or final choice to exit in the sub menu
void confirmExit()
{
	std::string yesOrNo;//represent user choice to quit/not quit the program

	displayQuittingText();
	getline(std::cin, yesOrNo);
	std::cout << "\n";

	if (yesOrNo == "1")
	{
		exit(1);
	}
	else if (yesOrNo == "2")
	{
		;
	}

	menuDisplay();
}

int main()
{
	std::string *userNumber = new std::string;//present menu option
	std::string fileName;
	std::string *fileNamePointer = &fileName;

	bool fileNotAccepted = true;//check whether file exist or if already exist
	bool notChangingFile = true;//allows new file during the submenu selection
	
	while(notChangingFile)
	{
		while (fileNotAccepted)
		{
			menuDisplay();
			fileName = pickingOptions(userNumber, fileName);
			fileNotAccepted = isAcceptableName(fileName, userNumber);
		}

		std::fstream file(fileName + ".txt", std::ios::in | std::ios::out | std::ios::app);
		std::fstream &thisFile = file;

		while (notChangingFile)
		{
			std::cout << "File Name:" << fileName << "\n";
			notChangingFile = subMenu(userNumber, thisFile, fileName, fileNamePointer);
		}
		notChangingFile = true;
		fileNotAccepted = true;
	}

	std::cout << "Something went wrong. The program has an error.\n";

	system("pause");
    return 0;
}

