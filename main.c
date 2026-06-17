#include "include/crust.h"
#include "include/macros.h"
#include "include/vector.h"
#include <stdio.h>

int main() {
  Vec(int) v = Vec_new();
  Vec_push(int, v, 1);
  Vec_push(int, v, 2);
  Vec_push(int, v, 3);
  Vec_remove(int, v, 1);
  println(unwrap_opt(Vec_get(int, v, 0)));
  println(unwrap_opt(Vec_get(int, v, 1)));

	println(Vec_contains(int, v, 10));

  println(unwrap_opt(Vec_get(int, v, 2)));
}
