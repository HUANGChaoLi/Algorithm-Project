#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include "Object.h"
using namespace std;

typedef pair<int, double> S;
typedef pair<double, pair<Object*, Object*> > CPL;
typedef pair<double, pair<int, int> > CPM;

// main function
// S int for obj num, double for distance

void swap(S & a, S & b) {
  S temp = a;
  a = b;
  b = temp;
}

CPM min(CPM & a, CPM b, CPM c) {
  if ((a.first != -1) && (a.first <= b.first || b.first == -1) && (a.first <= c.first || c.first == -1)) return a;
  if ((b.first != -1) && (b.first <= a.first || a.first == -1) && (b.first <= c.first || c.first == -1)) return b;
  if ((c.first != -1) && (c.first <= a.first || a.first == -1) && (c.first <= b.first || b.first == -1)) return c;
  return c;
}

int findMedianByQS(vector<S> & rpS, int start, int end) {
  swap(rpS[start], rpS[(start + end) / 2]);
  S pivot = rpS[start];
  int last_small = start;
  for (int i = start + 1; i <= end; ++i) {
    if (rpS[i].second < pivot.second) {
      last_small = last_small + 1;
      swap(rpS[last_small], rpS[i]);
    }
  }
  swap(rpS[start], rpS[last_small]);
  return last_small;
}

int median(vector<S> & rpS, int start, int end, int mid) {
  if (start >= mid || start >= end) return start;
  int pivot = findMedianByQS(rpS, start, end);
  if (pivot < mid)
    return median(rpS, pivot + 1, end, mid);
  if (pivot > mid)
    return median(rpS, start, pivot - 1, mid);
  return pivot;
}

CPM ClosestPairMedian(vector<S> & rpS, int start, int end) {
  if (end - start <= 0) {
    return CPM(-1, pair<int, int>(-1, -1));
  }
  if (end - start == 1) {
    if (rpS[start].second > rpS[end].second) swap(rpS[start], rpS[end]);
    return CPM(rpS[end].second - rpS[start].second, pair<int, int>(rpS[start].first, rpS[end].first));
  }
  int m = median(rpS, start, end, start + (end - start) / 2);
  CPM cpm1 = ClosestPairMedian(rpS, start, m);
  CPM cpm2 = ClosestPairMedian(rpS, m + 1, end);
  CPM cpm12(abs(rpS[m + 1].second - rpS[m].second), pair<int, int>(rpS[m].first, rpS[m + 1].first));
  return min(cpm1, cpm2, cpm12);
}

CPL ClosestPairLine(vector<S> & rpS, vector<Object*> db) {
  CPM cpm = ClosestPairMedian(rpS, 0, rpS.size() - 1);
  return CPL(cpm.first, pair<Object*, Object*>(db[cpm.second.first], db[cpm.second.second]));
}

// PointMultiply of aj and oi

double PointMultiply(vector<double> & aj, Object & oi) {
  double result = 0;
  for (int i = 0; i < aj.size(); ++i) {
    result += aj[i] * oi.getVal(i);
  }
  return result;
}


// Box-Muller method to generate a random variable from N(0, 1) and get a random d vector

void BoxMullerVector(vector<vector<double>*> & result, int m, int d) {
  time_t t;
  srand((unsigned) time(&t));
  double U1, U2, X1;
  for (int j = 0; j < m; ++j) {
    vector<double>* newOne = new vector<double>();
    for (int i = 0; i < d; ++i) {
      U1 = rand() / double(RAND_MAX);
      while (U1 == 0) U1 = rand() / double(RAND_MAX); // log not zero
      U2 = rand() / double(RAND_MAX);
      X1 = sqrt(-2 * log(U1)) * cos(2 * M_PI * U2);
      newOne->push_back(U1);
    }
    result.push_back(newOne);
  }
}

// RandomRrojection

vector<vector<S>*>* RandomRrojection(vector<Object*> db, int m, int d) {
  vector<vector<double>*> a;
  vector<vector<S>*>* result = new vector<vector<S>*>();
  // 1. generate a set of m random projection vector
  BoxMullerVector(a, m, d);

  // 2. empty Sj
  for (int j = 0; j < m; ++j) {
    result->push_back(new vector<S>());
  }

  // 3. calculate S
  int n = db.size();
  double vij;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      vij = PointMultiply(*a[j], *db[i]);
      (*result)[j]->push_back(S(i, vij));
    }
  }

  // free memory of a
  for (int i = 0; i < a.size(); ++i) {
    delete a[i];
  }
  return result;
}


pair<Object*, Object*> ClosestPair(vector<Object*> db, int m, int d) {
  // 1. get m RandomRrojections
  vector<vector<S>*>* dbS = RandomRrojection(db, m, d);

  // 2. let cp be the closest pair
  pair<Object*, Object*> cp;

  // 3. let min be the closest distance, set -1 for a infinity tag
  double min = -1;

  // 4. calculate the closest pair : TYPE CPL for ClosestPairLine return type
  for (int i = 0; i < m; ++i) {
    CPL cpl = ClosestPairLine(*((*dbS)[i]), db);
    double dist = Object::distance(*(cpl.second.first), *(cpl.second.second));
    if (dist <= min || min == -1) {
      min = dist;
      cp = cpl.second;
    }
  }

  // free memory
  for (int i = 0; i < dbS->size(); ++i) {
    delete (*dbS)[i];
  }

  delete dbS;

  return cp;
}


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
  /* get n and d and f and check */

  // start
  clock_t start,stop;
  start = clock();

  int ignoreNum;
  int pixel;
  int len = n;
  vector<Object*> database;

  fread(&ignoreNum, sizeof(char), 4, inputFile);
  fread(&ignoreNum, sizeof(char), 4, inputFile);
  fread(&ignoreNum, sizeof(char), 4, inputFile);
  fread(&ignoreNum, sizeof(char), 4, inputFile);

  while (len--) {
    Object* newOne = new Object(d);
    for (int i = 0; i < d; ++i) {
      fread(&pixel, sizeof(char), 1, inputFile);
      newOne->setVal(i, (int)pixel);
    }
    database.push_back(newOne);
  }

  int m = 100;
  pair<Object*, Object*> cp = ClosestPair(database, m, d);

  Object* one = cp.first;
  Object* two = cp.second;

  cout << *one << *two;

  for (int i = 0; i < database.size(); ++i) {
    delete database[i];
  }

  fclose(inputFile);

  stop = clock();
  printf("Total Use Time: %fs\n", (stop - start) / (CLOCKS_PER_SEC * 1.0));

  return 0;
}
