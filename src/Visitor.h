#ifndef LOG6302_VISITOR_H
#define LOG6302_VISITOR_H

#include <iostream>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTContext.h>
#include <clang/Lex/Lexer.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/Decl.h>
#include <clang/Basic/LLVM.h> 
#include <stack>
#include <utility>
#include <string>
/**
 * LOG6302 Cette classe est un exemple d'un visiteur récursif de clang. À l'intérieur, vous pouvez y trouver deux exemples
 * de visites, et un exemple de traverse.
 */
class Visitor : public clang::RecursiveASTVisitor<Visitor> {
public:

  Visitor(clang::ASTContext &context) : context_(context) {};

  // Visites
  bool VisitCXXRecordDecl(clang::CXXRecordDecl *D);
  bool VisitIfStmt(clang::IfStmt *S);
  bool VisitWhileStmt(clang::WhileStmt *S);
  bool VisitForStmt(clang::ForStmt *S);
  bool VisitBreakStmt(clang::BreakStmt *S);
  bool VisitContinueStmt(clang::ContinueStmt *S);
  bool VisitSwitchStmt(clang::SwitchStmt *S);
  bool VisitDoStmt(clang::DoStmt *S);
  bool VisitReturnStmt(clang::ReturnStmt *S);
  bool VisitVarDecl(clang::VarDecl* D);
  bool VisitFieldDecl(clang::FieldDecl* D); 

  // Traverses
  bool TraverseCXXMethodDecl(clang::CXXMethodDecl *D);

private:
  clang::ASTContext &context_;
  int nbIf = 0;
  int nbWhile = 0;
  int nbFor = 0;
  int nbContinue = 0;
  int nbBreak = 0;
  int nbDo = 0;
  int nbSwitch = 0;
  int nbReturn = 0;
  int nbVar = 0;
  int nbDataMember = 0;
  int nodeNumber = 0;
  std::stack<std::pair<unsigned int, std::string>> parents;
  std::map<unsigned int, std::string> nodes;
  std::vector<std::list<unsigned int>>edges;
  std::string GetStatementString(clang::Stmt *S) {
    bool invalid;
    if (!S) return "Something";

    clang::CharSourceRange conditionRange = clang::CharSourceRange::getTokenRange(S->getLocStart(), S->getLocEnd());
    std::string str = clang::Lexer::getSourceText(conditionRange, context_.getSourceManager(), context_.getLangOpts(), &invalid);
    if (invalid)
      return "Something";
    encode(str);
    return str;
  }

  void encode(std::string& data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
      switch(data[pos]) {
        case '&':  buffer.append("&amp;");       break;
        case '\"': buffer.append("&quot;");      break;
        case '\'': buffer.append("&apos;");      break;
        case '<':  buffer.append("&lt;");        break;
        case '>':  buffer.append("&gt;");        break;
        case '\n':  buffer.append("\\n");        break;
        case '\\':  buffer.append("\\\\");        break;
        case '|':  buffer.append("\\|");        break;
        default:   buffer.append(&data[pos], 1); break;
      }
    }
    data.swap(buffer);
  }
};


#endif //LOG6302_VISITOR_H
