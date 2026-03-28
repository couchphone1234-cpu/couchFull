/*********************************************************************************
*
* File Name: C:\programs\cgUpgrade\noncode\scrap.cpp
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
* Program Shell Generated At: 2:40:09p.m.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

//################################### GLOBAL DATA ###################################
	
	//Symbols.cpp ################################################################
	//scopes ( function or struct )
	class scope
	{
		public:
			
			bool initialize ( string n , int t , int s  , int c );
			symbol * addVariable ( string inputName , int inputType , int inputScope  , int inputCells , int category );
			symbol * addParameter ( string inputName , int inputType , int inputScope  , int inputCells );
			friend ostream & operator << ( ostream & os , const scope & s );
			symbol * getTemp ( int type , int scope , int cells );
			symbol * getSymbolByName ( string name , int scope );
			symbol * addSymbol ( symbol * s );
			//bool dumpScopes ( );

		
			//data #####################################
			string lexeme;
			vector < symbol * > parameters; //function parameters 
			map < string , symbol * > nameMap;//members ( variables )
			vector < symbol * > variables;// members ( variabes )
			vector < symbol * > types; 
			int varNum = 0; //for assigning numbers to scope variables
			int scopeNumber = -1;
			int returnType;//return type for functions
			
		private:
			
			int type; //above
			//int scopeNumber; //scope vector index
			int cells; //size 
			
			
			int tempNum = 0; //for temp values	
	};


	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@ Main scope data structures
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	vector < scope > scopes;//each scope ##############
	
	
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
	int addScope ( string name , int type );
	int getScope ( string name );
	bool dumpScopes ( );
	
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
