
add_executable(simple_calculator simple_calculator.cpp)

target_link_libraries(simple_calculator PRIVATE cppexample_shared)

install(TARGETS simple_calculator
    EXPORT simple_calculator-targets
    RUNTIME DESTINATION bin
)
