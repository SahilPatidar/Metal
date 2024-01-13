#!/bin/bash

	# unameOut="$(uname -s)"
	# case "${unameOut}" in
	# 	Linux*) 	machine=Linux;;
	# 	Darwin*)	machine=Mac;;
	# 	MINGW*)		machine=MinGw;;
	# 	*)          machine="UNKNOWN:${unameOut}"
	# esac

# if [ $EUID -ne 0] then
# 	echo "You must be root to install"
# 	exit 1
# fi


#!/bin/bash
MYLANG_SOURCE_DIR="$1"
MYLANG_BUILD_DIR="$MYLANG_SOURCE_DIR/build"
INSTALL_DIR="/usr/local/bin"
MYLANG_EXECUTABLE="metal"

# Check if directories exist, create if not
if [ ! -d "$MYLANG_BUILD_DIR" ]; then
    mkdir -p "$MYLANG_BUILD_DIR"
fi

if [ ! -d "$MYLANG_BUILD_DIR/llvm/build" ]; then
    mkdir -p "$MYLANG_BUILD_DIR/llvm/build"
fi

cd "$MYLANG_BUILD_DIR" || { echo "Error: Could not change to the build directory."; exit 1; }

# LLVM Archive URL and Destination
LLVM_ARCHIVE_URL="https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.1/llvm-project-17.0.1.src.tar.xz"
LLVM_ARCHIVE_DEST="./llvm.tar.xz"

echo "Installing LLVM...."

# Download LLVM archive
curl -L "$LLVM_ARCHIVE_URL" -o "$LLVM_ARCHIVE_DEST"

# Extract LLVM archive to the correct path
tar -xf "$LLVM_ARCHIVE_DEST" -C "./llvm" --strip-components=1

cd "./llvm/build" || { echo "Error: Could not change to the LLVM build directory."; exit 1; }

# Configure LLVM using CMake with Ninja as the generator
cmake -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DLLVM_ENABLE_PROJECTS=llvm \
  -S "$MYLANG_BUILD_DIR/llvm" \
  -B "$MYLANG_BUILD_DIR/llvm/build" \
  ..

cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug  -DLLVM_ENABLE_PROJECTS="llvm" -DCMAKE_INSTALL_PREFIX="." ../llvm

# Check for errors in CMake configuration
if [ $? -ne 0 ]; then
    echo "Error: Failed to configure LLVM using CMake."
    exit 1
fi

# Build LLVM using Ninja
ninja || { echo "Error: Failed to build LLVM using Ninja."; exit 1; }

# Optionally, install LLVM (adjust the path as needed)
ninja install

echo "LLVM is installed."

# Move back to the main build directory
cd "$MYLANG_BUILD_DIR" || { echo "Error: Could not change back to the main build directory."; exit 1; }


# Set LLVM paths
LLVM_DIR_PATH="$MYLANG_BUILD_DIR/llvm/build/lib/cmake/llvm/LLVM"
LLVM_INC_PATH="$MYLANG_BUILD_DIR/llvm/build/include"
LLVM_LIB_PATH="$MYLANG_BUILD_DIR/llvm/build/lib"

# Step 3: Compile and link with LLVM dynamically
cmake -D LLVM_DIR_PATH="$LLVM_DIR_PATH" -D LLVM_INC_PATH="$LLVM_INC_PATH" -D LLVM_LIB_PATH="$LLVM_LIB_PATH" ..

# Move back to the main build directory
cd "$MYLANG_BUILD_DIR" || { echo "Error: Could not change back to the main build directory."; exit 1; }

# Compile your language
make all || { echo "Error: Failed to compile the language."; exit 1; }

# Assuming the executable is generated in the build directory
MYLANG_COMPILER="./$MYLANG_EXECUTABLE"

# Step 4: Install mylang compiler to /usr/bin/
sudo cp "$MYLANG_EXECUTABLE" "$INSTALL_DIR" || { echo "Error: Failed to copy the executable to $INSTALL_DIR."; exit 1; }


# Step 5: Clean up temporary files
rm -rf ./llvm
rm -f "$LLVM_ARCHIVE_DEST"

echo "Installation complete."



