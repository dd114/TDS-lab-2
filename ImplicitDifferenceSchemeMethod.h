#pragma once
#include "Calculation.h"
class ImplicitDifferenceSchemeMethod :
    public Calculation {
    
private:
    double a;
    double stepByX;
    double stepByT;


public:

    ImplicitDifferenceSchemeMethod() : Calculation() {
        this->a = sqrt(k0);
    }

    double ValuesOfU(double t, double x) {
        Calculate(t, x);
        int firstPoint = floor(x / stepByX);
        //int secondPoint = firstPoint + 1;
        vector<double> lastTimeLayer = grid.back();
        return lastTimeLayer[firstPoint];
    }

    double ValuesOfU(double t, double x, int numberOfPointByT, int numberOfPointByX) {
        this->numberOfPointByX = numberOfPointByX;
        this->numberOfPointByT = numberOfPointByT;

        //this->grid = vector<vector<double>>(numberOfPointByT, vector<double>(numberOfPointByX));

        Calculate(t, x);
        int firstPoint = floor(x / stepByX);
        //int secondPoint = firstPoint + 1;
        vector<double> lastTimeLayer = grid.back();
        return lastTimeLayer[firstPoint];
    }

    double maximumOfInaccuracyGrid(double t, double x, int numberOfPointByT, int numberOfPointByX) {
        ValuesOfU(t, x, numberOfPointByT, numberOfPointByX);

        double maxInaccuracy = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                double exactValueOfU = exactSolution(i * stepByT, j * stepByX);
                double inaccuracy = abs(grid[i][j] - exactValueOfU);
                if (inaccuracy > maxInaccuracy) {
                    maxInaccuracy = inaccuracy;
                }
            }
        }
        return maxInaccuracy;
    }

    ~ImplicitDifferenceSchemeMethod() {

    }

private:
    virtual void Calculate(double t, double x) override {

        this->stepByX = 1. / (numberOfPointByX - 1);
        this->stepByT = t / (numberOfPointByT - 1);



    }

};

