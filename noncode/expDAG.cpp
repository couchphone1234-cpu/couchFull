//DAG tree node ##############
struct node
{
	int type;
	
	node * lhs = 0;
	node * rhs = 0;
	node * leaf = 0;
	node * result = 0;
	
	bool addExpression ( int type_in , node * lhs_in , node * rhs_in )
	{
		type = type_in;
		lhs = lhs_in;
		rhs = rhs_in;
		return true;
	}
	
	bool operand ( node * op )
	{
		type = INDENTIFIER;
		lhs = op;
	};
};

	bool generate3AC DAG (  node * expDAG  );

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
	vector < node * > treeNodes;
	map < string , node * > expMap;
	string key;
	string strOp;
	
	//get an operand ########################
	if ( basis ( scope , c_operand ) == false )
		return false;
	
	//put the operand on the stack ###########
	result = c_operand;
	
	//while not at the end of the expression @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	while ( tok.type == '+' or tok.type == '-' or tok.type == '*' or tok.type == '/' or tok.type == AND or tok.type == '=' or
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
		while ( operands.size ( ) >  1 and operators.size ( ) > 0 and opPrec [ op ] < opPrec [ operators.back ( ) ] ) //number of operators = operands - 1
		{   			
			node * lhs = treeNodes.back ( ); treeNodes.pop_back ( );
			node * rhs = treeNodes.back ( ); treeNodes.pop_back ( );
			node * newExp = nas.allocate ( );
			int stackOp = operators.back ( );
			
			//make the expression key #####################
			if ( stackOp < 127 )
				key = makeStringKey ( lhs ) + to_string ( stackOp ) + makeStringKey ( rhs );
			else 
				key = makeStringKey ( lhs ) + IDToKeywords [ stackOp ] + makeStringKey ( rhs );
				
			//if the key isn't in the map , just build the node #########
			if ( expMap.find ( key ) == expMap.end ( ) )
			{
				//push the result back on the stack #############
				treeNodes.push_back ( newExp.addExpression ( operators.back ( ) , lhs , rhs ) );
			}
			//if the key is in the map , use a calculation that's already done ****
			else 
			{
				treeNodes.push_back ( newExp.addOperand ( expMap.find ( key ) ) );
			}
			
			//treeNodes.pop_back ( );
			operators.pop_back ( );
		}
		
		//else put the operator on the stack ########
		operators.push_back ( op );
		node * newLeaf = nas.allocate ( );
		treeNodes.push_back ( newLeaf.operand ( c_operand ) );
	} //end of main expression loop #########################
	
	//###############################################################
	//calculate the rest of the stack if it's not empty #############
	//###############################################################
	if ( operators.size ( ) > 0 and operands.size ( ) > 0 )
	{
		if ( operands.size ( ) > 0 and operators.size ( ) >  0 )
		{
			do {	//make the instruction ##############
					node * lhs = treeNodes.back ( ); treeNodes.pop_back ( );
					node * rhs = treeNodes.back ( ); treeNodes.pop_back ( );
					
					//push the result back on the stack #############
					treeNodes.push_back ( newExp.addExpression ( operators.back ( ) , lhs , rhs ) );

					operators.pop_back ( );//pop the back of the operator stack
					
					//no operators left #################
					if ( operators.size ( ) == 0 or operands.size ( ) == 1 )
						break;
			} while ( 1 );
		}
	}
	
	//generate the DAG code #####################
	generate3AC DAG (  node * expDAG  );
	
	operand = result; //save the result ##########
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: valueNumberOptimization
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
string makeStringKey ( symbol * s  ) 
{ 
	string key;
	
	key += ( char ) s -> id;
	key += '.';
	key += ( char ) s -> scope;
	key += '.';
	key += ( char ) s -> type;

	return key ;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: DAG
*
* Parameters:  node * expDAG 
*
* Modifications: 
*
*
*
*
*
* Returns: bool generate3AC
*
* Comments: returns expression result.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
node * generate3AC DAG (  node * expDAG  ) 
{ 



	return
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: treeTo3AC
*
* Parameters:  node * expDAG 
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
bool treeTo3AC (  node * expDAG  ) 
{ 



	return
}


