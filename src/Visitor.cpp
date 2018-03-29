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

/**********************/
/* For visit          */
/**********************/
bool Visitor::VisitForStmt(clang::ForStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  	std::cout<<"[LOG6302] Visite d'une expression :For\n";
  	++nbFor;
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
	clang::RecursiveASTVisitor<Visitor>::TraverseCXXMethodDecl(static_cast<clang::CXXMethodDecl *>(S));
//  	clang::RecursiveASTVisitor<Visitor>::TraverseCXXMethodDecl(S);
  	std::cout << "[LOG6302] Fin expression : For\n";
  }
  parents.pop();
  return true;
}

/**********************/
/* Break visit        */
/**********************/
bool Visitor::VisitBreakStmt(clang::BreakStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  std::cout<<"[LOG6302] Visite d'une expression :break\n";
  ++nbBreak;
  }
  return true;
}


/**********************/
/* Continue visit     */
/**********************/
bool Visitor::VisitContinueStmt(clang::ContinueStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  
  std::cout<<"[LOG6302] Visite d'une expression :Continue\n";
  ++nbContinue;
  }
  return true;
}


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


/**********************/
/* Return visit     */
/**********************/
bool Visitor::VisitReturnStmt(clang::ReturnStmt *S)
{
	const clang::Stmt* st = nullptr;
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
 // std::cout<<"[LOG6302] Visite d'une expression :Return\n";
  	++nbReturn;
 	if(!parents.empty())
  	{
		std::cout << "return " << ", node number" << nodeNumber << ", from node " << parents.top().first << std::endl;
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
  return true;
}




/**********************/
/* visit declarations */
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
/* visit declarations */
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
		<< D->getResultType().getAsString()
		<< std::endl;
		std::string name_str = name.str();
		std::cout << name_str << std::endl;
		std::cout << "Node number " << std::to_string(nodeNumber) << std::endl;
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
 
		parents.pop();
}

  return true;
}
