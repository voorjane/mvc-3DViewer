CC 					= 	g++
OPEN				=	open
CFLAGS 				= 	-Wall -Werror -Wextra -std=c++17
INST_DIR			=	3DViewer
TEST_FLAGS 			= 	-lgtest_main -lpthread -lgtest --coverage
TEST_FILES 			= 	$(wildcard Tests/*.cc)
MODEL_FILES 		= 	$(wildcard Model/*.cc)
CONTROLLER_FILES 	= 	$(wildcard Controller/*.cc)

all: clean install

install: uninstall
	@mkdir $(INST_DIR)
	@cd $(INST_DIR) && cmake .. && make
	./$(INST_DIR)/3DViewer

uninstall:
	rm -rf $(INST_DIR)

clean:
	 @rm -rf test *.a report* *.o *.cfg *.gc* *.info *.tar *.dSYM

dvi:
	open documentation.md

dist:
	 @tar -cvzf dist.tar.gz *

tests:
	@$(CC) $(CFLAGS) Tests/*.cc Model/objparser.cc -o test $(TEST_FLAGS)
	@./test
	@make clean

launch:
	./$(INST_DIR)/3DViewer

clang:
	cp ../.clang-format .
	clang-format -n Controller/*.cc Controller/*.h Model/*.cc Model/*.h Tests/*.cc View/*.cc View/*.h
	rm .clang-format

valgrind:
	@make tests
	@valgrind --leak-check=full --leak-resolution=med -s ./test
	@make clean

 .PHONY: all install uninstall clean dvi dist tests launch style valgrind