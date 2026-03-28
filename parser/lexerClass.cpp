/*********************************************************************************
*
* File Name: /home/user/programs/cgUpgrade/noncode/scrap.cpp
*
* Date: January , 7 , 2025
* Comments: 
* Compiler/Assembler:
* Modifications:
*
*
*
*
*
*
*
* Program Shell Generated At: 7:17:17p.m.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


	#ifndef iostream
	#include <iostream>
	#endif

	#ifndef string
	#include <string>
	#endif

	#ifndef string_h
	#include <string.h>
	#endif

	#ifndef ctype_h
	#include <ctype.h>
	#endif

	#ifndef ifstream
	#include <fstream>
	#endif

	#ifndef stdlib_h
	#include <stdlib.h>
	#endif
	
	#ifndef map
	#include <map>
	#endif
	
	#ifndef vector
	#include <vector>
	#endif

	using namespace std;
	//#include "lexerClass.h"
	
	//#include "lexerData.cpp"
	
	//#define DEBUG

//################################### GLOBAL DATA ###################################



	

	


//##################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//###########################################################################################
	//Class Definition: lexerClass ##########################
	//###########################################################################################
	class lexerClass
	{
		public:

			lexerClass ( string filename ); 
			~lexerClass ( ); 
			lexerClass ( ) { peekMode = false;  lineNum = 0; colNum = 0; };
			bool setFile ( string fileName );
			bool getToken ( token & tok  );
			token getTokenAt ( int i );
			bool readIdentifier ( token & tok  );
			bool readNumber ( token & tok );
			bool getString ( token & tok );
			bool getASCII ( token & tok );
			bool peekToken ( token & tok );
			bool otherTokens ( token & tok );
			inline bool get_ch ( char & ch );
			inline bool peek_ch ( char & ch );
			inline bool eatComment ( char & ch );
			inline bool eatWhite ( char & ch );
			bool eofFound;
			bool fatalError = false;

		private:
			
			vector < token > tokens;
			bool peekMode;
			ifstream input;
			string filename;
			vector < string > errors;
			int lineNum;
			int colNum;
			char ch;
			int tabWidth = 3;
			
	};

#ifdef DEBUG
int main ( int argc , char * argv [ ] ) 
{
	lexerClass lc ( "C:\\programs\\couch\\noncode\\test.cch" );
	token tok;
	
	if ( lc.fatalError == true )
	{
		cout << "file didn't open" << endl;
		return 1;
	}
	
	while ( lc.eofFound != true )
	{
		lc.getToken ( tok );
		if ( lc.eofFound != true )
			cout << tok << endl;
	}
	
	cout << tok << endl;
	
	return 0; 
}
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- CONSTRUCTOR DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
 Function Name: 
*
* Parameters:
*
* Modifications:
*
*
*
*
*
* Returns:
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
lexerClass::lexerClass ( string fileName )
{
	filename = fileName;
	
	//open the file ###################
	input.open ( filename );
	
	//check if the file opened ########
	if ( input.fail ( ) )
	{
		cout << "Lexer input file did not open ( lexerClass )  "  << fileName << endl;
		fatalError = true;//report error 
		return;
	}
	
	//set the lexer's keywords ###############
	setKeywords ( );
	
	//get the first char ##############
	if ( get_ch ( ch ) == false )
	{
		fatalError = false;
		eofFound = true;
		input.close ( );
		return;
	}
	
	//if everything goes right set data ######
	lineNum = 1;
	colNum = 1;
	eofFound = false;
	peekMode = false;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- CONSTRUCTOR DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
 Function Name: 
*
* Parameters:
*
* Modifications:
*
*
*
*
*
* Returns:
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool lexerClass::setFile ( string fileName )
{
	filename = fileName;
	
	//open the file ###################
	input.open ( filename );
	
	//check if the file opened ########
	if ( input.fail ( ) )
	{
		cout << "Lexer file did not open ( sefFile )  " << endl;
		fatalError = true;
		return false;
	}
	
	//get the first char ##############
	if ( get_ch ( ch ) == false )
	{
		fatalError = true;
		eofFound = true;
		input.close ( );
		return false;
	}
	
	return true;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- DESTRUCTOR DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
*
 Function Name: 
*
* Parameters:
*
* Modifications:
*
*
*
*
*
* Returns:
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
lexerClass::~lexerClass ( )
{
	input.close ( );
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: getToken
*
* Parameters:  
*
* Modifications: 
*
*
*
*
*
* Returns: lexerModule::token
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool lexerClass::getToken ( token & tok ) 
{ 
	//reset the token ################
	tok.reset ( );
	tok.lineNum = lineNum;
	tok.colNum = colNum;
	
	//Handle peek operation ##########
	if ( peekMode == true )
	{
		peekMode = false;
		tok = tokens.back ( );
		return true;
	}
	
   //EOF found ############
   if ( eofFound == true )
		return false;
	
	//skip the white space ############
	if ( isspace ( ch ) )
		if ( eatWhite ( ch ) == false )
			return false;
	//eat the comments ################
	if ( ch == '/' )
		if ( eatComment ( ch ) == false )
			return false;
	
	//if you get here the char is a letter , digit , or symbol

	//Identifier #################
	if ( isalpha ( ch ) )
	{
		if ( readIdentifier ( tok ) == false )
			return false;
	}
	
	//Read a number ############
	else if ( isdigit ( ch  ) )
	{
		if ( readNumber ( tok ) == false )
			return false;
	}
	
	//String ###############################################
	else if ( ch == '\"' )
	{
		if ( getString ( tok ) == false )
			return false;
	}
	
	//Character #############################################
	else if ( ch == '\'' )
	{
		if ( getASCII ( tok ) == false )
			return false;
	}
	
	//Additional tokens ######################################
	//Make changes here **************************************
	else if ( SINGLE_CHAR_TOKENS ) //see definition in lexerData.cpp
	{
		//Just record a character #############################
		if ( otherTokens ( tok ) == false )
		{	
			//save line and col number #########################
			tok.colNum = colNum - 1;
			tok.lineNum = lineNum;
			
			tok.lexeme += ch;
			tok.type = ( int ) ch;
			tokens.push_back ( tok );
			if ( get_ch ( ch ) == false )
				return false;
		}

	}
	//Just record a character ################################
	else
	{
		//save line and col number #########################
		tok.colNum = colNum - 1;
		tok.lineNum = lineNum;
		
		tok.lexeme += ch;
		tok.type = ( int ) ch;
		tokens.push_back ( tok );
		if ( get_ch ( ch ) == false )
			return false;
	}
	
	return true;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: getTokenAt
*
* Parameters: int i
*
* Modifications: 
*
*
*
*
*
* Returns: lexerModule::token
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
token lexerClass::getTokenAt ( int i ) 
{ 
	return tokens [ i ];
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: readIdentifier
*
* Parameters:  
*
* Modifications: 
*
*
*
*
*
* Returns: bool
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool lexerClass::readIdentifier ( token & tok ) 
{ 
	//save line and col number #########################
	tok.colNum = colNum - 1;
	tok.lineNum = lineNum;
	
	//read the identifier ################################
	while ( ! eofFound && isalnum ( ch ) )
	{
		tok.lexeme += ch;
		
		//check character #########
		if ( get_ch ( ch ) == false ) 
			break;
	}
	
	//check if this is a keyword ########################
	if ( keywords.find ( tok.lexeme ) != keywords.end ( ) )
	{
		tok.type = keywords [ tok.lexeme ];
	}
	//set as an identifier then #########################
	else
		tok.type = IDENTIFIER ;
	
	//put the token in the vector ##############
	tokens.push_back ( tok );

	return true;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: readNumber
*
* Parameters:  
*
* Modifications: 
*
*
*
*
*
* Returns: bool
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool lexerClass::readNumber ( token & tok ) 
{ 
	//save line and col number #########################
	tok.colNum = colNum - 1;
	tok.lineNum = lineNum;
	
	//read the identifier ################################
	while ( isdigit ( ch ) )
	{
		tok.lexeme += ch;
		
		//check character #########
		if ( get_ch ( ch ) == false ) 
			break;
	}
	
	//check if this is a float ###########################
	if ( ch == '.' )
	{
		tok.lexeme += '.';
		tok.type = FLOAT;
		
		peek_ch ( ch );
		
		//get the decimal ################################
		while ( isdigit ( ch ) )
		{
			tok.lexeme += ch;
			
			//check character #########
			if ( get_ch ( ch ) == false ) 
				break;
		}
		
		if ( ch == '.' )
			tok.lexeme += '0';
	}
	else 
		tok.type = INT;
	
	//put the token in the vector ##############
	tokens.push_back ( tok );

	return true;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: getString
*
* Parameters:  
*
* Modifications: 
*
*
*
*
*
* Returns: bool
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool lexerClass::getString ( token & tok ) 
{ 
	//save line and col number #########################
	tok.colNum = colNum - 1;
	tok.lineNum = lineNum;
	
	get_ch ( ch );
	
	//read the identifier ################################
	while ( ! eofFound and ch != '\"' )
	{
		tok.lexeme += ch;
		
		//check character #########
		if ( get_ch ( ch ) == false ) 
			break;
	}
	
	//Unclosed string error@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if ( eofFound or ch != '\"' )
	{
		
		string error = "Unclosed string literal: ";
		error += tok.lexeme;		
		errors.push_back ( error  );
	}	
	
	tok.type = STRING;
	
	//put the token in the vector ##############
	tokens.push_back ( tok );

	get_ch ( ch );

	return true;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: skipMultiLineComment
*
* Parameters:  
*
* Modifications: 
*
*
*
*
*
* Returns: bool
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool lexerClass::getASCII ( token & tok  ) 
{ 
	//save line and col number #########################
	tok.colNum = colNum - 1;
	tok.lineNum = lineNum;

	//check character #########
	if ( get_ch ( ch ) == false ) 
		return false;
	
	tok.lexeme += ch;
	
	//check character #########
	if ( get_ch ( ch ) == false ) 
		return false;
	
	//Unclosed char ###############################
	if ( ch not_eq '\'' )
	{
		string error = "Unclosed character: ";
		error += tok.lexeme;
		errors.push_back ( error );
	}

	tok.type = CHAR;
	
	//check character #########
	if ( get_ch ( ch ) == false ) 
		return false;
	
	//put the token in the vector ##############
	tokens.push_back ( tok );
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: peekToken
*
* Parameters:  
*
* Modifications: 
*
*
*
*
*
* Returns: token
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool lexerClass::peekToken ( token & tok ) 
{ 
	//reset the token ################
	tok.reset ( );
	tok.lineNum = lineNum;
	tok.colNum = colNum;
	
	//Handle peek operation ##########
	if ( peekMode == true )
	{
		//peekMode = false;
		tok = tokens.back ( );
		return true;
	}
	
	peekMode = true;
	
   //EOF found ############
   if ( eofFound == true )
		return false;
	
	//skip the white space ############
	if ( isspace ( ch ) )
		if ( eatWhite ( ch ) == false )
			return false;
	//eat the comments ################
	if ( ch == '/' )
		if ( eatComment ( ch ) == false )
			return false;
	
	//if you get here the char is a letter , digit , or symbol

	//Identifier #################
	if ( isalpha ( ch ) )
	{
		if ( readIdentifier ( tok ) == false )
			return false;
	}
	
	//Read a number ############
	else if ( isdigit ( ch  ) )
	{
		if ( readNumber ( tok ) == false )
			return false;
	}
	
	//String ###############################################
	else if ( ch == '\"' )
	{
		if ( getString ( tok ) == false )
			return false;
	}
	
	//Character #############################################
	else if ( ch == '\'' )
	{
		if ( getASCII ( tok ) == false )
			return false;
	}
	
	//Additional tokens ######################################
	//Make changes here **************************************
	else if ( SINGLE_CHAR_TOKENS ) //see definition in lexerData.cpp
	{
		//Just record a character #############################
		if ( otherTokens ( tok ) == false )
		{	
			//save line and col number #########################
			tok.colNum = colNum - 1;
			tok.lineNum = lineNum;
			
			tok.lexeme += ch;
			tok.type = ( int ) ch;
			tokens.push_back ( tok );
			if ( get_ch ( ch ) == false )
				return false;
		}

	}
	//Just record a character ################################
	else
	{
		//save line and col number #########################
		tok.colNum = colNum - 1;
		tok.lineNum = lineNum;
		
		tok.lexeme += ch;
		tok.type = ( int ) ch;
		tokens.push_back ( tok );
		if ( get_ch ( ch ) == false )
			return false;
	}
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name:
*
* Parameters: 
*
* Modifications: 
*
*
*
*
*
* Returns: lexerModule::token
*
* Comments: Make changes here for keywords or tokens larger than a character like '&&'
* add new tokens to "keywords" map in lexerData.cpp
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool lexerClass::otherTokens ( token & tok ) 
{
	string s;
	
	//parse the two char token #@@@@@@@@@@@@@@@@@@@
	s += ch;
	
	//check character #########
	if ( peek_ch ( ch ) == false ) 
		return false;
	
	s += ch;

	//Check if the token is a keyword @@@@@@@@@@@@@@@@@@@@
	if ( keywords.find ( s ) != keywords.end ( ) )
	{
		//save line and col number #########################
		tok.colNum = colNum - 1;
		tok.lineNum = lineNum;
		
        tok.lexeme += s;
        tok.type = keywords [ tok.lexeme ];

		get_ch ( ch );
		get_ch ( ch );
		
		//put the token in the vector ##############
		tokens.push_back ( tok );

		return true;
	}
	else 
		ch = s [ 0 ];

	return false;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name:
*
* Parameters: 
*
* Modifications: 
*
*
*
*
*
* Returns: lexerModule::token
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
inline bool lexerClass::get_ch ( char & ch )
{
	//get the next character and check for eof #####
	if ( ! input.get ( ch ) )
	{
		eofFound = true;
		return false;
	}
	//cout << "char : " << ch  << endl;
	//this is a newline char ########
	if ( ch == '\n' )
	{
		colNum = 1;
		lineNum ++;
	}
	else if ( ch == '\t' )
	{
		colNum += tabWidth;
		//lineNum ++;
	}
	//record data ###################
	else 
	{
		colNum ++;
	}
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name:
*
* Parameters: 
*
* Modifications: 
*
*
*
*
*
* Returns: lexerModule::token
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
inline bool lexerClass::peek_ch ( char & ch )
{
	//get the first character ##
	ch = input.peek ( );
	
	//if this is the end of file , return false
	if ( ch == EOF )
	{
		eofFound = true;
		return false;
	}

	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name:
*
* Parameters: 
*
* Modifications: 
*
*
*
*
*
* Returns: lexerModule::token
*
* Comments: ends when it finds first char that's not a comment or a space
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
inline bool lexerClass::eatComment ( char & ch )
{
	char ph;
	do 
	{ //start do 
		if ( peek_ch ( ph ) == false )
			return false;

		//single line comment ##############
		if ( ph == '/' )
		{
			//read until the end of the line 
			while ( ! eofFound and ch != '\n' )
			{
				if ( get_ch ( ch ) == false )
					return false;
			}
				
			//get the next char after comment #########
			if ( get_ch ( ch ) == false )
				return false;
		}
		//multiline comment #################
		else if ( ph == '*' )
		{
			if ( get_ch ( ch ) == false )
				return false;
			
			//while not at the end of the loop ###
			while ( ! eofFound )
			{
				//check for comment end #############
				if ( ch == '*' )
				{
					if ( get_ch ( ph ) == false )
						return false;
					
					//end of comment ##################
					if ( ph == '/' )
					{
						if ( get_ch ( ch ) == false )
							return false;
						
						break;
					}
				}
				
				//get the next character #############
				if ( get_ch ( ch ) == false )
					return false;
			}
			
			//get next char for match #
			if ( get_ch ( ch ) == false )
				return false;
		}//end multi line comment 
		else //not a comment ####
			return true;
		
		//eat white space and find next comment ###
		if ( eatWhite ( ch ) == false )
			return false;
		
	} while ( ch == '/' );
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name:
*
* Parameters: 
*
* Modifications: 
*
*
*
*
*
* Returns: lexerModule::token
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
inline bool lexerClass::eatWhite ( char & ch )
{
	while ( ! eofFound and isspace ( ch ) )
	{
		//check character #########
		if ( get_ch ( ch ) == false ) 
			return false;
	}
	
	return true;
}
