/*********************************************************************************
*
* File Name: noncode/scrap.cpp
*
* Date: January , 11 , 2026
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
* Program Shell Generated At: January , 11 , 20262:13:45 a.m. 
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

//################################### GLOBAL DATA ###################################


//##################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	template < typename t >
	bool printVector ( vector < t > & v ); 


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: printVector
*
* Parameters: vector & v
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
template < typename t >
bool printVector ( vector < t > & v ) 
{ 
	if ( v.size () == 0 )
		return false;
	
	cout << "vector :";
	
	for ( auto a : v )
	{
		if constexpr ( is_pointer<t>::value )
			cout << * a << " ";
		else if ( typeid ( t ).name ( )  == "i" )
			cout << ( char ) a << " ";
		else 
			cout << ( char ) a << " ";
	}
	
	cout << endl;

	return true;
}

