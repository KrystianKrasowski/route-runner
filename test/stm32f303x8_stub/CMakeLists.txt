add_library(stm32f303x8 STATIC stm32f3xx_stub.c core_cm4_stub.c core_cm4_stub.h stm32f3xx.h)

target_include_directories(stm32f303x8 PUBLIC "./")