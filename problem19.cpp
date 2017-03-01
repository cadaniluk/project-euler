/*
 * This is one of the problems that don't require much math, just
 * some logical thinking. I've tried to solve it in a readable way.
 * The speed gain of a more efficient, but less readable way would not be
 * noticable.
 */

#include <iostream>
#include <unordered_map>

using Year = unsigned int;
using Day = unsigned int;

enum Month {
	Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};
	static bool leapYear(Year y)
	{
		if (y % 4 != 0)
			return false;
		if (y % 100 != 0)
			return true;
		if (y % 400 != 0)
			return false;
		return true;
	}
class Date {
	/*
	 * Day is not really for the number of days, but it enables type-safe
	 * comparison whether a day has overflowed.
	 */
	static std::unordered_map<Month, Day> days;

	static bool leapYear(Year y)
	{
		if (y % 4 != 0)
			return false;
		if (y % 100 != 0)
			return true;
		if (y % 400 != 0)
			return false;
		return true;
	}

	public:
	bool leap;

	Day d;
	Month m;
	Year y;

	Date(Day d, Month m, Year y): d{d}, m{m}, y{y}, leap{leapYear(y)} { }

	/*
	 * I use this for every arithmetic operation. Inefficient, but the
	 * difference is negligible.
	 */
	Date &operator++()
	{
		Day dayLimit = days[m] + (m == Feb && leap ? 1 : 0);

		if (d + 1 > dayLimit) { // if last day of month
			d = 1;
			if (m == Dec) { // if last month of year
				++y;
				leap = leapYear(y);
				m = Jan;
			} else {
				m = static_cast<Month>(m + 1);
			}
		} else {
			++d;
		}

		return *this;
	}

	bool operator<(const Date &date)
	{
		if (y < date.y)
			return true;
		if (y == date.y) {
			if (m < date.m)
				return true;
			if (m == date.m) {
				if (d < date.d)
					return true;
			}
		}
		return false;
	}
};

std::unordered_map<Month, unsigned int> Date::days {
	{ Jan, 31 },
	{ Feb, 28 },
	{ Mar, 31 },
	{ Apr, 30 },
	{ May, 31 },
	{ Jun, 30 },
	{ Jul, 31 },
	{ Aug, 31 },
	{ Sep, 30 },
	{ Oct, 31 },
	{ Nov, 30 },
	{ Dec, 31 }
};

/* In mm/dd/yyyy format. */
std::ostream &operator<<(std::ostream &os, const Date &d)
{
	os << d.m << '/' << d.d << '/' << d.y;
}

int main()
{
	/*
	 * 1900 is no leap year, so it had 365 days. If 1 Jan 1900 was a Monday
	 * and we enumerate the weekdays from 0 to 6, 366 % 7 gives us the weekday.
	 * 366 because 1 Jan 1901 is one day after the last of 1900, i.e., it's
	 * 366 days from 1 Jan 1900 till then.
	 */
	 unsigned int i = 0;
	 unsigned int weekday = 366 % 7;
	 for (Date d{1, Jan, 1901}; d < Date{1, Jan, 2001}; ++d, ++weekday) {
		 if (d.d == 1 && weekday % 7 == 6)
		 	++i;
	 }

	 std::cout << i << std::endl;
}