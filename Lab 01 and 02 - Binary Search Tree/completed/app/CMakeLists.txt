add_executable(bst_app
    BSTStartProject.cpp
)

configure_file(csList.txt csList.txt COPYONLY)
configure_file(csListMed.txt csListMed.txt COPYONLY)
configure_file(csListSmall.txt csListSmall.txt COPYONLY)

# Use C++17
target_compile_features(bst_app PRIVATE cxx_std_17)

# Link to the main library
target_link_libraries(bst_app PRIVATE bst)
