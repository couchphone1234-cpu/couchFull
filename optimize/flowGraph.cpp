/*********************************************************************************
*
* File Name: "valueNumbering.cpp"
*
* Date: 
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
* Program Shell Generated At: Fri Mar 27 23:56:48 2026
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


	//includes ##########################
	#ifndef iostream
	#include <iostream>
	#endif

	#ifndef string
	#include <string>
	#endif

	#ifndef string_h
	#include <string.h>
	#endif

	#ifndef string
	#include <string>
	#endif

	using namespace std;

//################################### GLOBAL DATA ###################################

	
	
	//basic block ############
	struct block
	{
		int blockNumber;
		int start = 0;
		int end = 0;
		
		//flow graph ##########
		vector < vector < int > > flowGraph;
	};
	
	//blocks ##################
	vector < block > blocks;

//##################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	bool makeBlockAdjacencyArray (  vector < instruction * > & instVec  ); 
	bool debugBlockArray (  );


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: makeBlockAdjacencyArray
*
* Parameters:  vector < instruction * > & instVec 
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
bool makeBlockAdjacencyArray (  vector < instruction * > & instVec  ) 
{ 
	int numberOfInstructions = instVec.size ( ); //get the number of instructions
	int i = 0;
	int blockNumber = 0;
	block b;
	
	
	//for all of the instructions ###################
	while ( i < numberOfInstruction )
	{
		//first block ###################################
		if ( i == 0 )
		{
			b.start = 0;
			b.end = -1;
		}
		//any istruction after a jump is a leader #######
		else if ( instVec [ i ] -> type == JUMP_TEST_INST or instVec [ i ] -> type == JUMP_INST )
		{
			b.end = i;
			blocks.push_back ( b );
			b.start = i + 1;
			b.end = -1;
			
		}
		//any target of a jump is a leader #############
		else if ( instVec [ i ] -> type == LABEL_INST )
		{
			b.end = i - 1;
			blocks.push_back ( b );
			b.start = i;
			b.end = -1;
		}
		
		i ++;
	}
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: debugBlockArray
*
* Parameters:  vector < instruction * > & instVec 
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
bool debugBlockArray (  ) 
{ 
	int i = 0;
	
	//output blocks $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	for ( auto b : blocks )
	{
		cout << i ++ << ". " << b.start < " " << b.end << endl;
	}

	return true;
}