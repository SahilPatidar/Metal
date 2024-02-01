# Metal
metal programming language is simple programming lang with all basic capability
like {function, struct, ifelse,  while, for ..etc}

# Examples

1. Hello World

```rs
extern fn printf;

fn main(argc i32, argv *const *const i8) -> i32 {
    printf("hello world!\n");
}
```

2. A Basic Function

```rs
extern fn printf;

fn func(data *const i8) {
	printf("Hello %s\n", data);
}

fn main() -> i32 {
	func("Sahil");
	return 0;
}
```

3. Factorial of 5

```rs
extern fn printf;

fn facto(data i32) -> i32 {
	let f = 1;
	for i in data..1..-1 {
		f *= i;
	}
	return f;
}

fn main() -> i32 {
	printf("Factorial of 5 is: %d\n", facto(5));
	return 0;
}
```

4. Structures 

There are no classes. Only structs. 

```rs
extern fn printf;

struct Point {
	x i32,
	y ui32,
	z flt64,
}


fn main() -> i32 {
	let mut point = Point{x:1, y:2, z:3.25};
	return 0;
}
```

# Installation

## Prerequisites

To install `metal`, the following programs are required:
* A C++11 standard compliant compiler
* CMake (build system - for compiling the project)

**Note**: working.


Visual Studio Code: [metal-lang/metalcode](https://github.com/metal-lang/metalcode.git)

system requirement:
llvm-17.0.0 above
clang 
C++14 above

