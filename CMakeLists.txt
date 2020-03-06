# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/12 12:28:11 by jpinyot           #+#    #+#              #
#    Updated: 2020/03/04 11:32:19 by jpinyot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)

# set the project name
project(DSLR)

# set definitions
add_definitions(-O2)

# add the executable
# DSLR
add_executable(	DSLR
				srcs/logisticRegression.cpp
				includes/plot.cpp
				includes/csvReader.cpp)
			set(HEADER_FILES	DSLR
								srcs/logisticRegression.h
								includes/plot.h
								includes/csvReader.h)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries (DSLR Eigen3::Eigen)


# dependencies for Python.h, used for ploting
find_package(Python2 COMPONENTS Development NumPy)
target_include_directories(DSLR PRIVATE ${Python2_INCLUDE_DIRS} ${Python2_NumPy_INCLUDE_DIRS})
target_link_libraries(DSLR Python2::Python Python2::NumPy)
