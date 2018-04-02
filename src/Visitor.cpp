#include "Visitor.h"
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
    std::cout<<"[LOG6302] Visite de la classe :"<< D->getNameAsString() <<"\n";
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
//std::cout<<"[LOG6302] Visite d'une condition : \" if "<< "" /*GetStatementString(S->getCond())*/ <<" \"\n";
  ++nbIf;
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
 // std::cout<<"[LOG6302] Visite d'une expression : \" While " << "" /*GetStatementString(S->getCond())*/<< " \"\n";
  ++nbWhile;
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
//  std::cout<<"[LOG6302] Visite d'une expression : \" For \"\n";
  ++nbFor;
  }
  return true;
}

/**********************/
/* Break visit        */
/**********************/
bool Visitor::VisitBreakStmt(clang::BreakStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
 // std::cout<<"[LOG6302] Visite d'une expression : \" break \"\n";
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
 // std::cout<<"[LOG6302] Visite d'une expression : \" Continue \"\n";
  ++nbContinue;
  }
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
  std::cout << "[LOG6302] Data member :" << D->getNameAsString() << std::endl;
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
	nbVar = 0;

	if (!D->isThisDeclarationADefinition() && !D->isPure() || D == nullptr ) {
		return true;
	}

	clang::SourceManager &sm = context_.getSourceManager();
	//if(/*sm.isFromMainFile(D->getLocation()) || */clang::TranslationUnitDecl::classof(D) )
	//{
		if(!sm.isInSystemHeader(D->getLocation()) && !sm.isInExternCSystemHeader(D->getLocation()))
		{

		clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());

		std::string file_path = sm.getFileEntryForID(location.getFileID())->getName();
		unsigned int line_number = location.getSpellingLineNumber();
		
		unsigned int numberParameters = D->getNumParams();
		
		
		std::ostringstream name;
		
		std::cout                 
		<< "[LOG6302] Traverse de la méthode \"";
		
		name 
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
				name << ", ";
		}	
		
		name
		<< ") "		
		<< " : " 
		<< D->getResultType().getAsString();
		if(D->isPure())
		{
		    name << " = 0";
		}
		std::cout 
		<< name.str()
		<< std::endl;

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
		}
	//}

  return true;
}
