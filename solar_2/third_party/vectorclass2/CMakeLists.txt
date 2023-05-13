add_library(VectorClass2 INTERFACE)
target_include_directories(VectorClass2 INTERFACE ".")
target_compile_definitions(VectorClass2 INTERFACE VCL_NAMESPACE=vcl)