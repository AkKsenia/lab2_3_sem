#include "others.h"
#include "library.h"

bool is_prime(int num) {
	if (num <= 1)
		return false;
	else {
		for (int i = 2; i <= num / 2; i++)
			if (num % i == 0) return false;
		return true;
	}
}
int nearest_prime_number(int num) {
	try {
		if (num <= 1)
			throw (num);
		for (int i = 0;; i++) {
			if (is_prime(num - i)) {
				return num - i;
				break;
			}
		}
	}
	catch (int number) {
		cout << "Не существует простых чисел, меньше или равных ";
		cout << number << endl;
	}
}