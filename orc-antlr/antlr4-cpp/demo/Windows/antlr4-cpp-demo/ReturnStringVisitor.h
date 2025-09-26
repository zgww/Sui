#pragma once


#include "OrcBaseVisitor.h"
#include <filesystem>
#include "OrcLexer.h"

#include <Windows.h>
#include "md5.h"
#include "Closure.h"
#include <FsUtil.h>
#include <StrUtil.h>



/**
 * This class provides an empty implementation of OrcVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class ReturnStringVisitor : public OrcBaseVisitor {
public:

	long long aggregateCostUs = 0L;
	long long startUs_ = 0L;

	void startUs();
	void endUs();

	virtual std::any visitTerminal(antlr4::tree::TerminalNode* node) override;

	virtual std::any defaultResult();
	virtual std::any aggregateResult(std::any aggregate, std::any nextResult);

	virtual std::string visitChildrenReturnString(antlr4::tree::ParseTree* node);
	virtual std::string visitReturnString(antlr4::tree::ParseTree* node);
};


class CostUsGuard {
public:
	long long startUs_ = 0L;
	ReturnStringVisitor* vi;
	CostUsGuard(ReturnStringVisitor *vi) {
		this->vi = vi;
		startUs_ = std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		).count();
	}
	~CostUsGuard() {
		long long us2 = std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		).count();
		long long cost = us2 - startUs_;
		this->vi->aggregateCostUs += cost;
	}
};


class CostUs {
public:
	std::vector<long long> timepoints;
	std::vector<std::string> labels;

	CostUs() {
		stat("");
	}
	void stat(std::string str) {
		long long us = std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		).count();
		timepoints.push_back(us);

		labels.push_back(str);
	}
	void print(std::string title) {
		printf("-------------%s----------\n", title.c_str());
		long long startUs = timepoints[0]; 
		for (int i = 1; i < labels.size(); i++) {
			long long prevUs = timepoints[i - 1] ;
			long long nowUs = timepoints[i] ;
			double cost = ((double)(nowUs - prevUs)) / 1000.0;
			double costTotal = ((double)(nowUs - startUs)) / 1000.0;
			printf("\t%40s:\t\t\t\t%8fms/%8fms\n", labels[i].c_str(), cost, costTotal);
		}
	}
};