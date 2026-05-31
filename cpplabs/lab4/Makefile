SRC_DIR = src
BUILD_DIR = build
CXX = g++ -g

OBJS = $(BUILD_DIR)/circle.o \
       $(BUILD_DIR)/lab4.o

MAIN_NAME = lab4

all: $(BUILD_DIR)/debug.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/circle.o: $(SRC_DIR)/circle.cpp $(SRC_DIR)/circle.hpp | $(BUILD_DIR)
	$(CXX) -c -o $@ $<

$(BUILD_DIR)/lab4.o: $(SRC_DIR)/lab4.cpp $(SRC_DIR)/circle.hpp | $(BUILD_DIR)
	$(CXX) -c -o $@ $<

$(BUILD_DIR)/debug.out: $(OBJS) | $(BUILD_DIR)
	$(CXX) -o $@ $^

$(BUILD_DIR)/leaks.out: $(OBJS) | $(BUILD_DIR)
	$(CXX) -o $@ $^ -fsanitize=address

debug: $(BUILD_DIR)/debug.out
	gdb ./$(BUILD_DIR)/debug.out

run: $(BUILD_DIR)/debug.out
	./$(BUILD_DIR)/debug.out

leaks: $(BUILD_DIR)/leaks.out
	./$(BUILD_DIR)/leaks.out

clean:
	rm -rf $(BUILD_DIR)
