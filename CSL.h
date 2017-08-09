/*
	Conversation Scripting Language (CSL) Interpreter
	Version: v0.01
	By: Necro
	(c)30.7.2017.

	An interpreter for the .CSL file format

	CSL is an file format for scripting dialogues thorugh a Root/Child/Node System;

*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
class CSL
	{ 
		public:
		std::string root;
		std::string node;
		std::string children[255];
		std::ifstream file;
		const char* fileaddr;
		int nuchildren;
		bool EndOfFile;
		//Checks for ROOT
		bool Croot( std::string buffer )
			{
				std::string ROOT("ROOT");
				if( buffer.find(ROOT) == 0 )
					{
						return true;	
					}
				else
					{
						return false;
					}
			}
		//Checks for CHILD
		bool Cchild( std::string buffer )
			{
				std::string CHILD("CHILD");
				if( buffer.find(CHILD) == 0 )
					{
						return true;
					}
				return false;
			}
		//Chekcs for NODE
		bool Cnode( std::string buffer )
			{
				std::string NODE("NODE");
				if( buffer.find(NODE) == 0 )
					{
						return true;
					}
				return false;
			}
		//Checks for open bracket
		bool Cstart( std::string buffer )
			{
				std::string START("{");
				if( buffer.find(START) == 0 )
					{
						return true;
					}
				return false;
			}
		//Checks for closed bracket
		bool Cend( std::string buffer )
			{
				std::string END("}");
				if( buffer.find(END) == 0 )
					{
						return true;
					}
				return false;
			}
		bool Cstring( std::string buffer, std::string string )
			{
				if( buffer.find( string ) == 0)
					{
						return true;
					}
				return false;
			}
		//Gets the string between brackets;
		std::string CleanString( std::string buffer )
			{
				std::size_t start = buffer.find( "(" )+1;
				std::size_t end = buffer.find(")") - start;
				std::string buffered = buffer.substr ( start, end );
				return buffered;
			}
		//Getsh children of node;
		int FindChildren( std::ifstream &file )
			{
				std::string buffer;
				while( !Cstart( buffer ) )
					{
						getline( file, buffer );
						if( file.eof() )
							{
								EndOfFile = true;
								break;
							}
					}
				int i = 0;
				while( 1 )	
					{
						getline( file, buffer );
						if( Cend ( buffer ) )
							{
								break;
							}
						children[i] = buffer;
						i++;
						if( file.eof() )
							{
								EndOfFile = true;
								break;
							}
					}
				return i;
			}
		//Finds a node:
		void FindNode( int child )
			{
				std::string buffer;
				node = children[child].replace(0,5, "NODE" );
				std::replace( node.begin(), node.end(), '(', '[' );
				std::replace( node.begin(), node.end(), ')', ']' );
				file.open(fileaddr);
				while( !Cstring( buffer, node ) )
					{
						getline( file, buffer );
						if( file.eof() )
							{
								EndOfFile = true;
								break;
							}
					}
				node = buffer;
				nuchildren = FindChildren( file );
				file.close( );
			}
		// Reads File Acodring to syntax
		void FindRoot( const char* addr )
			{
				fileaddr = addr;
				std::string buffer, buffer2;
				file.open( fileaddr );
				while( !Croot( buffer ) )
					{
						getline( file, buffer);
						if( file.eof() )
							{
								std::cout<<"No Root Round"<<std::endl;
								break;
							}
					}
				root = buffer;
				nuchildren = FindChildren( file );
				file.close();
			}
		};
void TestFunction( const char* file)
	{
		int option;
		CSL CLP;
		CLP.EndOfFile = 0;
		CLP.FindRoot( file );
		std::cout<<CLP.CleanString(CLP.root)<<std::endl;
		std::cout<<std::endl;
		for(int i=0; i < CLP.nuchildren; i++ )
			{
				std::cout<<CLP.CleanString(CLP.children[i])<<std::endl;
			}
		while( !CLP.EndOfFile )
			{
			std::cin>>option;
			CLP.FindNode( option-1 );
			std::cout<<CLP.CleanString(CLP.node)<<std::endl;
			std::cout<<std::endl;
			for( int i = 0; i < CLP.nuchildren; i++ )
				{
					std::cout<<CLP.CleanString(CLP.children[i])<<std::endl;
				}
			}
	}
