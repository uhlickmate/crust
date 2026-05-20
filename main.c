#include <stdio.h>
#include "include/crust.h"



int main() {
	Result(int, Err) x = Ok(1);
	printf("%d", unwrap(x));
}