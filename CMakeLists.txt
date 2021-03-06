cmake_minimum_required(VERSION 2.8)
project(slam_learn)

set(CMAKE_CXX_STANDARD 14)

# (un)set: cmake -DCVV_DEBUG_MODE=OFF ..
OPTION(CVV_DEBUG_MODE "cvvisual-debug-mode" ON)
if(CVV_DEBUG_MODE MATCHES ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCVVISUAL_DEBUGMODE")
endif()

# (un)set: cmake -CLOUDVIEWER_DEBUG_MODE=OFF ..
OPTION(CLOUDVIEWER_DEBUG_MODE "cloudviewer-debug-mode" ON)
if(CLOUDVIEWER_DEBUG_MODE MATCHES ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCLOUDVIEWER_DEBUG")
endif()

# (un)set: cmake -DDEBUG_MODE=OFF ..
OPTION(DEBUG_MODE "debug-mode" ON)
if(DEBUG_MODE MATCHES ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()



list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Eigen
include_directories("/usr/include/eigen3")
# OpenCV
find_package(OpenCV 3.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# Sophus 
find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})
# G2O
find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIRS})
# Ceres
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS} )
# Boost
find_package(Boost      REQUIRED COMPONENTS system chrono filesystem unit_test_framework program_options)
include_directories(${Boost_INCLUDE_DIR})
# PCL
find_package(PCL REQUIRED COMPONENTS common io visualization)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

set(THIRD_PARTY_LIBS
        ${OpenCV_LIBS}
        ${Sophus_LIBRARIES}
        g2o_core g2o_stuff g2o_types_sba
        ${CERES_LIBRARIES}
        ${Boost_LIBRARIES}
        opencv_cvv
        opencv_xfeatures2d
        ${PCL_LIBRARIES}
        )

include_directories("basic" "tracking" "local_map")
add_executable(slam_learn main.cpp basic/common_include.h basic/Camera.cpp basic/Camera.h basic/MapPoint.cpp basic/MapPoint.h basic/Map.cpp basic/Map.h basic/BA.cpp basic/BA.h SLAM.cpp SLAM.h tracking/VO.cpp tracking/VO.h tracking/Initializer.cpp tracking/Initializer.h basic/KeyFrame.cpp basic/KeyFrame.h basic/Solver2D2D.cpp basic/Solver2D2D.h local_map/LocalMap.cpp local_map/LocalMap.h tracking/Tracker.cpp tracking/Tracker.h basic/Solver3D2D.cpp basic/Solver3D2D.h basic/Matcher.cpp basic/Matcher.h basic/Triangulater.cpp basic/Triangulater.h basic/MapViewer.cpp basic/MapViewer.h basic/Config.cpp basic/Config.h basic/utility.h basic/utility.cpp basic/basic.h basic/basic.cpp basic/ORBextractor.h basic/ORBextractor.cpp)
target_link_libraries(slam_learn ${THIRD_PARTY_LIBS})