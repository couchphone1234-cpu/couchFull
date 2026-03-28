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
* Program Shell Generated At: 4:18:19 a.m.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/



//################################### GLOBAL DATA ###################################



//##################################################################################





/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: initializeSymbolTable
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
bool initializeSymbolTable ( ) 
{

	addScope ( "global" , FUNCTION );
	
	scopes [ 0 ].addVariable ( "ah" , AH , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "al" , AL , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "ax" , AX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "bh" , BH , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "bl" , BL , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "bp" , BP , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "bpl" , BPL , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "bx" , BX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "ch" , CH , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "cl" , CL , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "cx" , CX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "dh" , DH , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "di" , DI , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "dl" , DL , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "dx" , DX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "eax" , EAX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "ebp" , EBP , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "ebx" , EBX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "ecx" , ECX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "edi" , EDI , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "edx" , EDX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "esi" , ESI , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "esp" , ESP , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r10" , R10 , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r10b" , R10B , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r10d" , R10D , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r10w" , R10W , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r11" , R11 , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r11b" , R11B , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r11d" , R11D , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r11w" , R11W , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r12" , R12 , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r12b" , R12B , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r12d" , R12D , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r12w" , R12W , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r13" , R13 , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r13b" , R13B , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r13d" , R13D , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r13w" , R13W , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r14" , R14 , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r14b" , R14B , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r14d" , R14D , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r14w" , R14W , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r15" , R15 , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r15b" , R15B , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r15d" , R15D , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r15w" , R15W , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r8" , R8 , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r8b" , R8B , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r8d" , R8D , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r8w" , R8W , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r9" , R9 , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r9b" , R9B , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r9d" , R9D , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "r9w" , R9W , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "rax" , RAX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "rbp" , RBP , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "rbx" , RBX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "rcx" , RCX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "rdi" , RDI , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "rdx" , RDX , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "rsi" , RSI , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "rsp" , RSP , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "si" ,  SI , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "sil" , SIL , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "sp" ,  SP , 0 , 0 , REGISTER_CATEGORY );
	scopes [ 0 ].addVariable ( "main" , FUNCTION , 0 , 0 , FUNCTION_CATEGORY );
	
	addScope ( "main" , FUNCTION );
	
	//##############################################
	//operator precedence ##########################
	//##############################################
	opPrec [ '*' ] = 4;                                                                                                                                          
	opPrec [ '\\' ] = 4;                                                                                                                                            
	opPrec [ '%' ] = 4;
	
	opPrec [ '-' ] = 3;                                                                                                                                         
	opPrec [ '+' ] = 3; 
	
	opPrec [ AND ] = 2;                                                                                                                                       
	opPrec [ LOGICAL_EQ ] = 2;                                                                                                                                    
	opPrec [ GREAT_EQ ] = 2;
	opPrec [ LESS_EQ ] = 2;
	opPrec [ SHIFT_LEFT ] = 2; 
	opPrec [ SHIFT_RIGHT ] = 2;
	opPrec [ GREATER_THAN ] = 2;
	opPrec [ LESS_THAN ] = 2;
	opPrec [ EQUALS ] = 2;
	
	opPrec [ '=' ] = 1;
	
	//###############################################
	//Type Size #####################################
	//###############################################
	
	dataSize [ BYTE ] = 1;
	dataSize [ WORD ] = 2;
	dataSize [ DWORD ] = 4;
	dataSize [ QWORD ] = 8;
	dataSize [ TWORD ] = 10;
	dataSize [ FUNCTIONS ] = 0;
	dataSize [ STRUCT ] = 0;
	dataSize [ REGISTER ] = 0;
	dataSize [ AH ] = 1;
	dataSize [ AL ] = 1;
	dataSize [ AX ] = 2;
	dataSize [ BH ] = 1;
	dataSize [ BL ] = 1;
	dataSize [ BP ] = 2;
	dataSize [ BPL ] = 1;
	dataSize [ BX ] = 2;
	dataSize [ CH ] = 1;
	dataSize [ CL ] = 1;                                                                                                                                        
	dataSize [ CX ] = 2;                                                                                                                                       
	dataSize [ DH ] = 1;                                                                                                                                       
	dataSize [ DI ] = 2;                                                                                                                                      
	dataSize [ DL ] = 1;                                                                                                                                          
	dataSize [ DX ] = 2;                                                                                                                                       
	dataSize [ EAX ] = 4;                                                                                                                                       
	dataSize [ EBP ] = 4;                                                                                                                                     
	dataSize [ EBX ] = 4;                                                                                                                                       
	dataSize [ ECX ] = 4;                                                                                                                                       
	dataSize [ EDI ] = 4;                                                                                                                                      
	dataSize [ EDX ] = 4;                                                                                                                                      
	dataSize [ ESI ] = 4;                                                                                                                                       
	dataSize [ ESP ] = 4;                                                                                                                                      
	dataSize [ R10 ] = 8;                                                                                                                                       
	dataSize [ R10B ] = 1;                                                                                                                                      
	dataSize [ R10D ] = 4;                                                                                                                                     
	dataSize [ R10W ] = 2;                                                                                                                                      
	dataSize [ R11 ] = 8;
	dataSize [ R11B ] = 1;
	dataSize [ R11D ] = 4;
	dataSize [ R11W ] = 2;
	dataSize [ R12 ] = 8;
	dataSize [ R12B ] = 1;
	dataSize [ R12D ] = 4;
	dataSize [ R12W ] = 2;
	dataSize [ R13 ] = 8;
	dataSize [ R13B ] = 1;
	dataSize [ R13D ] = 4;
	dataSize [ R13W ] = 2;
	dataSize [ R14 ] = 8;
	dataSize [ R14B ] = 1;
	dataSize [ R14D ] = 4;
	dataSize [ R14W ] = 2;
	dataSize [ R15 ] = 8;
	dataSize [ R15B ] = 1;
	dataSize [ R15D ] = 4;
	dataSize [ R15W ] = 2;
	dataSize [ R8 ] = 8;
	dataSize [ R8B ] = 1;
	dataSize [ R8D ] = 4;
	dataSize [ R8W ] = 2;
	dataSize [ R9 ] = 8;
	dataSize [ R9B ] = 1;
	dataSize [ R9D ] = 4;
	dataSize [ R9W ] = 2;
	dataSize [ RAX ] = 8;
	dataSize [ RBP ] = 8;
	dataSize [ RBX ] = 8;
	dataSize [ RCX ] = 8;
	dataSize [ RDI ] = 8;
	dataSize [ RDX ] = 8;
	dataSize [ RSI ] = 8;
	dataSize [ RSP ] = 8;
	dataSize [ SI ] = 2;
	dataSize [ SIL ] = 1;
	dataSize [ SP ] = 2;
	
	return true;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
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
* Comments:
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
symbol * immediateTokenToSymbol ( token & tok , int scope )
{
	symbol * operand;
	string name = "immediate";
	
	name += to_string ( imNum ++ );
	
	//allocate the memory ############################
	operand = ( symbol * ) das.allocate ( 3 );
	
	//check the allocation ###########################
	if ( operand == 0 )
		return 0;
	
	operand -> lexeme = name;
	
	//immediate int ##########
	if ( tok.type == INT )
	{
		operand -> ivalue = stoi ( tok.lexeme );
		operand -> type = INT;
	}
	//immediate float ##############
	else if ( tok.type == FLOAT )
	{
		operand -> ivalue = stof ( tok.lexeme );
		operand -> type = FLOAT;
	}
	//immediate string or char
	else if ( tok.type = STRING )
	{
		operand -> svalue = tok.lexeme;
		operand -> type = STRING;
	}
	//immediate string or char
	else if ( tok.type = CHAR )
	{
		operand -> svalue = tok.lexeme;
		operand -> type = CHAR;
	}

	//add variable to the scope #########
	//int varId = scopes [ scope ].addVariable ( operand );
	
	//return the symbol ##################
	//sym = & scopes [ scope ].variables [ varId ];
	
	return operand;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: addScope
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
int addScope ( string name , int type )
{ 
	int scopeNumber = scopes.size ( ); //get the first empty scope 
	scope s;

	s.initialize ( name , type , scopeNumber , 0 );//initialize the scope 

	//add the scope to the vector #########################
	scopes.push_back ( s );

	return scopeNumber;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: getScope
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
int getScope ( string name )
{
	int i = 0;
	int numberScopes = scopes.size ( );
	
	//find the scope ****************************
	while ( i < numberScopes )
	{
		//if the scope exists , return it ########
		if ( scopes [ i ].lexeme == name )
			return i;
		
		i ++;
	}
	
	return - 1;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: addScope
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
bool dumpScopes ( )
{ 
	int numScopes = scopes.size ( );
	int i = 0;
	
	while ( i < numScopes )
	{
		cout << "Scope: " << scopes [ i ].lexeme << " scope number: " << scopes [ i ].varNum  << "*****************************" << endl;
	
		cout << "variables *************************" << endl;
		
		int j = 1;
		
		for ( auto v : scopes [ i ].variables )
		{
			cout << j ++ << " " << scopes [ i ].lexeme << " ***************" << endl;
			cout << * v << endl;
		}
		
		i ++;
	}
	
	return true;
}
