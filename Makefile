CC      := c++ -std=c++11
CCFLAGS := -O2 -Wall -Wextra
BUILD_DIR := build
LDFLAGS := -Lbuild
AR      = ar rc
RANLIB  = ranlib

# lex
LEX_DIR := lex
LEX_LIB_SRCS := \
	$(LEX_DIR)/token_loader.cc \
	$(LEX_DIR)/types.cc
LEX_LIB_OBJS := $(patsubst $(LEX_DIR)/%.cc, $(BUILD_DIR)/$(LEX_DIR)/%.o, $(LEX_LIB_SRCS))
LEX_LIB_NAME := elsh_lex
LEX_A := $(BUILD_DIR)/lib$(LEX_LIB_NAME).a

all: lex/lexical_ana.cc $(LEX_A)
		$(CC) $< -I. -o build/lexer $(CCFLAGS) $(LDFLAGS) -l$(LEX_LIB_NAME)

lex_a: $(LEX_A)
$(LEX_A): $(LEX_LIB_OBJS)
		@echo "create $(LEX_A)"
		@$(AR) $@ $(LEX_LIB_OBJS)
		@$(RANLIB) $@

$(BUILD_DIR)/$(LEX_DIR)/%.o: $(LEX_DIR)/%.cc
		@mkdir -p $(BUILD_DIR)/$(LEX_DIR)
		$(CC) -I. -c $< -o $@ $(CCFLAGS)

# test
TEST_DIR := test
TEST_FM_DIR := $(TEST_DIR)/utest_framework
TEST_FM_SRCS := $(wildcard $(TEST_FM_DIR)/*.cc)
TEST_FM_OBJS := $(patsubst $(TEST_FM_DIR)/%.cc, $(BUILD_DIR)/$(TEST_FM_DIR)/%.o, $(TEST_FM_SRCS))
TEST_FM_LIB_NAME := elsh_utest_fm
TEST_FM_A := $(BUILD_DIR)/lib$(TEST_FM_LIB_NAME).a

TEST_LEX_DIR := $(TEST_DIR)/$(LEX_DIR)
TEST_LEX_SRCS :=  $(wildcard $(TEST_LEX_DIR)/*.cc)
TEST_LEX_BINS := $(patsubst $(TEST_LEX_DIR)/%.cc, $(BUILD_DIR)/$(TEST_LEX_DIR)/%, $(TEST_LEX_SRCS))

## test framework
test: test_lex

test_a : $(TEST_FM_A)
$(TEST_FM_A): $(TEST_FM_OBJS)
		@echo "create $(TEST_FM_A)"
		@$(AR) $@ $(TEST_FM_OBJS)
		@$(RANLIB) $@

$(BUILD_DIR)/$(TEST_FM_DIR)/%.o: $(TEST_FM_DIR)/%.cc $(TEST_FM_DIR)/%.h
		@mkdir -p $(BUILD_DIR)/$(TEST_FM_DIR)
		$(CC) -I. -c $< -o $@ $(CCFLAGS)

## test lex
test_lex: $(TEST_LEX_BINS)
$(BUILD_DIR)/$(TEST_LEX_DIR)/%: $(TEST_LEX_DIR)/%.cc $(TEST_FM_A) $(LEX_A)
		@mkdir -p $(BUILD_DIR)/$(TEST_LEX_DIR)
		$(CC) $< -I. -o $@ $(CCFLAGS) $(LDFLAGS) -l$(TEST_FM_LIB_NAME) -l$(LEX_LIB_NAME)

echo:
		@echo "CC = $(CC)"
		@echo "BUILD_DIR = $(BUILD_DIR)"
		@echo "LEX_A = $(LEX_A)"
		@echo "TEST_FM_A = $(TEST_FM_A)"

clean:
		rm -rf build/*

.PHONY: all lex_a test_a test_lex clean echo