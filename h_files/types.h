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


//################################### GLOBAL DATA ###################################


	vector < symbol > typeArray;
	map < string , int > typeMap;
	
	const int FIRST_NEW_TYPE = 400;
	int currentNewType = 400; // new types start with 400

//##################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	 int addNewType ( string name ); 
	 symbol * addNewTypeMember ( string name , int type , int scope , int cells ); 
	 bool finishNewType (  ); 


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@