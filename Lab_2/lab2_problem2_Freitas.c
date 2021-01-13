#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>

// Take the character and convert it to an Int.
int ConvertChar(char ch)
{
	// If the char is '0' through '9' then just return those as ints.
	if (ch >= '0' && ch <= '9')
	{
		// '0' represents 48, so if c = '0' -> 48 - 48 =  return 0.
		return (int)ch - '0';
	}
	else
	{
		// Example: if c = 'A' then -> (int)c = 65, so 65 - 'A' = 0 + 10 = 10.
		return (int)ch - 'A' + 10;
	}
}

// Convert to decimal number sytem.
int ConvertToDecimal(char *number, int base)
{
	int digits = strlen(number), power = 1, sum = 0, i;
	
	for (i = digits - 1; i >= 0; i--)
	{
		if (ConvertChar(number[i]) >= base)
		{
			printf("The input number does not match the base.\n");
			return -1;
		}

		// Convert the char to int then multiply by the power.
		sum += ConvertChar(number[i]) * power;

		// Example -> base:5 -> i = 3: power = 1 * 5  = 5 -> i = 2: power = 5 * 5 = 25...
		power = power * base;
	}

	return sum;
}


int main(int argc, const char* argv[])
{
	int base;
	char number[10];

	// Take input for the number and the base.
	printf("Input number: ");
	scanf("%s", number);

	printf("Input base: ");
	scanf("%d", &base);

	// As long as the number is not invalid, print the sum.
	if (ConvertToDecimal(number, base) != -1)
		printf("Sum with base 10:%d\n", (ConvertToDecimal(number, base)));

	//system("pause");
	return 0;
}