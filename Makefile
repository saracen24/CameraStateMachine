CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -pedantic-errors -std=c++11
LDFLAGS =

TARGET ?= csm
BUILDDIR ?= ./build
SRCDIRS ?= ./src

SRCS := $(shell find $(SRCDIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILDDIR)/%.o)
DEPS := $(OBJS:.o=.d)

INCDIRS := $(shell find $(SRCDIRS) -type d)
INCFLAGS := $(addprefix -I,$(INCDIRS))

CPPFLAGS ?= $(INCFLAGS) -MMD -MP

$(BUILDDIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILDDIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
