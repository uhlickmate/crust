#include <stdio.h>
#include "include/crust.h"



int main() {
	Result(float, Error) res_ok = Ok(7.5);
	Result(int, Error) res_err = Err(ERR_NONE);
	Option(int) opt_some = Some(15);
	Option(bool) opt_none = None;

	println("res_ok has a value of ", unwrap_res(res_ok));
	println("opt_some has a value of ", expect_opt(opt_none, "Msg"));

}