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

        this->grid = vector<vector<double>>(numberOfPointByT, vector<double>(numberOfPointByX));

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

        for (int i = 0; i < grid[0].size(); i++)
            grid[0][i] = phi(stepByX * i);

        vector<vector<double>> matrix1(numberOfPointByX - 2, vector<double>(numberOfPointByX - 2));
        vector<double> matrix2(numberOfPointByX - 2);

        vector<double> tempNewTimeLayer(numberOfPointByX - 2);

        double ai = -a * a / (stepByX * stepByX);
        double bi = 1 / stepByT + 2 * a * a / (stepByX * stepByX);
        double ci = ai;


        for (int j = 1; j < numberOfPointByT; j++) {

            matrix1[0][0] = bi - ai * beta0 / (alfa0 * stepByX - beta0);
            matrix1[0][1] = ci;

            matrix2[0] = f0(stepByT * j, stepByX * 1) - ai * psi_0(stepByT * j) * stepByX / (alfa0 * stepByX - beta0) + grid[j - 1][1];




            int lastMatrixLayer = matrix1.size() - 1;

            matrix1[lastMatrixLayer][lastMatrixLayer - 1] = ai;
            matrix1[lastMatrixLayer][lastMatrixLayer] = bi + ci * beta1 / (alfa1 * stepByX + beta1);

            matrix2[lastMatrixLayer] = f0(stepByT * j, stepByX * (numberOfPointByX - 2)) - ci * psi_1(stepByT * j) * stepByX / (alfa1 * stepByX + beta1) + grid[j - 1][(numberOfPointByX - 2)];


            for (int l = 1; l < matrix1.size() - 1; l++) {
                matrix1[l][l - 1] = ai;
                matrix1[l][l] = bi;
                matrix1[l][l + 1] = ci;

                matrix2[l] = f0(stepByT * j, stepByX * (l + 1));
            }

            tempNewTimeLayer = tridiagonalSolution(matrix1, matrix2);

            for (int i = 0; i < numberOfPointByX - 2; i++) {
                grid[j][i + 1] = tempNewTimeLayer[i];
            }


            grid[j][0] = (psi_0(j * stepByT) * stepByX - beta0 * grid[j][1]) / (alfa0 * stepByX - beta0);
            grid[j][numberOfPointByX - 1] = (psi_1(j * stepByT) * stepByX + beta1 * grid[j][numberOfPointByX - 2]) / (alfa1 * stepByX + beta1);


        }





        //printArray(grid);


    }


    vector<double> tridiagonalSolution(const vector<vector<double>>& matrix1, const vector<double>& matrix2) {
        assert(matrix1.size() == matrix2.size() && "Sizes match");

        double y;
        int N = matrix2.size();
        int N1 = N - 1;
        vector<double> a(N), B(N), matRes(N);

        y = matrix1[0][0];
        a[0] = -matrix1[0][1] / y;
        B[0] = matrix2[0] / y;
        for (int i = 1; i < N1; i++) {
            y = matrix1[i][i] + matrix1[i][i - 1] * a[i - 1];
            a[i] = -matrix1[i][i + 1] / y;
            B[i] = (matrix2[i] - matrix1[i][i - 1] * B[i - 1]) / y;
        }

        matRes[N1] = (matrix2[N1] - matrix1[N1][N1 - 1] * B[N1 - 1]) / (matrix1[N1][N1] + matrix1[N1][N1 - 1] * a[N1 - 1]);
        for (int i = N1 - 1; i >= 0; i--) {
            matRes[i] = a[i] * matRes[i + 1] + B[i];
        }

        return matRes;

    }

};

