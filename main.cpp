#include <iostream>
#include <fstream>
#include "smartarray.h"
#include "smartmatrix.h"
#include "fraction.h"
#include "mixednumber.h"

using namespace std;

enum action {ONE_PARAMETER, HELP_MENU, THREE_PARAMETER,
             FOUR_PARAMETER, FIVE_PARAMETER, ACTION_ERROR};

/// PROTOTYPES
action checkCommandLine(int argc, char *argv[], string &inputFile, string &inputFileTwo,
                        string &outputFile, string &operation);

void oneParameter(ifstream &fin, ofstream &fout, string inputFile, smartMatrix &finalOut);

void mathParameter(ifstream &fin, ofstream &fout, string &outputFile,
                   const smartMatrix &finalOut, action op);

void editMatrix(ofstream &fout, const string &fileName, smartMatrix &finalOut);

void checkExtension(string &fileName);

bool checkFileExist(ifstream &fin, const string &fileName,
                    const string &errorMessage, bool end = true);

void retriveFromFile(ifstream &fin, const string &inputFile, smartMatrix &matrix);

void outputToFile(ofstream &fout, const string &fileName, const smartMatrix &matrix);

void performOperation(const string &operation, const smartMatrix &tempOne,
                      const smartMatrix &tempTwo, smartMatrix &finalOut);

void helpMenu();

void actionError();

/////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {

    ofstream fout;
    ifstream fin;
    string inputFile, inputFileTwo, outputFile, operation;
    try {

        smartMatrix tempOne;
        smartMatrix tempTwo;
        smartMatrix finalOut;
        action op;

        op = checkCommandLine(argc, argv, inputFile, inputFileTwo, outputFile, operation);

        if(op == HELP_MENU)
            helpMenu();
        else if(op == ACTION_ERROR)
            actionError();
        // One parameter ----------------------------------------------------------------------
        else if(op == ONE_PARAMETER)
            oneParameter(fin, fout, inputFile, finalOut);
        // Three parameter --------------------------------------------------------------------
        else if(op == THREE_PARAMETER || op == FOUR_PARAMETER || op == FIVE_PARAMETER) {

            // Edit file name by appending .mat
            checkExtension(inputFile);

            // Edit file name two by appending .mat
            checkExtension(inputFileTwo);

            // Check if file one exists
            checkFileExist(fin, inputFile, "Input file one does not exist.\n");
            retriveFromFile(fin, inputFile, tempOne);

            // Check if file two exists
            checkFileExist(fin, inputFileTwo, "Input file two does not exist.\n");
            retriveFromFile(fin, inputFileTwo, tempTwo);

            // Performs mathmatical function
            performOperation(operation, tempOne, tempTwo, finalOut);

            // Simply prints out the result of the operation ----------------------------------
            if(op == THREE_PARAMETER)
                cout << finalOut;

            // Outputs to a new file if more than three parameters ----------------------------
            else {
                mathParameter(fin, fout, outputFile, finalOut, op);
            }
        }
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
            cout << "Input too long. Limit is 10 characters." << endl;
        }
        if(e == HAS_ALPHABET) {
            cout << "Numbers only. Use x_x/x for whole numbers and x/x for fractions." << endl;
        }
        if(e == IMPROPER_SYMBOL_USE) {
            cout << "Improper symbol use. Use x_x/x for whole numbers and x/x for fractions." << endl;
        }
    }
    catch(...) {
        cout << "Unknown error occurred." << endl;
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////


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
/////////////////////////////////////////////////////////////////////////////////

/// @brief Performs the creation / editing of matrix
void oneParameter(ifstream &fin, ofstream &fout, string inputFile, smartMatrix &finalOut) {
    bool inputFileExists;

    // Appends .mat to filename if not there
    checkExtension(inputFile);

    // Check if file exists
    inputFileExists = checkFileExist(fin, inputFile, "", false);

    // Create new matrix, or allow user to edit
    if(!inputFileExists) {
        cin >> finalOut;
        outputToFile(fout, inputFile, finalOut);
    }
    else {
        retriveFromFile(fin, inputFile, finalOut);
        cout << finalOut;
        editMatrix(fout, inputFile, finalOut);
    }
}
/////////////////////////////////////////////////////////////////////////////////


/// @brief Deals with parameters that use math and file outputs
void mathParameter(ifstream &fin, ofstream &fout, string &outputFile,
                   const smartMatrix &finalOut, action op) {

    bool newFile = false;
    bool firstTime = true; // Checks if first iteration through loop for cin clear

    // Keeps in the loop if file name already exists
    while(!newFile) {

    // Edit output file name by appending .mat
        checkExtension(outputFile);

        bool outputFileExists = checkFileExist(fin, outputFile, "", false);

        newFile = true;

        if(outputFileExists && op == FOUR_PARAMETER) {

            newFile = false;
            cout << "Output file already exists. " << endl;
            cout << "Do you want to (O)verwrite or (E)dit the output file name? :: ";

            string userInput;
            char userChar;
            if(!firstTime) {
                cin.ignore(1000, '\n');
            }
            getline(cin, userInput);
            userChar = userInput[0];
            if(toupper(userChar) == 'E') {
                cout << "Enter a new output file name :: ";
                cin >> outputFile;
            }
            // Ends program if input not 'O', otherwise continues to writing
            else if(toupper(userChar) != 'O') {
                exit(0);
            }
            else {
                newFile = true;
            }
            firstTime = false;
        }
    }
    outputToFile(fout, outputFile, finalOut);
    cout << finalOut;
    cout << "Successfully saved to " << outputFile << '.' << endl;
}
/////////////////////////////////////////////////////////////////////////////////


/// @brief Allows the user to edit certain cells in the matrix
///
void editMatrix(ofstream &fout, const string &fileName, smartMatrix &finalOut) {

    string userInput;
    char userChar;
    cout << "(E)dit array, (D)elete, or (Q)uit? :: ";
    getline(cin, userInput);
    userChar = userInput[0];
    if(toupper(userChar) == 'E') {

        int userRow;
        int userCol;
        uint editCount = 0;
        char userContinue = 'Y';

        stringstream convert;

        while(toupper(userContinue) == 'Y') {
            cout << "Which row to edit? :: ";
            if(editCount != 0)
                cin.ignore();
            getline(cin, userInput);
            for(uint i = 0; i < userInput.length(); ++i) {
                if(!isdigit(userInput[i])) {
                    cout << "Bad row input." << endl;
                    exit(1);
                }
            }
            convert.str(std::string());
            convert.clear();
            convert << userInput;
            convert >> userRow;

            cout << "Which column to edit? :: ";
            getline(cin, userInput);
            for(uint i = 0; i < userInput.length(); ++i) {
                if(!isdigit(userInput[i])) {
                    cout << "Bad column input." << endl;
                    exit(1);
                }
            }

            convert.str(std::string());
            convert.clear();
            convert << userInput;
            convert >> userCol;

            // Tries to copy mixedNumber to ensure error occurs before new value output
            mixedNumber testErrorMessage(finalOut[userRow-1][userCol-1]);

            cout << "Enter new value :: ";
            cin >> finalOut[userRow-1][userCol-1];
            outputToFile(fout, fileName, finalOut);
            ++editCount;

            cout << "Edit another cell? (Y/N) :: ";
            cin >> userContinue;
        }
        cout << "Successfully edited " << editCount << " cells." << endl;
    }
    else if(toupper(userChar) == 'D') {
        if (remove(fileName.c_str()) != 0)
              cout << "Failed to delete file." << endl;
        else
              cout << fileName <<" has been deleted." << endl;
    }
}
/////////////////////////////////////////////////////////////////////////////////


/// @brief Makes sure extension name is proper, or adds it for user if not present
///
void checkExtension(string &fileName) {
    size_t findDot = fileName.find('.');
    if(findDot != string::npos &&  findDot != fileName.length()-7) {
        cout << "Bad file name. Only .matrix extension supported." << endl;
        exit(1);
    }
    if(findDot != string::npos && fileName.substr(fileName.length()-7) != ".matrix") {
        cout << fileName.substr(fileName.length()-4) << endl;
        cout << "Only .matrix extension supported." << endl;
        exit(1);
    }
    if(findDot == string::npos) {
        fileName += ".matrix";
    }
}
/////////////////////////////////////////////////////////////////////////////////


/// @brief Checks if file already exists or not
/// @return true if file exists
///
bool checkFileExist(ifstream &fin, const string &fileName, const string &errorMessage, bool end) {
    fin.open(fileName.c_str());
    bool fileExists = fin.good();

    if(!fileExists) {
        cout << errorMessage;
        if(end)
            exit(1);
    }
    fin.close();
    return fileExists;
}
/////////////////////////////////////////////////////////////////////////////////


/// @brief Takes in three matrixes, performs the operation and puts in third
///
void performOperation(const string &operation, const smartMatrix &tempOne,
                      const smartMatrix &tempTwo, smartMatrix &finalOut) {
    if(operation == "multiply" )
        finalOut = tempOne * tempTwo;
    else if(operation == "add")
        finalOut = tempOne + tempTwo;
    else
        cout << "Unknown error." << endl;
}
/////////////////////////////////////////////////////////////////////////////////


/// @brief Opens a file and puts its contents into smartMatrix
///
void retriveFromFile(ifstream &fin, const string &inputFile, smartMatrix &matrix) {
    fin.open(inputFile.c_str());
    fin >> matrix;
    fin.close();
}
/////////////////////////////////////////////////////////////////////////////////


/// @brief Creates a new file with the matrix within
///
void outputToFile(ofstream &fout, const string &fileName, const smartMatrix &matrix) {
    fout.open(fileName.c_str());
    fout << matrix;
    fout.close();
}
/////////////////////////////////////////////////////////////////////////////////


/// @brief Prints out a help menu
///
void helpMenu() {
    cout << "This program allows matrixes to be added or multiplied with each other."              << endl << endl;
    cout << "Usage is: matrix <inputfilename> [<add/multiply> <inputfilename2>] [outputfilename] [/f]"     << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"    << endl;
    cout << "<inputfilename>                   -   Allows creation of matrix or edit current matrix file." << endl;
    cout << "                                          Note : Editing is one-indexed, not zero-indexed."   << endl;
    cout << "[<add/multiply> <inputfilename2>] -   Uses two existing matrix files and performs operation." << endl;
    cout << "                                          Note : No files will be overwritten in this."       << endl;
    cout << "[outputfilename]                  -   Does matrix operation and outputs new file."            << endl;
    cout << "[/f]                              -   Use force to overwrite output matrix if file exists.  " << endl;
    cout << "\nThere are three types of inputs the matrix can hold and calculate:" << endl;
    cout << "Fractions     - (int)/(int)        ex. 1/2"   << endl;
    cout << "Whole numbers - (int)_(int)/(int)  ex. 1_2/3" << endl;
    cout << "Floats        - (double)           ex. 1.23"  << endl;
}
/////////////////////////////////////////////////////////////////////////////////


/// @brief Prints out correct argument usage
///
void actionError() {
    cout << "ERROR :: Correct usage is : matrix <input> [<'add'/'multiply'> <input2>] [output] [/f]" << endl;
}
/////////////////////////////////////////////////////////////////////////////////
