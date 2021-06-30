/*
 * main.cpp
 *
 */

#include <dirent.h>

#include "primitive.h"
#include "map.h"
#include "reduce.h"
#include "pipe.h"

using namespace std;

void dotprod(int len, int bitwidth) {
  Data *a[len];
  Data *b[len];
  for (int i = 0; i < len; ++i) {
    a[i] = new Data();
    b[i] = new Data();
  }

  /* dot product */
  Skeleton *dotprod = new Pipe(bitwidth);

  Skeleton *m = new Map(bitwidth);
  for (int i = 0; i < len; ++i) {
    m->append(new Primitive(bitwidth, MUL, a[i], b[i]));
  }

  Skeleton *r = new Reduce(bitwidth, new Primitive(bitwidth, ADD, m->outputs));

  dotprod->append(m);
  dotprod->append(r);

  /*
   * synthesize
   */
  dotprod->synthesize();
  cout << "cycle " << dotprod->cycle_compute << endl;
  cout << "bbox " << dotprod->bounding_box << endl;

  /*
   * simulate
   */
  for (int i = 0; i < len; ++i) {
    a[i]->set_value(i);
    a[i]->set_position(false);
    b[i]->set_value(i + 1);
    b[i]->set_position(false);
  }
  dotprod->simulate();
  cout << "value " << dotprod->outputs.front()->value << endl;

  /*
   * clean
   */
  delete dotprod;
  for (int i = 0; i < len; ++i) {
    delete a[i];
    delete b[i];
  }
}

int main() {
  dotprod(1000, 32);
  return 0;
}
