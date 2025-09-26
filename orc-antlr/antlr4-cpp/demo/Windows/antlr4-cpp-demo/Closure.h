#pragma once

#include <string>
#include <vector>
#include "OrcParser.h"

using namespace antlrcpptest;
/*
闭包处理思路
- 遍历ast, 判断变量是否被捕获，如果被捕获，把捕获的信息记录到closureInfo中. 每个ClosureExpression都会captureInfo的字段
- 生成block class 
- 创建block引用变量
- 替换对变量的访问、赋值。 需要考虑是不是在嵌套的闭包中? 对于for init，需要有特殊的处理
- 生成闭包结构体（暂不考虑附带头信息)
- 生成闭包创建函数
- 把闭包字面量替换为 new 闭包类，传入参数

要记录的信息
- block context
- block 生成的变量名、类名
- 
*/

class CaptureBlockInfo;
class UsedVarInfo {
public:
    OrcParser::IdentifierExpressionContext* idExpr = NULL;
    OrcParser::ThisExpressionContext* thisExpr = NULL;
    ClosureInfo* closureInfo = nullptr;

    OrcRuleContext* getExpr() {
        if (idExpr) {
            return idExpr;
        }
        if (thisExpr) {
            return thisExpr;
        }
        return NULL;
    }
};

//闭包捕获的信息
class CaptureVarInfo {
public:
    // var|arg|self|super|scope|globalVar|staticVar
    std::string type;
    std::string varName;

    OrcParser::VarDeclarationContext* varDeclaration = nullptr;
    OrcParser::ArgumentDeclarationContext* argumentDeclaration = nullptr;
    OrcParser::ScopeStatementContext* scopeStatement = nullptr;
    OrcParser::SuperExpressionContext* superExpression = NULL;
    OrcParser::ThisExpressionContext* thisExpression = NULL;

    OrcParser::BlockContext* blockContext = NULL;
    OrcParser::IterationStatementContext* iterationStatementContext = NULL;
    
    //归属的blockInfo
    std::weak_ptr<CaptureBlockInfo> ownedBlockInfo;

    //被哪些id expr 使用了
    std::vector<UsedVarInfo> usedExprs;

    void addUsedExpr_once(OrcParser::IdentifierExpressionContext* expr, ClosureInfo* closureInfo);

    void addUsedThisExpr_once(OrcParser::ThisExpressionContext* expr, ClosureInfo* closureInfo);

    //被哪些闭包使用了
    //std::vector<OrcParser::ClosureExpressionContext*> usedByClosures;
};

//哪个块要生成闭包块
class CaptureBlockInfo {
public:
    std::vector<std::shared_ptr<CaptureVarInfo>> captureVarInfos;

    OrcRuleContext* blockCtx;


    //标记位，是否已生成类
    bool flag_blockClassGenerated = false;
    //标记是否已生成实例
    bool flag_blockVarGenerated = false;

    std::string blockClassName;

    std::string goc_blockClassName();
    std::string calc_blockVarName();
    std::string calc_blockFiniFunctionName();


    //是否已经去找过了
    bool hadFind_closureThatBlockIsIn = false;
    OrcParser::ClosureExpressionContext* closureThatBlockIsIn = NULL;
    //查找块所在的closureExpr,如果不在closure,就返回空
    OrcParser::ClosureExpressionContext* getOrFind_closureThatBlockIsIn();


    bool hasVar(std::string varName);
    void addCaptureVarInfos_once(std::shared_ptr<CaptureVarInfo> info);

};

//闭包内用了哪些变量,用了哪些块
class ClosureInfo {
public:
    OrcParser::ClosureExpressionContext* ctx;
    std::string closureOriginalName; //声明闭包里的名称
    std::vector<std::shared_ptr<CaptureBlockInfo>> captureBlockInfos;
    std::vector<std::shared_ptr<CaptureVarInfo>> captureVarInfos;

    ClosureInfo* parent = NULL; 

    //bool hasBlock(std::shared_ptr<CaptureBlockInfo> blockInfo);

    void addBlockInfo_once(std::shared_ptr<CaptureBlockInfo>);
    void addCaptureVarInfo_once(std::shared_ptr<CaptureVarInfo>);


    std::string closureClassName;
    std::string closureFunctionName;
    std::string closureMakeFunctionName;
    std::string goc_closureClassName();
    //外置的函数体名称
    std::string goc_closureFunctionName();
    std::string goc_closureMakeFunctionName();
    //解引用闭包对block的引用
    std::string goc_closureFiniFunctionName();
};
