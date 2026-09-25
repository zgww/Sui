#pragma once
#include <chrono>


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