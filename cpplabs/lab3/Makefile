SRC_DIR = src
BUILD_DIR = build
CXX = g++ -g -std=c++11
CXXFLAGS = -Wall -Wextra

OBJS = $(BUILD_DIR)/BaseFile.o \
       $(BUILD_DIR)/mystring.o \
       $(BUILD_DIR)/matrix.o \
       $(BUILD_DIR)/workerdb.o \
       $(BUILD_DIR)/notification.o \
       $(BUILD_DIR)/notification_alt.o \
       $(BUILD_DIR)/notificationqueue.o \
       $(BUILD_DIR)/boolarray.o

MAIN_NAME = lab3

all: $(BUILD_DIR)/debug.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/BaseFile.o: $(SRC_DIR)/BaseFile.cpp $(SRC_DIR)/BaseFile.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/mystring.o: $(SRC_DIR)/mystring.cpp $(SRC_DIR)/mystring.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/matrix.o: $(SRC_DIR)/matrix.cpp $(SRC_DIR)/matrix.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/workerdb.o: $(SRC_DIR)/workerdb.cpp $(SRC_DIR)/workerdb.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/notification.o: $(SRC_DIR)/notification.cpp $(SRC_DIR)/notification.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/notification_alt.o: $(SRC_DIR)/notification_alt.cpp $(SRC_DIR)/notification_alt.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/notificationqueue.o: $(SRC_DIR)/notificationqueue.cpp $(SRC_DIR)/notificationqueue.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/boolarray.o: $(SRC_DIR)/boolarray.cpp $(SRC_DIR)/boolarray.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/debug.out: $(SRC_DIR)/$(MAIN_NAME).cpp $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/leaks.out: $(SRC_DIR)/$(MAIN_NAME).cpp $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -fsanitize=address

debug: $(BUILD_DIR)/debug.out
	gdb ./$(BUILD_DIR)/debug.out

run: $(BUILD_DIR)/debug.out
	./$(BUILD_DIR)/debug.out

leaks: $(BUILD_DIR)/leaks.out
	./$(BUILD_DIR)/leaks.out
