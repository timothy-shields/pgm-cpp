project(pgm CXX)

add_library(${PROJECT_NAME} ${LIB_TYPE}
	main.cpp

	log.h
	less_pair_first.h
	table_factor.h
	)
	
install_target(${PROJECT_NAME})
