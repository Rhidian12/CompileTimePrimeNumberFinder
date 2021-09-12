#include <iostream>

template<int NumberA, int NumberB>
constexpr bool IsNumberDivisible()
{
	if constexpr (NumberB == 0 || NumberB == 1)
		return true;
	else // doing else prevents warning C4702: unreachable code when the number is not a prime number
		return NumberA % NumberB != 0;
}

template<int NumberToCheck, int ... Numbers>
constexpr bool CheckIfNumberIsPrime(std::integer_sequence<int, Numbers...>)
{
	return (IsNumberDivisible<NumberToCheck, Numbers>() && ...); // all of these need to return true, or it is NOT a prime number
}

template<unsigned int Number>
constexpr bool CheckIfNumberIsPrime()
{
	if constexpr (Number == 0u || Number == 1u)
		return false;
	else
		return CheckIfNumberIsPrime<Number>(std::make_integer_sequence<unsigned int, (Number / 2u) + 1u>{}); // make sure we do Number / 2 + 1, since integer_sequence upper limit is exclusive
}

template<unsigned int ... Numbers>
constexpr void PrintIfNumbersArePrime(std::integer_sequence<unsigned int, Numbers...>)
{
	std::cout << std::boolalpha;
	((std::cout << Numbers << ": " << CheckIfNumberIsPrime<Numbers>() << std::endl), ...);
}

int main()
{
	PrintIfNumbersArePrime(std::make_integer_sequence<unsigned int, 11>{});

	return 0;
}