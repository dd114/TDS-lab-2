#include "ExplicitDifferenceSchemeMethod.h"

using namespace std;
int main() {

    //1.1
    ExplicitDifferenceSchemeMethod ExplicitDifferenceScheme;
    //1.2
    double x = 0.8;
    cout << ExplicitDifferenceScheme.ValuesOfU(1, x, 200, 10) << endl;
    //1.3
    x = 0.8;
    //cout << ExplicitDifferenceScheme.ValuesOfU(1, x, 2, 10) << endl;
    cout << ExplicitDifferenceScheme.maximumOfInaccuracyGrid(1, x, 2, 10) << endl;
    //cout << ExplicitDifferenceScheme.ValuesOfU(1, x, 2, 150) << endl;
    cout << ExplicitDifferenceScheme.maximumOfInaccuracyGrid(1, x, 2, 150) << endl;
    cout << "Exact solution = " << ExplicitDifferenceScheme.exactSolution(1, x) << endl;

    //cout << ExplicitDifferenceScheme.ValuesOfU(1, x, 1e+1, 5) << endl;

    //cout << "Hello World!" << endl;
}

