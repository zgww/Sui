#include "./OrcParserBase.h"
#include "antlr4-runtime.h"
#include "./OrcParser.h"
#include "Closure.h"

using namespace antlr4;
using namespace antlrcpptest;


OrcRuleContext::OrcRuleContext(ParserRuleContext* parent, size_t invokingStateNumber) 
    : ParserRuleContext(parent, invokingStateNumber) {
}

OrcRuleContext* OrcRuleContext::insert(antlr4::tree::ParseTree* kid, int at, bool changeParent)
{
    if (changeParent) {
        kid->parent = this;
    }
    if (at == -1) {
        children.push_back(kid);
    } 
    else {
        children.insert(children.begin() + at, kid);
    }
    return this;
}

void OrcRuleContext::removeChild(antlr4::tree::ParseTree* kid)
{
    auto it = std::find(children.begin(), children.end(), kid);
    if (it != children.end()) {
        children.erase(it);
        //kid->parent = NULL;
    }
}

void OrcRuleContext::replaceChild(antlr4::tree::ParseTree* kid, antlr4::tree::ParseTree* newkid) {
    for (int i = 0; i < children.size(); i++) {
        auto cur = children[i];
        if (cur == kid) {
            children.erase(children.begin() + i);
            kid->parent = NULL;

            children.insert(children.begin() + i, newkid);
            newkid->parent = this;
            break;
        }
    }
}
void OrcRuleContext::copyFrom(ParserRuleContext* ctx)
{
    if (ctx == NULL) {
        return;
    }
    ParserRuleContext::copyFrom(ctx);
}




OrcParserBase::OrcParserBase(TokenStream* input) : Parser(input) {
}

bool OrcParserBase::closeBrace() {
    return _input->LT(1)->getType() == OrcParser::CloseBrace;
}

bool OrcParserBase::lineTerminatorAhead() {
    // Get the token ahead of the current index.
    int possibleIndexEosToken = this->getCurrentToken()->getTokenIndex() - 1;
    auto ahead = _input->get(possibleIndexEosToken);

    if (ahead->getChannel() != Lexer::HIDDEN) {
        // We're only interested in tokens on the HIDDEN channel.
        return false;
    }

    if (ahead->getType() == OrcParser::LineTerminator) {
        // There is definitely a line terminator ahead.
        return true;
    }

    if (ahead->getType() == OrcParser::Whitespace) {
        // Get the token ahead of the current whitespaces.
        possibleIndexEosToken = this->getCurrentToken()->getTokenIndex() - 2;
        ahead = _input->get(possibleIndexEosToken);
    }

    // Get the token's text and type.
    std::string text = ahead->getText();
    int type = ahead->getType();

    // Check if the token is, or contains a line terminator.
    return (
        type == OrcParser::BlockComment 
        && (text.find("\r") != std::string::npos || text.find("\n") != std::string::npos)) 
        || type == OrcParser::LineComment
        ||
        (type == OrcParser::LineTerminator);
}



std::shared_ptr<CaptureVarInfo> OrcRuleContext::goc_captureInfo() {
    if (!captureInfo) {
        captureInfo = std::make_shared<CaptureVarInfo>();
    }
    return captureInfo;
}
std::shared_ptr<CaptureBlockInfo> OrcRuleContext::goc_captureBlockInfo() {
    if (!captureBlockInfo) {
        captureBlockInfo = std::make_shared<CaptureBlockInfo>();
        captureBlockInfo->blockCtx = this;
    }
    return captureBlockInfo;
}
std::shared_ptr<ClosureInfo> OrcRuleContext::goc_closureInfo() {
    if (!closureInfo) {
        closureInfo = std::make_shared<ClosureInfo>();
    }
    return closureInfo;
}