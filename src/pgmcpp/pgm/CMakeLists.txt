project(pgm CXX)

add_library(${PROJECT_NAME} ${LIB_TYPE}
	main.cpp	
	)
	
install_target(${PROJECT_NAME})
