#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <math.h>


using namespace std;

class Calculation {
private:
	string pointSchedule = "with points pointtype 5";
	string lineSchedule = "with lines lw 3";
	string path = "\"D:/MEGA/���/6 �������/���/labs/lab2/";


protected:
	int numberOfPointByT, numberOfPointByX;
	double (*f)(double, double);
	double (*phi)(double), (*psi_0)(double), (*psi_1)(double);
	double k0; 
	double alfa0, alfa1, beta0, beta1;

	vector<vector<double>> grid;


public:

	Calculation() { // individual option
		this->numberOfPointByT = 1e+3;
		this->numberOfPointByX = 1e+3;
		this->k0 = 1;
		this->f = [](double t, double x) {
			return t * x * x - t * t;
		};
		this->phi = [](double x) {
			return x;
		};
		this->psi_0 = [](double t) {
			return 1.0;
		};
		this->psi_1 = [](double t) {
			return 3 / 2 * t * t + 2;
		};
		this->alfa0 = 0;
		this->alfa1 = 1;
		this->beta0 = 1;
		this->beta1 = 1;

		grid = vector<vector<double>>(numberOfPointByT, vector<double>(numberOfPointByX));

	}


	void drawGraph(string name, string text) {
		string str;
		str = path + name + "\" using 1:2 title \"" + text + "\" " + pointSchedule + ";";
		std::ofstream graphic("file");
		cout << str << endl;
		//graphic << "plot " << str << "; pause mouse keypress" << "\n";
		graphic << "set border 3" << endl;
		graphic << "plot " << str << endl;
		graphic.close();
		system("gnuplot -persist file");

		graphic.close();
	}

	template <typename T, typename K>
	void makeFileForGraph(const vector<T>& first, const vector<K>& second, const string fileName) {
		//cout << "file" << endl;

		ofstream file(fileName);

		assert(first.size() == second.size() && "Size mismatch");

		for (int i = 0; i < first.size(); i++) {
			//cout << "file = " << i << endl;

			file << first[i] << " " << second[i] << endl;
		}


	}

	void setNumberOfPointByT(int numberOfPointByT) {
		this->numberOfPointByT = numberOfPointByT;
	}

	void setNumberOfPointByX(int numberOfPointByX) {
		this->numberOfPointByX = numberOfPointByX;
	}

	double exactSolution(double t, double x) {
		return t * t * x * x / 2 + x;
	}


protected:
	virtual void Calculate(double t, double x) = 0;



};

