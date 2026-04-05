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
		vector < int > flowGraph;
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
	map < string , int > labels; //maps label to line number
	map < int , string > jumps;
	
	
	//for all of the instructions ###################
	while ( i < numberOfInstructions )
	{
		//first block ###################################
		if ( i == 0 )
		{
			b.start = 0;
			b.blockNumber = 0;
			b.end = -1;
		}
		//any istruction after a jump is a leader , jump is the last instruction of the block
		else if ( instVec [ i ] -> type == JUMP_TEST_INST or instVec [ i ] -> type == JUMP_INST )
		{
			b.end = i; //last instruction of the block
			if ( instVec [ i ] -> type == JUMP_TEST_INST )
				b.flowGraph.push_back ( blockNumber + 1 );
			blocks.push_back ( b ); //this block is finished
			b.start = i + 1; //start a new block
			b.flowGraph.clear ( );
			b.blockNumber = blockNumber + 1;
			b.end = -1;//end not set yet
			
			//link the block number to label ###############
			if ( instVec [ i ] -> equ != 0 )
				jumps [ blockNumber ] = instVec [ i ] -> equ -> lexeme;
			else 
			{
				cout << * instVec [ i ] << endl;
				gerrors.push_back ( MAKE_ERROR ( "label name empty" ) );
			}
			
			blockNumber ++;
		}
		//any target of a jump is a leader #############
		else if ( instVec [ i ] -> type == LABEL_INST )
		{
			b.end = i - 1; //the  
			b.flowGraph.push_back ( blockNumber + 1 );
			blocks.push_back ( b ); //block is finished
			blockNumber ++;//this is the start of a new block
			b.start = i; //label is first instruction
			b.flowGraph.clear ( );
			b.blockNumber = blockNumber;//set the new block number 
			b.end = -1;//we don't have the last instruction yet
			
			//map the label to the block number #############
			if ( instVec [ i ] -> equ )
				labels [ instVec [ i ] -> equ -> lexeme ] = blockNumber;
			else 
			{
				gerrors.push_back ( MAKE_ERROR ( "label name empty" ) );
			}
		}
		
		i ++;
	}
	
	//if the last block is open , add it to the list 
	if ( b.end == - 1 )
	{
		b.end = i;
		blocks.push_back ( b ); //block is finished
	}
	
	int numberBlocks = blocks.size ( );
	cout << "jumps: " << jumps.size ( ) << endl;
	
	//build the adjacecy list #########################
	for ( auto it = jumps.begin ( ) ; it != jumps.end ( ) ; ++ it ) 
	{
		
		//make sure block number exists #######################
		if ( it -> first < numberBlocks )
		{
			//make sure the label name exists #################
			if ( labels.find ( it -> second ) != labels.end ( ) )
				blocks [ it -> first ].flowGraph.push_back ( labels [ it -> second ] );
			else
			{
				gerrors.push_back ( MAKE_ERROR ( "label name not in map" ) ); //no label exists error
			}
		}
		else 
		{
			gerrors.push_back ( MAKE_ERROR ( "block number out of range" ) ); //block out of range error
		}
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
	
	cout << endl << "Block map #########################" << endl;
	
	
	//output blocks $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	for ( auto b : blocks )
	{
		cout << "Block: " << b.blockNumber << ". " << b.start << " " << b.end << endl;
		cout << "adjacency list: ";
		
		//output the flow graph ##################
		for ( auto bl : b.flowGraph )
		{
			cout << bl << " ";
		}
		
		cout << endl;
	}
	
	cout << endl << "End block map ################################" << endl;

	return true;
}