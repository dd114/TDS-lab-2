#include "ExplicitDifferenceSchemeMethod.h"
#include "ImplicitDifferenceSchemeMethod.h"

using namespace std;

void PART1();
void PART2();


int main() {

    PART1();
    //PART2();

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
    cout << "mySolution = " << ExplicitDifferenceScheme.ValuesOfU(1, x, 200, 10) << endl;
    cout << "exactSolution = " << ExplicitDifferenceScheme.exactSolution(1, x) << endl;

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

    //ExplicitDifferenceScheme.makeFileForGraph(stepOfPointXGrid, inaccuracySolution, "1.3.txt");
    //ExplicitDifferenceScheme.drawGraph("1.3.txt", "Inaccuracy ExplicitDifferenceScheme solution");
}

void PART2() {
    int numberOfValues = 1;
    int offset = 5;
    vector<int> stepOfPointXGrid(numberOfValues);
    vector<double> valuesFunction(numberOfValues);
    vector<double> inaccuracySolution(numberOfValues);

    //2.1
    ImplicitDifferenceSchemeMethod ImplicitDifferenceScheme;

    //2.1
    double x = 0.8;
    cout << ImplicitDifferenceScheme.ValuesOfU(1, x, 10, 100) << endl;
    cout << ImplicitDifferenceScheme.exactSolution(1, x) << endl;
}
