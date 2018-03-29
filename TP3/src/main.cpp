#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <set>
#include <map>
#include "tinyxml2.h"


//using namespace tinyxml2;

int main(int argc, char* argv[])
{
#if 0
#if 0
   //std::ofstream ast_file(argv[1] , std::ios::out); 
    XMLDocument document("test.xml");
    XMLElement* root = document.FirstChildElement( "Document" );
	if ( root )
    {
		XMLElement* element = root->FirstChildElement( "Element" );
		if ( element )
		{
			XMLElement* child = element->FirstChildElement( "Child" );
			if ( child )
			{
				XMLElement* child2 = child->NextSiblingElement( "Child" );
				if ( child2 )
				{
				    child2->SetAttribute("NodeNumber", 3);
				    child2->SetAttribute("edge to", 4);
				}
			}
        }

    }
  
  #endif
  
  	    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
		tinyxml2::XMLNode* element = doc->InsertEndChild( doc->NewElement( "element" ) );

		tinyxml2::XMLElement* sub[3] = { doc->NewElement( "sub" ), doc->NewElement( "sub" ), doc->NewElement( "sub" ) };
		for( int i=0; i<3; ++i ) {
			sub[i]->SetAttribute( "attrib", i );
		}
		element->InsertEndChild( sub[2] );

		const int dummyInitialValue = 1000;
		int dummyValue = dummyInitialValue;

		tinyxml2::XMLNode* comment = element->InsertFirstChild( doc->NewComment( "comment" ) );
		comment->SetUserData(&dummyValue);
		element->InsertAfterChild( comment, sub[0] );
		element->InsertAfterChild( sub[0], sub[1] );
		sub[2]->InsertFirstChild( doc->NewText( "& Text!" ));
		doc->Print();
        
    #if 0 
    XMLElement root = XMLElement(&doc);
    root.SetAttribute("NodeNumber", 1);
    root.SetAttribute("Edge to", 3);
    
    XMLElement child1;
    child1.SetAttribute("NodeNumber", 3);
    child1.SetAttribute("edge to", 4);
    root->InsertEndChild(child1);
    
    XMLElement child2;
    child1.SetAttribute("NodeNumber", 4);
    child1.SetAttribute("edge to", 2);
    root->InsertEndChild(child2);
    
    doc.SaveFile();
    
    do{ 
            
    
    }while(file.eof());


    #endif
#endif



    
    return 0;
}

