//
//  main.cpp
//  Log6302_TP2
//
//  Created by Achille Bineli on 2018-03-11.
//  Copyright © 2018 Achille Bineli. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>

class UMLClass
{
    public :
    UMLClass()
    {
    };
    ~UMLClass()
    {
        public_methods_.clear();
        private_data_members_.clear();
        base_class_name_.clear();
        derived_class_name_.clear();
    }
    
    void setClassName(std::string rhs) {class_name_ = rhs;}
    
    void setMethodsNames(std::string rhs)
    {
        public_methods_.insert(rhs);
    }
    
    void setDataMembers(std::string rhs)
    {
        private_data_members_.insert(rhs);
    }
    
    void setBaseClasses (std::string rhs)
    {
        base_class_name_.insert(rhs);
    }
    
    void setDerivedClasses(std::string rhs)
    {
        derived_class_name_.insert(rhs) ;
    }
   
    void setMethodsAreRegistered()
    {
	methods_registered_ = true;
    }

    void setDataMemberRegistered()
    {
	 data_member_registered_ = true;
    }

    bool methodsAreRegistered()
    {
        return methods_registered_;
    }

    bool dataMemberAreRegistered()
    {
	    return data_member_registered_;
    } 
    void dotCodeGenerator(std::ofstream& dotFile)
    {        
        std::cout << "class name is : " << class_name_ << std::endl;
        dotFile << class_name_ << "[\n" << "\tlabel = \"{" << class_name_ << "|";
    
    
        std::set<std::string>::const_iterator it;
        
	    it = public_methods_.begin();
        for(it; it != public_methods_.end(); ++it)
        {
            std::cout << "method name is  " << *it << std::endl;		
            dotFile << "+ " << *it << "\\l" ;
        }
        dotFile << "|";
        
        it = private_data_members_.begin();
        for(it; it !=  private_data_members_.end(); ++it)
        {
	    std::cout << "data member is :" << *it << std::endl;
            dotFile << "+ " << *it << "\\l" ;
        }
        
        dotFile << "}\"\n]\n\n";
    }
    
private:
    std::string class_name_;
    std::set<std::string> public_methods_;
    
    std::set<std::string> private_data_members_;
    
    std::set<std::string> base_class_name_;
    
    std::set<std::string> derived_class_name_;
    
    bool data_member_registered_ = false;
    bool methods_registered_ = false;
};


int main(int argc, const char * argv[])
{
   
    std::ifstream ast_file(argv[1], std::ifstream::in);
    std::ofstream uml_file("umlFile.dot", std::ofstream::out);
    uml_file <<  "digraph G {\n" 
        << " \tfontname = \"Bitstream Vera Sans\"\n"
        << "\tfontsize = 8\n"
        << "\tnode [\n"
        << "\t\tfontname = \"Bitstream Vera Sans\"\n"
        << "\t\tfontsize = 8\n"
        << "\t\tshape = \"record\"\n"
        << "\t]\n\n"

        << "\tedge [\n"
        << "\t\tfontname = \"Bitstream Vera Sans\"\n"
        << "\t\tfontsize = 8\n"
        << "\t]\n\n";
    
    std::string ast_string;
    std::map<std::string, UMLClass*> tableOfClasses;
    std::string class_name;
    getline(ast_file, ast_string);
    
    do
    {
    
        do
        {   
            std::map<std::string, UMLClass*>::iterator pos;
            // set class name
            if(ast_string.find("Visite de la classe") != std::string::npos)
            {
                std::size_t begin_pos = ast_string.find_first_of(":");
                class_name = ast_string.substr(begin_pos + 1);
                pos = tableOfClasses.find(class_name);
                if(pos == tableOfClasses.end())  // classe non evaluated
                {
                    std::cout << "Class name  = "  << class_name << std::endl;
		            UMLClass* umlClass = new UMLClass();
		            std::pair<std::string, UMLClass*> umlPair = std::make_pair(class_name, umlClass);
		            tableOfClasses.insert(umlPair);
		            umlClass->setClassName(class_name);
                }
                getline(ast_file, ast_string);
            }

		    if(ast_string.find("Data member") != std::string::npos)
            {
                    do
                    {

                        if(tableOfClasses[class_name]->dataMemberAreRegistered() == false)
                        {
                            std::size_t memberPos = ast_string.find_first_of(":");
                            std::string dataMember = ast_string.substr(memberPos + 1);
                            tableOfClasses[class_name]->setDataMembers(dataMember);
                        }
                        getline(ast_file, ast_string);

                    }while(ast_string.find("Data member") != std::string::npos);
		            tableOfClasses[class_name]->setDataMemberRegistered();
            }

		    if(ast_string.find("Traverse de la méthode") != std::string::npos)
            {
                do
                {
                    if(tableOfClasses[class_name]->methodsAreRegistered() == false)
                    {
                        std::size_t methodPos = ast_string.find_first_of("\"");
                        std::string methodName = ast_string.substr(methodPos + 1);
                        tableOfClasses[class_name]->setMethodsNames(methodName);
                    }
                    getline(ast_file, ast_string);
			        getline(ast_file, ast_string); 
      		    }while(ast_string.find("Traverse de la méthode") != std::string::npos);
		        tableOfClasses[class_name]->setMethodsAreRegistered();
           }
	    
        }while(ast_string.find("Visite de la classe") != std::string::npos);
    
        getline(ast_file, ast_string);
    
    }while(tableOfClasses.size() < 12 && !ast_file.eof());
    
    
 
    for(auto it = tableOfClasses.begin(); it != tableOfClasses.end(); ++it)
    {
        it->second->dotCodeGenerator(uml_file);
    }
    uml_file << "}";
    
    ast_file.close();
    uml_file.close();
    
    std::cout << "The end " << std::endl;
    return 0;
    

  }
