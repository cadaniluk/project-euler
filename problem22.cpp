#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

static_assert(sizeof(unsigned long long) == 8, "Type might be too small");

int main()
{
	// First, read the names into memory.

	std::ifstream f{"names.txt"};
	if (!f) {
		std::cerr << "Error while opening the file 'names.txt'.\n";
		return EXIT_FAILURE;
	}

	std::vector<std::string> names;

	std::string tmp;
	while (std::getline(f, tmp, ',')) {
		// remove leading and trailing quotation marks
		tmp = tmp.substr(1, tmp.length() - 2);

		names.push_back(tmp);
	}

	// Now, sort the names alphabetically.
	std::sort(names.begin(), names.end());

	// Compute the sum.
	unsigned long long sum = 0;
	for (std::size_t i = 0; i < names.size(); ++i) {
		unsigned int nameSum = 0;
		for (auto c : names[i])
			nameSum += c - 'A' + 1;
		sum += nameSum * (i + 1);
	}

	std::cout << sum << std::endl;
}