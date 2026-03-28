/*********************************************************************************
*
* File Name: C:\programs\cgUpgrade\noncode\scrap.cpp
*
* Date: February , 9 , 2025
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
* Program Shell Generated At: 2:40:09p.m.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


//################################### GLOBAL DATA ###################################

	lexerClass lc;
	vector < map < string , int > > strMap;
	
	//the error handler #####################
	vector < string > gerrors; 
	
	#define REPORT_ERROR(error)\
	{\
		string e = error;\
		e += " ";\
		e += tok.lexeme;\
		gerrors.push_back ( e );\
	}
	
	//wrap a string in a string class #######
	string make_str ( string s )
	{
		return s;
	}
	
	//input and output file names ###########
	string inputFileName;
	string outputFileName;
	
	//variable coordinate tupple ######
	struct vcord //variable 
	{
		int scope; //scope number
		int vnum; //variable number
	};
	
	//dynamicAllocator da;
	dynamicTempAllocator < symbol > das;
	//dynamicTempAllocator < instruction > dai;
	
	#define isOperator(o) ( o == '+' or o == '-' or o == '*' or o == '\\' or o == AND or o == '=' or o == LOGICAL_EQ or o == GREAT_EQ or o == LESS_EQ or o == NOT_EQ or o == GREATER_THAN or o == LESS_EQ )
	#define isRegister(r) ( r > 260 and r < 327 ) 
