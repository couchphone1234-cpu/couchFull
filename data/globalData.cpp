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
	string buffer;
	
	//the error handler #####################
	vector < string > gerrors; 
	
	#define REPORT_ERROR(error)\
	{\
		string e = error;\
		e += " ";\
		e += "sl: ";\
		e += to_string ( __LINE__ );\
		e += " ";\
		e += tok.lexeme;\
		e += " ";\
		e += __FUNCTION__;\
		gerrors.push_back ( e );\
	}
	
	#define MAKE_ERROR(e) ( ( buffer = e ) + " sl: "  + to_string ( __LINE__ ) + " : " + __FUNCTION__ )
	
	
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

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: makeLabel
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
* 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool dumpErrors ( ) 
{
	//check if there's errors ############
	if ( gerrors.size ( ) == 0 )
		return false;
	
	cout << endl << "@@@@@@@@@@@@@@@@ ERRORS @@@@@@@@@@@@@@@@@@@@@" << endl;
	
	//output the errors ##############
	for ( auto e : gerrors )
	{
		cout << "error: " << e << endl;
	}
	
	cout << endl;
	
	return true;
}