#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "read_write_file.h"

using namespace std;
using namespace tensor_hao;

//Check sample size from a file
int file_sample_size(string filename, int L)
{
    ifstream file(filename);
    string line;
    int i=0;
    while( getline(file, line) ) i++;
    file.close();
    return i/L;
}



//Read data from file: complex<double>
void read_file(complex<double>& data, ifstream& file)
{
    double re, im;
    file >> re >> im;
    data = complex<double>(re, im);
}

//Read data from file: complex<double>*
void read_file(int L, complex<double>* data, ifstream& file)
{
    double re, im;
    for(int i=0; i<L; i++)
    {
        file >> re >> im;
        data[i] = complex<double>(re, im);
    }
}



//Read data from file (Use filename): complex<double>
void read_file(complex<double>& data, string filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in read_file!!! "<<filename<<endl; exit(1);}
    read_file(data, file);
    file.close();
}

//Read data from file (Use filename): complex<double>*
void read_file(int L, complex<double>* data, string filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if ( ! file.is_open() ) {cout << "Error opening file in read_file!!! "<<filename<<endl; exit(1);}
    read_file(L, data, file);
    file.close();

}



//Write data to file
void write_file(complex<double> data, string filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    file<<setprecision(16)<<scientific;
    file<<setw(26)<<data.real()<<setw(26)<<data.imag()<<"\n";
    file.close();
}

//Write data to file
void write_file(int L, const complex<double>* data, string filename)
{
    ofstream file;
    file.open(filename, ios::out|ios::app);
    file<<setprecision(16)<<scientific;
    for(int i=0; i<L; i++)
    {
        file<<setw(26)<<data[i].real()<<setw(26)<<data[i].imag()<<"\n";
    }
    file.close();
}
