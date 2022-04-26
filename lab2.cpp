#include <iostream>
#include "ExplicitDifferenceSchemeMethod.h"

using namespace std;
int main() {
    ExplicitDifferenceSchemeMethod ExplicitDifferenceScheme;
    ExplicitDifferenceScheme.ValuesOfU(10, 0.8);
    cout << "Hello World!" << endl;
}

