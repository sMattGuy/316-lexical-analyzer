#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class LexicalAnalyzer
{
  private:
	 string lexemes[45] = {"+","-","*","/","=","(",")",".",",",";",":",":=","<","<=","<>",">",">=","and","begin","boolean","div","do","downto","else","end","false","for","if","interger","mod","not","or","program","read","readln","real","repeat","then","to","true","until","var","while","write","writeln"};
    ifstream *sourceCodeFile;
	 bool validLexeme(string&, char, string[]);
	 bool checkLongLexeme(string&, string&);
	 TokenCodes tokenCodeSolver(string&, string[]);
	 bool checkNextCharacter(string&, string&, string[]);

  public:
    LexicalAnalyzer(ifstream*);
    Token* getNextToken();
};

#endif
