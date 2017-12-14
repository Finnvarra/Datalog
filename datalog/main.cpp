#include "Database.h"
#include "Scanner.h"

int main(int argc, char* argv[]) {
    string file1, file2;
   // cin>>file1>>file2;
    file1=argv[1];
    file2=argv[2];
    Scanner d;
    d.final(file1, file2);
    //cin>>file1;
    return 0;
}
