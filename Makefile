##
# Tiger compiler
#
# @file
# @version 0.1

BIN = cs8803_bin
RUNTIME = runtime
BUILD = build
SRC = src
ANTLR = java -Xmx500M -cp "/usr/local/lib/antlr-4.9.3-complete.jar:$CLASSPATH" org.antlr.v4.Tool
ANTLR_RUNTIME = /usr/local/include/antlr4-runtime
INCLUDE = \
	-I$(RUNTIME) \
	-I$(SRC) \
	-I$(ANTLR_RUNTIME)
CXXFLAGS = -std=c++17 -g -Wno-attributes -fsanitize=address -lstdc++fs
LDFLAGS = -fsanitize=address -lstdc++fs
LIBANTLR = /usr/local/lib/libantlr4-runtime.a
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
	$(CXX) -o $@ $(OBJECTS) $(GENERATED_OBJECTS) $(LIBANTLR) $(LDFLAGS)
$(OBJECTS): $(BUILD)/%.o: $(SRC)/%.cpp $(GENERATED_HEADERS) $(HEADERS) $(SOURCES)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@
$(GENERATED_FILES): Tiger.g4
	$(ANTLR) -o $(RUNTIME) -Dlanguage=Cpp -visitor $<
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
	@rm -f $(MAIN_OBJECT) $(OBJECTS) $(GENERATED_FILES) $(GENERATED_OBJECTS)
	@rm -f $(BIN)/tigerc

# end
