#include <ctime>
#include <iomanip>
#include <iostream>

using std::setw;
using std::cout;
using std::endl;

class Timer {
  private:
    clock_t start, finish;
  public:
    Timer() { start = clock(); }
    ~Timer() { finish = clock();
              cout << setw(5) << " "
                   << "Total time: "
                   << ((double)(finish - start)/CLOCKS_PER_SEC)
                   << endl; }
};
