#include "Lib.h"

double BMI(double height, double weight){
  height = height / 100;

  return weight / (height * height);
}
