#include <iostream>
#include <vector>
#include <random>

using namespace std;

// ��������� ���������� ������ � ����� �������� ����� ��� ����������
template <typename T>
struct ArrayAndInv {
	size_t InvCount;
	vector <T> Array;
};

// ���������� ������� � ������� ���������� ��������
template <typename T>
ArrayAndInv<T> SortAndCountInv(vector<T>);

// ������� ���� ������������� �������� � ������� "����������" ��������
template <typename T>
ArrayAndInv<T> MergeAndCountInv(vector<T>, vector<T>);

// ���������� ��������� ��������� ������
template <typename T>
ostream& operator<<(ostream&, vector<T>);

// ���������� ������� ���������� �������
vector<int> fillRandom(vector<int>, int, int, int);
vector<double> fillRandom(vector<double>, int, int, int);

int main() {
	//��������� ��� ���������� ��������� �����
	constexpr int MAX = 10;
	constexpr int MIN = 0;
	constexpr int AMOUNT = 8;

	vector<int> Numbers = fillRandom(Numbers, AMOUNT, MIN, MAX);
	cout << "Array:\n" << Numbers << endl;

	ArrayAndInv<int> SortNumbers = SortAndCountInv(Numbers);
	cout << "Amount of inversions:\n" << SortNumbers.InvCount << endl;

	return EXIT_SUCCESS;
}

// ���������� ������� � ������� ���������� ��������
template<typename T>
ArrayAndInv<T> SortAndCountInv(vector<T> Array){
	// ��� ������� ������
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
	// ������������ ������
	vector<T> Left, Right;

	//��������� ������� ������ �� ��� �����
	for (size_t i = 0; i < Array.size() / 2; ++i) {
		Left.push_back(Array.at(i));
		Right.push_back(Array.at(Array.size()/2 + i));
	}
	if (Array.size() % 2 != 0) Right.push_back(Array.back());

	// ��������� � ��������� ���������� �������� ����������
	ArrayAndInv<T> LeftPart = SortAndCountInv(Left);
	ArrayAndInv<T> RightPart = SortAndCountInv(Right);
	// ��������� ���  ������������� ������� � ��������� ����� "����������" ��������
	ArrayAndInv<T> Merge = MergeAndCountInv(LeftPart.Array, RightPart.Array);

	return {Merge.InvCount + LeftPart.InvCount + RightPart.InvCount, Merge.Array};
}

// ������� ���� ������������� �������� � ������� "����������" ��������
template<typename T>
ArrayAndInv<T> MergeAndCountInv(vector<T> Left, vector<T> Right){
	size_t i = 0, j = 0, splitInv = 0;
	vector<T> Result;
	// �������� ��� ������� ������� �� �������
	// � ������ ��������� ������ �� �������� ����� ����� ������������ �� ������� �� �������
	// ������� �� ������� ������� � ������� �� ������� ������� �������� �������� ����� � ������ �����,
	// ����� ������� �� ������� ������� ���������� � �������� ������ ����� ��������� �� ������� �������
	for (size_t k = 0; k < Left.size() + Right.size(); ++k) {
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

// ���������� ��������� ��������� ������
template<typename T>
ostream& operator<<(ostream& out, vector<T> Vector){
	for (size_t i = 0; i < Vector.size(); ++i) {
		out << Vector.at(i) << '\t';
	}
	return out;
}

// ������� ���������� ������� �������������� ���������� �������
vector<int> fillRandom(vector<int> Numbers, int amount, int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}

// ������� ���������� ������� ��������������� ���������� �������
vector<double> fillRandom(vector<double> Numbers, int amount, int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<>dist(min, max);

	for (size_t i = 0; i < amount; ++i) {
		Numbers.push_back(dist(gen));
	}

	return Numbers;
}