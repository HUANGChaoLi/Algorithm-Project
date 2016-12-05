#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char const *argv[]) {
  int n = 0, d = 0;
  string dbFileName;

  /* get n and d and f and check */
  for (int i = 0; i < argc; ++i) {
    if (argv[i][0] == char('-') && argv[i][1] == char('n')) {
      n = atoi(argv[i + 1]);
    }
    if (argv[i][0] == char('-') && argv[i][1] == char('d')) {
      d = atoi(argv[i + 1]);
    }
    if (argv[i][0] == char('-') && argv[i][1] == char('f')) {
      dbFileName = argv[i + 1];
    }
  }

  if ((n <= 0) || (d <= 0) ) {
    cout << "n and d must larger than zero." << endl;
    return 0;
  }

  FILE* inputFile = fopen(dbFileName.c_str(), "rb");

  if (!inputFile) {
    cout << "Unable to open file : " << dbFileName << endl;
    return 0;
  }
  /* get n and d and f and check*/

  ofstream outputFile;
  outputFile.open("example.txt");

  int ignoreNum;
  int pixel;
  int len = n;

  fread(&ignoreNum, sizeof(char), 4, inputFile);
  fread(&ignoreNum, sizeof(char), 4, inputFile);
  fread(&ignoreNum, sizeof(char), 4, inputFile);
  fread(&ignoreNum, sizeof(char), 4, inputFile);
  while (len--) {
    for (int i = 0; i < 28; ++i) {
      for (int j = 0; j < 28; ++j) {
        fread( &pixel, sizeof(char), 1, inputFile );
        outputFile << ( unsigned int) pixel;
        if (( unsigned int)pixel >= 100) outputFile << " ";
        else if (( unsigned int)pixel >= 10) outputFile << "  ";
        else outputFile << "   ";
      }
      outputFile << endl;
    }
    outputFile << endl;
  }
  fclose(inputFile);
  outputFile.close();

  return 0;
}