#ifndef ZPARSER_SEMANTIC_ANALYZER_H
#define ZPARSER_SEMANTIC_ANALYZER_H

#include "ASTVisitors.h"
#include "DataStructs.h"
#include "ZScript.h"

class SemanticAnalyzer : public RecursiveVisitor
{
public:
	// Used as a parameter to signal that no val is needed.
	static void* const paramNone;
	// Used as a parameter to signal that the rval is needed.
	static void* const paramRead;
	// Used as a parameter to signal that the lval is needed.
	static void* const paramWrite;
	// Used as a parameter to signal that both lval and rval are needed.
	static void* const paramReadWrite;

	SemanticAnalyzer(ZScript::Program& program);

	////////////////
	// Cases
	void caseProgram(ASTProgram& host, void* = NULL);
	// Statements
	void caseBlock(ASTBlock& host, void* = NULL);
    void caseStmtIf(ASTStmtIf& host, void* = NULL);
    void caseStmtIfElse(ASTStmtIfElse& host, void* = NULL);
	void caseStmtSwitch(ASTStmtSwitch& host, void* = NULL);
    void caseStmtFor(ASTStmtFor& host, void* = NULL);
    void caseStmtWhile(ASTStmtWhile& host, void* = NULL);
    void caseStmtReturn(ASTStmtReturn& host, void* = NULL);
    void caseStmtReturnVal(ASTStmtReturnVal& host, void* = NULL);
	// Declarations
	void caseTypeDef(ASTTypeDef& host, void* = NULL);
	void caseDataDeclList(ASTDataDeclList& host, void* = NULL);
	void caseDataDecl(ASTDataDecl& host, void* = NULL);
	void caseDataDeclExtraArray(ASTDataDeclExtraArray& host, void* = NULL);
    void caseFuncDecl(ASTFuncDecl& host, void* = NULL);
    void caseScript(ASTScript& host, void* = NULL);
	// Expressions
	void caseExprConst(ASTExprConst& host, void* = NULL);
	void caseExprAssign(ASTExprAssign& host, void* = NULL);
	void caseExprIdentifier(ASTExprIdentifier& host, void* = NULL);
    void caseExprArrow(ASTExprArrow& host, void* = NULL);
    void caseExprIndex(ASTExprIndex& host, void* = NULL);
	void caseExprCall(ASTExprCall& host, void* = NULL);
    void caseExprNegate(ASTExprNegate& host, void* = NULL);
    void caseExprNot(ASTExprNot& host, void* = NULL);
    void caseExprBitNot(ASTExprBitNot& host, void* = NULL);
    void caseExprIncrement(ASTExprIncrement& host, void* = NULL);
    void caseExprPreIncrement(ASTExprPreIncrement& host, void* = NULL);
    void caseExprDecrement(ASTExprDecrement& host, void* = NULL);
    void caseExprPreDecrement(ASTExprPreDecrement& host, void* = NULL);
    void caseExprAnd(ASTExprAnd& host, void* = NULL);
    void caseExprOr(ASTExprOr& host, void* = NULL);
    void caseExprGT(ASTExprGT& host, void* = NULL);
    void caseExprGE(ASTExprGE& host, void* = NULL);
    void caseExprLT(ASTExprLT& host, void* = NULL);
    void caseExprLE(ASTExprLE& host, void* = NULL);
    void caseExprEQ(ASTExprEQ& host, void* = NULL);
    void caseExprNE(ASTExprNE& host, void* = NULL);
    void caseExprPlus(ASTExprPlus& host, void* = NULL);
    void caseExprMinus(ASTExprMinus& host, void* = NULL);
    void caseExprTimes(ASTExprTimes& host, void* = NULL);
    void caseExprDivide(ASTExprDivide& host, void* = NULL);
    void caseExprModulo(ASTExprModulo& host, void* = NULL);
    void caseExprBitAnd(ASTExprBitAnd& host, void* = NULL);
    void caseExprBitOr(ASTExprBitOr& host, void* = NULL);
    void caseExprBitXor(ASTExprBitXor& host, void* = NULL);
    void caseExprLShift(ASTExprLShift& host, void* = NULL);
    void caseExprRShift(ASTExprRShift& host, void* = NULL);
	// Literals
	void caseStringLiteral(ASTStringLiteral& host, void* = NULL);
	void caseArrayLiteral(ASTArrayLiteral& host, void* = NULL);

	////////////////
	bool hasFailed() const {return failure;}

private:
	ZScript::Program& program;
	// Current scope.
	ZScript::Scope* scope;
	// Current function return type.
	ZVarType const* returnType;

	bool deprecateGlobals;

	// Signal a compile error if source can't be cast to target.
	void checkCast(ZVarType const& sourceType, ZVarType const& targetType,
				   AST* node = NULL);

	void analyzeFunctionInternals(ZScript::Function& function);

	////////////////////////////////////////////////////////////////
	// Helper Functions.

	void analyzeUnaryExpr(ASTUnaryExpr& host, ZVarType const& type);
	void analyzeIncrement(ASTUnaryExpr& host);
	void analyzeBinaryExpr(
			ASTBinaryExpr& host, ZVarType const& leftType,
			ZVarType const& rightType);

};

#endif

