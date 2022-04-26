#include <iostream>
#include "ExplicitDifferenceSchemeMethod.h"

using namespace std;
int main() {
    ExplicitDifferenceSchemeMethod ExplicitDifferenceScheme;
    cout << ExplicitDifferenceScheme.ValuesOfU(1, 0.8, 200, 10) << endl;
    cout << ExplicitDifferenceScheme.ValuesOfU(1, 0.8, 1e+1, 10) << endl;
    cout << ExplicitDifferenceScheme.exactSolution(1, 0.8) << endl;
    //cout << "Hello World!" << endl;
}

