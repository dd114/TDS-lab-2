#pragma once
#include "Calculation.h"
class ExplicitDifferenceSchemeMethod :
    public Calculation {
protected:

    int numberOfPointByFirstSegmentX;
    int numberOfPointBySecondSegmentX;
    int n;
    int k;



public:

    virtual void setNumberOfPointByX(int numberOfPointByX) {
        this->numberOfPointByFirstSegmentX = numberOfPointByX;
        this->n = numberOfPointByFirstSegmentX - 1;
        this->k = 
        this->numberOfPointBySecondSegmentX = numberOfPointByX;
    }

    virtual void setNumberOfPointByX(int numberOfPointByX) {
        this->numberOfPointByFirstSegmentX = numberOfPointByX;
        n = numberOfPointByFirstSegmentX - 1;
        int k =
        this->numberOfPointBySecondSegmentX = numberOfPointByX;
    }


protected:

    void Calculate(double t, double x) {
        double stepByX = x / n;
        double stepByT = t / (numberOfPointByT - 1);


        for (int j = 1; j < numberOfPointByT; j++) {
            for (int n = numberOfPointByX - 2; n <= numberOfPointByX; n++) {
                grid;
            }
        }

    }
};

