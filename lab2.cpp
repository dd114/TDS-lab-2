#include "ExplicitDifferenceSchemeMethod.h"

using namespace std;

void PART1();


int main() {

    PART1();

}

void PART1(){
    int numberOfValues = 1;
    int offset = 5;
    vector<int> stepOfPointXGrid(numberOfValues);
    vector<double> valuesFunction(numberOfValues);
    vector<double> inaccuracySolution(numberOfValues);


    //1.1
    ExplicitDifferenceSchemeMethod ExplicitDifferenceScheme;

    //1.2
    double x = 0.8;
    cout << ExplicitDifferenceScheme.ValuesOfU(1, x, 200, 10) << endl;

    //1.3
    offset = 5;
    numberOfValues = 100;
    stepOfPointXGrid.resize(numberOfValues - offset);
    valuesFunction.resize(numberOfValues - offset);
    inaccuracySolution.resize(numberOfValues - offset);
    x = 0.8;

    for (int numberOfPointByX = offset; numberOfPointByX < numberOfValues; numberOfPointByX++) {
        stepOfPointXGrid[numberOfPointByX - offset] = numberOfPointByX;
        inaccuracySolution[numberOfPointByX - offset] = ExplicitDifferenceScheme.maximumOfInaccuracyGrid(1, x, 5, numberOfPointByX);
    }

    ExplicitDifferenceScheme.makeFileForGraph(stepOfPointXGrid, inaccuracySolution, "1.3.txt");
    ExplicitDifferenceScheme.drawGraph("1.3.txt", "Inaccuracy ExplicitDifferenceScheme solution");
}
