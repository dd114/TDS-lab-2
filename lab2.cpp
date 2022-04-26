#include "ExplicitDifferenceSchemeMethod.h"

using namespace std;
int main() {
    ExplicitDifferenceSchemeMethod ExplicitDifferenceScheme;
    double x = 0.4;
    //cout << ExplicitDifferenceScheme.ValuesOfU(1, x, 200, 10) << endl;
    //cout << ExplicitDifferenceScheme.ValuesOfU(1, x, 1e+1, 10) << endl;
    //cout << ExplicitDifferenceScheme.exactSolution(1, x) << endl;

    cout << ExplicitDifferenceScheme.ValuesOfU(1, x, 1e+1, 5) << endl;

    //cout << "Hello World!" << endl;
}

