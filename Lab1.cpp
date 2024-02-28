#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <utility>


 int perebor(int *data, int size, int key) {
	for (int i = 0; i < size; i++) {
		if (data[i] == key) return i;
	}
	return 0;
}

 void A_strategy(int* data, int i) {
	 if(i!=0) std::swap(data[0], data[i]);
 }

 void B_strategy(int* data, int i) {
	 if (i != 0) std::swap(data[i-1], data[i]);
 }

 void C_strategy(int* data, int i, int* elem_check) {
	 ++elem_check[i];
	 if (i != 0) {
		 if (elem_check[i - 1] < elem_check[i]) {
			 std::swap(data[i - 1], data[i]);
			 std::swap(elem_check[i - 1], elem_check[i]);
		 }
	 }
 }

 bool pereb_v(std::vector<int> data, int key) {
	 for (int i = 0; i < data.size(); i++) {
		 if (data[i] == key) return true;
	 }
	 return false;
 }

int bin_search(int* data, int size, int key) {
	bool flag = false;
	int l = 0; 
	int r = size-1; 
	int mid;

	while ((l <= r) && (flag != true)) {
		mid = (l + r) / 2; 

		if (data[mid] == key) return 1; 
		if (data[mid] > key) r = mid - 1;
		else l = mid + 1;
	}
	return 0;
}

int straight_for_sum_of_2(int* data, int size, int key) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (j != i) {
				if (data[i] + data[j] == key) return 1;
			}
		}
	}
	return 0;
}

int cool_sum_of_2(int* data, int size, int key) {
	int l = 0;
	int r = size;
	while (l != r) {
		int cursum = data[l] + data[r];
		if (cursum < key) { ++l; }
		else if (cursum > key) { --r; }
		else { return 1; }
	}
	return 0;
}

static int data[100000] = {};
static int elem_check[100000] = {};

int main() {
	std::ofstream fin1;
	std::ofstream fin2;
	fin1.open("n_data.txt");
	fin2.open("time_data.txt");
	int counter = 100;
	unsigned seed = 1001;
	std::default_random_engine rng(seed);
	while (true) {
		counter += 10;
		std::normal_distribution<> dstr(1, counter/100);
		if (counter > 100000) { break; }
		for (int i = 0; i < counter; ++i) {
			data[i] = abs(static_cast<int>(dstr(rng)));
		}
		for (int i = 0; i < (counter / 100); i++) {
			C_strategy(data, perebor(data, counter, abs(static_cast<int>(dstr(rng)))), elem_check);
		}

		int num = abs(static_cast<int>(dstr(rng)));
		auto begin = std::chrono::steady_clock::now();
		for (int j = 100; j != 0; j--) { perebor(data, counter, num); }
		auto end = std::chrono::steady_clock::now();
		auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
		fin1 << counter << '\n';
		std::cout << counter << '\n';
		fin2 << time_span.count() << '\n';
	}
}


