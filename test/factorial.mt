extern fn printf;

fn facto(data i32) -> i32 {
	let mut f = 1;
	for i in 1..data {
		f *= i;
	}
	return f;
}

fn main() -> i32 {
	printf("Factorial of 5 is: %d\n", facto(5));
	return 0;
}