#pragma once
#include "Calculation.h"
class ExplicitDifferenceSchemeMethod :
    public Calculation {

private:
    double a;
    double stepByX;
    double stepByT;


public:

    ExplicitDifferenceSchemeMethod() : Calculation() {
        this->a = sqrt(k0);
    }

    double ValuesOfU(double t, double x) {
        Calculate(t, x);
        int firstPoint = floor(x / stepByX);
        int secondPoint = firstPoint + 1;
        vector<double> lastTimeLayer = grid.back();
        return (lastTimeLayer[firstPoint] + lastTimeLayer[secondPoint]) / 2;
    }

    //double ValuesOfU(double t, int numberOfPointByX) {
    //    this->numberOfPointByX = numberOfPointByX;
    //    this->x.resize(numberOfPoint);
    //    this->v.resize(numberOfPoint);

    //    Calculate(t);
    //    return B * x[this->numberOfPoint - 1];
    //}

    ~ExplicitDifferenceSchemeMethod() {

    }

private:
    bool stepByTÑheck(double stepByT, double stepByX) {
        return stepByT <= stepByX * stepByX / (2 * k0);
    }

    void Calculate(double t, double x) {

        this->stepByX = 1. / (numberOfPointByX - 1);
        this->stepByT = t / (numberOfPointByT - 1);

        if (!stepByTÑheck(stepByT, stepByX)) {
            this->numberOfPointByT = ceil(2 * t * k0 / (stepByX * stepByX) + 1);
            this->stepByT = t / (numberOfPointByT - 1);
            this->grid = vector<vector<double>>(numberOfPointByT, vector<double>(numberOfPointByX));
            cout << "VALUE numberOfPointByT WILL BE CHANGED ON " << numberOfPointByT << endl;
            //if (numberOfPointByT < 0) cerr << "numberOfPointByT is negative" << endl;
        }

        if (!stepByTÑheck(stepByT, stepByX)) {
            cerr << "ADDITIONAL VERIFICATION WASN'T PASSED" << endl;
            throw stepByT;
        }


        for (int i = 0; i < grid[0].size(); i++) 
            grid[0][i] = phi(stepByX * i);

        
        for (int j = 1; j < numberOfPointByT; j++) {
            for (int n = 1; n < numberOfPointByX - 1; n++) {
                grid[j][n] = grid[j - 1][n] + stepByT * (k0 / (stepByX * stepByX) * (grid[j - 1][n + 1] - 2 * grid[j - 1][n] + grid[j - 1][n - 1]));
            }
            grid[j][0] = (psi_0(j * stepByT) - beta0 / stepByX * grid[j][1]) / (alfa0 - beta0 / stepByX);
            grid[j][numberOfPointByX - 1] = (psi_1(j * stepByT) + beta1 / stepByX * grid[j][numberOfPointByX - 2]) / (alfa1 + beta1 / stepByX);


        }


    }
};

