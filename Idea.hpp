
/*
cmake_minimum_required(VERSION 3.25.1)
project(metal)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG ON)
set(CMAKE_CXX_COMPILE_FEATURES ON)

#set(LLVM_DIR /usr/local/lib/cmake/llvm/LLVM)
# macro for install.sh
set(LLVM_DIR LLVM_DIR_PATH)

# include_directories(include)
include_directories(UnknownLang PRIVATE ${PROJECT_SOURCE_DIR}/include)
set(SOURCES 
src/main.cpp
src/ResMgr.cpp
src/Module.cpp
src/lex/lex.cpp 
src/parser/Ast.cpp 
src/utils/File.cpp
src/utils/Error.cpp
src/parser/util.cpp
src/parser/Parser.cpp  

src/parser/type.cpp  
src/parser/Value.cpp  

src/codegen/AsmGen.cpp  
src/codegen/IR.cpp  
src/codegen/FunctionIR.cpp  
src/codegen/ExprIR.cpp  
src/codegen/StmtIR.cpp  
src/codegen/TypeIR.cpp  
src/codegen/IntrinsicIR.cpp

src/codegen/init.cpp


src/analyzer/Extern.cpp
src/analyzer/Intrinsic.cpp
src/analyzer/v.cpp
src/analyzer/Resolve.cpp
src/analyzer/Sema.cpp
src/analyzer/StmtTy.cpp
src/analyzer/Stmt.cpp
src/analyzer/Expr.cpp

src/analyzer/refn.cpp
)

find_package(LLVM REQUIRED CONFIG)
# find_package(${LLVM_DIR})

include_directories(${LLVM_INCLUDE_PATH})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(metal ${SOURCES})

llvm_map_components_to_libnames(llvm_libs support core irreader codegen)


target_link_libraries(metal
LLVMWindowsManifest LLVMXRay LLVMLibDriver LLVMDlltoolDriver LLVMCoverage LLVMLineEditor LLVMXCoreDisassembler LLVMXCoreCodeGen LLVMXCoreDesc LLVMXCoreInfo LLVMX86TargetMCA LLVMX86Disassembler LLVMX86AsmParser LLVMX86CodeGen LLVMX86Desc LLVMX86Info LLVMWebAssemblyDisassembler LLVMWebAssemblyAsmParser LLVMWebAssemblyCodeGen LLVMWebAssemblyUtils LLVMWebAssemblyDesc LLVMWebAssemblyInfo LLVMVEDisassembler LLVMVEAsmParser LLVMVECodeGen LLVMVEDesc LLVMVEInfo LLVMSystemZDisassembler LLVMSystemZAsmParser LLVMSystemZCodeGen LLVMSystemZDesc LLVMSystemZInfo LLVMSparcDisassembler LLVMSparcAsmParser LLVMSparcCodeGen LLVMSparcDesc LLVMSparcInfo LLVMRISCVTargetMCA LLVMRISCVDisassembler LLVMRISCVAsmParser LLVMRISCVCodeGen LLVMRISCVDesc LLVMRISCVInfo LLVMPowerPCDisassembler LLVMPowerPCAsmParser LLVMPowerPCCodeGen LLVMPowerPCDesc LLVMPowerPCInfo LLVMNVPTXCodeGen LLVMNVPTXDesc LLVMNVPTXInfo LLVMMSP430Disassembler LLVMMSP430AsmParser LLVMMSP430CodeGen LLVMMSP430Desc LLVMMSP430Info LLVMMipsDisassembler LLVMMipsAsmParser LLVMMipsCodeGen LLVMMipsDesc LLVMMipsInfo LLVMLoongArchDisassembler LLVMLoongArchAsmParser LLVMLoongArchCodeGen LLVMLoongArchDesc LLVMLoongArchInfo LLVMLanaiDisassembler LLVMLanaiCodeGen LLVMLanaiAsmParser LLVMLanaiDesc LLVMLanaiInfo LLVMHexagonDisassembler LLVMHexagonCodeGen LLVMHexagonAsmParser LLVMHexagonDesc LLVMHexagonInfo LLVMBPFDisassembler LLVMBPFAsmParser LLVMBPFCodeGen LLVMBPFDesc LLVMBPFInfo LLVMAVRDisassembler LLVMAVRAsmParser LLVMAVRCodeGen LLVMAVRDesc LLVMAVRInfo LLVMARMDisassembler LLVMARMAsmParser LLVMARMCodeGen LLVMARMDesc LLVMARMUtils LLVMARMInfo LLVMAMDGPUTargetMCA LLVMAMDGPUDisassembler LLVMAMDGPUAsmParser LLVMAMDGPUCodeGen LLVMAMDGPUDesc LLVMAMDGPUUtils LLVMAMDGPUInfo LLVMAArch64Disassembler LLVMAArch64AsmParser LLVMAArch64CodeGen LLVMAArch64Desc LLVMAArch64Utils LLVMAArch64Info LLVMOrcDebugging LLVMOrcJIT LLVMWindowsDriver LLVMMCJIT LLVMJITLink LLVMInterpreter LLVMExecutionEngine LLVMRuntimeDyld LLVMOrcTargetProcess LLVMOrcShared LLVMDWP LLVMDebugInfoLogicalView LLVMDebugInfoGSYM LLVMOption LLVMObjectYAML LLVMObjCopy LLVMMCA LLVMMCDisassembler LLVMLTO LLVMPasses LLVMCFGuard LLVMCoroutines LLVMipo LLVMVectorize LLVMLinker LLVMInstrumentation LLVMFrontendOpenMP LLVMFrontendOpenACC LLVMFrontendHLSL LLVMExtensions LLVMDWARFLinkerParallel LLVMDWARFLinker LLVMGlobalISel LLVMMIRParser LLVMAsmPrinter LLVMSelectionDAG LLVMCodeGen LLVMTarget LLVMObjCARCOpts LLVMCodeGenTypes LLVMIRPrinter LLVMInterfaceStub LLVMFileCheck LLVMFuzzMutate LLVMScalarOpts LLVMInstCombine LLVMAggressiveInstCombine LLVMTransformUtils LLVMBitWriter LLVMAnalysis LLVMProfileData LLVMSymbolize LLVMDebugInfoBTF LLVMDebugInfoPDB LLVMDebugInfoMSF LLVMDebugInfoDWARF LLVMObject LLVMTextAPI LLVMMCParser LLVMIRReader LLVMAsmParser LLVMMC LLVMDebugInfoCodeView LLVMBitReader LLVMFuzzerCLI LLVMCore LLVMRemarks LLVMBitstreamReader LLVMBinaryFormat LLVMTargetParser LLVMTableGen LLVMSupport LLVMDemangle
)


# add_executable(metal "${PROJECT_SOURCE_DIR}/src/main.cpp" ${SRCS} ${INCS})

# target_include_directories(mta PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

*/



