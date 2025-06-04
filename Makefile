# Diretórios
SRC_DIR = src
BIN_DIR = bin

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
HDRS = $(wildcard $(SRC_DIR)/*.h)

# Executáveis
TARGETS = main_avl main_bst main_rbt test_avl test_bst test_rbt

# Geração dos binários
all: $(TARGETS)

main_avl: $(SRC_DIR)/main_avl.cpp $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_DIR)/main_avl.cpp $(filter-out $(SRC_DIR)/main_bst.cpp $(SRC_DIR)/main_rbt.cpp $(SRC_DIR)/test_%.cpp, $(SRCS))

main_bst: $(SRC_DIR)/main_bst.cpp $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_DIR)/main_bst.cpp $(filter-out $(SRC_DIR)/main_avl.cpp $(SRC_DIR)/main_rbt.cpp $(SRC_DIR)/test_%.cpp, $(SRCS))

main_rbt: $(SRC_DIR)/main_rbt.cpp $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_DIR)/main_rbt.cpp $(filter-out $(SRC_DIR)/main_avl.cpp $(SRC_DIR)/main_bst.cpp $(SRC_DIR)/test_%.cpp, $(SRCS))

test_avl: $(SRC_DIR)/test_avl.cpp $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_DIR)/test_avl.cpp $(filter-out $(SRC_DIR)/main_%.cpp $(SRC_DIR)/test_bst.cpp $(SRC_DIR)/test_rbt.cpp, $(SRCS))

test_bst: $(SRC_DIR)/test_bst.cpp $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_DIR)/test_bst.cpp $(filter-out $(SRC_DIR)/main_%.cpp $(SRC_DIR)/test_avl.cpp $(SRC_DIR)/test_rbt.cpp, $(SRCS))

test_rbt: $(SRC_DIR)/test_rbt.cpp $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_DIR)/test_rbt.cpp $(filter-out $(SRC_DIR)/main_%.cpp $(SRC_DIR)/test_avl.cpp $(SRC_DIR)/test_bst.cpp, $(SRCS))

# Limpeza dos binários
clean:
	rm -f $(TARGETS)
