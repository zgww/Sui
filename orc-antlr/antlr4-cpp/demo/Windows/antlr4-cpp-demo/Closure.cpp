#include "Closure.h"
#include <format>
#include "Symbol.h"


OrcParser::ClosureExpressionContext* CaptureBlockInfo::getOrFind_closureThatBlockIsIn()
{
	if (!hadFind_closureThatBlockIsIn) {
		hadFind_closureThatBlockIsIn = true;
		closureThatBlockIsIn = ast_findAncestorByType<OrcParser::ClosureExpressionContext>(this->blockCtx);
	}
	return closureThatBlockIsIn;
}

bool CaptureBlockInfo::hasVar(std::string varName)
{
	for (auto& e : this->captureVarInfos) {
		if (e->varName == varName) {
			return true;
		}
	}
	return false;
}

void CaptureBlockInfo::addCaptureVarInfos_once(std::shared_ptr<CaptureVarInfo> info)
{

	if (hasVar(info->varName)) {
		//已经注册过了
		return;

	}
	else {
		this->captureVarInfos.push_back(info);
	}
}

std::string CaptureBlockInfo::goc_blockClassName()
{
	if (blockClassName.empty()) {
		blockClassName = std::format(
			"__Block_{}_{}",
			blockCtx->getStart()->getLine(),
			blockCtx->getStart()->getCharPositionInLine()
		);
	}
	return blockClassName;
}

std::string CaptureBlockInfo::calc_blockVarName()
{
	auto blockClassName = this->goc_blockClassName();
	auto ret = std::format("__var_{}", blockClassName);

	return ret;
}
std::string CaptureBlockInfo::calc_blockFiniFunctionName()
{
	auto blockClassName = this->goc_blockClassName();
	auto ret = std::format("__finiBlock_{}", blockClassName);

	return ret;
}

void ClosureInfo::addBlockInfo_once(std::shared_ptr<CaptureBlockInfo> info)
{
	for (auto& e : captureBlockInfos) {
		if (e == info) {
			return;
		}
	}
	captureBlockInfos.push_back(info);
}

void ClosureInfo::addCaptureVarInfo_once(std::shared_ptr<CaptureVarInfo> info)
{
	for (auto& e : captureVarInfos) {
		if (e == info) {
			return;
		}
	}
	captureVarInfos.push_back(info);
}

std::string ClosureInfo::goc_closureClassName()
{
	if (closureClassName.empty()) {
		auto originName = ctx->Id()? ctx->Id()->getText() : "";
		if (!originName.empty()) {
			closureClassName = std::format(
				"__Closure_{}_{}", originName,
				ctx->getStart()->getLine()
			);
		}
		else {
			closureClassName = std::format(
				"__Closure_{}_{}",
				ctx->getStart()->getLine(),
				ctx->getStart()->getCharPositionInLine()
			);
		}
	}
	return closureClassName;
}

//外置的函数体名称
std::string ClosureInfo::goc_closureFunctionName() {
	if (closureFunctionName.empty()) {
		auto className = goc_closureClassName();
		closureFunctionName = std::format("__fn_{}", className);
	}
	return closureFunctionName;
}

//外置的函数体名称
std::string ClosureInfo::goc_closureMakeFunctionName() {
	if (closureMakeFunctionName.empty()) {
		auto className = goc_closureClassName();
		closureMakeFunctionName = std::format("__make_{}", className);
	}
	return closureMakeFunctionName;
}

//外置的函数体名称
std::string ClosureInfo::goc_closureFiniFunctionName() {
	auto className = goc_closureClassName();
	return std::format("__fini_{}", className);
}

void CaptureVarInfo::addUsedExpr_once(OrcParser::IdentifierExpressionContext* expr, ClosureInfo* closureInfo)
{
	for (auto& e : usedExprs) {
		if (e.idExpr == expr) {
			return;
		}
	}
	UsedVarInfo uvi;
	uvi.idExpr = expr;
	uvi.closureInfo = closureInfo;
	usedExprs.push_back(uvi);
}


void CaptureVarInfo::addUsedThisExpr_once(OrcParser::ThisExpressionContext* expr, ClosureInfo* closureInfo)
{
	for (auto& e : usedExprs) {
		if (e.thisExpr == expr) {
			return;
		}
	}
	UsedVarInfo uvi;
	uvi.thisExpr = expr;
	uvi.closureInfo = closureInfo;
	usedExprs.push_back(uvi);
}
