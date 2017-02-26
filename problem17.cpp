#include <iostream>
#include <unordered_map>

std::unordered_map<int, int> subTwenty =
{
	{ 0, 4 },
	{ 1, 3 },
	{ 2, 3 },
	{ 3, 5 },
	{ 4, 4 },
	{ 5, 4 },
	{ 6, 3 },
	{ 7, 5 },
	{ 8, 5 },
	{ 9, 4 },
	{ 10, 3 },
	{ 11, 6 },
	{ 12, 6 },
	{ 13, 8 },
	{ 14, 8 },
	{ 15, 7 },
	{ 16, 7 },
	{ 17, 9 },
	{ 18, 8 },
	{ 19, 8 }
};

std::unordered_map<int, int> tens =
{
	{ 2, 6 },
	{ 3, 6 },
	{ 4, 5 },
	{ 5, 5 },
	{ 6, 5 },
	{ 7, 7 },
	{ 8, 6 },
	{ 9, 6 }
};

int main()
{
	unsigned long result = 11; // "one thousand" --> 11

	// starts from 1
	const auto digitSum = [] () -> unsigned long
	{
		unsigned long ret = 0;
		for (int iDigits = 1; iDigits < 10; ++iDigits)
			ret += subTwenty[iDigits];
		return ret;
	}();

	const auto subTwentySum = [] () -> unsigned long
	{
		unsigned long ret = 0;
		for (int iSubTwenty = 1; iSubTwenty < 20; ++iSubTwenty)
			ret += subTwenty[iSubTwenty];
		return ret;
	}();

	// Less than one hundred starting from .
	result += subTwentySum;
	for (int iTens = 2; iTens < 10; ++iTens)
		result += tens[iTens] * 10 + digitSum;

	// From 100 to 999.
	result += (900 - 9) * 10 + 9 * 7; // 891x "hundred and" + 9x "hundred"
	for (int iHundreds = 1; iHundreds < 10; ++iHundreds) {
		result += subTwenty[iHundreds] * 100;

		result += subTwentySum;
		for (int iTens = 2; iTens < 10; ++iTens)
			result += tens[iTens] * 10 + digitSum;
	}

	std::cout << result << std::endl;
}