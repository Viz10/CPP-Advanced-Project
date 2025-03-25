#include "mySTL.h"
#include "Singleton.h"

std::ifstream fin("data.in");

using std::string;
using std::cin;
using std::cout;
using mySTL::Pair;
using Singleton::MySingleton;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    MySingleton::init();
    MySingleton::init();
    MySingleton::init();
    MySingleton::init();
    auto& instance1 = MySingleton::get();
    instance1.display();
    MySingleton::destroy(); /// no instance exists
    
    auto& instance2 = MySingleton::get();
    instance2.get().get().display();
    MySingleton::get().get().display();
    MySingleton::destroy();

    cout << "aaa\n";
}

/*
    string line;
    while (getline(fin, line)) {
        cout << line<<"\n";
    }
    const char* aux = line.c_str();
    cout << aux;

    Pair<int,int> pair1(1, 2);
    Pair<double,int> pair2(2.3,1);

    pair1 = pair2;

    cout << pair1.first << " " << pair1.second;

    mySTL::Dummy<double> helper;
    helper.display(7.7);
   */
