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

/*

	using namespace std;

//################################### GLOBAL DATA ###################################
	
	const int LABEL_INST = 0;
	const int JUMP_INST = 1;
	const int JUMP_TEST_INST = 2;
	const int NEG_INST = 3;
	const int INC_INST = 4;
	const int DEC_INST = 5;
	const int ARRAY_INDEX_INST = 6;
	const int PUSH = 7;
	const int CALL = 8;
	const int STRUCT_SELECTION = 9;
	const int MOVE = 10;
	
	//string instructions [ 11 ] = { "label" , "jump" , "jump_test" , "negate" , "inc" , "dec" ,
	//								"array_eval" , "push" , "call" , "struct_select" , "move" };
	vector < string > instructions = { "label" , "jump" , "jump_test" , "negate" , "inc" , "dec" ,
												 "array_eval" , "push" , "call" , "struct_select" , "move" };
	
	
	struct instruction
	{
		symbol * rhs = 0;
		symbol * lhs = 0;
		symbol * equ = 0;
		
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
				cout << s.equ -> lexeme << " " << s.type << " ";
			
			if ( s.lhs != 0 and s.lhs -> lexeme.size ( ) > 0)
				cout << s.lhs -> lexeme << " ";
			
			if ( s.rhs != 0 and s.rhs -> lexeme.size ( ) > 0 )
				cout << s.rhs -> lexeme << " ";
		
			//output instruction number @##@@@@@
			cout << s.instructionNum << endl;
			
			return os;
		
		};
	};
	
	vector < instruction * > instVec;
	queue < instruction * > delayedIns;
	dynamicTempAllocator < instruction > dai;
	int labelNum = 0;
*/
//##################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	instruction * makeLabel ( int scope , string notes = "" ); 
	instruction * makeInstruction (  int type , symbol * equ , symbol * lhs , symbol * rhs , int scope , string notes = "" ) ;
	instruction * makeDelayedInstruction ( int type , symbol * equ , symbol * lhs , symbol * rhs , int scope );
	inline int addDelayedInstructions ( );
	int dumpInstructions ( );
	instruction * addInstruction ( symbol * equ , symbol * lhs , symbol * rhs , int  scope , int type );
	instruction * addDelayedInstruction ( symbol * equ , symbol * lhs , symbol * rhs , int  scope , int type );


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



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
* Comments: Label format: equ = label, rhs and lhs = 0 , type = label
	//initialise the symbol
	
	ins.equ = symbol * label;
	ins.lhs = 0;
	ins.rhs = 0;
	ins.type = LABEL_INST;
	ins.scopeNum = scope;
	
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
instruction * makeLabel ( int scope , string notes ) 
{ 
	//complete any delayed instructions first ###########
	addDelayedInstructions ( );
	instruction * ins;
	symbol * label;
	string name = "label" + to_string ( labelNum ++ );
	
	//make a label symbol in the scope ###################
	label = scopes [ scope ].addVariable( name , LABEL , scope , 0 , LABEL_CATEGORY );
	
	ins = addInstruction ( label , 0 , 0 , scope , LABEL_INST );
	
	if ( notes.size ( ) > 0 )
		ins -> notes = notes;

	return ins;//insNum;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: makeInstruction
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
* Comments: type will be ascii value of op , or token value if it's a non-char op ( "<<" )
	JUMP_INST: equ = label
	JUMP_TEST_INST: equ = label , lhs = test result
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
instruction * makeInstruction ( int type , symbol * equ , symbol * lhs , symbol * rhs , int scope , string notes ) 
{ 
	//do the delayed instructions first ###
	addDelayedInstructions ( );
	instruction * ins;
	
	ins = addInstruction ( equ , lhs , rhs , scope , type );
	
	//add notes if needed ###################
	if ( notes.size ( ) > 0 )
		ins -> notes = notes;

	return ins;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: instruction
*
* Parameters:  
*
* Modifications: 
*
*
*
*
*
* Returns: bool makeDelayed
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
instruction * makeDelayedInstruction (  int type , symbol * equ , symbol * lhs , symbol * rhs , int scope ) 
{ 
	addDelayedInstructions ( );
	
	instruction * ins;
	
	//make the delayed instruction ######################
	ins = addDelayedInstruction ( equ , lhs , rhs , scope , type );
	
	return ins;
}

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
int dumpInstructions ( ) 
{
	int i = 0;
	int numInst = instVec.size ( );
	
	cout << numInst << " Instructions *******************************" << endl;
	
	//output the instructions ######################
	while ( i < numInst )
	{
		//output move instruction #############
		if ( ( char ) instVec [ i ] -> type == MOVE ) 
		{
			cout << "mov ";
			if ( instVec [ i ] -> equ  != 0  )
				cout << instVec [ i ] -> equ -> lexeme << " , ";
			if ( instVec [ i ] -> lhs != 0  )	
				cout << instVec [ i ] -> lhs -> lexeme;
		}
		//output binary operator #######################
		else if ( isOperator ( instVec [ i ] -> type ) )
		{
			if ( instVec [ i ] -> equ  != 0 and instVec [ i ] -> equ -> lexeme.size ( ) > 0 )
				cout << instVec [ i ] -> equ -> lexeme << " ";
			
			cout << " = ";
			
			if ( instVec [ i ] -> lhs != 0 and instVec [ i ] -> lhs -> lexeme.size ( ) > 0 )
				cout << instVec [ i ] -> lhs -> lexeme << " ";
			
			if ( instVec [ i ] -> type > 260 )
				cout << IDToKeywords [ instVec [ i ] -> type ] << " ";
			else 
				cout << ( char ) instVec [ i ] -> type << " ";
			
			if ( instVec [ i ] -> rhs != 0 and instVec [ i ] -> rhs -> lexeme.size ( ) > 0 )
				cout << instVec [ i ] -> rhs -> lexeme << " ";
		}
		//output push instruction ##############
		else if ( instVec [ i ] -> type == PUSH )
		{
			cout << "push ";
			if ( instVec [ i ] -> equ  != 0  )
				cout << instVec [ i ] -> equ -> lexeme;
		}
		//output function call #################
		else if ( instVec [ i ] -> type == CALL )
		{
			cout << "call ";
			if ( instVec [ i ] -> equ  != 0  )
				cout << instVec [ i ] -> equ -> lexeme;
		}
		//output label instruction #############
		else if ( instVec [ i ] -> type == LABEL_INST )
		{
			cout << "label ";
			if ( instVec [ i ] -> equ  != 0  )
				cout << instVec [ i ] -> equ -> lexeme << ":";
		}
		
		else if ( instVec [ i ] -> type == JUMP_TEST_INST )
		{
			cout << "jmp ";  
			if ( instVec [ i ] -> equ  != 0  )
				cout << instVec [ i ] -> equ -> lexeme << " ";
			if ( instVec [ i ] -> lhs != 0  )	
				cout << instVec [ i ] -> lhs -> lexeme;
			if ( instVec [ i ] -> jump != 0 )
				cout << " " << instVec [ i ] -> jump -> equ -> lexeme;
			
		}
		else if ( instVec [ i ] -> type == JUMP_INST )
		{
			cout << "jmp ";  
			if ( instVec [ i ] -> equ  != 0  )
				cout << instVec [ i ] -> equ -> lexeme << " ";
			if ( instVec [ i ] -> jump != 0 )
				cout << " " << instVec [ i ] -> jump -> equ -> lexeme;
		}
		else if ( instVec [ i ] -> type == NEG_INST )
		{
			if ( instVec [ i ] -> lhs  != 0  )
				cout << "NEG " << instVec [ i ] -> lhs -> lexeme << " ";
		}
		
		else if ( instVec [ i ] -> type == PRE_INC_INST )
		{
			if ( instVec [ i ] -> equ  != 0  )
				cout << "++ " << instVec [ i ] -> equ -> lexeme << " ";
		}
		else if ( instVec [ i ] -> type == PRE_DEC_INST )
		{
			if ( instVec [ i ] -> equ  != 0  )
				cout << "-- " << instVec [ i ] -> equ -> lexeme << " ";
		}
		else if ( instVec [ i ] -> type == ARRAY_INDEX_INST )
		{
			if ( instVec [ i ] -> equ  != 0  )
				cout << instVec [ i ] -> equ -> lexeme << " ";
			cout << " [ ";
			if ( instVec [ i ] -> lhs != 0  )	
				cout << instVec [ i ] -> lhs -> lexeme;
			cout << " ] ";
		}
		//struct selection ############################
		else if ( instVec [ i ] -> type == STRUCT_SELECTION )
		{
			if ( instVec [ i ] -> equ  != 0  )
				cout << instVec [ i ] -> equ -> lexeme << " ";
			
			cout << ".";
			
			if ( instVec [ i ] -> lhs != 0  )	
				cout << instVec [ i ] -> lhs -> lexeme;
		}
		
		//output the notes @@@@@@@@@@@@@@@@@@@@@
		if ( instVec [ i ] -> notes.size ( ) > 0 )
			cout << " //" << instVec [ i ] -> notes;
		
		cout << endl;
		
		i ++;
	}
	
	return 0;
}

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
inline int addDelayedInstructions ( )
{
	//add the delayed instructions @@@@@@@@@@@@@
	while ( ! delayedIns.empty ( ) )
	{
		instVec.push_back ( delayedIns.front ( ) );
		delayedIns.pop ( );
	}
	
	return 0;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

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
* Returns: bool
*
* 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int makeInstructionRet ( int type , symbol *& equ , symbol * lhs , symbol * rhs , int scope ) 
{ 
	
	addDelayedInstructions ( );
	
	instruction ins;
	int size;
	
	int lhsSize;//get the size of the lhs
	int rhsSize;//get the size of the rhs
	
	if ( lhs )
		lhsSize = dataSize [ lhs -> type ];//get the size of the lhs
	else
		lhsSize = 0;
	
	if ( rhs )
		rhsSize = dataSize [ rhs -> type ];//get the size of the rhs
	else
		rhsSize = 0;
	
	//get the equ size ##########
	if ( lhsSize > rhsSize )
		size = lhsSize;
	else 
		size = rhsSize;
	
	//get a temp variable ############
	scopes [ scope ].getTemp ( size , scope , 0 );
	
	//initialize the instruction ############
	ins.initialize ( equ , lhs , rhs , scope , type );
	
	//add the variable to the instruction vector #########
	//instVec.push_back ( ins ); 

	return 1;// ins.instructionNum;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: instruction
*
* Parameters:  
*
* Modifications: 
*
*
*
*
*
* Returns: bool makeDelayed
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
instruction * addInstruction ( symbol * equ , symbol * lhs , symbol * rhs , int  scope , int type )
{
	instruction * ins;
	
	//allocate the memory ############################
	ins = ( instruction * ) dai.allocate ( sizeof ( instruction ) );
	
	//check the allocation ###########################
	if ( ins == 0 )
		return 0;
	
	//initialize the instruction #####################
	ins -> initialize ( equ , lhs , rhs , scope , type );
	
	//add the instruction the list ###################
	instVec.push_back ( ins );

	return ins;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: instruction
*
* Parameters:  
*
* Modifications: 
*
*
*
*
*
* Returns: bool makeDelayed
*
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
instruction * addDelayedInstruction ( symbol * equ , symbol * lhs , symbol * rhs , int  scope , int type )
{
	instruction * ins;
	
	//allocate the memory ############################
	ins = ( instruction * ) dai.allocate ( sizeof ( instruction ) );
	
	//check the allocation ###########################
	if ( ins == 0 )
		return 0;
	
	//initialize the instruction #####################
	ins -> initialize ( equ , lhs , rhs , scope , type );
	
	//add the instruction the list ###################
	delayedIns.push ( ins );

	return ins;
}
