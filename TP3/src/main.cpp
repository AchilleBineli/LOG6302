#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <utility>


class Graph
{
public: 
    Graph(){}
    
    ~Graph()
    {
        nodes.clear();
        vertex.clear();
    }
    
    void addMethod(std::string methodName)
    {
        name_ = methodName;
        //add entry node
        
        std::string entryName = "Entry" + name_;
        std::string exitName = "Exit" + name_;
        nodes[nodeNumber] = entryName;
        vertex.push_back(std::list<unsigned int>());
        parentNode = std::make_pair(nodeNumber, entryName);
        nodeNumber++;
        
        // add exit node
        nodes[nodeNumber] = exitName;
        vertex.push_back(std::list<unsigned int>());
        nodeNumber++;
    }
    
    void addWhile()
    {
        nodes[nodeNumber] = "WhileBegin";
        vertex.push_back(std::list<unsigned int>());
        if( parentNode.first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.first + 1); 
            }
            vertex.back().push_back(parentNode.first); 
        }   
        lastLoopNode.push(nodeNumber);
        nodeNumber++;
        
        nodes[nodeNumber] = "Condition";
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber -1);
        parentNode = std::make_pair(nodeNumber, "Condition");
        nodeNumber++;
        
        
        nodes[nodeNumber] = "WhileEnd";
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        nodeNumber++;
    }
    
    
    void addIf()
    {
        nodes[nodeNumber] = "IfBegin";
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.second == "DoBegin")
            {
            // condition node is a parent too
                vertex.back().push_back(parentNode.first + 1); 
            }
            vertex.back().push_back(parentNode.first); 
            
        }
        nodeNumber++;
        
        
        nodes[nodeNumber] = "Condition";
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        parentNode = std::make_pair(nodeNumber, "Condition");
        nodeNumber++;
                
                
        nodes[nodeNumber] = "IfEnd";      
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        nodeNumber++;
    }
    
    
    void addFor()
    {
        nodes[nodeNumber] = "ForBegin";
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.first + 1); 
            }
            vertex.back().push_back(parentNode.first); 
        }   
        lastLoopNode.push(nodeNumber); 
        nodeNumber++;
        
        nodes[nodeNumber] = "Condition";
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        parentNode = std::make_pair(nodeNumber, "Condition");
        nodeNumber++;
        
        
        nodes[nodeNumber] = "ForEnd";      
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        nodeNumber++;
    }
    
    void addSwitch()
    {
        nodes[nodeNumber] = "SwitchBegin";
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.first + 1); 
            }
            vertex.back().push_back(parentNode.first); 
        }   
        lastLoopNode.push(nodeNumber); 
        nodeNumber++;
        
        
        
        nodes[nodeNumber] = "SwitchEnd";
        vertex.push_back(std::list<unsigned int>());
        vertex[nodeNumber].push_back(nodeNumber - 1);
        nodeNumber++;
    }
    
    void addDo()
    {
        nodes[nodeNumber] = "DoBegin";
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.first + 1); 
            }
            vertex.back().push_back(parentNode.first); 
        }   
        lastLoopNode.push(nodeNumber); 
        parentNode = std::make_pair(nodeNumber, "DoBegin");
        nodeNumber++;
        
        
        nodes[nodeNumber] = "Condition";
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        nodeNumber++;
        
        
        nodes[nodeNumber] = "DoEnd";
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        nodeNumber++;
    }
    
    void addReturn()
    {
        nodes[nodeNumber] = "Return";
        vertex.push_back(std::list<unsigned int>());
         if(parentNode.first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.first + 1); 
            }
            vertex.back().push_back(parentNode.first); 
        } 
        // add return stmt as one of the parent of the ExitMethod node
        vertex[1].push_back(nodeNumber);
        nodeNumber++;        
    }
    
    void addContinue()
    {
        nodes[nodeNumber] = "Continue";
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.first + 1); 
            }
            vertex.back().push_back(parentNode.first); 
        } 
        vertex[lastLoopNode.top()].push_back(nodeNumber);
        nodeNumber++;        
    }
    
    void addBreak()
    {
        nodes[nodeNumber] = "Break";
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.first + 1); 
            }
            vertex.back().push_back(parentNode.first); 
        } 
        vertex[lastLoopNode.top()].push_back(nodeNumber);
        nodeNumber++;        
    }
    
    void popLastLoop()
    {
        lastLoopNode.pop();
        parentNode.first = -1;
    }
    
    
    void drawCFGDot(std::ofstream& outfile)
    {
        outfile << "digraph { " << "\n";  
        for(auto it = nodes.cbegin(); it != nodes.cend(); ++it)
        {
            outfile << it->second << "\n";
        }
        for(int i = 0; i < vertex.size(); ++i)
        {
        
            for(auto it =  vertex[i].cbegin(); it != vertex[i].cend(); ++it)
                outfile << nodes[*it] << " -> " << nodes[i] << "\n"; 
        }
        outfile << "}";
    }

private:
    unsigned int nodeNumber = 0;
    std::string dot_file;
    std::string name_;
    std::map<unsigned int, std::string> nodes;
    std::vector<std::list<unsigned int>> vertex;
    std::stack<unsigned int> lastLoopNode;
    std::pair<unsigned int, std::string> parentNode;
    //std::stack<unsigned int>parentNode;
    //unsigned int parentNodeNumber_;

};



int main(int argc, const char * argv[])
{
   
    std::ifstream ast_file(argv[1], std::ifstream::in);
    std::ofstream cfg_file("cfg.dot", std::ofstream::out);
    cfg_file <<  "digraph G {\n" 
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
    getline(ast_file, ast_string);
    
//    unsigned int nodeNumber = 0;
//    std::map<int, std::string> nodes;
//    std::vector<std::list<int>>vertex;
//    std::stack<int> parentNode;
    
    std::vector<class Graph> tablesOfGraph;
    Graph graph_object;

    do
    {   
        // set class name
        if(ast_string.find("Visite de la classe") != std::string::npos)
        {
            getline(ast_file, ast_string);
        }
        
	    if(ast_string.find("Traverse de la méthode") != std::string::npos)
        {
        
            std::size_t methodPos = ast_string.find_first_of("\"");
            std::string methodName = ast_string.substr(methodPos + 1);
            graph_object.addMethod(methodName);
            getline(ast_file, ast_string);
            do
            {
                // traverse while
                if(ast_string.find("Traverse while") != std::string::npos)
                {
                   
                    graph_object.addWhile();
		            getline(ast_file, ast_string); 
                }
                
               
                // traverse if
                if(ast_string.find("Traverse if") != std::string::npos)
                {
                    graph_object.addIf();
                    getline(ast_file, ast_string); 
                }
         
                 
                // traverse for
                if(ast_string.find("Traverse for") != std::string::npos)
                {
                    graph_object.addFor();
                    getline(ast_file, ast_string); 
                }
	
			        
		        
                // traverse switch
                if(ast_string.find("Traverse switch") != std::string::npos)
                {
                    graph_object.addSwitch();
                    getline(ast_file, ast_string); 
                }
             
		        
	            // traverse do
                if(ast_string.find("Traverse Do") != std::string::npos)
                {
                    graph_object.addDo();
		            getline(ast_file, ast_string); 
                }
                
	            // fin traverse 
                if( ast_string.find("Fin de traverse de for") != std::string::npos ||
                    ast_string.find("Fin de traverse de While") != std::string::npos ||
                    ast_string.find("Fin de traverse de Switch") != std::string::npos ||
                    ast_string.find("Fin de traverse de Do") != std::string::npos)
                {
                
                    graph_object.popLastLoop();
		            getline(ast_file, ast_string); 
                }
		        
		        
	            // visit return
                if(ast_string.find("Visite d'une expression return") != std::string::npos)
                {
                     graph_object.addReturn();
		            getline(ast_file, ast_string); 
                }
		        
	            // visit break
                if(ast_string.find("Visite d'une expression :break") != std::string::npos)
                {
                    graph_object.addBreak();
                    getline(ast_file, ast_string);
                }
		        
		        
		        // visit continue
                if(ast_string.find("Visite d'une expression :Continue") != std::string::npos)
                {  
                    graph_object.addContinue();                      
		            getline(ast_file, ast_string); 
                }
                
                else
                {
		            getline(ast_file, ast_string); 
		        }
		        
  		    }while(ast_string.find("Fin traverse de la méthode") != std::string::npos);
        }
        getline(ast_file, ast_string);

    }while(!ast_file.eof());

    graph_object.drawCFGDot(cfg_file);
    
 
    
    ast_file.close();
    cfg_file.close();
    
    std::cout << "The end " << std::endl;
    return 0;
 

}

