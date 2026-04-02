/*********************************************************************************
*
* File Name: C:\programs\cgUpgrade\noncode\parser.cpp
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
* Program Shell Generated At: 2:35:03p.m.
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
	
	bool continueStatement ( int scope , instruction * testLabel );

	using namespace std;


/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: parse
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
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool parse ( string fileName ) 
{ 
	cout << fileName << endl;
	
	//test if the file opens #################
	if ( lc.setFile ( fileName ) == false )
		return false;
	
	lc.getToken ( tok );
	
	//parse the file ###############
	while ( ! lc.eofFound )
	{
		//variable #################
		if ( tok.type == VAR )
		{
			variableDec ( 0 );
		}
		else if ( tok.type == STRUCT )
		{
			structDeclaration ( 0 );
		}
		//function #################
		else if ( tok.type == FUNC )
		{
			function (  );
		}
		else if ( tok.type == PROTOTYPE )
		{
			prototype (  );
		}
		//error
		else 
		{
			string e = "Unknown token: ";
			e += tok.lexeme;
			gerrors.push_back ( e );
		}
		//dumpInstructions ( ) ;
		lc.getToken ( tok );
	}

	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: functionCall
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
bool function (  ) 
{ 
	token returnTok;
	int scope = 0;
	symbol * result;
	symbol parameter;
	symbol * functionName;
	symbol * functionSymbol;
	
	//get the return type token ####################
	GET_TOKEN ( tok )
	
	returnTok = tok; //save the return type
	
	//get identifer symbol #################################
	if ( expect ( ( returnTok.type == BYTE or returnTok.type == WORD or returnTok.type == DWORD or returnTok.type == QWORD or returnTok.type == TWORD ) , "Expecting Memory Type" ) == false )
	{
		return false;
	}
	
	//get the next token ####################
	GET_TOKEN ( tok )
	
	//get identifer symbol #################################
	if ( expect ( ( tok.type == IDENTIFIER ) , MAKE_ERROR ( "Function Name ( identifier ) " ) ) == true )
	{
		//put a symbol for the function in the global scope ##################
		functionSymbol = scopes [ 0 ].addVariable ( tok.lexeme , FUNCTION , scope , 0 , FUNCTION_CATEGORY );
	}
	
	//see if the scope exists ################
	scope = getScope ( tok.lexeme );
	
	//if the scope doesn't exist #############
	if ( scope == -1 )
	{
		//create a new scope ##################
		scope = addScope ( tok.lexeme , FUNCTION );
		//initialize the scope ################
		scopes [ scope ].initialize ( tok.lexeme , FUNCTION , scope , 0 ); //initialize the scope
		scopes [ scope ].returnType = returnTok.type; //set the function return type
	}
	
	//new label for the function #####################
	makeLabel ( scope ); 

	//get the next open bracket ( ####################
	GET_TOKEN ( tok )
	
	//expect an operand ####################################
	if ( expect ( ( tok.type == '(' ) , MAKE_ERROR ( "'(' " ) ) == false )
		return false;
	
	//get the next token ####################
	GET_TOKEN ( tok )
	
	//get the function parameter ##################
	//we're doing call by name , just an identifier for a paramter.
	while ( ! lc.eofFound and tok.type == IDENTIFIER )
	{
		//add the parameter @###############
		scopes [ scope ].addParameter ( tok.lexeme , NAME , scope , 0  );

		//get the next token ####################
		GET_TOKEN ( tok )
		
		//expect an operand ####################################
		if ( expect ( ( tok.type == ',' or tok.type != ')' ) , MAKE_ERROR ( "Expecting ',' or ')'" ) ) == false )
			return false;
		
		//end parameters #######################################
		if ( tok.type == ')' )
			break;
		
		//get the next token ####################
		GET_TOKEN ( tok )
	}
	
	//expect ) for end of parameter list ####################################
	if ( expect ( ( tok.type == ')' ) , MAKE_ERROR ( "')' for end of parameter list" ) ) == false )
		return false;
	
	//get the next token ####################
	GET_TOKEN ( tok )
		
	//expect { for end of parameter list ####################################
	if ( expect ( ( tok.type == '{' ) , MAKE_ERROR ( "'{' for start of statement list" ) ) == false )
		return false;

	//get the next token ####################
	GET_TOKEN ( tok )
	
	//dumpInstructions ( );
	
	//get the function statement list #########
	while ( ! lc.eofFound and tok.type != '}' )
	{
		
		//while loop #############
		if ( tok.type == WHILE )
		{
			whileLoop ( scope );
		}
		//if statement ############
		else if ( tok.type == IF )
		{
			ifStatementDriver ( scope );

		}
		//possible expression ##############
		else if ( tok.type == '@' or tok.type == '+' or tok.type == '-' or tok.type == IDENTIFIER )
		{
			expression ( scope , result );
		}
		
		else if ( tok.type == STRUCT )
		{
			structDeclaration ( scope );
		}
		
		//declaration #############
		else if ( tok.type == VAR )
		{
			variableDec ( scope );
		}
		else if ( tok.type == RETURN )
		{
			returnStatement ( scope );
		}
		//get the next token ######################
		GET_TOKEN ( tok )
	}
	
	//expect } for end of parameter list ####################################
	if ( expect ( ( tok.type == '}' ) , MAKE_ERROR ( "'}' for start function of statement list" ) ) == false )
		return false;
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: while
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
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool whileLoop ( int scope ) 
{ 
	instruction * loopTest = 0;
	instruction * jumpToTest = 0;
	instruction * jumpOut = 0;
	instruction * endOfLoop = 0;
	symbol * expResult = 0;
	symbol * dummy = 0;
	
	//dumpInstructions ( );
	
	//get the next token ######################
	GET_TOKEN ( tok )
	
	//expect '(' ##########################################
	if ( expect ( ( tok.type == '(' ) , MAKE_ERROR ( "Open brace ( " ) ) == false )
		return false;
	
	//make test label ######################
	loopTest = makeLabel ( scope , "while loop start" );
	endOfLoop = makeLabelDontInsert ( scope );
	
	GET_TOKEN ( tok )
	
	//get the test expression ######################
	if ( expression ( scope , expResult ) == false )
		return false;
	
	//jump to test ####################################
	jumpOut = makeInstruction (  JUMP_TEST_INST , dummy , expResult , 0 , scope );
	
	//expect ')' ##########################################
	if ( expect ( ( tok.type == ')' ) , MAKE_ERROR ( "Closed brace ) " ) ) == false )
		return false;
	
	GET_TOKEN ( tok )

	//expect '(' ##########################################
	if ( expect ( ( tok.type == '{' ) , MAKE_ERROR ( "Open brace { " ) ) == false )
		return false;
		
	//get the loop statement list ##################
	if ( loopStatementList ( scope , loopTest ) == false )
		return false;	
	
	//expect '(' ##########################################
	if ( expect ( ( tok.type == '}' ) , MAKE_ERROR ( "Open brace } " ) ) == false )
		return false;
	
	//jump to test ####################################
	jumpToTest = makeInstruction (  JUMP_INST , loopTest -> equ , 0 , 0 , scope );
	
	addInstructionToList ( endOfLoop );
	
	//backpatch jump out instruction ###########################################
	jumpOut -> equ = endOfLoop -> equ;
	jumpOut = endOfLoop;
	
	return true;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: if
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
* if ( a )
* {
*       s1
* }
* else if  ( b )
* {
*       s2
* }
* else
* {
*       s3
* }
********************************************
* exp ( a );
* jmpl a e1:
*       s1
* jmp out:
*
* e1:
* exp ( b )
* jmp b e2:
*       s2
* jmp out:
*
* e2:
*       s3
* out:
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool ifStatement ( int scope , vector < instruction * > & backpatchList ) 
{ 
	int testLabelId;
	int jumpToTest;
	//int jumpOut;
	symbol * expResult = 0;
	instruction * jmpOut = 0;
	symbol * dummy = 0;
	instruction * endIfJmpOut = 0;
	token tokPeek;
	//vector < instruction * > backpatchList;
	instruction * elseLabel = 0;
	instruction * end = 0;
	
	GET_TOKEN ( tok );
	
	//expect '(' ##########################################
	if ( expect ( ( tok.type == '(' ) , MAKE_ERROR ( "Open brace ( " ) ) == false )
		return false;
	
	GET_TOKEN ( tok )
	
	//get the test expression ######################
	if ( expression ( scope , expResult ) == false )
		return false;
	
	//jump out or next on zero
	jmpOut = makeInstruction ( JUMP_TEST_INST , dummy , expResult , 0 , scope , "if statement start" );

	//expect '(' ##########################################
	if ( expect ( ( tok.type == ')' ) , MAKE_ERROR ( "Closed brace ) " ) ) == false )
		return false;
	
	GET_TOKEN ( tok )

	//expect '(' ##########################################
	if ( expect ( ( tok.type == '{' ) , MAKE_ERROR ( "Open brace { " ) ) == false )
		return false;

	GET_TOKEN ( tok )
		
	//get the loop statement list ##################
	if ( statementList ( scope ) == false )
		return false;	
	
	//GET_TOKEN ( tok )
	
	//expect '}' ##########################################
	if ( expect ( ( tok.type == '}' ) , MAKE_ERROR ( "Open brace } " ) ) == false )
		return false;

	if ( lc.peekToken ( tokPeek ) == false )
		return false;
	
	//if the else keyword is found ###########
	if ( tokPeek.type == ELSE )
	{
		//jump to end for the if statement above #####
		endIfJmpOut = makeInstruction ( JUMP_INST , dummy , 0 , 0 , scope );
		backpatchList.push_back ( endIfJmpOut );//all jump to end of if statements labels need to be backpatched
		
		//label to next test ##################
		elseLabel = makeLabel ( scope );//make the label for the "else if" code
		jmpOut -> jump = elseLabel;//jump to the else
		
		//lc.getToken ( tok );
		GET_TOKEN ( tok ) //get the else out of the stream 
		GET_TOKEN ( tok ) //get the next token
		
		//get the else production ##############
		if ( tok.type == '{' )
		{
			//get the loop statement list ##################
			if ( statementList ( scope ) == false )
				return false;	
				
			//expect '}' ##########################################
			if ( expect ( ( tok.type == '}' ) , MAKE_ERROR ( "Open brace } " ) ) == false )
				return false;
					
			//end = makeLabel ( scope );// end of the if statement 
		}
		//if the token is an IF
		else if ( tok.type == IF )
		{
			ifStatement ( scope , backpatchList );
		}
	}
	else 
	{
		backpatchList.push_back ( jmpOut );
	}
	
	return true;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: variableDec
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
 bool variableDec ( int scope ) 
{ 
	int index;
	int indexValue;
	string name;
	int type;
	string userDefinedType;
	
	//get the return type token ####################
	GET_TOKEN ( tok )
	
	//expect a declaration type ##########################################
	if ( expect ( ( tok.type == BYTE or tok.type == WORD or tok.type == DWORD or tok.type == QWORD or tok.type == TWORD or tok.type == IDENTIFIER ) , "Expecting Memory Type" ) == false )
		return false;
	
	//if this is a user-defined type ########
	if ( tok.type == IDENTIFIER )
	{
		type = typeMap [ tok.lexeme ];
		userDefinedType = tok.lexeme;
	}
	else
	{
		//save type ###########################################	
		type = tok.type;
	}
	
	//get the next token ##################################
	GET_TOKEN ( tok )
	
	//read the declaration #################################
	while ( ! lc.eofFound  )
	{
		//expect '(' ##########################################
		if ( expect ( ( tok.type == IDENTIFIER ) , MAKE_ERROR ( "Variable Identifier" ) ) == false )
			return false;
		
		//save the token lexeme ###############################
		name = tok.lexeme;
		
		//get the next token ##################################
		GET_TOKEN ( tok )
		
		//see if this is an array ################################
		if ( tok.type == '[' )
		{
			//get the next token ##################################
			GET_TOKEN ( tok )
			
			//expect int ##########################################
			if ( expect ( ( tok.type == INT ) , MAKE_ERROR ( "Int Index" ) ) == false )
				return false;
			
			indexValue = stoi ( tok.lexeme );
			
			//expect ']' ##########################################
			if ( expect ( ( tok.type == ']' ) , MAKE_ERROR ( "Array Index Close ]" ) ) == false )
				return false;
		}	
		else 
			indexValue = 1;
		
		//make a new symbol #################
		if ( type >= FIRST_NEW_TYPE )
		{
			symbol * baseStructSymbol = scopes [ scope ].getSymbolByName ( userDefinedType , scope );//get the struct template
			
			//test if struct exists ##############
			if ( baseStructSymbol )
			{
				symbol * clone = scopes [ scope ].cloneSymbol ( baseStructSymbol );//clone the struct for the instance
				clone -> lexeme = name;
				scopes [ scope ].addSymbol ( clone );//add the instance to the scope
			}
			//report error if the struct doesn't exist #####
			else
			{
				REPORT_ERROR ( "Undefined Struct !" );
			}
		}
		else 
		{
			//add the symbol to the table ############################
			scopes [ scope ].addVariable ( name , type  , scope , indexValue , BUILT_IN_CATEGORY );
		}
		
		if ( tok.type == ';' )
			break;
		
		//expect ',' ##########################################
		if ( expect ( ( tok.type == ',' ) , MAKE_ERROR ( "Name Divider , " ) ) == false )
			return false;	

		//get the next token ##################################
		GET_TOKEN ( tok )
	}
	
	//check if the declaration is ended properly....
	if ( tok.type != ';' )
		return false;

	return true;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: basis
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
bool basis ( int scope , symbol *& operand ) 
{ 
	//token tok;
	vector < int > prefixOps;
	symbol * expResult = 0;
	symbol * op = 0;
	symbol * imm = 0;
	token currentOperand;
	int opCode;
	token peek_token;

	//get the prefixes #########################
	while ( (  tok.type == '-' or tok.type == '+' or tok.type == INCREMENT or tok.type == DECREMENT ) )
	{
		prefixOps.push_back ( tok.type );
		
		//get the next token ####################
		GET_TOKEN ( tok )
	}
	
	//expect an operand ####################################
	if ( expect ( ( tok.type == IDENTIFIER or tok.type == INT or tok.type == FLOAT or tok.type == STRING or tok.type == CHAR or isRegister ( tok.type ) ) , "Expecting Variable Identifier" ) == false )
		return false;
	
	//get identifer symbol #################################
	if ( tok.type == IDENTIFIER or isRegister ( tok.type ) )
	{
		//get the symbol for the name token ################
		//operand = getSymbolByName ( tok.lexeme , scope );
		operand = scopes [ scope ].getSymbolByName ( tok.lexeme , scope );
		
		//check if the symbol is defined ###################
		if ( operand == 0 )
		{
			REPORT_ERROR ( "Symbol not defined ")//report an error 
			return false;//should maybe put dummy symbol here 
		}
	}
	// immediate value #####################################
	else 
	{
		//operand = immediateTokenToSymbol  ( tok , scope );
		operand = immediateTokenToSymbol ( tok , scope );
	}
	
	//######################################################
	//evaluate the prefix operators #
	//######################################################
	
	//while we still have prefix ops ##############
	while ( not prefixOps.empty ( ) )
	{
		opCode = prefixOps.back ( );
		prefixOps.pop_back ( );
		//do the negation instruction ##############
		if ( opCode == '-' )
		{
			symbol * s = scopes [ scope ].getTemp ( operand -> type , scope , 0 );
			makeInstruction ( MOVE , s , operand , 0 , scope , "make temp for negation" );
			makeInstruction ( NEG_INST , s , s , 0 , scope );	
			operand = s;
		}
		//pre increment operator ###############
		else if ( opCode == INCREMENT )
			makeInstruction (  PRE_INC_INST , operand ,operand , 0 , scope );
		//post operator operator ###############
		else if ( opCode == DECREMENT )
			makeInstruction (  PRE_DEC_INST , operand , operand , 0 , scope );
	}
	
	//get the next token ###################################
	PEEK_TOKEN ( peek_token )
		
	//see if there's a postfix operator ####################
	if ( peek_token.type == '[' or peek_token.type == '.' or peek_token.type == '(' )
	{
		GET_TOKEN ( tok )
		
		//get the postfix ops ##################################
		while ( tok.type == '[' or tok.type == '.' or tok.type == '(' )
		{
			//array index ########################
			if ( tok.type == '[' )
			{
				GET_TOKEN ( tok )//get next 
				
				//check for expression fail ######################
				if ( expression ( scope , expResult ) == false )
					return false;
				
				//expect ']' ##########################################
				if ( expect ( ( tok.type == ']' ) , MAKE_ERROR ( "Unclosed array index: " ) ) == false )
					return false;
			
				makeInstruction ( ARRAY_INDEX_INST , operand , expResult , 0 , scope , "array index instruction"); //make the array index
				
				//* add array code here 
				GET_TOKEN ( tok );
				
			}
			//struct member operator ############
			else if ( tok.type == '.' )
			{
				int size = operand -> members.size ( );
				
				//get the next token ###################################
				GET_TOKEN ( tok )//get after .
				
				if ( expect ( ( tok.type == IDENTIFIER ) , MAKE_ERROR ( "Variable Identifier" ) ) == false )
					return false;

				//substitute varible for struct member here ##############
				int memberIndex = operand -> findMember ( tok.lexeme );
				
				//check if the member exists ###########################
				if ( memberIndex == -1 )
				{
					REPORT_ERROR ( "Struct member not defined" )
				}
				//if the member is found generate the instruction #########
				else 
				{
					//instruction selection operator #########################
					makeInstruction ( STRUCT_SELECTION , operand , operand -> members [ memberIndex ] , 0 , scope ); //make the array index
					operand = operand -> members [ memberIndex ];
				}
				
				GET_TOKEN ( tok )//leave next token in stream
			}
			//function call ###################
			else if ( tok.type == '(' )
			{
				//get the next token ##############
				GET_TOKEN ( tok )//get after (
				
				if ( expression ( scope , expResult ) == false ) 
					return false;
				
				//make a push instuction ############
				makeInstruction (  PUSH , expResult , 0 , 0 , scope );
				
				//read all the paramters #############
				while ( tok.type == ',' )
				{
					GET_TOKEN ( tok )
					
					//break on end brace ################
					if ( tok.type == ')' )
						break;
					
					//get next expression ###############
					if ( expression ( scope , expResult ) == false ) 
						return false;
				
					//make a push instuction ############
					makeInstruction ( PUSH , expResult , 0 , 0 , scope );
				}
				
				//make a push instuction ############
				makeInstruction ( CALL , operand , 0 , 0 , scope );
				
				//get the closing ')' #######################
				if ( expect ( ( tok.type == ')' ) , MAKE_ERROR ( " )" ) ) != true )
					return false;
				
				GET_TOKEN ( tok )
			}
			//add post increment operator ##############
			else if ( tok.type == INCREMENT )
			{
				addDelayedInstruction ( POST_INC_INST , operand ,operand , 0 , scope );
				GET_TOKEN ( tok )
			}
			//add post decrement operator ##############
			else if ( tok.type == DECREMENT )
			{
				addDelayedInstruction ( POST_INC_INST , operand ,operand , 0 , scope );
				GET_TOKEN ( tok )
			}
		}
	}
	else 
	{
		GET_TOKEN ( tok )
	}

	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: expect
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
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
inline bool expect ( bool result , string what ) 
{ 
	//the input is correct , continue ######################
	if ( result == true )
		return true;
	
	//bad input #############################################
	else
	{
		gerrors.push_back ( "Parser Error: Expecting: " + what ); 
		token tok;
	
		//Find the start of a new production ##########
		lc.getToken ( tok );
		
		//eat the bad input ############################
		while ( ! lc.eofFound && tok.lexeme != ";" )
			lc.getToken ( tok );
	
		return false;
	}
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: parse
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
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool statementList ( int scope )
{ 
	
	symbol * result;
	
	//get the function statement list #########
	while ( ! lc.eofFound and tok.type != '}' )
	{
		//while loop #############
		if ( tok.type == WHILE )
		{
			whileLoop ( scope );
		}
		//if statement $$$$$$$$$$$$
		else if ( tok.type == IF )
		{
			ifStatementDriver ( scope );

		}
		//identifier ##############
		else if ( tok.type == IDENTIFIER or isRegister ( tok.type ) )
		{
			expression ( scope , result );
		}
		
		//declaration #############
		else if ( tok.type == VAR )
		{
			variableDec ( scope );
		}
		else if ( tok.type == STRUCT )
		{
			structDeclaration ( scope );
		}
		else if ( tok.type == RETURN )
		{
			returnStatement ( scope );
		}
		//get the next token ######################
		GET_TOKEN ( tok )
	}
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: expression
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
bool expression ( int scope , symbol *& operand ) 
{ 
	vector < symbol * > operands;
	vector < int > operators;
	symbol * c_operand = 0 , * lhs = 0 , * rhs = 0 , * result = 0 , * storage = 0 , * accumulator = 0;
	int countOfCalculations = 0 , op;
	bool outOfOperands = false;
	
	//get an operand ########################
	if ( basis ( scope , c_operand ) == false )
		return false;
	
	//put the operand on the stack ###########
	result = c_operand;
	
	if ( tok.type == '=' )
	{
		accumulator = c_operand; //default return
	}
	else
	{
		accumulator = scopes [ scope ].getTemp ( INT , scope , 0 );
		operands.push_back ( c_operand );
	}
	
	//while not at the end of the expression @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	while ( tok.type == '+' or tok.type == '-' or tok.type == '*' or tok.type == '\\' or tok.type == AND or tok.type == '=' or
			  tok.type == LOGICAL_EQ or tok.type == GREAT_EQ or tok.type == LESS_EQ or tok.type == NOT_EQ or
			  tok.type == '>' or tok.type == '<' )
	{	//get the operator #######################
		op = tok.type;
		GET_TOKEN ( tok )
		
		if ( basis ( scope , c_operand ) == false )
			return false;
		
		//operands.push_back ( c_operand ); //----------------------------
		//#####################################################################		
		//Check if higher priority calculations need to be done first #########################
		//#####################################################################
		while ( operands.size ( ) >  0 and operators.size ( ) > 0 and opPrec [ op ] <= opPrec [ operators.back ( ) ] ) //number of operators = operands - 1
		{   //get the operands ##################
			if ( countOfCalculations ++ == 0 )
			{
				makeInstruction ( MOVE , accumulator , operands.back ( ) , 0 , scope , "expression start" );
				operands.pop_back ( );
				continue;
			}
						
			//make the instruction ##############
			makeInstruction ( operators.back ( ) , accumulator , operands.back ( ) , accumulator ,scope );
			operands.pop_back ( );
			operators.pop_back ( );
		}
		
		//else put the operator on the stack ########
		operators.push_back ( op );
		operands.push_back ( c_operand );
	} //end of main expression loop #########################
	
	//###############################################################
	//calculate the rest of the stack if it's not empty #############
	//###############################################################
	if ( operators.size ( ) > 0 and operands.size ( ) > 0 )
	{
		//see if we need a move instruction #
		if ( countOfCalculations ++ == 0 )
		{
			makeInstruction ( MOVE , accumulator , operands.back ( ) , 0 , scope , "expression start" );
			operands.pop_back ( );
		}

		if ( operands.size ( ) > 0 and operators.size ( ) >  0 )
		{
			do {	//make the instruction ##############
					makeInstruction ( operators.back ( ) , accumulator , operands.back ( ), accumulator , scope );
					operands.pop_back ( );
					operators.pop_back ( );

					//no operators left #################
					if ( operators.size ( ) == 0 or operands.size ( ) == 0 )
					{
						result = accumulator;
						break;
					}
	
			} while ( 1 );
		}
	}
	
	operand = result; //save the result ##########
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: expectTok
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
* Comments: compare a token against a number of possible matches 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
template < typename T, typename... Args >
bool expectTok ( T & tok , string error , const Args... args ) 
{
	//get the next token ###################################
	if ( lc.getToken ( tok ) == false )
	{
		gerrors.push_back ( "Error getting next token (expectTok): " + __LINE__ ); 
		
		return false;
	}

	//match token against all possible acceptable token types ########
	//bool typeMatches = ( false || ... || ( tok.type == args ) );
	bool typeMatches = ( ( tok.type == args ) || ... );
	
	//no tokens matched the input , eat tokens until start of new production ####
	if ( typeMatches == false )
	{
		//Find the start of a new production ##########
		lc.getToken ( tok );
		
		//eat the bad input ############################
		while ( ! lc.eofFound && tok.lexeme != ";" )
			lc.getToken ( tok );
	
		return false;
	}
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: functionCall
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
bool prototype ( ) 
{ 
	//token tok;
	token returnTok;
	int scope = 0;
	symbol * result;
	symbol parameter;
	
	symbol * functionName;
	int functionID;
	symbol * functionSymbol = 0;
	
	//get the return type token ####################
	GET_TOKEN ( tok )
	
	returnTok.copy ( tok );
	
	//get identifer symbol #################################
	if ( expect ( ( returnTok.type == BYTE or returnTok.type == WORD or returnTok.type == DWORD or returnTok.type == QWORD or returnTok.type == TWORD ) , "Expecting Memory Type" ) == false )
	{
		return false;
	}
	
	//get the next token ####################
	GET_TOKEN ( tok )
	
	//this part is wrong , should create new function 
	//get identifer symbol #################################
	if ( expect ( ( tok.type == IDENTIFIER ) , MAKE_ERROR ( "Function Name ( identifier ) " ) ) != true )
	{
		return false;
	}
	
	symbol * s;
	
	s = scopes [ 0 ].getSymbolByName ( tok.lexeme , 0 );
	
	//make sure the function name isn't defined#################
	if ( s != 0 )
	{
		REPORT_ERROR ( tok.lexeme + " is already defined , need a original function name !!!" )
		return false;
	}
	
	//make a new symbol for the function in the 0 scope ############
	functionSymbol = scopes [ 0 ].addVariable ( tok.lexeme , FUNCTION , 0 , 0 , FUNCTION_CATEGORY ); //put the function in the symbol table

	//create a new scope ##################
	scope = addScope ( tok.lexeme , FUNCTION );

	//set the functions scope so it can be found ###############
	functionSymbol -> scope = scope;
	
	//initialize the scope ################
	scopes [ scope ].initialize ( tok.lexeme , FUNCTION , scope , 0 ); //initialize the scope
	scopes [ scope ].returnType = returnTok.type; //set the function return type

	//get the next open bracket ( ####################
	GET_TOKEN ( tok )
	
	//expect an operand ####################################
	if ( expect ( ( tok.type == '(' ) , MAKE_ERROR ( "'(' " ) ) == false )
		return false;
	
	//get the next token ####################
	GET_TOKEN ( tok )
	
	//get the function parameter ##################
	//we're doing call by name , just an identifier for a paramter.
	while ( ! lc.eofFound and tok.type == IDENTIFIER )
	{
		//add the parameter @###############
		scopes [ scope ].addParameter ( tok.lexeme , NAME , scope , 0  );
		
		//get the next token ####################
		GET_TOKEN ( tok )
		
		//expect an operand ####################################
		if ( expect ( ( tok.type == ',' or tok.type == ')' ) , MAKE_ERROR ( "',' or ')'" ) ) == false )
			return false;
		
		//end parameters #######################################
		if ( tok.type == ')' )
			break;
		
		//get the next token ####################
		GET_TOKEN ( tok )
	}
	
	//expect ) for end of parameter list ####################################
	if ( expect ( ( tok.type == ')' ) , MAKE_ERROR ( "')' for end of parameter list" ) ) == false )
		return false;
	
	//get the next token ####################
	GET_TOKEN ( tok )
		
	//expect { for end of parameter list ####################################
	if ( expect ( ( tok.type == ';' ) , MAKE_ERROR ( " ';' for end of prototype" ) ) == false )
		return false;
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: ifStatementDriver
*
* Parameters:  vector < instruction > & backpatchList
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
bool  ifStatementDriver ( int scope )
{
	vector < instruction * >  backpatchList;
	bool result;
	instruction * end;
	
	//call the if statement handler #################
	result = ifStatement ( scope , backpatchList );
	
	end = makeLabel ( scope );// end of the if statement 
	
	//if there are items to backpatch ##################
	if ( backpatchList.size ( ) > 0 )
	{	
		//backpatch the end jumps #######################
		for ( auto i : backpatchList )
		{
			i -> jump = end;
		}
	}
	
    return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: structDeclaration
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
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool structDeclaration ( int scope ) 
{ 
	int type;
	string name;
	int indexValue;
	symbol * s;
	symbol * newType;
	
	//get struct token ####################
	GET_TOKEN ( tok )
	
	//expect '{' ##########################################
	if ( expect ( ( tok.type == IDENTIFIER ) , MAKE_ERROR ( "struct name" ) ) == false )
		return false;
		
	//allocate the memory ############################
	newType = ( symbol * ) das.allocate ( sizeof ( symbol ) );
	newType -> initialize ( tok.lexeme , STRUCT , scope , 0 , STRUCT_CATEGORY );

    GET_TOKEN ( tok )
    
    //expect ']' ##########################################
	if ( expect ( ( tok.type == '{' ) , MAKE_ERROR ( "{ for struct" ) ) == false )
			return false;
			
	GET_TOKEN ( tok )
	
	//read the declaratio ###########################
	while ( tok.type != '}' )
	{
		//expect a declaration type ##########################################
		if ( expect ( ( tok.type == BYTE or tok.type == WORD or tok.type == DWORD or tok.type == QWORD or tok.type == TWORD ) , "Expecting Memory Type" ) == false )
			return false;
		
		//save type ###########################################	
		type = tok.type;
		
		//get the next token ##################################
		GET_TOKEN ( tok )

		//expect '(' ##########################################
		if ( expect ( ( tok.type == IDENTIFIER ) , MAKE_ERROR ( "Expecting Variable Identifier" ) ) == false )
			return false;
		
		//save the token lexeme ###############################
		name = tok.lexeme;
		
		//get the next token ##################################
		GET_TOKEN ( tok )
		
		//see if this is an array ################################
		if ( tok.type == '[' )
		{
			//get the next token ##################################
			GET_TOKEN ( tok )
			
			//expect int ##########################################
			if ( expect ( ( tok.type == INT ) , MAKE_ERROR ( "Int Index" ) ) == false )
				return false;
			
			indexValue = stoi ( tok.lexeme );
			
			//expect ']' ##########################################
			if ( expect ( ( tok.type == ']' ) , MAKE_ERROR ( "Array Index Close ]" ) ) == false )
				return false;
		}	
		else 
			indexValue = 1;
		
		//allocate the memory ############################
		s = ( symbol * ) das.allocate ( sizeof ( symbol ) );
		
		//initialize the symbol and add it to the type member list ####
		s -> initialize ( name , type , scope , indexValue , BUILT_IN_CATEGORY );
		newType -> members.push_back ( s );

		if ( expect ( ( tok.type == ';' ) , MAKE_ERROR ( " ;" ) ) == false )
			return false;

		//get the next token ##################################
		GET_TOKEN ( tok )
	}
	
	//add a new type #######################
	addNewType ( newType -> lexeme );
	
	//add the scope to the table ##########
	scopes [ scope ].addSymbol ( newType );
	
	//check if the closing brace is there ###########
	if ( expect ( ( tok.type == '}' ) , MAKE_ERROR ( " }" ) ) == false )
		return false;

	return true;
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: jumpStatements
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
* Comments: for return statements , continue , break
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool returnStatement ( int scope ) 
{
	symbol * result;
	
	//get struct token ####################
	GET_TOKEN ( tok )
	
	//if this is an empty return ############
	if ( tok.type == ';' )
	{
		makeInstruction ( RETURN_STATEMENT , 0 , 0 , 0, scope );//make empty return statement
	}
	//if this returns an expression #################################
	else if ( tok.type == '-' or tok.type == '+' or tok.type == INCREMENT or tok.type == DECREMENT or tok.type == IDENTIFIER or isRegister ( tok.type ) ) 
	{
		//if the expression parses correctly #########################
		if ( expression ( scope , result ) == true )
		{
			makeInstruction ( RETURN_STATEMENT , result , 0 , 0, scope ); //make the return value function 
		}
	}
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: parse
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
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool loopStatementList ( int scope , instruction * testLabel )
{ 
	symbol * result;
	
	//get the function statement list #########
	while ( ! lc.eofFound and tok.type != '}' )
	{
		//while loop #############
		if ( tok.type == WHILE )
		{
			whileLoop ( scope );
		}
		//if statement $$$$$$$$$$$$
		else if ( tok.type == IF )
		{
			ifStatementDriver ( scope );

		}
		//identifier ##############
		else if ( tok.type == IDENTIFIER or isRegister ( tok.type ) )
		{
			expression ( scope , result );
		}
		
		//declaration #############
		else if ( tok.type == VAR )
		{
			variableDec ( scope );
		}
		else if ( tok.type == STRUCT )
		{
			structDeclaration ( scope );
		}
		else if ( tok.type == RETURN )
		{
			returnStatement ( scope );
		}
		else if ( tok.type == CONTINUE )
		{
			continueStatement ( scope , testLabel );
		}
		//get the next token ######################
		GET_TOKEN ( tok )
	}
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: continueStatement
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
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool continueStatement ( int scope , instruction * testLabel )
{ 
	//get struct token ####################
	GET_TOKEN ( tok )
	
	//if this is an empty return ############
	if ( tok.type == ';' )
	{
		makeInstruction ( CONTINUE , 0 , 0 , 0, scope );//make empty return statement
	}

	return true;
}