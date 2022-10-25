#include <iostream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
  sourceCodeFile = scf;
}

Token* LexicalAnalyzer::getNextToken()
{
	Token *t;
	t = new Token();

	if(sourceCodeFile->eof()){
		t->setLexemeString("end of file");
		t->setTokenCode(TokenCodes::EOI);
		return t;
	}

	string newToken = "";
	char tokenPart = ' ';

	//cout<<"Showing token part outside loop: "<<tokenPart<<endl;
	while(!LexicalAnalyzer::validLexeme(newToken, tokenPart, LexicalAnalyzer::lexemes) && !sourceCodeFile->eof()){
		//cout<<"Showing token part: "<<tokenPart<<endl;
		sourceCodeFile->get(tokenPart);
		tokenPart = tolower(tokenPart);
		if(newToken.length() != 0 && tokenPart == ' '){
			//will have to process what it read
			//cout<<"Leaving loop due to space"<<endl;
			break;
		}
		while(tokenPart <= 32){
			sourceCodeFile->get(tokenPart);
			tokenPart = tolower(tokenPart);
		}
		newToken += tokenPart;
		//cout<<"Token so far: "<<newToken<<endl;
		char peekedToken = sourceCodeFile->peek();
		//cout<<"peeked token: "<<peekedToken<<endl;
		string nextCharacter(1, peekedToken);
		//cout<<"next character: "<<nextCharacter<<endl<<"~~~~~~~~"<<endl;
		/**
			check to see if next character is 
			if :
				:=
			if <
				<=, <>
			if >
				>=
		**/
		if(LexicalAnalyzer::checkLongLexeme(newToken, nextCharacter)){
			//lexeme falls into long category
			//cout<<"long lex found: "<<newToken<<" "<<nextCharacter<<endl;
			sourceCodeFile->get(tokenPart);
			tokenPart = tolower(tokenPart);
			newToken += tokenPart;
			break;
		}
		//cout<<"checking next lex which is: "<<nextCharacter<<endl;
		if(LexicalAnalyzer::checkNextCharacter(newToken, nextCharacter, LexicalAnalyzer::lexemes) || peekedToken <= 32){
			//next char is lexeme so break outta this
			//cout<<"Leaving loop due to found next lexeme: "<<newToken<<endl;
			break;
		}
	}

	//cout<<"Final token: "<<newToken<<endl;
	//add to *t
	t->setLexemeString(newToken);

	t->setTokenCode(LexicalAnalyzer::tokenCodeSolver(newToken, LexicalAnalyzer::lexemes));  
	return t;
}

bool LexicalAnalyzer::checkNextCharacter(string &newToken, string &nextToken, string lexemes[]){
	//cout<<"in validLexemes function, current token: "<<token<<endl;
	for(int i=0;i<45;i++){
		//cout<<"in validLexemes function, current lexemes to check: "<<lexemes[i]<<endl;
		if(lexemes[i] == nextToken){
			if(nextToken == "." && (newToken[0] >= 48 && newToken[0] <= 57)){
				//possible number so we ignore it
				return false;
			}
			//cout<<"token: "<<newToken<<"   nextToken: "<<nextToken<<endl;
			//cout<<"found matching lexeme: token: "<<token<<"   lexeme: "<<lexemes[i]<<endl;
			return true;
		}
	}
	return false;
}

bool LexicalAnalyzer::validLexeme(string &token, char tokenpart, string lexemes[]){
	//cout<<"in validLexemes function, current token: "<<token<<endl;
	for(int i=0;i<45;i++){
		//cout<<"in validLexemes function, current lexemes to check: "<<lexemes[i]<<endl;
		if(lexemes[i] == token){
			//cout<<"found matching lexeme: token: "<<token<<"   lexeme: "<<lexemes[i]<<endl;
			if(token[0] >= 97 && token[0] <= 122 && tokenpart >= 97 && tokenpart <= 122){
				return false;
			}
			return true;
		}
	}
	return false;
}

bool LexicalAnalyzer::checkLongLexeme(string &token, string &nextToken){
	if(token == ":"){
		//check if next is =
		if(nextToken == "="){
			return true;
		}
	}
	else if(token == "<"){
		if(nextToken == "=" || nextToken == ">"){
			return true;
		}
	}
	else if(token == ">"){
		if(nextToken == "="){
			return true;
		}
	}
	return false;
}

TokenCodes LexicalAnalyzer::tokenCodeSolver(string &token, string lexemes[]){
	for(int i=0;i<45;i++){
		//cout<<"in validLexemes function, current lexemes to cehck: "<<lexemes[i]<<endl;
		if(lexemes[i] == token){
			//cout<<"found matching lexeme: token: "<<token<<"   lexeme: "<<lexemes[i]<<endl;
			TokenCodes result = static_cast<TokenCodes>(i);
			return result;
		}
	}
	//check if identifier
	if(token[0] >= 97 && token[0] <= 122){
		//starts with letter, make sure its a valid identifier (alphanumeric only)
		for(int i=0;i<token.length();i++){
			if((token[i] < 48 || token[i] > 57) && (token[i] < 97 || token[i] > 122)){
				return TokenCodes::NAL;
			}
		}
		return TokenCodes::IDENT;
	}
	//check if numerical
	else if(token[0] >= 48 && token[0] <= 57){
		//starts with letter, make sure its a valid identifier (alphanumeric only)
		for(int i=0;i<token.length();i++){
			if(token[i] < 48 || token[i] > 57){
				//check if .
				if(token[i] == 46){
					i++;
					//continue loop for decimal point
					for(i;i<token.length();i++){
						if(token[i] < 48 || token[i] > 57){
							//cout<<"oopsie: "<<token<<"   "<<i<<" token "<<token[i]<<endl;
							return TokenCodes::NAL;
						}
					}
					return TokenCodes::NUMLIT;
				}
				else{
					return TokenCodes::NAL;
				}
			}
		}
		return TokenCodes::NUMLIT;
	}
	else{
		//couldnt find match, return NAL
		return TokenCodes::NAL;
	}
}