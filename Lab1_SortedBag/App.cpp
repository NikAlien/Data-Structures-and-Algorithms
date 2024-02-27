#include <iostream>
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

int main() {
	testAll();
	testAllExtended();
	
	cout << "Test over" << endl;
	 system("pause");
}
