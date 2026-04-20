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


//################################### GLOBAL DATA ###################################

	token tok;
	struct instruction;
	
	//postfix operators ############
	const int STRUCT_SELECT = 1;
	const int FUNC_CALL = 2;
	const int POST_DEC = 3;
	const int POST_INC = 4;
	
	//for postix operators 
	struct postfix
	{
		vector < string > params; //for function parameters 
		int type; //type of postfix operators
	};
	
	//#######################################
	//get token macro #######################
	//#######################################
	#define GET_TOKEN(t)\
	{\
		if ( lc.getToken ( t ) == false )\
			return false;\
	}
	
	#define PEEK_TOKEN(t)\
	{\
		if ( lc.peekToken ( t ) == false )\
			return false;\
	}
	
	//try macro ###############################
	#define _try(e)\
	{\
		if ( ( e ) )\
			return false;\
	}
	
	#define _expect(t,m)\
	{\
		if ( expect ( ( t ) , m ) == false )\
		return false;\
	}
	
	//function call struct ##############
	struct functionCall
	{
		instruction * returnLabel;//return label node
	};
	
	//call stack ########################
	vector < functionCall > callStack;
	
	
	//type ########################
	const int LEAF = -1;
	
	//DAG tree node ##############
	struct node
	{
		int type;
		
		node * lhs = 0;
		node * rhs = 0;
		symbol * equ = 0;
		
		node * addExpression ( int type_in , node * lhs_in , node * rhs_in , symbol * equ_in )
		{
			type = type_in;
			lhs = lhs_in;
			rhs = rhs_in;
			equ = equ_in;
			return this;
		};
		
		node * operand ( symbol * op )
		{
			type = IDENTIFIER;
			equ = op;
			lhs = 0;
			rhs = 0;
			return this;
		};
	};
	

//##################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
	bool parse ( string sourceFile ); 
	bool function ( );
	bool whileLoop ( int scope ); 
	bool ifStatement ( int scope , vector < instruction > & backpatchList ); 
	bool variableDec ( int scope  ); 
	//bool expression ( int scope , symbol & operand );
	inline bool expect ( bool result , string what );
	bool statementList ( int scope );
	bool basis ( int scope , symbol *& operand );
	bool expression ( int scope , symbol *& operand );
	template < typename T, typename... Args >
	bool expectTok ( T & tok , string error , const Args... args ); 
	bool prototype (  );
	bool ifStatementDriver ( int scope );
	bool structDeclaration ( int scope );
	bool returnStatement ( int scope );
	bool loopStatementList ( int scope , instruction * testLabel , instruction * endLabel );
	bool continueStatement ( int scope , instruction * testLabel );
	bool brakeStatement ( int scope , instruction * endLoopLabel );
	
	//DAG expression function ######################
	bool expressionDAG ( int scope , symbol *& operand );
	string makeStringKeyDAG ( symbol * s  ) ;
	symbol * generate3AC_DAG (  node * expDAGTree , symbol * accumulator ,  int scope  ); 
	node * treeTo3AC (  node * expDAG , symbol * accumulator , int scope );
	bool printTreenodeStack (  vector < node * > & sourceTree , int & recursionLevel );
	bool printNode (  node * n , int recursionLevel );
	
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



