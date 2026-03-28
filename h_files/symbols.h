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
	//category ######################
	const int REGISTER_CATEGORY = 1;
	const int BUILT_IN_CATEGORY = 2;
	const int IMMEDIATE_CATEGORY = 3;
	const int FUNCTION_CATEGORY = 4;
	const int PARAMETER_CATEGORY = 5;
	const int LABEL_CATEGORY = 6;
	const int STRUCT_CATEGORY = 7;
	
	//symbols #######################
	struct symbol
	{
		string lexeme;
		
		int type; //above
		int scope; //map vector index
		int id; //struct vector index
	
		int cells; //size
		int category; 

		int ivalue;
		float fvalue;
		string svalue;
		
		vector < symbol * > members;
		map < string , symbol * > nameMap;

		//initialize the symbol ############
		bool initialize ( string n , int t , int s , int c , int cat )
		{
			lexeme = n;
			type = t;
			scope = s;
			cells = c;
			category = cat;
			
			return true;
		};
		
		//assignment operator ################
		symbol & operator= ( const symbol & lhs )
		{
			lexeme = lhs.lexeme;
			type = lhs.type;
			scope = lhs.scope;
			cells = lhs.cells;
			
			members = lhs.members;
			
			return * this;
		}
		
		//print the symbol #####################
		friend ostream & operator << ( ostream & os , const symbol & sym )
		{
			cout << "### name " << sym.lexeme << " type " << sym.type << " scope " << sym.scope << " id " << sym.id << " cells " << sym.cells << endl;
			return os;	
		};
		//see if a member exists in the symbol ##########
		int findMember ( string lexeme )
		{
			int i = 0;
			int numMembers = members.size ( );//get the number of members
			
			//see if the member is in the member array #####
			while ( i < numMembers )
			{
				//if the lexeme is found return true
				if ( members [ i ] -> lexeme == lexeme )
					return i;
				i ++;
			}
			
			return -1;
		};
	};
	
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@ Main scope data structures
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	int tempNum = 0;
	int imNum = 0;
	vector < symbol > immediateValues;
	map < int , int > opPrec;
	map < int , int > dataSize;
	
	int typeSize [ 6 ] = { 0 , 1 , 2 , 4 , 8 , 20 };
	
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	bool initializeSymbolTable ( );
	bool wrapImmediateValue ( token & tok , symbol *& sym , int scope );

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
