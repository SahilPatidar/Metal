#!/bin/bash

	# unameOut="$(uname -s)"
	# case "${unameOut}" in
	# 	Linux*) 	machine=Linux;;
	# 	Darwin*)	machine=Mac;;
	# 	MINGW*)		machine=MinGw;;
	# 	*)          machine="UNKNOWN:${unameOut}"
	# esac
	# # install opam dependencies
	# cd /home/opam/opam-repository && git pull
	# opam update 
	# cd -
	# eval $(opam env)
	# make install

	# if [[ $clang -ne 0]]; then
	# fi


	# run  wget https://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz
	# run tar xf clang*
	# run sudo cp -r clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04/* /usr/local/



#!/bin/bash
# if [ $EUID -ne 0] then
# 	echo "You must be root to install"
# 	exit 1
# fi

# Define variables
MYLANG_SOURCE_DIR=$1
MYLANG_BUILD_DIR="$MYLANG_SOURCE_DIR/build"
INSTALL_DIR="/usr/local/bin"
MYLANG_EXECUTABLE="metal"

cd $MYLANG_SOURCE_DIR || exit
mkdir -p "build"
cd "build" || exit

# LLVM Archive URL and Destination
LLVM_ARCHIVE_URL="https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.4/llvm-17.0.4.src.tar.xz"
LLVM_ARCHIVE_DEST="/llvm/llvm.tar.xz"
# LLVM_ARCHIVE_DEST="/llvm/llvm.tar.gz"

# Step 1: Download and extract LLVM
if command -v llvm-config &> /dev/null; then
    echo "LLVM is installed."
	LLVM_DIR_PATH="/usr/local/lib/cmake/llvm/LLVM"
	LLVM_INC_PATH="/usr/local/include"
	LLVM_LIB_PATH="/usr/local/lib"
	# Step 2: Build your metal compiler
	cmake -D -LLVM_DIR_PATH="$LLVM_DIR_PATH" -LLVM_INC_PATH="$LLVM_INC_PATH" -LLVM_LIB_PATH="$LLVM_LIB_PATH"  "../CmakeLists.txt"
	# cmake "../CmakeLists.txt"
else
    echo "installing LLVM...."
	mkdir -p llvm
	mkdir -p /llvm/build
	# curl -L $LLVM_ARCHIVE_URL -o $LLVM_ARCHIVE_DEST
	wget $LLVM_ARCHIVE_URL
	tar -xf $LLVM_ARCHIVE_DEST -C /llvm
	cd /llvm/build || exit
	if command -v cmake &> /dev/null; then
		echo "CMake is installed."
	else
		echo "CMake is not installed."
		exit
	fi

	if command -v make &> /dev/null; then
		echo "Make is installed."
	else
		echo "Make is not installed."
		exit
	fi

	if command -v clang &> /dev/null; then
		echo "Clang is installed."
	else
		echo "Clang is not installed." 
		exit
	fi
	cmake -S llvm -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DLLVM_ENABLE_PROJECTS=llvm ../
	cmake -S llvm -B build -G Unix Makefiles -DCMAKE_INSTALL_PREFIX=. -DCMAKE_BUILD_TYPE=Debug -DLLVM_ENABLE_PROJECTS=llvm ../
	make j$npm
    echo "LLVM is installed."
	LLVM_DIR_PATH="/llvm/"
	LLVM_INC_PATH="/llvm/include"
	LLVM_LIB_PATH="/llvm/lib"

	# Replace the following commands with your actual build commands
	# For example, if you are using cmake:

	# Step 3: Compile and link with LLVM dynamically
	cmake -D -LLVM_DIR_PATH="$LLVM_DIR_PATH" -LLVM_INC_PATH="$LLVM_INC_PATH" -LLVM_LIB_PATH="$LLVM_LIB_PATH"  "../CmakeLists.txt"

	# Step 5: Clean up temporary files
	rm -rf /llvm
	rm -f $LLVM_ARCHIVE_DEST
	cd "$MYLANG_SOURCE_DIR" || exit
fi

	
make all
# mkdir -p "$MYLANG_BUILD_DIR"
# cd "$MYLANG_BUILD_DIR" || exit


# Assuming the executable is generated in the build directory
MYLANG_COMPILER="./$MYLANG_EXECUTABLE"

# Step 4: Install mylang compiler to /usr/bin/
sudo cp "$MYLANG_EXECUTABLE" "$INSTALL_DIR"

echo "Installation complete."

