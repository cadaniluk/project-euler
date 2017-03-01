/* Brute force. It even works in a reasonable time. */

#include <iostream>

int main()
{
	unsigned int max = 0, maxLen = 0;
	for (unsigned int i = 999999; i >= 1; --i) {
		unsigned int j = i, newMaxLen = 0;
		for ( ; j != 1; (j % 2 == 0 ? j /= 2 : j = j * 3 + 1), ++newMaxLen);
		if (newMaxLen > maxLen) {
			maxLen = newMaxLen;
			max = i;
		}
	}

	std::cout << max << std::endl;
}