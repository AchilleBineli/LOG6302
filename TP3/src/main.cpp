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
    Graph(std::ofstream& out):outfile(out){}
    
    ~Graph()
    {
        nodes.clear();
        vertex.clear();
    }
    
    void addMethod(std::string methodName)
    {
        name_ = methodName;
        //add entry node
        
        std::string entryName = "Entry" + name_ ;
        std::string exitName = "Exit" + name_;
        nodes[nodeNumber] = entryName + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        parentNode.push(std::make_pair(nodeNumber, entryName));
        nodeNumber++;
        
        // add exit node
        nodes[nodeNumber] = exitName + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        nodeNumber++;
    }
    
    void addWhile()
    {
        nodes[nodeNumber] = "WhileBegin" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        if( parentNode.top().first == 0) 
        {
            if(first_time == true)
            {
                vertex.back().push_back(0);
                first_time = false;
            }
            else vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.top().second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.top().first + 1); 
            }
            vertex.back().push_back(parentNode.top().first); 
        }   
        lastLoopNode.push(nodeNumber);
        nodeNumber++;
        
        nodes[nodeNumber] = "WhileCondition" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber -1);
        parentNode.push(std::make_pair(nodeNumber, "Condition"));
        nodeNumber++;
        
        
        nodes[nodeNumber] = "WhileEnd" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        nodeNumber++;
    }
    
    
    void addIf()
    {
        nodes[nodeNumber] = "IfBegin" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
       
            if(parentNode.top().first == 0) 
            {
                if(first_time == true)
                {
                    vertex.back().push_back(0);
                    first_time = false;
                }
                else 
                {
                   
                    vertex.back().push_back(lastLoopNode.top() + 2);
                }
            }
            else
            {
                if(parentNode.top().second == "DoBegin")
                {
                // condition node is a parent too
                    vertex.back().push_back(parentNode.top().first + 1); 
                }
                vertex.back().push_back(parentNode.top().first); 
                
            }
        
        nodeNumber++;
        
        
        nodes[nodeNumber] = "IfCondition" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        parentNode.push(std::make_pair(nodeNumber, "Condition"));
        nodeNumber++;
                
                
        nodes[nodeNumber] = "IfEnd" + std::to_string(nodeNumber);      
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        if(!lastLoopNode.empty())
        {
            vertex[lastLoopNode.top() + 1].push_back(nodeNumber);
        }
        nodeNumber++;
    }
    
    
    void addFor()
    {
        nodes[nodeNumber] = "ForBegin" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.top().first == 0) 
        {
            if(first_time == true)
            {
                vertex.back().push_back(0);
                first_time = false;
            }
            else vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.top().second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.top().first + 1); 
            }
            vertex.back().push_back(parentNode.top().first); 
        }   
        lastLoopNode.push(nodeNumber); 
        nodeNumber++;
        
        nodes[nodeNumber] = "ForCondition" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        parentNode.push(std::make_pair(nodeNumber, "Condition"));
        nodeNumber++;
        
        
        nodes[nodeNumber] = "ForEnd" + std::to_string(nodeNumber);      
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        nodeNumber++;
    }
    
    void addSwitch()
    {
        nodes[nodeNumber] = "SwitchBegin" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.top().first == 0) 
        {
            if(first_time == true)
            {
                vertex.back().push_back(0);
                first_time = false;
            }
            else vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.top().second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.top().first + 1); 
            }
            vertex.back().push_back(parentNode.top().first); 
        }   
        lastLoopNode.push(nodeNumber); 
        nodeNumber++;
        
        
        
        nodes[nodeNumber] = "SwitchEnd" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        vertex[nodeNumber].push_back(nodeNumber - 1);
        nodeNumber++;
    }
    
    void addDo()
    {
        nodes[nodeNumber] = "DoBegin" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.top().first == 0) 
        {
            if(first_time == true)
            {
                vertex.back().push_back(0);
                first_time = false;
            }
            else vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.top().second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.top().first + 1); 
            }
            vertex.back().push_back(parentNode.top().first); 
        }   
        lastLoopNode.push(nodeNumber); 
        parentNode.push(std::make_pair(nodeNumber, "DoBegin"));
        nodeNumber++;
        
        
        nodes[nodeNumber] = "DoCondition" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        nodeNumber++;
        
        
        nodes[nodeNumber] = "DoEnd" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        vertex.back().push_back(nodeNumber - 1);
        nodeNumber++;
    }
    
    void addReturn()
    {
        nodes[nodeNumber] = "Return" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
         if(parentNode.top().first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.top().second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.top().first + 1); 
            }
            vertex.back().push_back(parentNode.top().first); 
        } 
        // add return stmt as one of the parent of the ExitMethod node
        vertex[1].push_back(nodeNumber);
        nodeNumber++;        
    }
    
    void addContinue()
    {
        nodes[nodeNumber] = "Continue" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.top().first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.top().second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.top().first + 1); 
            }
            vertex.back().push_back(parentNode.top().first); 
        } 
        vertex[lastLoopNode.top()].push_back(nodeNumber);
        nodeNumber++;        
    }
    
    void addBreak()
    {
        nodes[nodeNumber] = "Break" + std::to_string(nodeNumber);
        vertex.push_back(std::list<unsigned int>());
        if(parentNode.top().first == -1) 
        {
            vertex.back().push_back(nodeNumber - 1);
        }
        else
        {
            if(parentNode.top().second == "DoBegin")
            {
                // condition node is a parent too
                vertex.back().push_back(parentNode.top().first + 1); 
            }
            vertex.back().push_back(parentNode.top().first); 
        } 
        vertex[lastLoopNode.top()].push_back(nodeNumber);
        nodeNumber++;        
    }
    
    void popLastLoop()
    {
        lastLoopNode.pop();
    }
    
    void endGraph()
    {
        vertex[1].push_back(nodeNumber - 1);
        drawCFGDot(outfile);
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
             {
                outfile << nodes[*it] << " -> " << nodes[i] << "\n"; 
                std::cout << nodes[*it] << " -> " << nodes[i] << "\n"; 
             }
        }
        outfile << "}";
    }

    void dominators(std::ofstream& outfile)
    {
        outfile << "digraph { " << "\n"; 
        //fill initial structure
         
        
        outfile << "}";    
    }
    
private:
    bool first_time = true;
    unsigned int nodeNumber = 0;
    std::string dot_file;
    std::string name_;
    std::map<unsigned int, std::string> nodes;
    std::vector<std::list<unsigned int>> vertex;
    std::stack<unsigned int> lastLoopNode;
    std::stack<std::pair<unsigned int, std::string>>parentNode;
    std::stack<unsigned int> lastNestedStmt;
    std::ofstream& outfile;
    //std::stack<unsigned int>parentNode;
    //unsigned int parentNodeNumber_;

};



int main(int argc, const char * argv[])
{
   
    std::ifstream ast_file(argv[1], std::ifstream::in);
    std::ofstream cfg_file("cfg.dot", std::ofstream::out);
    
   
    
    std::string ast_string;
    getline(ast_file, ast_string);
    
    
    Graph graph_object(cfg_file);

    do
    {   
        // set class name
        if(ast_string.find("Visite de la classe") != std::string::npos)
        {
            getline(ast_file, ast_string);
        }
        
	    if(ast_string.find("Traverse de la methode") != std::string::npos)
        {
        
            std::size_t methodPos = ast_string.find_first_of("\"");
            std::string methodName_deb = ast_string.substr(methodPos + 2);
            methodPos = methodName_deb.find_first_of("(");
            std::string methodName = methodName_deb.substr(0, methodPos-1);
            
//            graph_object->addMethod(methodName);
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
	            // fin traverse 
                if( ast_string.find("Fin de traverse de") != std::string::npos)
                {
                    if( ast_string.find("for") != std::string::npos ||
                        ast_string.find("While") != std::string::npos ||
                        ast_string.find("Switch") != std::string::npos ||
                        ast_string.find("Do") != std::string::npos)
                    {
                        graph_object.popLastLoop();
                    }
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
                
                if(ast_string.find("Fin traverse de la méthode") != std::string::npos)
                {
                    graph_object.endGraph();
                }
		        
  		    }while(ast_string.find("Fin traverse de la méthode") == std::string::npos);
        }
        getline(ast_file, ast_string);

    }while(!ast_file.eof());
    

    graph_object.drawCFGDot(cfg_file);
    
 
    
    ast_file.close();
    cfg_file.close();
    
    std::cout << "The end " << std::endl;
    return 0;
 

}

