#include <iostream>
#include "ExplicitDifferenceSchemeMethod.h"

using namespace std;
int main() {
    ExplicitDifferenceSchemeMethod ExplicitDifferenceScheme;
    cout << ExplicitDifferenceScheme.ValuesOfU(10, 0.8) << endl;
    cout << ExplicitDifferenceScheme.exactSolution(10, 0.8) << endl;
    cout << "Hello World!" << endl;
}

