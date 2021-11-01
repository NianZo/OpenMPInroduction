set(BINARY PiMonteCarlo)

set(SOURCES PiMonteCarlo.cpp random.cpp)

add_executable(${BINARY}_run ${SOURCES})

#add_library(${BINARY} _lib STATIC ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})

# Link warning flags; not my code, so doesn't abide by my conventions
# target_link_libraries(${BINARY}_run PRIVATE project_warnings)

# Link OpenMP
find_package(OpenMP)
target_link_libraries(${BINARY}_run PUBLIC OpenMP::OpenMP_CXX)