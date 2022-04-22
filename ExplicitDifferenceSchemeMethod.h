#pragma once
#include "Calculation.h"
class ExplicitDifferenceSchemeMethod :
    public Calculation {

    void Calculate(double t, double x) {
        double stepByT = t / (numberOfPointByT - 1);
        double stepByX = x / (numberOfPointByX - 2);

        for (int j = 1; j < numberOfPointByT; j++) {
            for (int n = numberOfPointByX - 2; n <= numberOfPointByX; n++) {
                grid;
            }
        }

    }
};

