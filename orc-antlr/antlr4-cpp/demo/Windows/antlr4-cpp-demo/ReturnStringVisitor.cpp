#include "ReturnStringVisitor.h"
#include <chrono>

using namespace antlrcpptest;
using namespace antlr4;

std::any ReturnStringVisitor::visitTerminal(antlr4::tree::TerminalNode* node) {
	//return node->getText();
	return defaultResult();
}

std::any ReturnStringVisitor::defaultResult() {
	return std::string("");
}

std::any ReturnStringVisitor::aggregateResult(std::any aggregate, std::any nextResult) {
	std::string agg = std::any_cast<std::string>(aggregate);
	std::string next = std::any_cast<std::string>(nextResult);

	long long us = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	auto ret = agg + next;
	long long us2 = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	aggregateCostUs += us2 - us;
	return ret;
}


void ReturnStringVisitor::startUs() {
	startUs_  = std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::system_clock::now().time_since_epoch()
	).count();
}
void ReturnStringVisitor::endUs() {
	long long us2 = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();

	aggregateCostUs += us2 - startUs_;
}

std::string ReturnStringVisitor::visitChildrenReturnString(antlr4::tree::ParseTree* node) {
	auto ret = visitChildren(node);
	auto str = std::any_cast<std::string>(ret);
	return str;
}

std::string ReturnStringVisitor::visitReturnString(antlr4::tree::ParseTree* node) {
	if (node == NULL) {
		return "";
	}
	auto ret = visit(node);
	auto str = std::any_cast<std::string>(ret);
	return str;
}
