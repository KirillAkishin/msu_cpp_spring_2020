#include "counter.h"
#include "threadPool.h"


int handler(std::string& line) {
	int ac = 0;
	int value = 0;
	std::istringstream strStm(line);
	while (strStm >> value) {
		ac += value;
	}
	return ac;
}

int counter(std::ifstream& infile) {
	std::string line = "";
	ThreadPool pool(2);
	int sum = 0;
	std::vector<std::future<int>> futures;
	while (!infile.eof()) {
		getline(infile, line);
		futures.push_back(pool.exec(handler, line));
	}
	for (int i = 0; i < futures.size(); i++) {
		sum += futures[i].get();
	}
	return sum;
}