SRC_DIR = src
BUILD_DIR = build
CXX = g++ -g
OBJS = $(BUILD_DIR)/BaseFile.o $(BUILD_DIR)/mystring.o
MAIN_NAME = lab2
TEST_DIR = tests

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) -c -o $@ $<

$(BUILD_DIR)/debug.out: $(SRC_DIR)/$(MAIN_NAME).cpp $(OBJS)
	$(CXX) -o $@ $^

$(BUILD_DIR)/leaks.out: $(SRC_DIR)/$(MAIN_NAME).cpp $(OBJS)
	$(CXX) -o $@ $^ -fsanitize=address

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/test_%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/test_basefile: $(BUILD_DIR)/test_basefile.o $(OBJS)
	$(CXX) -o $@ $^

$(BUILD_DIR)/test_base32file: $(BUILD_DIR)/test_base32file.o $(OBJS)
	$(CXX) -o $@ $^

$(BUILD_DIR)/test_rlefile: $(BUILD_DIR)/test_rlefile.o $(OBJS)
	$(CXX) -o $@ $^

$(BUILD_DIR)/test_composition: $(BUILD_DIR)/test_composition.o $(OBJS)
	$(CXX) -o $@ $^

$(BUILD_DIR)/test_base32file2: $(BUILD_DIR)/test_base32file2.o $(OBJS)
	$(CXX) -o $@ $^

$(BUILD_DIR)/test_rlefile2: $(BUILD_DIR)/test_rlefile2.o $(OBJS)
	$(CXX) -o $@ $^

test: $(BUILD_DIR)/test_basefile $(BUILD_DIR)/test_base32file $(BUILD_DIR)/test_rlefile $(BUILD_DIR)/test_composition $(BUILD_DIR)/test_rlefile2 ./$(BUILD_DIR)/test_base32file2
	./$(BUILD_DIR)/test_basefile
	./$(BUILD_DIR)/test_base32file
	./$(BUILD_DIR)/test_rlefile
	./$(BUILD_DIR)/test_composition
	./$(BUILD_DIR)/test_base32file2
	./$(BUILD_DIR)/test_rlefile2



debug: $(BUILD_DIR)/debug.out
	gdb ./$(BUILD_DIR)/debug.out

run: $(BUILD_DIR)/debug.out
	./$(BUILD_DIR)/debug.out
	
leaks: $(BUILD_DIR)/leaks.out
	./$(BUILD_DIR)/leaks.out

