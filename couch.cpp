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
	
	#include <map>
	#include <vector>
	#include <queue>
	#include <cassert>
	#include <type_traits>
	#include <typeinfo>

	using namespace std;
	
	//.h files ##################
	
	#include "h_files/lexerClass.h"
	#include "h_files/symbols.h"
	
	#include "h_files/scopes.h"
	#include "h_files/types.h"
	#include "h_files/parser.h"
	
	
	//###########################
	
	//original sources #########
	#include "configure.cpp"
	
	#include "parser/lexerClass.cpp"
	//#include "libs/dynamicAllocator.cpp"
	#include "libs/dynamicTempAllocator.cpp"
	#include "data/globalData.cpp"
	#include "variables/types.cpp"
	#include "variables/dataEnvironment.cpp"
	#include "variables/scopes.cpp"
	//#include "variables/types.cpp"
	#include "h_files/instGen.h"
	#include "instructions/instGen.cpp"
	#include "parser/debug.cpp"
	#include "parser/parser.cpp"
	
	//defines ##################
	#define DEBUG

//################################### GLOBAL DATA ###################################


//##################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	bool readCLP ( int numArgs , char * args [ ] );


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int main ( int argc , char * argv [ ] ) 
{
	//process the command line arguments #######
	if ( readCLP ( argc , argv ) == false )
		return 1;
	
	//set keywords ##########
	setKeywords ( );
	
	//initialize symbol table #########
	initializeSymbolTable ( );
	
	//parse the input #################
	parse ( inputFileName );
	
	#ifdef DEBUG 
	//dump symbol table ###############
	//dumpSymbolTable ( );
	#endif
	
	dumpInstructions ( );
	//dumpScopes ( );
	dumpErrors ( );
	
	return 0; 
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: readCLP
*
* Parameters: vector<string> & strings
*
* Modifications: 
*
*  
*
*
*
* Returns: bool
* Comments: couch <inputFileName> < options .... >
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool readCLP ( int numArgs , char * args [ ] )
{ 
   //Check for the right number of params ###############
   if ( numArgs < 2 )
	{
		cout << "@*@*@*@*@*@*@*@* Couch Language @*@*@*@*@*@*@*@*" << endl;
		cout << "# Usage: couch <fileName> <options....>" 			  << endl;
		cout << "# -o <outputFileName> , set the output file name" << endl;
		cout << "################################################" << endl;
		return false;
	}

	//set code file input name , -t is debug file input ############
	if ( strcmp ( args [ 1 ] , "-t" ) == 0 )
	{
		inputFileName = debugCodeTestFilePath;
	}
	else 
		//set the source file name ##########
		inputFileName = args [ 1 ];

	//get the rest of the options #################
   int i = 2;  
   
   //Get the options #############
   while ( i < numArgs )
   {
      //Output file ###############      
      if ( strcmp ( args [ i ] , "-o" ) == 0 and i + 1 < numArgs )
      {
         outputFileName = args [ ++ i ]; 
      }
      
      else if ( strcmp ( args [ i ] , "-t" ) == 0 and i + 1 < numArgs )
      {
		  inputFileName = "C:\\programs\\couch\\noncode\\test.cch";
		  cout << "setting input file name " << endl;
	  }
      
      i ++;
   }

   return true;
}

