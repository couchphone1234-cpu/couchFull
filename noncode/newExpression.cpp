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
	symbol * c_operand = 0;
	symbol * lhs = 0;
	symbol * rhs = 0;
	symbol * result = 0;
	symbol * storage = 0;
	int op;
	
	//get an operand ########################
	if ( basis ( scope , c_operand ) == false )
		return false;
	
	//put the operand on the stack E###########
	operands.push_back ( c_operand );

	result = c_operand; //default return
	
	
	
	//while not at the end of the expression @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	while ( tok.type == '+' or tok.type == '-' or tok.type == '*' or tok.type == '\\' or tok.type == AND or tok.type == '=' or
			  tok.type == LOGICAL_EQ or tok.type == GREAT_EQ or tok.type == LESS_EQ or tok.type == NOT_EQ
			  or tok.type == GREATER_THAN or tok.type == LESS_EQ )
	{
		
		//get the operator #######################
		op = tok.type;	
		//operators.push_back ( tok.type );
		
		//get the next token after operator ##################################
		GET_TOKEN ( tok )
		
		//get an operand ########################
		if ( basis ( scope , c_operand ) == false )
			return false;
		
		operands.push_back ( c_operand );
				
		//save the operand #########################
		if ( operators.size ( ) > 0 )
		{
			//get the operator #########################
			int top = operators.back ( ); //
			
			if ( top == '=' )
				storage = operands.back ( );
			
			//if the operators is higher precedence than the top of stack do the operation #######
			while ( opPrec [ op ] < opPrec [ top ] )
			{
				//must have at least operands ##########
				if ( operands.size ( ) > 1 )
				{
					//get the operands ##################
					rhs = operands.back ( );//get rhs
					operands.pop_back ( );
					lhs = operands.back ( );//get lhs
					operands.pop_back ( );
					
					//make the instruction ##############
					makeInstructionRet ( tok.type , result , lhs , rhs ,scope );
					operands.push_back ( result );
				}
				
				//get the next operand ##################
				operators.pop_back ( );
				int top = operators.back ( );
			}
			
			operators.push_back ( tok.type );
			
		}
		//else put the operator on the stack ########
		else 
			operators.push_back ( tok.type );
	}
	
	//calculate the rest of the stack if it's not empty #############
	if ( operators.size ( ) > 0 )
	{
		assert ( operands.size ( )>= 2 );
		assert ( operators.size ( ) == operands.size ( ) - 1  );
		
		//get the operands ##################
		rhs = operands.back ( );//get rhs
		operands.pop_back ( );
		lhs = operands.back ( );//get lhs
		operands.pop_back ( );
		
		//get the operator ##################
		op = operators.back ( );
		operators.pop_back ( );
		
		//do the calculations @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		
		do {
				//make the instruction ##############
				makeInstruction ( op , result , lhs , rhs , scope );
				
				if ( operands.size ( ) > 0 )
				{
					//get the next operand ##########
					lhs = operands.back ( );
					operands.pop_back ( );
					
					//get the next operator #########
					op = operators.back ( );
					operators.pop_back ( );
				}
				//no operators left #################
				else 
					break;
				
				//save the instruction result #######
				rhs = result;
				
				dumpInstructions ( );
			
		} while ( 1 );
	}
	
	operand = result; //save the result ##########
	
	return true;
}