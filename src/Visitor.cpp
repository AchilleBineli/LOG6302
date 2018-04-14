#include "Visitor.h"
#include "tinyxml2.h"
#include <sstream>
/**********************/
/* C++ Class traverse */
/**********************/
bool Visitor::VisitCXXRecordDecl(clang::CXXRecordDecl *D) {
    clang::SourceManager &sm = context_.getSourceManager();

    if(!sm.isInSystemHeader(D->getLocation()))
    {
    std::cout<<"[LOG6302] Visite de la classe "<< D->getNameAsString() <<"\n";
    nbDataMember = 0;
    }
    return true;
}


/**********************/
/* Break visit        */
/**********************/
bool Visitor::VisitBreakStmt(clang::BreakStmt *S)
{
    
        ++nbBreak;
        if(!parents.empty())
        std::cout<<"[LOG6302] Visite d'une expression :break\n";

    ++nodeNumber;
    return true;
}


/**********************/
/* Continue visit     */
/**********************/
bool Visitor::VisitContinueStmt(clang::ContinueStmt *S)
{
  
        ++nbContinue;
        if(!parents.empty()){
            std::cout<<"[LOG6302] Visite d'une expression :Continue\n";
    
    ++nodeNumber;}
    return true;
}


/**********************/
/* Return visit     */
/**********************/
bool Visitor::VisitReturnStmt(clang::ReturnStmt *S)
{
  
  	
 	if(!parents.empty()){
		std::cout << "[LOG6302] Visite d'une expression return\n";
  ++nbReturn;  
  }   
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
  //std::cout << "[LOG6302] Data member : " << D->getNameAsString() << std::endl;
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
    if(parents.empty())
        return true;
    else
    {
    
    
        const clang::Stmt* thenStmt = S->getThen();
        const clang::Stmt* elseStmt = S->getElse();
        //if(thenStmt != nullptr)
        //{
            std::cout << "[LOG6302] Traverse if\n";
            parents.push(std::make_pair(nodeNumber, "if"));
            nodeNumber++;
            clang::RecursiveASTVisitor<Visitor>::TraverseIfStmt(S);
            parents.pop();
            std::cout << "[LOG6302] Fin de traverse de if" << std::endl;
        //}
        #if 0
        if(elseStmt != nullptr)
        {
            std::cout << "[LOG6302] Traverse else" << std::endl;
            parents.push(std::make_pair(nodeNumber, "if"));
            nodeNumber++;
            clang::RecursiveASTVisitor<Visitor>::TraverseIfStmt(S);
            parents.pop();
            std::cout << "[LOG6302] Fin traverse else" << std::endl;
        }
        #endif
    }
    return true;
}





/***********************/
/* C++ For traverse */
/***********************/
bool Visitor::TraverseForStmt(clang::ForStmt* S)
{

    if(parents.empty())
        return true;
   
    else
    {
        std::cout << "[LOG6302] Traverse for\n";
        parents.push(std::make_pair(nodeNumber, "for"));
        nodeNumber++; 
        clang::RecursiveASTVisitor<Visitor>::TraverseForStmt(S);
        parents.pop();
        std::cout << "[LOG6302] Fin de traverse de for" << std::endl;
    }
    return true;
}



/***********************/
/* C++ While traverse */
/***********************/
bool Visitor::TraverseWhileStmt(clang::WhileStmt* S)
{
    if(parents.empty())
        return true;
   
    else
    {
        std::cout << "[LOG6302] Traverse while\n";
        parents.push(std::make_pair(nodeNumber, "While"));
        nodeNumber++; clang::RecursiveASTVisitor<Visitor>::TraverseWhileStmt(S);
        parents.pop();
        std::cout << "[LOG6302] Fin de traverse de While" << std::endl;
    }
    return true;
}


/***********************/
/* C++ Do traverse */
/***********************/
bool Visitor::TraverseDoStmt(clang::DoStmt* S)
{

    if(parents.empty())
        return true;

    else
    {
        std::cout << "[LOG6302] Traverse Do\n";
        parents.push(std::make_pair(nodeNumber, "Do"));
        nodeNumber++; clang::RecursiveASTVisitor<Visitor>::TraverseDoStmt(S);
        parents.pop();
        std::cout << "[LOG6302] Fin de traverse de Do" << std::endl;
    }
    return true;
}



/***********************/
/* C++ Switch traverse */
/***********************/
bool Visitor::TraverseSwitchStmt(clang::SwitchStmt* S)
{

    if(parents.empty())
        return true;

    else
    {
        std::cout << "[LOG6302] Traverse switch\n"; 
        parents.push(std::make_pair(nodeNumber, "Switch"));
        nodeNumber++;
        clang::RecursiveASTVisitor<Visitor>::TraverseSwitchStmt(S);
        parents.pop();
        std::cout << "[LOG6302] Fin de traverse de Switch" << std::endl;
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

	//if (/*!D->isThisDeclarationADefinition() ||*/ D == nullptr ) {
	//	return true;
	//}
	
	clang::FullSourceLoc location = context_.getFullLoc(D->getLocation());   
	clang::SourceManager &sm = context_.getSourceManager();
	//if(sm.isFromMainFile(D->getLocStart()) || clang::TranslationUnitDecl::classof(D) )
	//{

	if(!sm.isInSystemHeader(D->getLocation()) && !sm.isInExternCSystemHeader(D->getLocation()))
	{
	//	clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());

		std::string file_path = sm.getFileEntryForID(location.getFileID())->getName();
		unsigned int line_number = location.getSpellingLineNumber();
		
		unsigned int numberParameters = D->getNumParams();
		
		clang::QualType Q = D->getResultType();
		std::ostringstream name;
		name
		<< "[LOG6302] Traverse de la methode\" "
		<< D->getNameAsString()
		<< " (";
		
		
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
		<< ", node number " << nodeNumber << std::endl;

		parents.push(std::make_pair(nodeNumber, name_str));
		nodeNumber++;
		std::cout << "after  push" << std::endl;
	
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
 	     
        //std::cout 
        //<< file_path
		//<< std::endl;     
		parents.pop();  
		std::cout<<"[LOG6302] Fin traverse de la méthode \""<<  D->getNameAsString()  <<" \" \n";

		
}
//}
  return true;
}
