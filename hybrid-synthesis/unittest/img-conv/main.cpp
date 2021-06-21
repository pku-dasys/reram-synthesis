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

void image_convolution(int bit_width) {
  /*
   * initialize input data
   */
  const int image_size = 100;
  const int filter_size = 3;
  Data *image[image_size][image_size];
  for (int i = 0; i < image_size; ++i) {
    for (int j = 0; j < image_size; ++j) {
      image[i][j] = new Data();
    }
  }
  Data *filter[filter_size][filter_size];
  for (int i = 0; i < filter_size; ++i) {
    for (int j = 0; j < filter_size; ++j) {
      filter[i][j] = new Data();
    }
  }

  /*
   * represent the application with skeletons (bottom up)
   */
  Skeleton *convolution = new Map(bit_width);
  for (int i = 0; i <= image_size - filter_size; ++i) {
    for (int j = 0; j <= image_size - filter_size; ++j) {
      Skeleton *mac = new Pipe(bit_width);
      Skeleton *muls = new Map(bit_width);
      for (int k = 0; k < filter_size; ++k) {
        for (int l = 0; l < filter_size; ++l) {
          muls->append(
              new Primitive(bit_width, MUL, image[i + k][j + l], filter[k][l]));
        }
      }
      mac->append(muls);
      mac->append(
          new Reduce(bit_width, new Primitive(bit_width, ADD, muls->outputs)));
      convolution->append(mac);
    }
  }

  /*
   * synthesize
   */
  convolution->synthesize();
  cout << "cycle " << convolution->cycle_compute << endl;
  cout << "bbox " << convolution->bounding_box << endl;

  /*
   * simulate
   */
  for (int i = 0; i < image_size; ++i) {
    for (int j = 0; j < image_size; ++j) {
      image[i][j]->set_value(1);
      image[i][j]->set_position(false);
    }
  }
  for (int i = 0; i < filter_size; ++i) {
    for (int j = 0; j < filter_size; ++j) {
      filter[i][j]->set_value(1);
      filter[i][j]->set_position(false);
    }
  }
  convolution->simulate();

  /*
   * clean
   */
  delete convolution;
  for (int i = 0; i < image_size; ++i) {
    for (int j = 0; j < image_size; ++j) {
      delete image[i][j];
    }
  }
  for (int i = 0; i < filter_size; ++i) {
    for (int j = 0; j < filter_size; ++j) {
      delete filter[i][j];
    }
  }
}

int main() {
  image_convolution(8);
  return 0;
}
