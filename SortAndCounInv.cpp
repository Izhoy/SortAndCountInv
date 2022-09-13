#include <iostream>
#include <vector>
#include <random>

using namespace std;

// A structure containing a vector and the number of inversions between its elements
template <typename T>
struct ArrayAndInv {
	size_t InvCount;
	vector <T> Array;
};

// Sorting the array and counting the number of inversions
template <typename T>
ArrayAndInv<T> SortAndCountInv(vector<T>);

// Merging two ordered arrays and counting "separated" inversions
template <typename T>
ArrayAndInv<T> MergeAndCountInv(vector<T>, vector<T>);

// Overload of the output stream operator
template <typename T>
ostream& operator<<(ostream&, vector<T>);

// Filling a vector with random numbers
vector<int> fillRandom(vector<int>, int, int, int);
vector<double> fillRandom(vector<double>, int, int, int);

int main() {
	//Parameters for calculating random numbers
	constexpr int MAX = 10;
	constexpr int MIN = 0;
	constexpr int AMOUNT = 8;

	vector<int> Numbers = fillRandom(Numbers, AMOUNT, MIN, MAX);
	cout << "Array:\n" << Numbers << endl;

	ArrayAndInv<int> SortNumbers = SortAndCountInv(Numbers);
	cout << "Amount of inversions:\n" << SortNumbers.InvCount << endl;

	return EXIT_SUCCESS;
}

// Sorting the array and counting the number of inversions
template<typename T>
ArrayAndInv<T> SortAndCountInv(vector<T> Array){
	// 2 base cases
	if (Array.size() < 2) return { 0, Array };
	else if (Array.size() == 2) {
		if (Array.at(0) > Array.at(1)) {
			swap(Array.at(0), Array.at(1));
			return { 1, Array };
		}
		else {
			return { 0, Array };
		}
	}
	// Recursion case
	vector<T> Left, Right;

	//Split input array on 2 parts
	for (size_t i = 0; i < Array.size() / 2; ++i) {
		Left.push_back(Array.at(i));
		Right.push_back(Array.at(Array.size()/2 + i));
	}
	if (Array.size() % 2 != 0) Right.push_back(Array.back());

	// Sort and calculate the number of inversions recursively
	ArrayAndInv<T> LeftPart = SortAndCountInv(Left);
	ArrayAndInv<T> RightPart = SortAndCountInv(Right);
	// We connect two ordered arrays and calculate the number of "separated" inversions
	ArrayAndInv<T> Merge = MergeAndCountInv(LeftPart.Array, RightPart.Array);

	return {Merge.InvCount + LeftPart.InvCount + RightPart.InvCount, Merge.Array};
}

// Merging two ordered arrays and counting "separated" inversions
template<typename T>
ArrayAndInv<T> MergeAndCountInv(vector<T> Left, vector<T> Right){
	size_t i = 0, j = 0, splitInv = 0;
	vector<T> Result;
	// Passing two input arrays in order
	// If one of the arrays ends, the numbers will be copied in order from the other
	// An element of their first array and an element from the second array form an inversion if and only if
	// when an element from the second array is copied to the output array before an element from the first arrayfor (size_t k = 0; k < Left.size() + Right.size(); ++k) {
		if (i > Left.size() - 1) {
			Result.push_back(Right.at(j));
			++j;
		}
		else if (j > Right.size() - 1) {
			Result.push_back(Left.at(i));
			++i;
		}
		else {
			if (Left.at(i) <= Right.at(j)) {
				Result.push_back(Left.at(i));
				++i;
			}
			else {
				Result.push_back(Right.at(j));
				++j;
				splitInv = splitInv + (Left.size() + Right.size()) / 2 - i;
			}
		}
	}

	return {splitInv, Result};
}

// Overload of the output stream operator
template<typename T>
ostream& operator<<(ostream& out, vector<T> Vector){
	for (size_t i = 0; i < Vector.size(); ++i) {
		out << Vector.at(i) << '\t';
	}
	return out;
}

// Filling a vector with integers random numbers
vector<int> fillRandom(vector<int> Numbers, int amount, int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}

// Filling a vector with real random numbers
vector<double> fillRandom(vector<double> Numbers, int amount, int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}
