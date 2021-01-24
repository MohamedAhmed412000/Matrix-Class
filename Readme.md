# What is made in this class:

	// Define Matrix //
		- Matrix name(height(no. of raws), width(no. of columns))     -ex- Matrix a(3, 3)   - This is the default -
		- Matrix name()                                                                     - This will create matrix 3*3 -
		- Matrix name(string matrix in matlab form)                   -ex- Matrix a("[2 3;-5.2 0;7.1 -8]")
	
	// Input Matrix //
		- cin >> name                                                                        - follow the steps -
		- name.InputMatrix(string matrix in matlab form)               -ex- a.InputMatrix("[2 3;-5.2 0;7.1 -8]")
		- name.InputMatrix()                                                                 - follow the steps -

	// Change Matrix Size //
		- name.SetArray(height(no. of raws), width(no. of columns))    -ex- a.SetArray(3, 2);

	// Print Matrix //
		- name.PrintInLine()                                                                 - Print Matrix in matlab form
		- cout << name                                                                       - Print in matrix look

	// Operation Support //
		- Sum
			  c = a + b;
		- Multiply
			  c = a * b;
		- Multiply with number
			  float x;
			  c = a * x;                                                                       - every number in matrix multiplied with x
		- Subtract
			  c = a - b;
		- Division
			  c = a / b;
		- Transpose
			  b = name.Transpose()
		- Determinant
			  float x = name.Determinant()
		- Inverse
			  b = name.Inverse()
