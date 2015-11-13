CXX = g++
CXXFLAGS = -g -Wall -std=c++11
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

PROJECT = ns
SRCDIR = src
OBJDIR = obj
SRCS := $(wildcard **/*.cc)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean

all: $(PROJECT)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(PROJECT): $(OBJS)
	$(CXX) $(OBJS) $(LDLIBS) -o $(PROJECT)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean:
	rm -f -r $(OBJDIR) $(PROJECT)

run: $(PROJECT)
	./$(PROJECT)
