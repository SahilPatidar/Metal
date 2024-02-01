extern fn printf;

fn func(data *const i8) {
	printf("Hello %s\n", data);
}

fn main() -> i32 {
	func("Electrux");
	return 0;
}