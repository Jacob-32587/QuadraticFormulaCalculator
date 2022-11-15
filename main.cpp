#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define QFC_ERROR_MSG "Formatting error on last input, try again\n"
#define QFC_BUFF_SIZE 32

long double promptAndGet(const char *message, char *buff);
bool onlyZeroF(const char *input);

int main()
{
	char buff[QFC_BUFF_SIZE];

	long double a = 0.0L;
	long double b = 0.0L;
	long double c = 0.0L;

	while (1)
	{
		a = promptAndGet("a = ", buff);
		if (isinf(a) || (a == HUGE_VALL))
		{
			printf(QFC_ERROR_MSG);
			continue;
		}

		b = promptAndGet("b = ", buff);
		if (isinf(b) || (b == HUGE_VALL))
		{
			printf(QFC_ERROR_MSG);
			continue;
		}

		c = promptAndGet("c = ", buff);
		if (isinf(c) || (c == HUGE_VALL))
		{
			printf(QFC_ERROR_MSG);
			continue;
		}

		break;
	} // User input collection loop

	return 0;
}

// ARG0: Message that the user will be prompted to enter data with
// ARG1: Buffer to hold data

long double promptAndGet(const char *message, char *buff)
{
	long double retVal = 0.0L;

	printf("%s", message);

	if (fgets(buff, QFC_BUFF_SIZE, stdin) != nullptr)
	{
		retVal = strtold(buff, nullptr);

		printf("%d", onlyZeroF(buff));

		if (retVal == 0.0 && !onlyZeroF(buff))
			return INFINITY;
		else
			return retVal;
	}
	else
		return INFINITY;
}

// ARG0: Checks in the null-terminated character string is of zero value
// ie: "0.0000000" "0.0" "0"
bool onlyZeroF(const char *input)
{
	short decimalCnt = 0; // Track number of decimal places

	while (*input != '\0')
	{
		// Only a valid character if 1 decimal appears and any number of zero's
		if (*input == '0' || isspace(*input))
			;
		else if (*input == '.')
			decimalCnt++;
		else
			return false;

		if (decimalCnt == 2) // Cannot have more than 1 decimal marker
			return false;

		input++; // Next character
	}

	return true; // Past all tests
}