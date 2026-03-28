/*********************************************************************************
*
* File Name: noncode/scrap.cpp
*
* Date: November , 8 , 2025
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
* Program Shell Generated At: November , 8 , 20252:45:46 P.m. 
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

	#ifndef string
	#include <string>
	#endif

	using namespace std;



/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: addNewType
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
int addNewType ( string name ) 
{ 
	symbol newType;
	
	newType.initialize ( name , currentNewType , 0 , 0 );
	typeArray.push_back ( newType );
	typeMap [ name ] = currentNewType ++;
	
	return ( currentNewType - 1 );
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: addNewTypeMember
*
* Parameters: int type
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
 symbol * addNewTypeMember ( int userDefinedType , string name , int type , int scope , int cells ) 
{ 
	symbol member;
	
	//type out of range ###################################
	if ( userDefinedType < 400 or userDefinedType >= currentNewType )
		return 0;
	
	//initialize the new member #####################
	member.initialize ( name , type , scope , cells );
	
	//add the member to the current type ###################
	typeArray [ userDefinedType ].members.push_back ( member ); 

	return & typeArray [ userDefinedType ].members.back ( );
}


