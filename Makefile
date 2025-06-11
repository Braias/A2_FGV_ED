CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc
SRCDIR = src

BST_EXEC = bst_main
AVL_EXEC = avl_main
RBT_EXEC = rbt_main
BST_TEST_EXEC = test_bst
AVL_TEST_EXEC = test_avl
RBT_TEST_EXEC = test_rbt

BST_SOURCES = $(SRCDIR)/main_bst.cpp $(SRCDIR)/bst.cpp $(SRCDIR)/data.cpp $(SRCDIR)/tree_utils.cpp
AVL_SOURCES = $(SRCDIR)/main_avl.cpp $(SRCDIR)/avl.cpp $(SRCDIR)/data.cpp $(SRCDIR)/tree_utils.cpp
RBT_SOURCES = $(SRCDIR)/main_rbt.cpp $(SRCDIR)/rbt.cpp $(SRCDIR)/data.cpp $(SRCDIR)/tree_utils.cpp
BST_TEST_SOURCES = $(SRCDIR)/test_bst.cpp $(SRCDIR)/bst.cpp $(SRCDIR)/tree_utils.cpp
AVL_TEST_SOURCES = $(SRCDIR)/test_avl.cpp $(SRCDIR)/avl.cpp $(SRCDIR)/tree_utils.cpp
RBT_TEST_SOURCES = $(SRCDIR)/test_rbt.cpp $(SRCDIR)/rbt.cpp $(SRCDIR)/tree_utils.cpp

all: $(BST_EXEC) $(AVL_EXEC) $(RBT_EXEC) $(BST_TEST_EXEC) $(AVL_TEST_EXEC) $(RBT_TEST_EXEC)

$(BST_EXEC): $(BST_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(BST_EXEC) $(BST_SOURCES)

$(AVL_EXEC): $(AVL_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(AVL_EXEC) $(AVL_SOURCES)

$(RBT_EXEC): $(RBT_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(RBT_EXEC) $(RBT_SOURCES)

$(BST_TEST_EXEC): $(BST_TEST_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(BST_TEST_EXEC) $(BST_TEST_SOURCES)

$(AVL_TEST_EXEC): $(AVL_TEST_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(AVL_TEST_EXEC) $(AVL_TEST_SOURCES)

$(RBT_TEST_EXEC): $(RBT_TEST_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(RBT_TEST_EXEC) $(RBT_TEST_SOURCES)