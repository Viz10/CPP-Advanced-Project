
#include "mySTL.h"

std::ifstream fin("data.in");

using std::string;
using std::cin;
using std::cout;
using mySTL::Pair;

int main()
{
    /*
        string line;
        while (getline(fin, line)) {
            cout << line<<"\n";
        }
        const char* aux = line.c_str();
        cout << aux;
    */


    Pair<int,int> pair1(1, 2);
    Pair<double,int> pair2(2.3,1); 
    
    pair1 = pair2;

    cout << pair1.first << " " << pair1.second;

    //mySTL::Dummy<double> helper;
    //helper.display(7.7);
   
}

