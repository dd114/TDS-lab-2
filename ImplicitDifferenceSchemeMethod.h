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

        int numberOfStepsX = numberOfPointByX - 1;
        int numberOfStepsT = numberOfPointByT - 1;


        double* elementsMatrix = new double[numberOfPointByX * 4]; // 0 - верх диаг.; 1 - ср. диаг.; 2 - нижн. диаг.;

        for (unsigned i = 0; i < numberOfPointByX; i++) {
            grid[0][i] = phi(i * stepByX);
        }

        for (unsigned t = 0; t < numberOfStepsT; ++t) {

            //верхн.
            elementsMatrix[0 * (numberOfStepsX + 1) + 0] = beta0;

            //ср.
            elementsMatrix[1 * (numberOfStepsX + 1) + 0] = stepByX * alfa0 - beta0;
            elementsMatrix[1 * (numberOfStepsX + 1) + numberOfStepsX] = alfa1 * stepByX + beta1;

            //нижн; 
            elementsMatrix[2 * (numberOfStepsX + 1) + numberOfStepsX - 1] = -beta1;

            //прав;
            elementsMatrix[3 * (numberOfStepsX + 1) + 0] = stepByX * psi_0(stepByT * (t + 1));
            elementsMatrix[3 * (numberOfStepsX + 1) + numberOfStepsX] = stepByX * psi_1(stepByT * (t + 1));



            for (unsigned x = 1; x < numberOfStepsX; ++x) {
                //верхн.
                elementsMatrix[0 * (numberOfStepsX + 1) + x] = k0 * stepByT / (stepByX * stepByX);

                //ср.
                elementsMatrix[1 * (numberOfStepsX + 1) + x] = -2. * stepByT * k0 / (stepByX * stepByX) - 1;

                //нижн;
                elementsMatrix[2 * (numberOfStepsX + 1) + x - 1] = k0 * stepByT / (stepByX * stepByX);

                //прав;
                elementsMatrix[3 * (numberOfStepsX + 1) + x] = -grid[t][x] - stepByT * f0(stepByT * (t + 1), stepByX * (x));
            }

            progonka(elementsMatrix, t + 1);
        }

        delete[] elementsMatrix;

    }


    void progonka(double* matrix, unsigned time)
    {
        for (unsigned x = 1; x <= numberOfStepsX; x++) {
            matrix[1 * (numberOfStepsX + 1) + x] = matrix[1 * (numberOfStepsX + 1) + x] -
                matrix[0 * (numberOfStepsX + 1) + x - 1] *
                (matrix[2 * (numberOfStepsX + 1) + x - 1] /
                 matrix[1 * (numberOfStepsX + 1) + x - 1]);

            matrix[3 * (numberOfStepsX + 1) + x] = matrix[3 * (numberOfStepsX + 1) + x] -
                matrix[3 * (numberOfStepsX + 1) + x - 1] *
                (matrix[2 * (numberOfStepsX + 1) + x - 1] /
                 matrix[1 * (numberOfStepsX + 1) + x - 1]);

            matrix[2 * (numberOfStepsX + 1) + x - 1] = 0;
        }

        grid[(numberOfStepsX + 1) * time + numberOfStepsX] = matrix[3 * (numberOfStepsX + 1) + numberOfStepsX] / matrix[1 * (numberOfStepsX + 1) + numberOfStepsX];
        for (int x = numberOfStepsX - 1; x >= 0; --x)
            grid[(numberOfStepsX + 1) * time + x] = (matrix[3 * (numberOfStepsX + 1) + x] -
                                                       matrix[0 * (numberOfStepsX + 1) + x] *
                                                       grid[(numberOfStepsX + 1) * time + x + 1]) /
            matrix[1 * (numberOfStepsX + 1) + x];
    }

};

