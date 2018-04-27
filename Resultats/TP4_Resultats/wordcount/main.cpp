//
//  main.cpp
//  Slicing_LOG6302
//
//  Created by Achille Bineli on 2018-04-17.
//  Copyright © 2018 Achille Bineli. All rights reserved.
//

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <list>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <set>
#include <iterator>
#include <fstream>


// type of node that will be in the graph
// control_statement: conditional node
// statement : instructions that don't compute a value
// assignment : expression statement that producing a value to a variable
enum class NodeType{control_statement, statement, assignment};

/**
 *Class name:        CFGNOde
 *
 *Description:       implementation of a node use to construct the graph
 */
class CFGNode
{
public:
    
    CFGNode(){}
    
    CFGNode(NodeType type, std::string name, unsigned int number):
    type_(type), name_(name), number_(number){}

    CFGNode& operator=(const CFGNode& rhs)
    {
        if(this != &rhs)
        {
            type_ = rhs.type_;
            name_ = rhs.name_;
            number_ = rhs.number_;
        }
        return *this;
    }
    
    NodeType getNodeType() const {return type_;}
    std::string getName() const {return name_;}
    unsigned int getNodeNumber() const {return number_;}
private:
    NodeType type_; //statement, expression,
    std::string name_; //example : c = getchar()
    unsigned int number_ = 0;
};


/**
 *Class name:        CFGList
 *
 *Description:       implementation of the CFG class using an
 *                   adjacency list
 */
class CFGList
{
public:
    CFGList()
    {
        std::unique_ptr<CFGNode>
        start_node(new CFGNode(NodeType::control_statement, "start", 0));
        nodes[numberOfNodes] = *start_node.get();
        vertex.push_back(std::list<CFGNode>());
        ++numberOfNodes;
    }
    void addNode(NodeType type , const std::string& name, unsigned int nodeNumber)
    {
        std::unique_ptr<CFGNode> node(new CFGNode(type, name, nodeNumber));
        nodes[nodeNumber] = *node.get();
        vertex.push_back(std::list<CFGNode>());
        ++numberOfNodes;
    }
    
    void addVertex(unsigned int predeccesor_number, unsigned int successor_number)
    {
        CFGNode succNode = nodes[successor_number];
        vertex[predeccesor_number].push_back(succNode);
    }
    
    void endCFG()
    {
        std::unique_ptr<CFGNode>stop_node
        (new CFGNode(NodeType::control_statement, "stop", numberOfNodes));
        nodes[numberOfNodes] = *stop_node.get();
        vertex.push_back(std::list<CFGNode>());
        ++numberOfNodes;
        
        
        std::unique_ptr<CFGNode>entry_node
        (new CFGNode(NodeType::control_statement, "entry", numberOfNodes));
        nodes[numberOfNodes] = *entry_node.get();
        vertex.push_back(std::list<CFGNode>());
        ++numberOfNodes;
    }
    
    const std::vector<std::list<CFGNode>>& getVertex() const
    {
        return vertex;
    }
    
    const  std::map<unsigned int, CFGNode>& getNodes() const
    {
        return nodes;
    }
private:
    unsigned int numberOfNodes = 0;
    std::map<unsigned int, CFGNode> nodes;
    std::vector<std::list<CFGNode>>vertex;
};


/**
 *Function name:     Reverse_graph
 *
 *Description:       Take the predecessors data structure and compute the successors
 *                   and vice-versa
 *
 *Return:            The reverse vertex of the graph
 */
void reverse_graph(const std::map<unsigned int , CFGNode>&nodes,
                   const std::vector<std::list<CFGNode>>&predecessors,
                   std::vector<std::list<CFGNode>>&successors)
{
    for(unsigned int i = 0; i < predecessors.size(); i++)
    {
        CFGNode actualNode = nodes.at(i);
        for(auto it = predecessors[i].cbegin(); it != predecessors[i].cend(); ++it)
        {
            successors[it->getNodeNumber()].push_back(actualNode);
        }
    }
}



/**
 *Function name:     postdomination
 *
 *Description:       compute the postdominators of a given node in the CFG
 */
void postdomination(const std::vector<std::list<CFGNode>>& successors,
                    std::vector<std::list<unsigned int>>& postdominators,
                    unsigned int index)
{
    std::list<CFGNode>successors_i = successors[index];
    if(successors_i.size() > 1)
    {
        auto itBegin = successors_i.cbegin();
        
        while(postdominators[itBegin->getNodeNumber()].empty() && itBegin != successors_i.cend())
            ++itBegin;
        
        if(itBegin == successors_i.cend())
        {
            std::cout << std::endl << "error in postdominance computation" <<  std::endl;
            std::abort();
        }
        postdominators[index] = postdominators[itBegin->getNodeNumber()];
        ++itBegin;
        
        while(itBegin != successors_i.cend())
        {
            if(postdominators[itBegin->getNodeNumber()].empty());
            else
            {
                std::list<unsigned int> intersection;
                std::set_intersection(postdominators[index].cbegin(), postdominators[index].cend(),
                                      postdominators[itBegin->getNodeNumber()].cbegin(), postdominators[itBegin->getNodeNumber()].cend(),
                                      std::back_inserter(intersection));
                postdominators[index] = intersection;
            }
            ++itBegin;
        }
    }
    else
    {
        postdominators[index] = postdominators[successors_i.back().getNodeNumber()];
    }
    postdominators[index].push_back(index);
    postdominators[index].sort();
}



/**
 *Function name:     postdominators_fast
 *
 *Description:       compute the postdominators given a CFG
 *                   Uses the optizimed way by traversing
 *                   each node once
 *
 *Return :           the list of postdominators of each node in the CFG
 */
void postdominators_fast(const std::vector<std::list<CFGNode>>& successors,
                         const std::vector<std::list<CFGNode>>& predecessors,
                         std::vector<std::list<unsigned int>>& postdominators)
{
    unsigned int vec_size = static_cast<unsigned int>(successors.size());
    std::queue<unsigned int> next_nodes;
    std::vector<unsigned int> visited_nodes;
    
    //begin with the node that has no successors
    unsigned int to_visit = vec_size;
    for(to_visit = vec_size - 1  ; to_visit > 0; --to_visit)
    {
        if(successors[to_visit].empty())
        {
            postdominators[to_visit].push_back(to_visit);
            visited_nodes.push_back(to_visit);
            break;
        }
    }
    
    
    for(auto it = predecessors[to_visit].cbegin(); it != predecessors[to_visit].cend(); ++it)
    {
        next_nodes.push(it->getNodeNumber());
        visited_nodes.push_back(it->getNodeNumber());
        sort(visited_nodes.begin(), visited_nodes.end());
    }
    
    while(!next_nodes.empty())
    {
        unsigned int index = next_nodes.front();
        for(auto it = predecessors[index].cbegin(); it != predecessors[index].cend(); ++it)
        {
            if(!std::binary_search(visited_nodes.cbegin(), visited_nodes.cend(), it->getNodeNumber()))
            {
                next_nodes.push(it->getNodeNumber());
                visited_nodes.push_back(it->getNodeNumber());
                sort(visited_nodes.begin(), visited_nodes.end());
            }
        }
        postdomination(successors, postdominators, index);
        next_nodes.pop();
    }
}

/**
 *Function name:     immediate_postdom
 *
 *Description:       compute the immediate postdominators given
 *                   the postdominators
 *
 *Return :           the list of dominators of each node in the CFG
 */
void immediate_postdom(const std::vector<std::list<CFGNode>>& successors,
                       const std::vector<std::list<unsigned int>>& postdominators,
                       std::vector<std::list<unsigned int>>& ipostdom)
{
    
    for(unsigned int i = 0; i < successors.size(); i++)
    {
        
        // if the nodes i has only one predecessors, that predecessors is its dominators
        if(successors[i].size() == 1)
        {
            ipostdom[i].push_back(successors[i].back().getNodeNumber());
        }
        else
        {
            std::list<unsigned int>postdom_list = postdominators[i];
            for(auto itList = postdom_list.crbegin(); itList != postdom_list.crend(); ++itList)
            {
                if(*itList == i) ; // do nothing because the node itself cannot be and ipostdom
                else
                {
                    std::list<unsigned int> difference;
                    std::set_difference(postdom_list.cbegin(), postdom_list.cend(),
                                        postdominators[*itList].cbegin(), postdominators[*itList].cend(),
                                        std::back_inserter(difference));
                    
                    if(difference.back() == i)
                    {
                        ipostdom[i].push_back(*itList);
                        break;
                    }
                }
            }
        }
    }
}



/**
 *Function name:     domination
 *
 *Description:       compute the dominators of a given node in the CFG
 */
void domination(const std::vector<std::list<CFGNode>>& predecessors,
                std::vector<std::list<unsigned int>>& dominators,
                unsigned int index)
{
    std::list<CFGNode>pred_i = predecessors[index];
    if(pred_i.size() > 1)
    {
        auto itBegin = pred_i.cbegin();
        while(dominators[itBegin->getNodeNumber()].empty() && itBegin != pred_i.cend())
            ++itBegin;
        // impossible that the dominators of all the predecessors are not computed
        // at least one predecessors is already visited
        if(itBegin == pred_i.cend())
        {
            std::cout << std::endl << "error in dominance computation" << std::endl;
            std::abort();
            
        }
        dominators[index] = dominators[itBegin->getNodeNumber()];
        ++itBegin;
        while(itBegin != pred_i.cend())
        {
            if(dominators[itBegin->getNodeNumber()].empty());
            else
            {
                std::list<unsigned int> intersection;
                std::set_intersection(dominators[index].cbegin(), dominators[index].cend(),
                                      dominators[itBegin->getNodeNumber()].cbegin(), dominators[itBegin->getNodeNumber()].cend(),
                                      std::back_inserter(intersection));
                dominators[index] = intersection;
            }
            ++itBegin;
        }
    }
    else
    {
        dominators[index] = dominators[pred_i.back().getNodeNumber()];
    }
    dominators[index].push_back(index);
    dominators[index].sort();
}

/**
 *Function name:     dominators_fast
 *
 *Description:       compute the dominators given a CFG
 *                   Uses the optizimed way by traversing
 *                   each node once
 *
 *Return :           the list of dominators of each node in the CFG
 */
void dominators_fast(const std::vector<std::list<CFGNode>>& successors,
                     const std::vector<std::list<CFGNode>>& predecessors,
                     std::vector<std::list<unsigned int>>& dominators)
{
    
    std::queue<unsigned int>next_nodes;
    std::vector<unsigned int>visited_nodes;
    
    unsigned int first_node;
    for(first_node = 0; first_node < predecessors.size(); ++first_node)
    {
        if(predecessors[first_node].empty())
        {
            dominators[first_node].push_back(first_node);
            visited_nodes.push_back(first_node);
            break;
        }
    }
    
    
    for(auto it = successors[first_node].cbegin(); it != successors[first_node].cend(); ++it)
    {
        next_nodes.push(it->getNodeNumber());
        visited_nodes.push_back(it->getNodeNumber());
        sort(visited_nodes.begin(), visited_nodes.end());
    }
    
    while(!next_nodes.empty())
    {
        unsigned int index = next_nodes.front();
        for(auto it = successors[index].cbegin(); it != successors[index].cend(); ++it)
        {
            if(!std::binary_search(visited_nodes.cbegin(), visited_nodes.cend(), it->getNodeNumber()))
            {
                next_nodes.push(it->getNodeNumber());
                visited_nodes.push_back(it->getNodeNumber());
                sort(visited_nodes.begin(), visited_nodes.end());
            }
        }
        domination(predecessors, dominators, index);
        next_nodes.pop();
    }
}



/**
 *Function name:    immediate_domitors
 *
 *Description:      compute the immediate dominators given the dominators
 *
 *Return :          the list of dominators of each node in the CFG
 */
void immediate_dominators(const std::vector<std::list<CFGNode>>& vertex,
                          const std::vector<std::list<unsigned int>>& dom,
                          std::vector<std::list<unsigned int>>& idom)
{
    
    for(unsigned int i = 1; i < vertex.size(); i++)
    {
        // if the nodes i has only one predecessors, that predecessors is its dominators
        if(vertex[i].size() == 1)
        {
            idom[i].push_back(vertex[i].back().getNodeNumber());
        }
        else
        {
            std::list<unsigned int>dom_list = dom[i];
            for(auto itList = dom_list.crbegin(); itList != dom_list.crend(); ++itList)
            {
                if(*itList == i) ; // do nothing
                else
                {
                    std::list<unsigned int> difference;
                    std::set_difference(dom_list.cbegin(), dom_list.cend(),
                                        dom[*itList].cbegin(), dom[*itList].cend(),
                                        std::back_inserter(difference));
                    
                    if(difference.back() == i)
                    {
                        idom[i].push_back(*itList);
                        break;
                    }
                }
            }
        }
    }
}


/**
 *Function name:    compute_control_dependancy
 *
 *Description:      compute the control dependancy of a arc in the CFG in which
 *                  the successor is not a postdominator of the predecessor
 *
 *Return :          the list of node dependant to the predecessor node
 */
void compute_control_dependancy(const std::vector<std::list<unsigned int>>& postdominators,
                                const std::vector<std::list<unsigned int>>& ipdom,
                                std::map<unsigned int, std::list<unsigned int>>& control_dep,
                                unsigned int pred,
                                unsigned int succ)
{
    //case where pred is the immediate postdom of succ
    if(std::binary_search(postdominators[succ].cbegin(), postdominators[succ].cend(), pred))
    {
        control_dep[pred].push_back(pred);
        control_dep[pred].push_back(succ);
        
        unsigned int node_to_add = ipdom[succ].back();
        do
        {
            control_dep[pred].push_back(node_to_add);
            node_to_add= ipdom[node_to_add].back();
        }while(node_to_add != pred);
        
    }
    // case where the immediate post dom of pred is a postdom of succ
    else
    {
        unsigned int post_predecessor = ipdom[pred].back();
        control_dep[pred].push_back(succ);
        unsigned int next_to_add = ipdom[succ].back();
        while(next_to_add != post_predecessor)
        {
            control_dep[pred].push_back(next_to_add);
            next_to_add = ipdom[next_to_add].back();
        }
    }
}


/**
 *Function name:    controldependancy
 *
 *Description:      look for arc in the CFG where the successor is not
 *                  a postdominator of the predecessor
 *
 *Return :          the list of dominators of each node in the CFG
 */
void controldependancy(const std::vector<std::list<CFGNode>>& successors,
                       const std::vector<std::list<unsigned int>>& postdominators,
                       const std::vector<std::list<unsigned int>>& ipdom,
                       std::map<unsigned int, std::list<unsigned int>>& dep)
{
    for(int i = 0; i < successors.size(); i++)
    {
        std::list<CFGNode>successors_i = successors[i];
        for(auto it = successors_i.cbegin(); it != successors_i.cend(); ++it)
        {
            if(!std::binary_search(postdominators[i].cbegin(), postdominators[i].cend(), it->getNodeNumber()))
            {
                compute_control_dependancy(postdominators, ipdom, dep, i, it->getNodeNumber());
            }
        }
    }
}



/**
 *Function name:    generate_kill_set
 *
 *Description:      Take the list of nodes and whith their type, compute the
 *                  genrerate and kill sets for the reaching definitions analysis
 *
 *Return :          gen and kill sets
 */
void generate_kill_set(const std::map<unsigned int, CFGNode>&nodes,
                       std::vector<std::list<unsigned int>>& gen_set,
                       std::vector<std::list<unsigned int>>& kill_set)
{
    std::set<unsigned int>node_visited;
    // iterate on all the nodes
    for(auto it  = nodes.cbegin(); it != nodes.cend(); ++it)
    {
        unsigned int actualNode = it->second.getNodeNumber();
        // if this node or any of the nodes it generates or kills
        // has been visited no need to visit the node again
        if(node_visited.find(actualNode) == node_visited.end())
        {
            // if the node is of type control_statement or statement,
            // gen_set and kill_set are null
            if(it->second.getNodeType() != NodeType::assignment)
            {
                node_visited.insert(actualNode);
            }
            // if it is an assignment, gen_set = node
            else
            {
                std::string to_kill = it->second.getName();
                // vector to store all assignment nodes with the same lhs value
                // as this the node with number actualNode
                std::vector<unsigned int> kill_index;
                unsigned int index;
                for(auto pos = it; pos != nodes.cend(); ++pos)
                {
                    index = pos->second.getNodeNumber();
                    if(node_visited.find(index) != node_visited.cend())
                    {
                        continue;
                    }
                    else
                    {
                        if(pos->second.getName() == to_kill && pos->second.getNodeType() == NodeType::assignment)
                        {
                            gen_set[index].push_back(index);
                            kill_index.push_back(index);
                            node_visited.insert(index);
                        }
                    }
                }
                // all elements in the kill_index have the same kill_set which
                // is kill_index
                for(auto i = kill_index.begin(); i != kill_index.end(); ++i)
                {
                    std::copy(kill_index.begin(), kill_index.end(), std::back_inserter(kill_set[*i]));
                }
            }
        }
    }
}



/**
 *Function name:    reaching_definitions
 *
 *Description:      Take the list of nodes and whith their type, the reaching
 *                  definitions at each node. The algorithm is iterative
 *
 *Return :          set of node reaching the each node of the CFG
 */
void reaching_definitions(const std::vector<std::list<CFGNode>>& predecessors,
                          const std::vector<std::list<unsigned int>>& gen_set,
                          const std::vector<std::list<unsigned int>>& kill_set,
                          std::vector<std::list<unsigned int>>& out,
                          std::vector<std::list<unsigned int>>& in)
{
    unsigned int size = (unsigned int)predecessors.size();
    std::vector<std::list<unsigned int>> oldout(size);
    std::set<unsigned int>nodes_changed;
    
    // begin by adding all node to a vector, after each iteration,
    // check if the out and in sets of that node have changed, if so remove
    // that node from the vector
    for(unsigned int i = 1; i < size; i++)
    {
        nodes_changed.insert(i);
    }
    
    int nbIteration = 0;
    // the algorithm ceases when after an iteration we have no changes of
    // in and out vector for any node of the CFG
    while(!nodes_changed.empty())
    {
        ++nbIteration;
        for(int i = 1; i < predecessors.size(); i++)
        {
            
            std::list<CFGNode>pred_i = predecessors[i];
            
            auto itBegin = pred_i.cbegin();
            if(itBegin != pred_i.cend())
            {
                in[i] = out[itBegin->getNodeNumber()];
                
                ++itBegin;
                std::list<unsigned int> union_in;
                while(itBegin != pred_i.cend())
                {
                    std::set_union(out[itBegin->getNodeNumber()].cbegin(), out[itBegin->getNodeNumber()].cend(),
                                   in[i].cbegin(), in[i].cend(),std::back_inserter(union_in));
                    in[i] = union_in;
                    union_in.clear();
                    ++itBegin;
                }
            }
            
            // register the old out before the computation of the new out for comparison
            oldout[i] = out[i];
            oldout[i].sort();
          
            // out[S] = gen[S] U { in[S] - kill[S] }
            out[i].clear();
            std::list<unsigned int> diff_set;
            
            // in[S] - kill[S]
            std::set_difference(in[i].cbegin(), in[i].cend() ,
                                kill_set[i].cbegin(), kill_set[i].cend(),std::back_inserter(diff_set));
            
            //gen[S] U { in[S] - kill[S] }
            std::set_union(gen_set[i].cbegin(), gen_set[i].cend(),
                           diff_set.cbegin(), diff_set.cend(), std::back_inserter(out[i]));
            
            out[i].sort();
            
            if(out[i] == oldout[i])
            {
                nodes_changed.erase(i);
            }
        }
    }
}



/**
 *Function name:    slicing
 *
 *Description:      Take the  dependancy graph and the reaching defintions graph
 *                  to compute the slice for a particular node of the CFG
 *
 *Return :          set of node in the slice of the node with number nodeNumber
 */
void slicing(unsigned int nodeNumber,
             const std::map<unsigned int, std::list<unsigned int>>&control_dep,
             const std::vector<std::list<unsigned int>>&reaching_def,
             const std::map<unsigned int, CFGNode>&nodes,
             std::set<unsigned int>& slice)
{
    std::queue<unsigned int>node_to_visit;
    node_to_visit.push(nodeNumber);
    std::set<unsigned int>node_visited;
    while(!node_to_visit.empty())
    {
        nodeNumber = node_to_visit.front();
        
        // check in the CD graph if any node is a predecessor of nodeNumber
        // except the entry node
        for(auto it = control_dep.cbegin(); it != control_dep.cend(); ++it)
        {
            std::list<unsigned int>con_i = it->second;
            auto  val = std::find(it->second.cbegin(), it->second.cend(), nodeNumber);
            if(val != it->second.cend() && it->first != nodes.size() - 1)
            {
                if(node_visited.find(it->first) == node_visited.cend() && it->first != nodeNumber)
                {
                    node_to_visit.push(it->first);
                }
            }
        }
        
        // check in the out_set of the reaching definitions if a node has
        // the same lhs variable. That node is the slice set
        std::string nodeName = nodes.at(nodeNumber).getName();
        for(auto it = reaching_def[nodeNumber].cbegin();  it != reaching_def[nodeNumber].cend(); ++it)
        {
            if(nodes.at(*it).getNodeNumber() == nodeNumber) continue;
            if(nodes.at(*it).getName()== nodeName)
            {
                if(node_visited.find(nodeNumber) == node_visited.cend())
                {
                    node_to_visit.push(*it);
                }
            }
        }
        node_to_visit.pop();
        node_visited.insert(nodeNumber);
        slice.insert(nodeNumber);
    }
}


void graphVisualizeDom(std::ofstream& outfile, 
                   const std::vector<std::list<unsigned int>>& analysis)
{
   
    outfile << "digraph {\n";
    for(int i = 0; i < analysis.size(); i++)
    {
        if(analysis[i].empty()) continue;
        outfile <<  analysis[i].back() << "->" << i <<   std::endl;
    }
    outfile << " } ";
}

void controlDepVisualize(std::ofstream& outfile, 
                        const std::map<unsigned int, std::list<unsigned int>>& dep)
{

  outfile << "digraph {\n";
    for(auto it = dep.cbegin(); it != dep.cend(); ++it)
    {
        const std::list<unsigned int>& list_it = it->second;
        for(auto val = list_it.cbegin(); val != list_it.cend(); ++val)
        {
            outfile << it->first << "->" <<  *val << std::endl;
        }
        
    }
    outfile << " } ";
}

void slice_visualize(unsigned int number, 
                    const std::set<unsigned int>& slice, 
                    const std::map<unsigned int, CFGNode>& nodes)
{
    std::cout << "slice for \""<< number << ','<< nodes.at(number).getName() << "\":"<< std::endl;
    for(auto it = slice.cbegin(); it != slice.cend(); ++it) 
    {    
        std::cout << *it << ' ' << nodes.at(*it).getName();
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[])
{
    std::unique_ptr<CFGList> dominance_graph(new CFGList());
    dominance_graph->addNode(NodeType::assignment, "inword" , 1);
    dominance_graph->addNode(NodeType::assignment, "nl" , 2);
    dominance_graph->addNode(NodeType::assignment, "nw" , 3);
    dominance_graph->addNode(NodeType::assignment, "nc" , 4);
    dominance_graph->addNode(NodeType::assignment, "c" , 5);
    dominance_graph->addNode(NodeType::control_statement, "c" , 6);
    dominance_graph->addNode(NodeType::assignment, "nc" , 7);
    dominance_graph->addNode(NodeType::control_statement, "c" , 8);
    dominance_graph->addNode(NodeType::assignment, "nl" , 9);
    dominance_graph->addNode(NodeType::control_statement, "c" , 10);
    dominance_graph->addNode(NodeType::assignment, "inword" , 11);
    dominance_graph->addNode(NodeType::control_statement, "inword" , 12);
    dominance_graph->addNode(NodeType::assignment, "inword" , 13);
    dominance_graph->addNode(NodeType::assignment, "nw" , 14);
    dominance_graph->addNode(NodeType::assignment, "c" , 15);
    dominance_graph->addNode(NodeType::statement, "nl" , 16);
    dominance_graph->addNode(NodeType::statement, "nw" , 17);
    dominance_graph->addNode(NodeType::statement, "nc" , 18);
    dominance_graph->addNode(NodeType::control_statement, "stop", 19);
    
    dominance_graph->addVertex(1, 0);
    dominance_graph->addVertex(2, 1);
    dominance_graph->addVertex(3, 2);
    dominance_graph->addVertex(4, 3);
    dominance_graph->addVertex(5, 4);
    dominance_graph->addVertex(6, 5);
    dominance_graph->addVertex(6, 15);
    dominance_graph->addVertex(7, 6);
    dominance_graph->addVertex(8, 7);
    dominance_graph->addVertex(9, 8);
    dominance_graph->addVertex(10, 8);
    dominance_graph->addVertex(10, 9);
    dominance_graph->addVertex(11, 10);
    dominance_graph->addVertex(12, 10);
    dominance_graph->addVertex(13, 12);
    dominance_graph->addVertex(14, 13);
    dominance_graph->addVertex(15, 11);
    dominance_graph->addVertex(15, 12);
    dominance_graph->addVertex(15, 14);
    dominance_graph->addVertex(16, 6);
    dominance_graph->addVertex(17, 16);
    dominance_graph->addVertex(18, 17);
    dominance_graph->addVertex(19, 18);
   
    


    std::unique_ptr<CFGList> word_count(new CFGList());
    word_count->addNode(NodeType::assignment, "inword" , 1);
    word_count->addNode(NodeType::assignment, "nl" , 2);
    word_count->addNode(NodeType::assignment, "nw" , 3);
    word_count->addNode(NodeType::assignment, "nc" , 4);
    word_count->addNode(NodeType::assignment, "c" , 5);
    word_count->addNode(NodeType::control_statement, "c" , 6);
    word_count->addNode(NodeType::assignment, "nc" , 7);
    word_count->addNode(NodeType::control_statement, "c" , 8);
    word_count->addNode(NodeType::assignment, "nl" , 9);
    word_count->addNode(NodeType::control_statement, "c" , 10);
    word_count->addNode(NodeType::assignment, "inword" , 11);
    word_count->addNode(NodeType::control_statement, "inword" , 12);
    word_count->addNode(NodeType::assignment, "inword" , 13);
    word_count->addNode(NodeType::assignment, "nw" , 14);
    word_count->addNode(NodeType::assignment, "c" , 15);
    word_count->addNode(NodeType::statement, "nl" , 16);
    word_count->addNode(NodeType::statement, "nw" , 17);
    word_count->addNode(NodeType::statement, "nc" , 18);
    word_count->endCFG();
    
    word_count->addVertex(0, 20);
    word_count->addVertex(1, 0);
    word_count->addVertex(2, 1);
    word_count->addVertex(3, 2);
    word_count->addVertex(4, 3);
    word_count->addVertex(5, 4);
    word_count->addVertex(6, 5);
    word_count->addVertex(6, 15);
    word_count->addVertex(7, 6);
    word_count->addVertex(8, 7);
    word_count->addVertex(9, 8);
    word_count->addVertex(10, 8);
    word_count->addVertex(10, 9);
    word_count->addVertex(11, 10);
    word_count->addVertex(12, 10);
    word_count->addVertex(13, 12);
    word_count->addVertex(14, 13);
    word_count->addVertex(15, 11);
    word_count->addVertex(15, 12);
    word_count->addVertex(15, 14);
    word_count->addVertex(16, 6);
    word_count->addVertex(17, 16);
    word_count->addVertex(18, 17);
    word_count->addVertex(19, 18);
    word_count->addVertex(19, 20);
    
    std::vector<std::list<CFGNode>>predecessors = word_count->getVertex();
    std::vector<std::list<CFGNode>>successors(predecessors.size());
    std::vector<std::list<unsigned int>>postdom(predecessors.size());
    std::vector<std::list<unsigned int>>ipostdom(predecessors.size());
    std::vector<std::list<unsigned int>>dom(predecessors.size());
    std::vector<std::list<unsigned int>>idom(predecessors.size());
    
    std::vector<std::list<CFGNode>>predec_dom = dominance_graph->getVertex();
    std::vector<std::list<CFGNode>>succes_dom(predec_dom.size());
    std::vector<std::list<unsigned int>>new_dom(predec_dom.size());
    std::vector<std::list<unsigned int>>new_idom(predec_dom.size());
    // reverse the graph to obtain the successors from the predecessors or vice-versa
    reverse_graph(word_count->getNodes(), word_count->getVertex(), successors);
    reverse_graph(dominance_graph->getNodes(), dominance_graph->getVertex(), succes_dom);
    
   
    //compute post dominators and immediate post dominators
    postdominators_fast(successors, predecessors, postdom);
    immediate_postdom(successors, postdom, ipostdom);
    
 

    
    //compute dominators and immediate dominators
    dominators_fast(successors, predecessors, dom);
    immediate_dominators(predecessors, dom, idom);
   
    dominators_fast(succes_dom, predec_dom, new_dom);
    immediate_dominators(predec_dom, new_dom, new_idom);
    
    std::vector<std::list<unsigned int>> gen_set(predecessors.size());
    std::vector<std::list<unsigned int>> kill_set(predecessors.size());
    std::map<unsigned int, CFGNode> nodes = word_count->getNodes();
    std::vector<std::list<unsigned int>> out(predecessors.size());
    std::vector<std::list<unsigned int>> in(predecessors.size());
    
    
    //visualize dominance and postdominance
    std::ofstream idom_graph("idom.dot", std::ios::out);
    std::ofstream ipostdom_graph("ipdom.dot", std::ios::out);
    graphVisualizeDom(idom_graph, new_idom);
    graphVisualizeDom(ipostdom_graph, ipostdom);
    
    //compute the gen and kill sets for the reaching definitions
    generate_kill_set(nodes, gen_set, kill_set);
    reaching_definitions(predecessors,gen_set,kill_set, out,in);
    
    
    //compute the control dependancy of the CFG
    std::map<unsigned int, std::list<unsigned int>> dep;
    controldependancy(successors,postdom, ipostdom, dep);
    
    //visualize dominanc
    std::ofstream control_dep_graph("control_dependency.dot", std::ios::out);
    controlDepVisualize(control_dep_graph, dep);

    //compute the slicing for a particular node
    std::set<unsigned int> slice;
    
    int numberSlicing;
    do
    {
    std::cout << "Entrer un numero de ligne pour le slicing" << std::endl;
    std::cin >> numberSlicing;
    } while(numberSlicing < 0 );
   
    slicing(numberSlicing, dep, in, nodes, slice);
    slice_visualize((unsigned int)numberSlicing,  slice, nodes);
    slice.clear();
        
}
