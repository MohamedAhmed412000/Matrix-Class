// What is made in this class
/*
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

*/

#include <iostream>
#include <vector>
#include<math.h>
#include<string>
#include<cstdlib>
using namespace std;

int GetRows (string str)
{
	int r = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i]==';')
		{
			r++;
		}
	}
	r++;
	return r;
}
int GetColumns (string str)
{
	int c=1;
	for (int i = 0; i < str.length() ; i++)
	{
		if (str[i]==' ')
		{
			c++;
		}
		else if (str[i]==';')
		{
			break;
		}
	}
	return c;
}
bool check (string str){
	int c = 0, i1 = 0;   //c : count of spaces between every semicolon and onother semicolon
	bool flag = true;
	vector <int> check1;
	for(int x1 = 0; x1 < (str.length()-1); x1++)
	{
		while (!(str[i1]==';'||str[i1]==']'))
		{ 
			i1++;
			if (str[i1]==' ')
			{
				c++;
			}
		}
		x1 = i1;
		i1++;
		check1.push_back(c);
		c = 0;
	}
	for(int j = 0; j < GetRows(str)-1; j++)
	{
		if(check1.at(j+1)!=check1.at(j))
		{
			flag = false;
			break;
		}
	}
	return flag;
}
float** StringToMatrix(string str){
	int count1 = 0, count2 = 0;
	vector <int> arr1;
	vector <string> arr2;
	vector <float> arr3;
	float **ar = new float*[100];
	for (int i = 0; i < 100; i++)
	{
		ar[i] = new float[100];
	}
	// We made 2-dimensional array
	for (int i = 0; i < str.length() ; i++)
	{
		if (str[i]=='['||str[i]==' '||str[i]==';'||str[i]==']')
		{
			arr1.push_back(i);
			count1++;
		}
	}
	count1--;
	// We Stored the places of ÝæÇÕá
	for (int i = 0; i < count1 ; i++)
	{
		arr2.push_back(str.substr(arr1.at(i)+1, (arr1.at(i+1) - arr1.at(i) - 1)));
	}
	// cut long string into small strings
	for (int i = 0; i < count1 ; i++)
	{
		arr3.push_back(atof(arr2.at(i).c_str()));
	}
	// We convert small strings to array of floats
	for (int i = 0; i < GetRows(str); i++)
	{
		for(int s = 0; s < GetColumns(str); s++)
		{
			ar[i][s] = arr3.at(count2);
			count2++;
		}
	}
	return ar;
}
struct pos{
	int i,j;
	pos(int x, int y){
		i = x;
		j = y;
	}
};

class Matrix{
private:
	int height,width;
	float **arr;
	bool test;  // To know that user entered the array
	int index;
public:
	Matrix(int h = 3, int w = 3){
		height = h;
		width = w;
		test = false;
		arr = new float*[height];
		for (int i = 0; i < height; i++)
		{
			arr[i] = new float[width];
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				arr[i][j] = 0;
			}
		}
	}
	Matrix(const Matrix& b){
		height = b.height;
		width = b.width;
		test = b.test;
		arr = new float*[height];
		for (int i = 0; i < height; i++)
		{
			arr[i] = new float[width];
		}
		for(int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				arr[i][j] = b.arr[i][j];
			}
		}
	}
	Matrix(string mat){
		InputMatrix(mat);
	}
	friend istream& operator >> (istream& in, Matrix mat){
		cout << "Enter No of Rows, Columns Respectely\n";
		in >> mat.height >> mat.width;
		for (int i = 0; i < mat.height; i++)
		{
			for (int j = 0; j < mat.width; j++)
			{
				cout << "Enter the element of raw: " << i + 1 << " and column: " << j + 1 << endl;
				in >> mat.arr[i][j];
			}
		}
		system("cls");
		mat.test = true;
		return in;
	}
	void InputMatrix(string mat){
		if(check(mat)){
			arr = StringToMatrix(mat);
			height = GetRows(mat);
			width = GetColumns(mat);
			test = true;
		}	
		else
			cout << "ERROR, The Matrix Is Wrong\n";
	}
	void InputMatrix(){
		string mat;
		getline(cin, mat);
		InputMatrix(mat);
	}
	void SetArray(int h, int w){
		height = h;
		width = w;
		delete arr;
		arr = new float*[height];
		for (int i = 0; i < height; i++){
			arr[i] = new float [width];
		}
		test = false;
	}
	Matrix operator+ (Matrix b){
		if(height == b.height && width == b.width){
			Matrix c = *this;
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					c.arr[i][j] = arr[i][j] + b.arr[i][j];
				}
			}
			c.test = true;
			return c;
		}
		else
			cout << "ERROR, Matrices Dimensions Are Different\n";
	}
	Matrix operator- (Matrix b){
		if(height == b.height && width == b.width){
			Matrix c = *this;
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					c.arr[i][j] = arr[i][j] - b.arr[i][j];
				}
			}
			c.test = true;
			return c;
		}
		else
			cout << "ERROR, Matrices Dimensions Are Different\n";
	}
	Matrix operator* (Matrix b){
		if(width == b.height){
			Matrix c;
			c.height = height;
			c.width = b.width;
			float sum = 0;
			for (int i = 0; i < height; i++){
				for (int j = 0; j < b.width; j++){
					for (int k = 0; k < width; k++){
						sum += arr[i][k] * b.arr[k][j];
					}
					c.arr[i][j] = sum;
					sum = 0;
				}
			}
			c.test = true;
			return c;
		}
		else
			cout << "ERROR, Matrix Dimensions aren't Possible to Multiply\n";
	}
	Matrix operator* (float no){
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				this->arr[i][j] *= no;
			}
		}
		test = true;
		return *this;
	}
	Matrix operator^ (int no){
		if (height == width){
			if(no < 0){
				cout << "ERROR, No Change";
				return *this;
			}
			else
			{
				Matrix b;
				if (no == 0)
					b = GenerateUnitMatrix(height);
				else if(no > 0){
					b = *this;
					for (int i = 1; i < no; i++)
					{
						b = b * *this;
					}
				}
				b.test = true;
				return b;
			}
		}
		else
			cout << "ERROR, Matrix Can't be Multiblied\n";
	}
	Matrix Transpose (){
		Matrix b(width, height);
		b.height = width;
		b.width = height;
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				b.arr[j][i] = arr[i][j];
			}
		}
		b.test = true;
		return b;
	}
	float Determinant (){
		if (height == width){
			if(test){
				float con = 0, det = 1;
				for (int i = 1; i < height; i++){
					int k = 0;
					while (k != i){ 
						con = (-(arr[i][k]) / arr[k][k]);
						for (int j = 0; j < width; j++){
							arr[i][j]=((con * arr[k][j]) + arr[i][j]);    //ÚÔÇä äÎáí ÇáãËáË ÇáÓÝáí ÈÕÝÑ 
						}
						k++;
					}
				}
				for (int i = 0;i < width ;i++){
					for (int j = 0;j < width; j++){
						if (i == j)
							det *= arr[j][i];                 // ÚÔÇä äÍÓÈ ÇáãÍÏÏ ãä ÚáÇÞÉ ÍÇÕá ÖÑÈ ÚäÇÕÑ ÇáÞØÑ ÇáÑÆíÓí
					}
				}
				return det;
			}
			else
				cout << "ERROR, Please enter the array first\n";
		}
		else
			cout << "ERROR, The Matrix must be Square Matrix\n";
	}
	Matrix Inverse (){
		if (height == width){
			Matrix b(height, 2 * width), c;
			b.test = true;
			c = *this;
			int k;
			float con = 0;
			for (int j = 0; j < b.width; j++){
				for (int i = 0; i < b.height; i++){
					if (j < b.width /2){
						b.arr[i][j] = arr[i][j];
					}
					else
					{
						if ((j - width) == i)                //ÚÔÇä äßæä ÇáãÕÝæÝ ÇáÞØÑíÉ I ÌäÈ ÇáãÕÝæÝÉ ÇáÇÕáíå
							b.arr[i][j] = 1;
					}
				}
			}
			for (int i = 1; i < b.height; i++){
				k = 0;
				while (k != i){
					con = (-(b.arr[i][k]) / b.arr[k][k]);
					for (int j = 0; j < b.width; j++){
						b.arr[i][j] = ((con * b.arr[k][j]) + b.arr[i][j]);        //ßÏå ÕÝÑäÇ ÇáãËáÊ ÇáÓÝáí
					}
					k++;
				}
			}
			for (int i = 0; i < b.height; i++){
				con = b.arr[i][i];
				for (int j = 0; j < b.width; j++){
					b.arr[i][j] = b.arr[i][j] / con;                       //ßÏå ÎáíäÇ ãÚÇãáÇÊ ÇáÞØÑ ÇáÑÆíÓí Ýí ÇáãÕÝæÝÉ = 1
				}
			}
			for (int i = 1; i < b.height; i++){
				k = 0;
				while(k != i){
					con = -b.arr[k][i];
					for (int j = 0; j < b.width; j++){
						b.arr[k][j] = (con * b.arr[i][j]) + b.arr[k][j];        //ßÏå ÕÝÑäÇ ÇáãËáË ÇáÚáæí ááãÕÝæÝÉ
					}
					k++;
				}
			}
			for (int i = 0; i < height; i++){
				for (int j = 0; j < width; j++){
					c.arr[i][j] = b.arr[i][j + width];          //ßÏå ÇÍäÇ äÞáäÇ ÇáãÕÝæÝÉ ÇáãÚßæÓÉ ááÇãÇßä ÇáÇæáí
				}
			}
			c.test = true;
			return c;
		}
		else
			cout << "ERROR, Matrix must be Square Matrix\n ";
}
	Matrix operator/ (Matrix b){
		if (width == b.height && b.height == b.width){
			Matrix c(height, b.width), d = b;
			d = b.Inverse();
			c = *this * d;
			return c;
		}
		else
			cout << "ERROR, Matrices Dimensions aren't possible for division\n";

	}
	/*
	float& operator[] (pos x){
		if(x.i <= height && x.j <= width && x.i > 0 && x.j > 0){
			if(test){
				float z = arr[x.i-1][x.j-1];
				return z;
			}
			else
				cout << "ERROR, Please enter the array first\n";
		}
		else
			cout << "ERROR, Out of Range\n";
	}*/
	/*
	float* operator [] (int x){
		index = x;
		float *ar = arr[index];
		return ar;
	}
	float operator [] (float y){
		int k = (int)y;
		return ((*this)[index][k]);
	}
	*/
	float& operator() (int x, int y){
		if (x <= height && y <= width && x > 0 && y > 0){
			if(test){
				return arr[x-1][y-1];
			}
			else
				cout << "ERROR, Please enter the array first\n";
		}
		else
			cout << "ERROR, Out of Range\n";
	}
	friend Matrix GenerateUnitMatrix (int);
	void PrintInLine(){
		if (test){
			cout<<"[";
			for (int i = 0; i < height; i++){
				for (int j = 0; j < width-1; j++){
					cout<<arr[i][j]<<" ";
				}
				cout<<arr[i][width-1];
				if(i != height-1)
					cout<<";";
			}
			cout<<"]\n";
		}
		else
			cout << "ERROR, Please Enter the array first\n";
	}
	friend ostream& operator << (ostream& o, Matrix mat){
		if (mat.test)
		{
			for (int i = 0; i < mat.height; i++){
				for (int j = 0; j < mat.width; j++){
					if(j == 0)
						o << "[";
					o << " " << mat.arr[i][j] << " ";
					if(j == mat.width-1)
						o << "]\n";
				}
			}
		}
		else
			o << "ERROR, Please enter the array first\n";
		return o;
	}
	/*
	~Matrix(){
		height = width = 0;
		for (int i = 0; i < height; i++)
		{
			delete arr[i];
		}
		delete arr;
	}
	*/ 
	// The destractor makes the code doesn't work
};

Matrix GenerateUnitMatrix (int no){
	if(no < 1)
		cout << "ERROR";
	else{
		Matrix b;
		b.height = b.width = no;
		for (int i = 0; i < no; i++){
			for (int j = 0; j < no; j++){
				if(i == j)
					b.arr[i][j] = 1;
				else
					b.arr[i][j] = 0;
			}
		}
		b.test = true;
		return b;
	}
}

void main()
{
	Matrix m1, m2, m3;
	Matrix m4("[1 -2.5;4 5.2]");
	// m1.InputMatrix("[1 -2.5 3;4 5.25 6;7 8 9.12]"); // [4 5 6;1 7 3]
	// m2.InputMatrix("[3 4.2 10.2;12 -1 0;67 2 13]"); // [1 2 3;5 -1 9]
	//m4.InputMatrix("[1 -2.5;4 5.2]");
	m4 = m4.Inverse();
	m4 = m4.Inverse();
	//m3 = m1 + m2;
	//cout << m4.Determinant();
	m4.PrintInLine();
	cout << m4;
	system("pause");
}