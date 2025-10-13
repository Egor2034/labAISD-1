#include <iostream>
#include "set.h"

int main() {
	Set<int> set_int_1(5, 1, 25);
	Set<int> set_int_2(5, 10, 25);
	Set<int> set_int_result = (set_int_1 + set_int_2) - intersection(set_int_1, set_int_2);
	
	std::cout << set_int_1 << "\n";
	std::cout << set_int_2 << "\n";
	std::cout << set_int_result << "\n\n";

	Set<float> set_float_1(3, 1.5, 2);
	Set<float> set_float_2(2, 1, 2);
	Set<float> set_float_result = (set_float_1 + set_float_2) - intersection(set_float_2, set_float_1);

	std::cout << set_float_1 << "\n";
	std::cout << set_float_2 << "\n";
	std::cout << set_float_result << "\n\n";

	std::string arr1[5] = { "Hello", "world", "i am", "from", "Mars" };
	std::string arr2[3] = { "hello", "world", "thank" };

	Set<std::string> set_string_1(arr1, 5);
	Set<std::string> set_string_2(arr2, 3);
	Set<std::string> set_string_result = (set_string_1 + set_string_2) - intersection(set_string_1, set_string_2);

	std::cout << set_string_1 << "\n";
	std::cout << set_string_2 << "\n";
	std::cout << set_string_result << "\n\n";

	std::pair<int, double> pairs1[3] {
		{ 1, 12.3 },
		{ 2, 14.23 },
		{ 3, 19.913 }
	};

	std::pair<int, double> pairs2[4]{
		{ 6, 12.15 },
		{ 2, 14.23 },
		{ 3, 19.9123 },
		{ 4, 19.913 }
	};

	Set<std::pair<int, double>> set_pair_1(pairs1, 3);
	Set<std::pair<int, double>> set_pair_2(pairs2, 4);
	Set<std::pair<int, double>> set_pair_result = (set_pair_1 + set_pair_2) - intersection(set_pair_1, set_pair_2);

	std::cout << set_pair_1 << "\n";
	std::cout << set_pair_2 << "\n";
	std::cout << set_pair_result << "\n\n";

	return 0;
}