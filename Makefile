# Auto-detect compiler for cross-platform support (macOS uses clang++ by default)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
CXX := clang++
else
CXX := g++
endif
CXXFLAGS := -std=c++11 -Wall -Wextra -O2
INCLUDES := -I include
LDFLAGS  :=
TARGET   := DigitalPet
SRCDIR   := src
OBJDIR   := obj

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

.PHONY: all clean run

all: $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TARGET).exe
