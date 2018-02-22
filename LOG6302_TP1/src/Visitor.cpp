#include "Visitor.h"

/**********************/
/* C++ Class traverse */
/**********************/
bool Visitor::VisitCXXRecordDecl(clang::CXXRecordDecl *D) {
  if(context_.getSourceManager().isFromMainFile(D->getLocStart()) ||  clang::TranslationUnitDecl::classof(D))
  {
  std::cout<<"[LOG6302] Visite de la classe \""<<D->getName().str()<<"\"\n";
  nbVar = 0;
}
  return true;
}

/**********************/
/* If visit           */
/**********************/

bool Visitor::VisitIfStmt(clang::IfStmt *S) {
  
   if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {std::cout<<"[LOG6302] Visite d'une condition : \" if ("<<GetStatementString(S->getCond())<<") \"\n";
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
  std::cout<<"[LOG6302] Visite d'une expression : \" While ("<<GetStatementString(S->getCond())<<") \"\n";
  ++nbWhile;}
  return true;
}
 
/**********************/
/* For visit          */
/**********************/
bool Visitor::VisitForStmt(clang::ForStmt *S)
{
	 if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  std::cout<<"[LOG6302] Visite d'une expression : \" For \"\n";
  ++nbFor;}
  return true;
}

/**********************/
/* Break visit        */
/**********************/
bool Visitor::VisitBreakStmt(clang::BreakStmt *S)
{
  if(context_.getSourceManager().isFromMainFile(S->getLocStart()))
  {
  std::cout<<"[LOG6302] Visite d'une expression : \" break \"\n";
  ++nbBreak;
  }
  return true;
}

bool Visitor::VisitVarDecl(clang::VarDecl* D)
{
	if(context_.getSourceManager().isFromMainFile(D->getLocStart()))
	{
		if(D->hasLocalStorage() || D->isStaticLocal())
       		{
		//std::string varName = D->getQualifiedNameAsString();
		//std::string varType = D->getType().getAsString();
		//std::cout << "visit de la variable " << varName << " de type " << varType << std::endl;
		++nbVar;
		}
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
  std::cout<<"[LOG6302] Visite d'une expression : \" Continue \"\n";
  ++nbContinue;}
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
	if (!D->isThisDeclarationADefinition() /*|| static_cast<clang::NamedDecl>(D).getIdentifier()*/) {
		return true;
	}
	
	clang::SourceManager &sm = context_.getSourceManager();
	//const char* declKindName = D->getDeclKindName();	
	if(sm.isFromMainFile(D->getLocStart()) || clang::TranslationUnitDecl::classof(D) )
	{ 
		
		clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());

		std::string file_path = sm.getFileEntryForID(location.getFileID())->getName();
		std::cout << std::endl <<"PATH_YESSS" << std::endl;
		unsigned int line_number = location.getSpellingLineNumber();
		std::cout << "LINE_NUMBER_YESSSS" << std::endl; 

		std::cout
		<< "\" ("
                << file_path
                << ":"
                << line_number
                <<")\n"
		<< "[LOG6302] Traverse de la méthode \""
		
		<<  D->getName().str()<< std::endl << "NAME_YESSSS" << std::endl;
	//	<< "\" ("
	//	<< file_path
	//	<< ":"
	//	<< line_number
	//	<<")\n";


		clang::RecursiveASTVisitor<Visitor>::TraverseCXXMethodDecl(D);

		std::cout << "Nombre de if = " << nbIf << std::endl;
		std::cout << "Nombre de for = " << nbFor << std::endl;
		std::cout << "Nombre de while = " << nbWhile << std::endl;
		std::cout << "Nombre de Break = " << nbBreak << std::endl;
		std::cout << "Nombre de Continue = " << nbContinue << std::endl;
		std::cout << "Nombre de variables locales = " << nbVar  << std::endl;
	
		std::cout<<"[LOG6302] Fin traverse de la méthode \""<<  D->getName().str()  <<" \" \n";
	}
 
   return true;
}
