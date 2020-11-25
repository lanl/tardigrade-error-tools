import os


CMAKE_CXX_STANDARD = 11
ROOT_DIRECTORY = os.path.abspath(os.path.join("..", ".."))
PROJECT_CMAKE_FILE = os.path.join(ROOT_DIRECTORY, "CMakeLists.txt")
CPP_SOURCE_DIRECTORY = os.path.join(ROOT_DIRECTORY, "src", "cpp")
CPP_BUILD_DIRECTORY = os.path.join(ROOT_DIRECTORY, "build")
