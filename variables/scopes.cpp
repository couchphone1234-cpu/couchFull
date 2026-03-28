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

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

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
bool scope::initialize ( string inputName , int inputType , int inputScope  , int inputCells )
{
	lexeme = inputName;
	type = inputType;
	scopeNumber = inputScope;
	cells = inputCells;
	varNum = 0;
	
	return true;
};

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
symbol * scope::addVariable ( string inputName , int inputType , int inputScope  , int inputCells , int category )
{
	symbol * s;
	
	//check if the variable is in the table #############
	if ( nameMap.find ( inputName ) != nameMap.end ( ) )
	{
		REPORT_ERROR ( inputName + "Variable already defined !!!" )
	}
	
	//allocate the memory ############################
	s = ( symbol * ) das.allocate ( sizeof ( symbol ) );
	
	//check the allocation ###########################
	if ( s == 0 )
		return 0;
	
	//initialize the new symbol ######################
	s -> initialize ( inputName , inputType , inputScope , inputCells , BUILT_IN_CATEGORY );
	
	//enter the symbol in the scope ##################
	variables.push_back ( s );
	nameMap [ inputName ] = s;
	
	return s;
};

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
symbol * scope::addParameter ( string inputName , int inputType , int inputScope  , int inputCells )
{
	symbol * s;
	
	//check if the variable is in the table #############
	if ( nameMap.find ( inputName ) != nameMap.end ( ) )
	{
		REPORT_ERROR ( inputName + "Parameter already defined !!!" )
	}
	
	//allocate the memory ############################
	s = ( symbol * ) das.allocate ( sizeof ( symbol ) );
	
	//check the allocation ###########################
	if ( s == 0 )
		return 0;
	
	//initialize the new symbol ######################
	s -> initialize ( inputName , inputType , inputScope , inputCells , PARAMETER_CATEGORY );
	
	//enter the symbol in the scope ##################
	parameters.push_back ( s );
	nameMap [ inputName ] = s;
	
	return s;
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
ostream & operator << ( ostream & os , const scope & s )
{
	//output the scope data ######################
	cout << "Scope " << s.varNum << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "### name " << s.lexeme << " type " << IDToKeywords [ s.type ] << " scope " << s.scopeNumber << " id " << s.scopeNumber << " cells " << s.cells << " varNum " << s.varNum << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ variables #####" << endl;
	
	int numberOfVariables = s.variables.size ( );
	int i = 0;
	
	//print all the variables @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	while ( i < numberOfVariables )
	{
		cout << * s.variables [ i ] << endl;
		i ++;
	}
	
	int numberOfParameters = s.parameters.size ();
	i = 0;
	
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ parameters " << endl;
	while ( i < numberOfParameters )
	{
		cout << * s.parameters [ i ] << endl;
		i ++;
	}
	
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ map @@@@@@@ " << endl;
	for ( auto i = s.nameMap.begin ( ) ; i != s.nameMap.end ( ) ; i ++ )
		cout << i -> first << " -> " << * i -> second << endl;

	return os;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: getTemp
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
symbol * scope::getTemp ( int type , int scope , int cells )
{ 
	symbol * s;
	int index;

	string name = "temp" + to_string ( tempNum ++ );//make temp name
	
	
	//allocate the memory ############################
	s = ( symbol * ) das.allocate ( sizeof ( symbol ) );
	
	//check the allocation ###########################
	if ( s == 0 )
		return 0;
	
	//initialize the new symbol ######################
	s -> initialize ( name , type , scope , cells , BUILT_IN_CATEGORY );
	
	//enter the symbol in the scope ##################
	variables.push_back ( s );
	nameMap [ name ] = s;
	
	return s;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: addSymbol
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
symbol * scope::getSymbolByName ( string name , int scope )
{
	// Check if the key is found
	if ( nameMap.find ( name ) != scopes [ scope ].nameMap.end ( ) ) 
	{
		return nameMap [ name ]; //return the pointer 
	} 
	//Symbol not found ###########
	else if ( scopes [ 0 ].nameMap.find ( name ) != scopes [ 0 ].nameMap.end ( ) )
	{
		return scopes [ 0 ].nameMap [ name ]; //return the pointer 
	}

	return 0;
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: addSymbol
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
symbol * scope::addSymbol ( symbol * s )
{
	//save the variable symbol ##########
	variables.push_back ( s );
	nameMap [ s -> lexeme ] = s;
	
	return s;
}
