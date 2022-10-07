CXX = g++
FLAGS = --std=c++17 #-ggdb3 
WFLAGS = -Wall -Werror -Wextra
GCOV = --coverage
LCOV = lcov --no-external -t
OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBS = -lgtest -pthread -lm -lsubunit
	OPEN = xdg-open
	LEAKS = valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(EXETESTFILES)
else
	LIBS = -lgtest -lstdc++ 
	OPEN = open
	LEAKS = CK_FORK=no leaks --atExit -- ./$(EXETESTFILES)
endif

COMMIT = "Final push"
BRANCH = develop

FILES = s21_containers.h s21_containersplus.h
TESTFILES = s21_containers_test.cpp
EXETESTFILES = test
GCOVFILES = gcov_report.info
REPORTDIR = report
REPORTFILES = index.html

.PHONY: all test gcov_report gcov_open clean checks code_check style_check leaks git

# ======================================================================================== #

all: test

test: gcov_report

gcov_report: clean
	@clear
	@$(CXX) $(FLAGS) $(WFLAGS) $(GCOV) $(TESTFILES) $(FILES) $(LIBS) -o $(EXETESTFILES)
	@./$(EXETESTFILES)
	@$(LCOV) "$(EXETESTFILES)" -o $(GCOVFILES) -c -d .
	@genhtml -o $(REPORTDIR) $(GCOVFILES)

gcov_open:
	@$(OPEN) ./$(REPORTDIR)/$(REPORTFILES)

clean:
	@rm -f *.o *.a *.gcno *.gcda *.info *.out *.txt *.h.gch *.log $(EXETESTFILES) 
	@rm -rf ./$(REPORTDIR) *.dSYM
	@clear

leaks: test
	@$(LEAKS)
