#include <iostream>
#include <fstream>
#include "smartarray.h"
#include "smartmatrix.h"
#include "fraction.h"
#include "mixednumber.h"

using namespace std;

enum action {ONE_PARAMETER, HELP_MENU, THREE_PARAMETER,
             FOUR_PARAMETER, FIVE_PARAMETER, ACTION_ERROR};

action checkCommandLine(int argc, char *argv[], string &inputFile, string &inputFileTwo,
                        string &outputFile, string &operation);

void helpMenu();
void actionError();

int main(int argc, char *argv[]) {

    ofstream fout;
    ifstream fin;
    string inputFile, inputFileTwo, outputFile, operation;
    try {

        smartMatrix tempOne;
        smartMatrix tempTwo;
        smartMatrix finalOut;
        action op = checkCommandLine(argc, argv, inputFile, inputFileTwo, outputFile, operation);

        if(op == HELP_MENU)
            helpMenu();
        else if(op == ACTION_ERROR)
            actionError();
        // One parameter -----------------------------------------------------------------------
        else if(op == ONE_PARAMETER) {
            bool inputFileExists;

            size_t findDot = inputFile.find('.');
            if(findDot != string::npos &&  findDot != inputFile.length()-4) {
                cout << "Bad file name." << endl;
                exit(1);
            }
            if(findDot != string::npos && inputFile.substr(inputFile.length()-4) != "mat") {
                cout << "Only .mat extension supported." << endl;
                exit(1);
            }
            if(findDot == string::npos) {
                inputFile += ".mat";
            }

            // Check if file exists
            fin.open(inputFile.c_str());
            inputFileExists = fin.good();

            if(!inputFileExists) {
                cin >> finalOut;
                fout.open(inputFile.c_str());
                fout << finalOut;
                fout.close();
            }
            else {
                fin >> finalOut;
                cout << finalOut;
            }
        }
        // Three parameter --------------------------------------------------------------------
        else if(op == THREE_PARAMETER || op == FOUR_PARAMETER || op == FIVE_PARAMETER) {
            bool inputFileExists;
            bool inputFileTwoExists;
            bool outputFileExists;

            // Edit file name by appending .mat
            size_t findDot = inputFile.find('.');
            if(findDot != string::npos &&  findDot != inputFile.length()-4) {
                cout << "Bad file name." << endl;
                exit(1);
            }
            if(findDot != string::npos && inputFile.substr(inputFile.length()-4) != "mat") {
                cout << "Only .mat extension supported." << endl;
                exit(1);
            }
            if(findDot == string::npos) {
                inputFile += ".mat";
            }

            // Edit file name two by appending .mat
            size_t findDotTwo = inputFileTwo.find('.');
            if(findDot != string::npos &&  findDot != inputFileTwo.length()-4) {
                cout << "Bad file name." << endl;
                exit(1);
            }
            if(findDot != string::npos && inputFileTwo.substr(inputFileTwo.length()-4) != "mat") {
                cout << "Only .mat extension supported." << endl;
                exit(1);
            }
            if(findDot == string::npos) {
                inputFileTwo += ".mat";
            }

            // Check if file exists
            fin.open(inputFile.c_str());
            inputFileExists = fin.good();

            if(!inputFileExists) {
                cout << "Input file one does not exist." << endl;
                exit(1);
            }
            else {
                fin >> tempOne;
            }
            fin.close();

            // Check if file exists
            fin.open(inputFileTwo.c_str());
            inputFileTwoExists = fin.good();

            if(!inputFileTwoExists) {
                cout << "Input file two does not exist." << endl;
                exit(1);
            }
            else {
                fin >> tempTwo;
            }
            fin.close();

            if(operation == "multiply" )
                finalOut = tempOne * tempTwo;
            else if(operation == "add")
                finalOut = tempOne + tempTwo;
            else
                cout << "Unknown error." << endl;

            if(op == THREE_PARAMETER) {
                cout << finalOut << endl;
            }
            else if(op == FOUR_PARAMETER || op == FIVE_PARAMETER) {

                // Edit output file name by appending .mat
                size_t findDotThree = outputFile.find('.');
                if(findDotThree != string::npos &&  findDotThree != outputFile.length()-4) {
                    cout << "Bad output file name." << endl;
                    exit(1);
                }
                if(findDotThree != string::npos && inputFile.substr(outputFile.length()-4) != "mat") {
                    cout << "Only .mat extension supported." << endl;
                    exit(1);
                }
                if(findDotThree == string::npos) {
                    outputFile += ".mat";
                }
                fin.open(outputFile.c_str());
                outputFileExists = fin.good();

                if(outputFileExists && op == FOUR_PARAMETER) {
                    cout << "Error: File already exists. Use '/f' to overwrite." << endl;
                    exit(0);
                }

                fout.open(outputFile.c_str());
                fout << finalOut;
                fout.close();

                cout << finalOut << endl;
            }
        }
        // Four parameter --------------------------------------------------------------------
    }
    catch (smartArrayErrors e) {
        if(e == OUT_OF_BOUNDS) {
            cout << "Out of Bounds." << endl;
        }
        if(e == BAD_ARRAY_SIZE) {
            cout << "Bad column value." << endl;
        }
    }
    catch (smartMatrixErrors e) {
        if(e == BAD_ROW_VALUE) {
            cout << "Bad row value." << endl;
        }
        if(e == BAD_COLUMN_VALUE) {
            cout << "Bad column value." << endl;
        }
        if(e == ADDITION_NOT_POSSIBLE) {
            cout << "Addition not possible." << endl;
        }
        if(e == MULTIPLICATION_NOT_POSSIBLE) {
            cout << "Multiplication not possible." << endl;
        }
    }
    catch (mixedNumberErrors e) {
        if(e == INPUT_TOO_LONG) {
            cout << "Input too long." << endl;
        }
        if(e == BAD_NUM_INPUT) {
            cout << "Numbers only. Use _ for whole numbers and / for fractions." << endl;
        }
    }

    catch(...) {
        cout << "Unknown error occurred." << endl;
    }


    return 0;
}


/// @brief Takes in the command line and returns the inputs
///
action checkCommandLine(int argc, char *argv[], string &inputFile,
                        string &inputFileTwo, string &outputFile, string &operation) {
    if(argc == 2) {
        inputFile = argv[1];
        if(inputFile == "/h" || inputFile == "/?")
            return HELP_MENU;
        return ONE_PARAMETER;
    }
    else if(argc == 4) {
        inputFile = argv[1];
        operation = argv[2];
        inputFileTwo = argv[3];

        if(operation != "multiply" && operation != "add") {
            return ACTION_ERROR;
        }
        return THREE_PARAMETER;
    }
    else if(argc == 5) {
        inputFile = argv[1];
        operation = argv[2];
        inputFileTwo = argv[3];
        outputFile = argv[4];
        if(operation != "multiply" && operation != "add") {
            return ACTION_ERROR;
        }
        return FOUR_PARAMETER;
    }
    else if(argc == 6) {
        string temp;
        inputFile = argv[1];
        operation = argv[2];
        inputFileTwo = argv[3];
        outputFile = argv[4];
        temp = argv[5];
        if(operation != "multiply" && operation != "add") {
            return ACTION_ERROR;
        }
        if(temp != "/f") {
            return ACTION_ERROR;
        }
        return FIVE_PARAMETER;
    }
    else {
        return ACTION_ERROR;
    }
}


/// @brief Prints out a help menu
///
void helpMenu() {
    cout << "This program allows matrixes to be added or multiplied with each other." << endl;
    cout << "Usage is: matrix <inputfilename> [<add/multiply> <inputfilename2>] [outputfilename] [/f]" << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << "<inputfilename> - Allows creation of matrix or edit current matrix file." << endl;
    cout << "[<add/multiply> <inputfilename2>] - Uses two existing matrix files and performs operation." << endl;
    cout << "[outputfilename] - Does matrix operation and outputs new file." << endl;
    cout << "[/f] - Use force to overwrite output matrix, even if the file already exists." << endl;
}

/// @brief Prints out correct argument usage
///
void actionError() {
    cout << "ERROR :: Correct usage is : matrix <input> [<'add'/'multiply'> <input2>] [output] [/f]" << endl;
}
