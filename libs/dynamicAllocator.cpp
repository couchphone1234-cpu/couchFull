/*********************************************************************************
*
* File Name: /home/user/programs/cgUpgrade/noncode/scrap.cpp
*
* Date: September , 19 , 2025
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
* Program Shell Generated At: 6:26:37p.m.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


	#ifndef iostream
	#include <iostream>
	#endif

	#ifndef string_h
	#include <string.h>
	#endif
	
	#include <vector>
	
	#include <string>
	#include <cstdlib> 

	using namespace std;

//################################### GLOBAL DATA ###################################

	#define MAX_BUFFER 10000
	//#define DEBUG

//##################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	void print ( const char * mes );


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//###########################################################################################
	//Class Definition: dynamicAllocator ##########################
	//###########################################################################################
	class dynamicAllocator
	{
		public:

			dynamicAllocator ( ); 
			~dynamicAllocator ( ); 
			void * allocate ( int size );
			int bufferIndex = 0;
		private:
		
			vector < void * > memory;
			
	};

dynamicAllocator sa;

#ifdef DEBUG
int main ( int argc , char * argv [ ] ) 
{
	char * s;
	
	int * i;
	
	s = ( char * ) sa.allocate ( 10 );
	strcpy_s ( s , 10 , "hello" );
	cout << s << endl;
	i = ( int * ) sa.allocate ( 4 );
	* i = 25;
	cout << * i << endl;
	
	
	struct testS
	{
		int i;
		int j;
	};
	
	testS * sp = ( testS * ) sa.allocate ( sizeof ( testS ) );
	
	sp -> i = 1;
	sp -> j = 2;
	
	cout << sp -> j << endl;
	
	
	

	return 0; 
}
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- CONSTRUCTOR DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
 Function Name: 
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
dynamicAllocator::dynamicAllocator ( )
{



}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- DESTRUCTOR DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
*
 Function Name: 
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
dynamicAllocator::~dynamicAllocator ( )
{
	//delete the memory #####################
	for ( auto mem : memory )
	{
		//cout << "delete " << * mem << endl;
		delete mem;
	}
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=- FUNCTION DEFINITION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*
* Function Name: allocate
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
void * dynamicAllocator::allocate ( int size ) 
{ 
	void * m = operator new ( size ); //allocate the memory

	//check the allocator ##########################
	if ( m == 0 )
		return 0; 
	
	//push the memory in the list ##################
	memory.push_back ( m );
	
	//return the memory ############################
	return m;
}


