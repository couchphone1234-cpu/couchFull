/*********************************************************************************
*
* File Name: C:\programs\cgUpgrade\noncode\scrap.cpp
*
* Date: February , 10 , 2025
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
* Program Shell Generated At: 3:13:26 a.m.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/



	using namespace std;

//################################### GLOBAL DATA ###################################
	
	const int LABEL_INST = 0;
	const int JUMP_INST = 1;
	const int JUMP_TEST_INST = 2;
	const int NEG_INST = 3;
	const int INC_INST = 4;//not used
	const int DEC_INST = 5;//not used 
	const int ARRAY_INDEX_INST = 6;
	const int PUSH = 7;
	const int CALL = 8;
	const int STRUCT_SELECTION = 9;
	const int MOVE = 10;
	const int PRE_INC_INST = 11;
	const int POST_INC_INST = 12;
	const int PRE_DEC_INST = 13;
	const int POST_DEC_INST = 14;
	const int RETURN_STATEMENT = 15;
	
	//string instructions [ 11 ] = { "label" , "jump" , "jump_test" , "negate" , "inc" , "dec" ,
	//								"array_eval" , "push" , "call" , "struct_select" , "move" };
	vector < string > instructions = { "label" , "jump" , "jump_test" , "negate" , "inc" , "dec" ,
												 "array_eval" , "push" , "call" , "struct_select" , "move" ,
												 "pre_inc" , "post_inc" , "pre-dec" , "post-dec" };
	
	
	struct instruction
	{
		symbol * rhs = 0;
		symbol * lhs = 0;
		symbol * equ = 0;
		
		string notes;
		int scopeNum; //scope of instruction
		int instructionNum; //instruction index in the list
		instruction * jump = 0;
		
		
		int type; //type of instruction
		
		//initialize the instructions ################################
		int initialize ( symbol * equi , symbol * lhsi , symbol * rhsi , int scopei , int typei )
		{
			equ = equi;
			lhs = lhsi;
			rhs = rhsi;
			scopeNum = scopei;
			type = typei;
			
			return 0;
		};	
		
		//print the instruction ###############################
		friend ostream & operator << ( ostream & os , const instruction & s )
		{
			cout << "instruction: ";
			
			//output params ##############
			if ( s.equ != 0  and s.equ -> lexeme.size ( ) > 0 )
				cout << "equ :" << s.equ -> lexeme << " " << s.type << " ";
			
			if ( s.lhs != 0 and s.lhs -> lexeme.size ( ) > 0)
				cout << "lhs :" <<  s.lhs -> lexeme << " ";
			
			if ( s.rhs != 0 and s.rhs -> lexeme.size ( ) > 0 )
				cout << "rhs : " << s.rhs -> lexeme << " ";
		
			//output instruction number @##@@@@@
			cout << s.instructionNum << endl;
			
			return os;
		
		};
	};
	
	vector < instruction * > instVec;
	queue < instruction * > delayedIns;
	dynamicTempAllocator < instruction > dai;
	int labelNum = 0;

//##################################################################################
