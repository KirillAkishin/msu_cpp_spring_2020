#include <iostream>
#include <fstream>
#include "counter.h"


int read_file(std::ifstream &file) {
	if (file)
    {
		int sum = 0;
		int n;
		for(file >> n; !file.eof(); file >> n){
			sum += n;
		}
		file >> n;
		sum += n;

		return sum;
	}
	return 0;
}

int main() {
	std::string file = "test.txt";

	std::ifstream infile_test(file);
	int correct_sum = read_file(infile_test);
	infile_test.close();

	std::ifstream infile(file);
	int sum = counter(infile);
	infile.close();

	if (sum == correct_sum) {
		std::cout << "Test passed!.\n";
	} else {
		std::cout << "Expted sum: " << sum << '\n';
		std::cout << "Result sum: " << correct_sum << '\n';
		std::cout << "Test failed: incorrect sum!\n";
	}

	return 0;
}