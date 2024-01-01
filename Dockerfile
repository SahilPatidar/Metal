# Use a base image with the necessary tools (e.g., Ubuntu with curl and g++)
FROM ubuntu:20.04

# Set the working directory
WORKDIR /app

# Install dependencies
RUN apt-get update && \
    apt-get install -y curl g++

# Copy your mylang source code and the installation script
COPY . .

# LLVM Archive URL and Destination
ARG LLVM_ARCHIVE_URL="https://example.com/path/to/llvm/llvm.tar.gz"
ARG LLVM_ARCHIVE_DEST="/tmp/llvm.tar.gz"

# Download and extract LLVM
RUN mkdir -p /tmp/llvm && \
    curl -L $LLVM_ARCHIVE_URL -o $LLVM_ARCHIVE_DEST && \
    tar -xf $LLVM_ARCHIVE_DEST -C /tmp/llvm

# Build your mylang compiler
RUN cd "$MYLANG_SOURCE_DIR" && \
    mkdir -p "$MYLANG_BUILD_DIR" && \
    cd "$MYLANG_BUILD_DIR" && \
    # Replace the following commands with your actual build commands
    # For example, if you are using cmake:
    # cmake ..
    # make
    cmake .. && \
    make

# Compile and link with LLVM dynamically
RUN cd "$MYLANG_BUILD_DIR" && \
    g++ -o "$MYLANG_EXECUTABLE" -I"/tmp/llvm/include" -L"/tmp/llvm/lib" -lLLVMCore -lLLVMCodeGen -lLLVMX86CodeGen "$MYLANG_EXECUTABLE"

# Install mylang compiler to /usr/bin/
RUN cp "$MYLANG_EXECUTABLE" "/usr/bin/"

# Clean up temporary files
RUN rm -rf /tmp/llvm && \
    rm -f $LLVM_ARCHIVE_DEST

# Set the entry point for your container
CMD ["mylangc"]
