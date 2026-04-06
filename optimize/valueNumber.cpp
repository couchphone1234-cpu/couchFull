/*********************************************************************************
*
* File Name: "valueNumberOptimization.cpp"
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
* Program Shell Generated At: Sun Apr 05 19:28:30 2026
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


	using namespace std;

//################################### GLOBAL DATA ###################################


//##################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	bool valueNumberOptimization (   ); 
	string makeStringKey ( symbol * s  );


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




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
bool valueNumberOptimization ( ) 
{ 
	int numberOfInstructions = instVec.size ( );
	int i = 0;
	int valueNumber = 0;
	map < string , int > valueMap;
	map < int , symbol * > valueToSymbolMap;
	
	//process all the instructions @@@@@@@@@@@@@@@@@@@@
	while ( i < numberOfInstructions )
	{
		//process variable operators ###################
		if ( isOperator ( instVec [ i ] -> type ) )
		{
			
			string lhsKey = makeStringKey ( instVec [ i ] -> lhs );
			string rhsKey = makeStringKey ( instVec [ i ] -> rhs );
			
			//see if the value is in the value map ############
			if ( valueMap.find ( lhsKey ) == valueMap.end ( ) )
			{
				valueMap [ lhsKey ] = valueNumber;
				valueToSymbolMap [ valueNumber ] = instVec [ i ] -> lhs;
				valueNumber ++;
			}
			//see if the value is in the value map ############
			if ( valueMap.find ( rhsKey ) == valueMap.end ( ) )
			{
				valueMap [ lhsKey ] = valueNumber;
				valueToSymbolMap [ valueNumber ] = instVec [ i ] -> rhs;
				valueNumber ++;
			}
		
			string op; op += ( char ) instVec [ i ] -> type;
			string expKey = lhsKey + op + rhsKey;
			string expKeyRev = rhsKey + op + lhsKey;
			
			//check if the expression is in the table ####
			if ( valueMap.find ( expKey ) == valueMap.end ( ) )
			{
				valueMap [ expKey ] = valueNumber;
				
				string equKey = makeStringKey ( instVec [ i ] -> equ );
				valueMap [ equKey ] = valueNumber;
				valueToSymbolMap [ valueNumber ] = instVec [ i ] -> equ;
				valueNumber ++;
			}
			//add the replacement value for the number ###
			else
			{
				int valueNumberForExpression = valueMap [ expKey ];
				symbol * s = valueToSymbolMap [ valueNumberForExpression ];
				
				//set the new assignment equ = valueSymbol;
				if ( s != 0 )
				{
					instVec [ i ] -> type = '=';
					instVec [ i ] -> rhs = 0;
					instVec [ i ] -> lhs = s;
				}
				else 
				{
					gerrors.push_back ( MAKE_ERROR ( "Value number missing" ) );
				}
			}
			//check if the expression is in the table ####
			if ( valueMap.find ( expKeyRev ) == valueMap.end ( ) )
			{
				valueMap [ expKeyRev ] = valueNumber;
				
				string equKey = makeStringKey ( instVec [ i ] -> equ );
				valueMap [ equKey ] = valueNumber;
				valueToSymbolMap [ valueNumber ] = instVec [ i ] -> equ;//could there be more than one value ?
				valueNumber ++;
			}
			//replace the redundant expression ############
			else 
			{
				int valueNumberForExpression = valueMap [ expKeyRev ];
				symbol * s = valueToSymbolMap [ valueNumberForExpression ];
				
				//set the new assignment equ = valueSymbol;
				if ( s != 0 )
				{
					instVec [ i ] -> type = '=';
					instVec [ i ] -> rhs = 0;
					instVec [ i ] -> lhs = s;
				}
				else 
				{
					gerrors.push_back ( MAKE_ERROR ( "value number missing" ) );
				}
			}
		}
		
		i ++;
	}
	
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
