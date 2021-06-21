/*
 * main.cpp
 *
 */

#include <dirent.h>

#include "skeleton.h"
#include "primitive.h"
#include "map.h"
#include "pipe.h"

using namespace std;

void sha_3(int bit_width) {
  /*
   * initialize input data
   */
  Data *A[5][5];
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      A[i][j] = new Data();
    }
  }
  Data *RC = new Data();

  /*
   * represent the application with skeletons (bottom up)
   */
  Skeleton *theta1 = new Map(bit_width);
  for (int i = 0; i < 5; ++i) {
    Skeleton *xors = new Pipe(bit_width);
    vector<Data *> outputs =
        xors->append(new Primitive(bit_width, XOR, A[i][0], A[i][1]));
    for (int j = 2; j < 5; ++j) {
      outputs =
          xors->append(new Primitive(bit_width, XOR, outputs[0], A[i][j]));
    }
    theta1->append(xors);
  }

  Skeleton *theta2 = new Map(bit_width);
  for (int i = 0; i < 5; ++i) {
    theta2->append(new Primitive(bit_width, XOR, (*theta1)[(i + 4) % 5],
                                 (*theta1)[(i + 1) % 5]));
  }

  Skeleton *theta3 = new Map(bit_width);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      theta3->append(new Primitive(bit_width, XOR, A[i][j], (*theta2)[i]));
    }
  }

  Skeleton *chi = new Map(bit_width);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Skeleton *naxs = new Pipe(bit_width);
      vector<Data *> outputs = naxs->append(
          new Primitive(bit_width, NOT, (*theta3)[(i + 1) % 5 * 5 + j]));
      outputs = naxs->append(new Primitive(bit_width, AND, outputs[0],
                                           (*theta3)[(i + 2) % 5 * 5 + j]));
      naxs->append(
          new Primitive(bit_width, XOR, outputs[0], (*theta3)[i * 5 + j]));
      chi->append(naxs);
    }
  }

  Skeleton *iota = new Primitive(bit_width, XOR, (*chi)[0], RC);

  Skeleton *sha_3 = new Pipe(24);
  sha_3->append(theta1);
  sha_3->append(theta2);
  sha_3->append(theta3);
  sha_3->append(chi);
  sha_3->append(iota);

  /*
   * synthesize
   */
  sha_3->synthesize();
  cout << "cycle " << sha_3->cycle_compute << endl;
  cout << "bbox " << sha_3->bounding_box << endl;

  /*
   * simulate
   */
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      A[i][j]->set_value(1);
      A[i][j]->set_position(false);
    }
  }
  RC->set_value(1);
  RC->set_position(false);
  sha_3->simulate();

  /*
   * clean
   */
  delete sha_3;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      delete A[i][j];
    }
  }
  delete RC;
}

int main() {
  sha_3(64);
  return 0;
}
