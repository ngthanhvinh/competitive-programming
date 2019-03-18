#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int n = inf.readInt(1, 2500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2500, "m");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
      inf.readToken("[0-1]{" + vtos(m) + "}", "s");
      inf.readEoln();
    }

    inf.readEof();

    return 0;
}
