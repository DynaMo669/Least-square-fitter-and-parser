#include "stdlib.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple> 
#include <string>
#include <sstream>
#pragma warning (disable : 4996)

using namespace std;


tuple<vector<double>, vector<double>> parser(string);

void LSF(vector<double>, vector<double> );



tuple<vector<double>, vector<double>> parser(string path) {

	vector<char> t_x, t_y;
	vector<double> x_val, y_val;
	string containerx;
	string containery;
	


	long lsize;
	FILE* datafile = fopen(path.c_str(), "rb");
	fseek(datafile, 0, SEEK_END);
	lsize = ftell(datafile);
	rewind(datafile);

	char* buff;

	buff = (char*)malloc(sizeof(char) * lsize);


	fread(buff, 1, lsize, datafile);




	fclose(datafile);



	for (int i = 0; i < (lsize); i++) {

		if (buff[i] == '(') {

			int j = 0;


			while (buff[i + j + 1] != ',') {

				
				t_x.push_back((buff[i + j + 1]));
				j++;
				


			}

			
			for (int z = 0; z < (size(t_x)); ++z) {


				containerx = containerx + t_x[z];


			}
			
			x_val.push_back(stod(containerx));
			t_x.clear();
			containerx.clear();
		}


	}


	for (int i = 0; i < (lsize); i++) {

		if (buff[i] == ',') {
			
			int j = 0;


			while (buff[i + j + 1] != ')') {

				
				t_y.push_back((buff[i + j + 1]));
				j++;
				


			}




			for (int z = 0; z < size(t_y); z++) { // concactenate t_y into a number


				containery = containery + t_y[z];


			}

			
			y_val.push_back(stod(containery));
			t_y.clear();
			containery.clear();



		}




	}


	free(buff);

	

	return make_tuple(x_val, y_val);
}





	




void LSF(vector<double> x, vector<double> y) { // the thingamajig that takes x and y values and spits out the slope and intercept for our eq.

	double m, b =  0;
	double xsum = 0;
	double ysum = 0;
	double xxsum = 0;
	double yysum = 0;
	double xysum = 0;
	
	
	
	int n = x.size();
	double det = 0;
	
	


	for (int i = 0; i < n; i++) {

		xsum = xsum + x[i];
		ysum = ysum + y[i];
		xxsum = xxsum + pow(x[i], 2);
		yysum = yysum + pow(y[i], 2);
		xysum = xysum + (x[i] * y[i]);
		
	}

	det = (n * xxsum) - pow(xsum, 2);
	m = ((n * xysum) - (xsum * ysum)) / det;
	b = ((xxsum * ysum) - (xsum * xysum)) / det;


	cout << endl << xsum << endl << ysum << endl << xxsum << endl << yysum << endl << xysum << endl << det ;
	cout << endl << m << " x + " << b << " = y";
}


/*
residual = observed data - fitted data
y = mx+b
sum of residuals squared = sum(sq((y-mx-b)) /// squared: so we can differentiate and get the minima

dS/dm = -2sum(x(y-mx-b)) = 0
dS/db = -2sum(y-mx-b) = 0

b = 1/n(sum(y)-m sum(x)

yfitted = Ax + B/x +C


*/





int main() {

	
	string PATH = "data.txt";



	vector<double> xvec, yvec;
	tie(xvec, yvec) = parser(PATH);
	LSF(xvec, yvec);


}