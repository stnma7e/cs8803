##
# Tiger compiler
#
# @file
# @version 0.1

BIN = bin
RUNTIME = runtime
BUILD = build
SRC = src
ANTLR_RUNTIME = $(PWD)/vendor/antlr4/runtime/src
ARGPARSE_INC = $(PWD)/vendor/argparse/include
INCLUDE = \
	-I$(RUNTIME) \
	-I$(SRC) \
	-I$(ANTLR_RUNTIME) \
	-I$(ARGPARSE_INC)
CXXFLAGS = -std=c++17 -g -Wno-attributes -fsanitize=address
LDFLAGS = -fsanitize=address
LIBANTLR = $(PWD)/vendor/antlr4/build/runtime/libantlr4-runtime.a
GENERATED_SOURCES = \
	$(RUNTIME)/TigerParser.cpp \
	$(RUNTIME)/TigerLexer.cpp \
	$(RUNTIME)/TigerBaseVisitor.cpp \
	$(RUNTIME)/TigerVisitor.cpp \
	$(RUNTIME)/TigerBaseListener.cpp \
	$(RUNTIME)/TigerListener.cpp
GENERATED_HEADERS = \
	$(RUNTIME)/TigerParser.h \
	$(RUNTIME)/TigerLexer.h \
	$(RUNTIME)/TigerBaseVisitor.h \
	$(RUNTIME)/TigerVisitor.h \
	$(RUNTIME)/TigerBaseListener.h \
	$(RUNTIME)/TigerListener.h
GENERATED_FILES = \
	$(GENERATED_SOURCES) \
	$(GENERATED_HEADERS) \
	$(RUNTIME)/Tiger.tokens \
	$(RUNTIME)/Tiger.interp \
	$(RUNTIME)/TigerLexer.tokens \
	$(RUNTIME)/TigerLexer.interp
GENERATED_OBJECTS = \
	$(BUILD)/TigerParser.o \
	$(BUILD)/TigerLexer.o \
	$(BUILD)/TigerVisitor.o \
	$(BUILD)/TigerBaseVisitor.o \
	$(BUILD)/TigerBaseListener.o \
	$(BUILD)/TigerListener.o
HEADERS = \
	$(SRC)/TigerFileBaseVisitor.h \
	$(SRC)/TokenInfo.h
SOURCES = \
	$(SRC)/tigerc.cpp \
	$(SRC)/TigerFileBaseVisitor.cpp \
	$(SRC)/TokenInfo.cpp
OBJECTS = \
	$(BUILD)/tigerc.o \
	$(BUILD)/TigerFileBaseVisitor.o \
	$(BUILD)/TokenInfo.o

all : dirs $(BIN)/tigerc
$(BIN)/tigerc: $(OBJECTS) $(GENERATED_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(GENERATED_OBJECTS) $(LIBANTLR)
$(OBJECTS): $(BUILD)/%.o: $(SRC)/%.cpp $(GENERATED_HEADERS) $(HEADERS) $(SOURCES)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@
$(GENERATED_FILES): Tiger.g4
	java -Xmx500M -cp "/home/delmerico/cs8803/antlr-4.11.1-complete.jar:$CLASSPATH" org.antlr.v4.Tool -o $(RUNTIME) -Dlanguage=Cpp -visitor $<
$(GENERATED_OBJECTS): $(BUILD)/%.o: $(RUNTIME)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@
dirs: bin build runtime
bin:
	mkdir -p $(BIN)
build:
	mkdir -p $(BUILD)
runtime:
	mkdir -p $(RUNTIME)
.PHONY:
clean:
	@rm -f $(MAIN_OBJECT) $(OBJECTS) $(GENERATED_FILES)
	@rm -f bin/tigerc

# end
