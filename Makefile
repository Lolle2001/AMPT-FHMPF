CXX = g++
CXXFLAGS = -std=c++17 -fopenmp

INCDIR = include
BUILDDIR = build

SRCS = $(wildcard $(INCDIR)/*.cpp)
OBJS = $(patsubst $(INCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
# MAIN = $(INCDIR)/main.cpp

TARGET = output

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) #$(MAIN)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(BUILDDIR)/%.o: $(INCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)
