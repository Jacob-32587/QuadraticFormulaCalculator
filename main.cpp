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

	long double discriminant = 0.0L;

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

	discriminant = (b * b) - (4 * a * c);

	if (a != 0) // Equation is quadratic
	{
		if (discriminant < 0) // Imaginary roots
		{
			printf("First root: %lfi\n", (double)((-b + sqrt(discriminant * -1.0L)) / (2.0L * a)));
			printf("Second root: %lfi\n", (double)((-b - sqrt(discriminant * -1.0L)) / (2.0L * a)));
		}
		else if (discriminant != 0) // Quadratic has two roots
		{
			printf("sFirst root: %lf\n", (double)((-b + sqrt(discriminant)) / (2 * a)));
			printf("Second root: %lf\n", (double)((-b - sqrt(discriminant)) / (2 * a)));
		}
		else // Quadratic has multiplicity of 2
			printf("Multiplicity of 2, singular root is: %lf\n", (double)(-b / (2 * a)));
	}
	else if (b != 0) // Equation is linear
	{
		printf("Singular root is: %lf", (double)(-c / b));
	}
	else // Not an equation
	{
		printf("You've only entered a constant value...");
	}

	return 0;
}

// ARG0: Message that the user will be prompted to enter data with
// ARG1: Buffer to hold data

long double promptAndGet(const char *message, char *buff)
{
	long double retVal = 0.0L; // Hold value that may be returned

	printf("%s", message); // Prompt user to enter data

	if (fgets(buff, QFC_BUFF_SIZE, stdin) != nullptr)
	{
		retVal = strtold(buff, nullptr); // Convert the input string into a long double

		if (retVal == 0.0 && !onlyZeroF(buff)) // Check if strtold() could not convert the input
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