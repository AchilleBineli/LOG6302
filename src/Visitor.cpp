#include "Visitor.h"
#include "tinyxml2.h"
#include <sstream>
/**********************/
/* C++ Class traverse */
/**********************/
bool Visitor::VisitCXXRecordDecl(clang::CXXRecordDecl *D) {
    clang::SourceManager &sm = context_.getSourceManager();
    if(!D->isThisDeclarationADefinition() || D == nullptr )
    {
        return true;
    }
    if(!sm.isInSystemHeader(D->getLocStart()))
    {
    std::cout<<"[LOG6302] Visite de la classe "<< D->getNameAsString() <<"\n";
    nbDataMember = 0;
    }
    return true;
}

#if 0
/**********************/
/* If visit           */
/**********************/
bool Visitor::VisitIfStmt(clang::IfStmt *S) {

   if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
	  std::cout<<"[LOG6302] Visite d'une condition :if\n";
	  ++nbIf;
	  std::cout<<"[LOG6302] Fin condition :if\n";
}
  return true;
}
#endif


#if 0
/**********************/
/* While visit        */
/**********************/
bool Visitor::VisitWhileStmt(clang::WhileStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  std::cout<<"[LOG6302] Visite d'une expression :While\n";
  ++nbWhile;
  std::cout<<"[LOG6302] Fin expression : While\n";
  }
  return true;
}
#endif

#if 0
/**********************/
/* For visit          */
/**********************/
bool Visitor::VisitForStmt(clang::ForStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  	std::cout<<"[LOG6302] Visite d'une expression :For\n";
  	++nbFor;
#if 0
  	parents.push(std::make_pair(nodeNumber, "if"));
  	nodeNumber++;
  	if(!parents.empty())
  	{
	  std::cout << "Node number" << nodeNumber << ", from node " << parents.top().first << std::endl;
  	}
//	clang::RecursiveASTVisitor<Visitor>::VisitForStmt(static_cast<clang::Stmt*>(S));
//	clang::RecursiveASTVisitor<Visitor>::VisitIfStmt(static_cast<clang::Stmt*>(S));
//	clang::RecursiveASTVisitor<Visitor>::VisitSwitchStmt(static_cast<clang::Stmt*>(S));
//	clang::RecursiveASTVisitor<Visitor>::VisitWhileStmt(static_cast<clang::Stmt*>(S));
//	clang::RecursiveASTVisitor<Visitor>::VisitDoStmt(static_cast<clang::Stmt*>(S));
//	clang::RecursiveASTVisitor<Visitor>::VisitBreakStmt(static_cast<clang::Stmt*>(S));
//	clang::RecursiveASTVisitor<Visitor>::VisitReturnStmt(static_cast<clang::Stmt*>(S));
//	clang::RecursiveASTVisitor<Visitor>::VisitContinueStmt(static_cast<clang::Stmt*>(S));
//	clang::RecursiveASTVisitor<Visitor>::TraverseCXXMethodDecl(static_cast<clang::CXXMethodDecl *>(S));
//  	clang::RecursiveASTVisitor<Visitor>::TraverseCXXMethodDecl(S);
  	
#endif 
  	std::cout << "[LOG6302] Fin expression : For\n";

  }
//  parents.pop();
  return true;
}
#endif

/**********************/
/* Break visit        */
/**********************/
bool Visitor::VisitBreakStmt(clang::BreakStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  std::cout<<"[LOG6302] Visite d'une expression :break" << ", node number" << nodeNumber << ", parent node " << parents.top().first << std::endl;;
  ++nbBreak;
  }
  ++nodeNumber;
  return true;
}


/**********************/
/* Continue visit     */
/**********************/
bool Visitor::VisitContinueStmt(clang::ContinueStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  
  std::cout<<"[LOG6302] Visite d'une expression :Continue " << ", node number" << nodeNumber << ", parent node " << parents.top().first << std::endl;
  ++nbContinue;
  }
  ++nodeNumber;
  return true;
}

#if 0
/**********************/
/* Do visit     */
/**********************/
bool Visitor::VisitDoStmt(clang::DoStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  std::cout<<"[LOG6302] Visite d'une expression :Do\n";
  ++nbDo;
  std::cout<<"[LOG6302] Fin expression :Do\n ";
  }
  return true;
}
#endif

#if 0
/**********************/
/* Switch visit     */
/**********************/
bool Visitor::VisitSwitchStmt(clang::SwitchStmt *S)
{
//	clang::Stmt* st = nullptr;
//	clang::Stmt::child_iterator it  = S->child_begin();
//	for(it; it != S->child_end(); ++it)
//	{
//		//st = it->get<clang::Stmt>();
//		it->dump();
//	}i

  
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  std::cout<<"[LOG6302] Visite d'une expression :Switch\n";
  ++nbSwitch;
  std::cout<<"[LOG6302] Fin expression :Switch\n ";
  }
  return true;
}
#endif

/**********************/
/* Return visit     */
/**********************/
bool Visitor::VisitReturnStmt(clang::ReturnStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {

  	++nbReturn;
 	if(!parents.empty())
  	{
		std::cout << "[LOG6302] Visite d'une expression return " << ", node number" << nodeNumber << ", parent node " << parents.top().first << std::endl;
	}
  }
  
#if 0
//      clang::Stmt* st = nullptr;
      clang::Stmt::child_iterator it  = S->child_begin();
      for(it; it != S->child_end(); ++it)
      {
              //st = it->get<clang::Stmt>();
	      if(*it == nullptr ) return false;
              it->dump();
      }
#endif
  ++nodeNumber;      
  return true;
}


/**********************/
/* visit data members */
/**********************/
bool Visitor::VisitFieldDecl(clang::FieldDecl* D)
{
  clang::SourceManager &sm = context_.getSourceManager();

  if(sm.isInSystemHeader(D->getLocStart()))
  {
    return true;
  }
  ++nbDataMember;
  std::cout << "[LOG6302] Data member : " << D->getNameAsString() << std::endl;
  return true; 
}


/**********************/
/* visit variables */
/**********************/
bool Visitor::VisitVarDecl(clang::VarDecl* D)
{	
	clang::SourceManager &sm = context_.getSourceManager();
	if(context_.getSourceManager().isFromMainFile(D->getLocStart()) && !sm.isInSystemHeader(D->getLocStart()) )
	{
		++nbVar;
	}
	return true;
}


/***********************/
/* C++ If traverse */
/***********************/
bool Visitor::TraverseIfStmt(clang::IfStmt* S)
{

  if(!parents.empty())
  {
          std::cout << "[LOG6302] Traverse if,  node number" << nodeNumber << ", parent node " << parents.top().first << ", parent name " << parents.top().second << std::endl;
  }
  parents.push(std::make_pair(nodeNumber, "if"));
  nodeNumber++;
  clang::RecursiveASTVisitor<Visitor>::TraverseIfStmt(S);
  parents.pop();
  std::cout << "[LOG6302] Fin de traverse de if" << std::endl;
  return true;
}





/***********************/
/* C++ For traverse */
/***********************/
bool Visitor::TraverseForStmt(clang::ForStmt* S)
{

  if(!parents.empty())
  {
	  std::cout << "[LOG6302] Traverse for,  node number" << nodeNumber << ", parent node " << parents.top().first << ", parent name " << parents.top().second<< std::endl;
  }
  parents.push(std::make_pair(nodeNumber, "for"));
  nodeNumber++; 
  clang::RecursiveASTVisitor<Visitor>::TraverseForStmt(S);
  parents.pop();
  std::cout << "[LOG6302] Fin de traverse de for" << std::endl;
  return true;
}



/***********************/
/* C++ While traverse */
/***********************/
bool Visitor::TraverseWhileStmt(clang::WhileStmt* S)
{

  if(!parents.empty())
  {
          std::cout << "[LOG6302] Traverse while,  node number" << nodeNumber << ", parent number " << parents.top().first << ", parent name " << parents.top().second << std::endl;
  }

  parents.push(std::make_pair(nodeNumber, "While"));
  nodeNumber++; clang::RecursiveASTVisitor<Visitor>::TraverseWhileStmt(S);
  parents.pop();
  std::cout << "[LOG6302] Fin de traverse de While" << std::endl;
  return true;
}


/***********************/
/* C++ Do traverse */
/***********************/
bool Visitor::TraverseDoStmt(clang::DoStmt* S)
{

  if(!parents.empty())
  {
          std::cout << "[LOG6302] Traverse Do,  node number" << nodeNumber << ", parent node " << parents.top().first << ", parent name " << parents.top().second << std::endl;
  }

  parents.push(std::make_pair(nodeNumber, "Do"));
  nodeNumber++; clang::RecursiveASTVisitor<Visitor>::TraverseDoStmt(S);
  parents.pop();
  std::cout << "[LOG6302] Fin de traverse de Do" << std::endl;
  return true;
}



/***********************/
/* C++ Switch traverse */
/***********************/
bool Visitor::TraverseSwitchStmt(clang::SwitchStmt* S)
{

  if(!parents.empty())
  {
          std::cout << "[LOG6302] Traverse switch,  node number" << nodeNumber << ", parent node " << parents.top().first << ", parent name " << parents.top().second << std::endl;
  }
  parents.push(std::make_pair(nodeNumber, "Switch"));
  nodeNumber++;
  clang::RecursiveASTVisitor<Visitor>::TraverseSwitchStmt(S);
  parents.pop();
  std::cout << "[LOG6302] Fin de traverse de Switch" << std::endl;
  return true;
}



/***********************/
/* C++ Method traverse */
/***********************/
bool Visitor::TraverseCXXMethodDecl(clang::CXXMethodDecl *D) {

	nbIf = 0;
	nbWhile = 0;
	nbFor = 0;
	nbContinue = 0;
	nbBreak = 0;
	nbSwitch = 0;
	nbDo = 0;
	nbVar = 0;
	nodeNumber = 0;

	if (!D->isThisDeclarationADefinition() || D == nullptr ) {
		return true;
	}
   
	clang::SourceManager &sm = context_.getSourceManager();
	if(sm.isFromMainFile(D->getLocStart()) || clang::TranslationUnitDecl::classof(D) )
	{

		clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());

		std::string file_path = sm.getFileEntryForID(location.getFileID())->getName();
		unsigned int line_number = location.getSpellingLineNumber();
		
		unsigned int numberParameters = D->getNumParams();
		
		clang::QualType Q = D->getResultType();
		std::ostringstream name;
		name
		<< "[LOG6302] Traverse de la méthode\" "
		<< D->getNameAsString()
		<< " (";
		
		// XML additions
		#if 0
		TinyXML::XMLElement root;
		root.setAttribute("Node 1", D->getNameString());
		root.setAttribute("Node 2", )
		
		#endif
				
		
		clang::ParmVarDecl* decl;  
		std::string paramType;

		for(int i = 0; i < numberParameters; ++i)
		{
			decl = D->getParamDecl(i);
		       	paramType = decl->getType().getAsString();	
			name << paramType; 
			if(i  != numberParameters - 1) 	
				std::cout << ", ";
		}	
		
		name
		<< ") "
		<< " : " 
		<< D->getResultType().getAsString();

		std::string name_str = name.str();
		std::cout 
	        << name_str
		<< ", node number " << nodeNumber;
	       
		if(!parents.empty())
		{
		std::cout << ", parent node " << parents.top().first << ", parent name " << parents.top().second;
		}
		std::cout << std::endl;

		parents.push(std::make_pair(nodeNumber, name_str));
		nodeNumber++;
#if 0 
		nodes[nodeNumber] = name_str;
		edges.push_back(std::list<int>())
		++nodeNumber;

		nodes[nodeNumnber] = "Exit" + name_str;
		edges.push_back(std::list<int>());
		++nodeNumber;
#endif		
		/*
		std::cout 
		<< file_path
		<< ":"
		<< line_number
		<< std::endl;
		*/

		clang::RecursiveASTVisitor<Visitor>::TraverseCXXMethodDecl(D);

//		std::cout << "Nombre de if = " << nbIf << std::endl;
//		std::cout << "Nombre de for = " << nbFor << std::endl;
//		std::cout << "Nombre de while = " << nbWhile << std::endl;
//		std::cout << "Nombre de Break = " << nbBreak << std::endl;
//		std::cout << "Nombre de Continue = " << nbContinue << std::endl;
//		std::cout << "Nombre de variables locales = " << nbVar  << std::endl;
        
		std::cout<<"[LOG6302] Fin traverse de la méthode \""<<  D->getNameAsString()  <<" \" \n";
		nodeNumber = 0; 
		parents.pop();
}

  return true;
}
