#pragma once
#include "antlr4-runtime.h"
#include <string>


class CaptureVarInfo;
class CaptureBlockInfo;
class ClosureInfo;
class SymbolTypeWithHostSpace;

class OrcRuleContext : public antlr4::ParserRuleContext {
public:
    // 全名称
    std::string fullname;
    bool prevent_classNameIdExpr_translate= false; //阻止classNameIdExpr被转为vtable_ClassName_init...
    bool translateVisited = false; //用来表示在转译过程中已访问过.由于会动态生成statement,影响children遍历的顺序，可能导致二次访问同一个statement,所以需要此
    bool forWrappedBlock = false; //for语句是不是已经外包了一层block了


    int numberTmpThis = 0;//第几个TmpThis;  用来在生成 tmpThis 变量时， 产生唯一的变量名字
    int numberReturn = 0;//第几个return;  用来在生成 tmpReturn 变量时， 产生唯一的变量名字

    bool needCreateMeta = false; //是否需要生成meta
    bool isStaticStruct = false; //是否是静态结构体。在创建闭包时，需要

    bool isTmpThisVarForClosure = false; //是不是临时的this变量，用于closureType,如果true,就不需要生成URGC_VAR_CLEANUP
    //bool isStatic = false; // 用于struct, class

    //缓存符号
    std::shared_ptr<SymbolTypeWithHostSpace> symbolTypeWithHostSpace = nullptr;


    OrcRuleContext() = default;
    OrcRuleContext(ParserRuleContext* parent, size_t invokingStateNumber);

    OrcRuleContext* insert(antlr4::tree::ParseTree *kid, int at = -1, bool changeParent=true);
    void removeChild(antlr4::tree::ParseTree* kid);
    void replaceChild(antlr4::tree::ParseTree* kid, antlr4::tree::ParseTree* newkid);


    void copyFrom(ParserRuleContext* ctx) override;


    std::shared_ptr<CaptureVarInfo> captureInfo = nullptr;//闭包捕获的相关信息
    std::shared_ptr<CaptureBlockInfo> captureBlockInfo = nullptr;//闭包捕获的相关信息
    std::shared_ptr<ClosureInfo> closureInfo = nullptr;//闭包捕获的相关信息

    std::shared_ptr<CaptureVarInfo> goc_captureInfo();
    std::shared_ptr<CaptureBlockInfo> goc_captureBlockInfo();
    std::shared_ptr<ClosureInfo> goc_closureInfo();
};

class OrcParserBase : public antlr4::Parser{
public:

    OrcParserBase(antlr4::TokenStream* input);

    bool closeBrace();
    bool lineTerminatorAhead();
};

