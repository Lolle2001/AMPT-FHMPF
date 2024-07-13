CXX = g++
CXXFLAGS = -std=c++17 

OMP_PATH = /opt/homebrew/opt/libomp

# OBJECTS = main/main.cpp
# CMAKE_CXX_COMPILER = -CMAKE_CXX_COMPILER="/opt/homebrew/opt/llvm@13/bin/clang++"
# OPENMP_LIBRARIES = -OPENMP_LIBRARIES="/opt/homebrew/opt/libomp/lib"
# OPENMP_INCLUDES = -OPENMP_INCLUDES="/opt/homebrew/opt/libomp/include"
# CXX_OPENMP_FLAGS = $(CMAKE_CXX_COMPILER) $(OPENMP_INCLUDES) $(CXX_OPENMP_FLAGS)

# SRCDIR = main
# SRC = $(wildcard $(SRCDIR)/main.cpp)
# OBJ = $(SRC:.cpp=.o)

INCDIR = include
BUILDDIR = build

SRCS = $(wildcard $(INCDIR)/*.cpp)
OBJS = $(patsubst $(INCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

TARGET = output

.PHONY: all clean

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -Xpreprocessor -fopenmp -I$(OMP_PATH)/include -L$(OMP_PATH)/lib -lomp $^ -o $@

$(BUILDDIR)/%.o: $(INCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -Xpreprocessor -fopenmp -I$(OMP_PATH)/include -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET) 