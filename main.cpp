#include <stdio.h>
#include <math.h>

#define QFC_ERROR_MSG "Unexpected Input, try again\n"
#define QFC_BUFF_SIZE 32

long double promptAndGet(const char *message, char *buff);

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
	}

	// printf("%f %f %f", (double)a, (double)b, (double)c);

	return 0;
}

long double promptAndGet(const char *message, char *buff)
{
	printf("%s", message);

	if (fgets(buff, QFC_BUFF_SIZE, stdin) != NULL)
	{
		return strtold(buff, nullptr);
	}
	else
		return INFINITY;
}