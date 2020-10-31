CC 			 = gcc
SRCDIR 		 = src
HEADERDIR 	 = header
OBJDIR 		 = obj
LEXERPATH 	 = ../lexer
TESTDIR 	 = testing
EXPECTEDPATH = $(TESTDIR)/expected
ACTUALPATH 	 = $(TESTDIR)/actual
OBJS  	  	 = $(OBJDIR)/recognizer.o $(OBJDIR)/parser.o $(OBJDIR)/types.o $(OBJDIR)/lexeme.o $(OBJDIR)/lexer.o
OOPTS 		 = -Wall -Wextra -g -c
LOPTS 		 = -Wall -Wextra -g


all : recognizer


recognizer : $(OBJS)
	@echo Creating recognizer executable...
	@$(CC) $(LOPTS) $(OBJDIR)/* -o recognizer
	@echo Done.


$(OBJDIR)/recognizer.o : $(SRCDIR)/recognizer.c $(LEXERPATH)/$(HEADERDIR)/types.h $(LEXERPATH)/$(HEADERDIR)/lexeme.h $(LEXERPATH)/$(HEADERDIR)/lexer.h
	@echo Compiling recognizer...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/recognizer.c -o $@


$(OBJDIR)/types.o : $(LEXERPATH)/$(SRCDIR)/types.c $(LEXERPATH)/$(HEADERDIR)/types.h
	@echo Compiling types...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(LEXERPATH)/$(SRCDIR)/types.c -o $@


$(OBJDIR)/lexeme.o : $(LEXERPATH)/$(SRCDIR)/lexeme.c $(LEXERPATH)/$(HEADERDIR)/lexeme.h $(LEXERPATH)/$(HEADERDIR)/types.h
	@echo Compiling lexeme...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(LEXERPATH)/$(SRCDIR)/lexeme.c -o $@


$(OBJDIR)/lexer.o : $(LEXERPATH)/$(SRCDIR)/lexer.c $(LEXERPATH)/$(HEADERDIR)/lexer.h $(LEXERPATH)/$(HEADERDIR)/lexeme.h $(LEXERPATH)/$(HEADERDIR)/types.h
	@echo Compiling lexer...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(LEXERPATH)/$(SRCDIR)/lexer.c -o $@


$(OBJDIR)/parser.o : $(SRCDIR)/parser.c $(LEXERPATH)/$(HEADERDIR)/lexer.h $(LEXERPATH)/$(HEADERDIR)/lexeme.h $(LEXERPATH)/$(HEADERDIR)/types.h
	@echo Compiling parser...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/parser.c -o $@


test-bad-filename : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out


test-variables : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-class : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out

test-variables-bad-0 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-1 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-2 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-3 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-4 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-5 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-0 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-1 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-2 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-3 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-4 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-5 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-6 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-7 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-8 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-9 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-10 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-class-bad-0 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-class-bad-1 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-class-bad-2 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-0 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-1 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-2 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-3 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-4 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-5 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-0 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-1 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-2 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-3 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-4 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-5 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-6 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-7 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-8 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-9 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-10 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-11 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-12 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-13 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-14 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-15 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-16 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-17 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-18 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-19 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-20 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-21 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-22 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-23 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-0 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-1 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-2 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-3 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-4 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-5 : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-all : recognizer
	@echo Testing $@...
	@make test-variables -s
	@make test-functions -s
	@make test-class -s
	@make test-conditionals -s
	@make test-loops -s
	@make test-arrays -s
	@make test-variables-bad-0 -s
	@make test-variables-bad-1 -s
	@make test-variables-bad-2 -s
	@make test-variables-bad-3 -s
	@make test-variables-bad-4 -s
	@make test-variables-bad-5 -s
	@make test-functions-bad-0 -s
	@make test-functions-bad-1 -s
	@make test-functions-bad-2 -s
	@make test-functions-bad-3 -s
	@make test-functions-bad-4 -s
	@make test-functions-bad-5 -s
	@make test-functions-bad-6 -s
	@make test-functions-bad-7 -s
	@make test-functions-bad-8 -s
	@make test-functions-bad-9 -s
	@make test-functions-bad-10 -s
	@make test-class-bad-0 -s
	@make test-class-bad-1 -s
	@make test-class-bad-2 -s
	@make test-conditionals-bad-0 -s
	@make test-conditionals-bad-1 -s
	@make test-conditionals-bad-2 -s
	@make test-conditionals-bad-3 -s
	@make test-conditionals-bad-4 -s
	@make test-conditionals-bad-5 -s
	@make test-loops-bad-0 -s
	@make test-loops-bad-1 -s
	@make test-loops-bad-2 -s
	@make test-loops-bad-3 -s
	@make test-loops-bad-4 -s
	@make test-loops-bad-5 -s
	@make test-loops-bad-6 -s
	@make test-loops-bad-7 -s
	@make test-loops-bad-8 -s
	@make test-loops-bad-9 -s
	@make test-loops-bad-10 -s
	@make test-loops-bad-11 -s
	@make test-loops-bad-12 -s
	@make test-loops-bad-13 -s
	@make test-loops-bad-14 -s
	@make test-loops-bad-15 -s
	@make test-loops-bad-16 -s
	@make test-loops-bad-17 -s
	@make test-loops-bad-18 -s
	@make test-loops-bad-19 -s
	@make test-loops-bad-20 -s
	@make test-loops-bad-21 -s
	@make test-loops-bad-22 -s
	@make test-loops-bad-23 -s
	@make test-arrays-bad-0 -s
	@make test-arrays-bad-1 -s
	@make test-arrays-bad-2 -s
	@make test-arrays-bad-3 -s
	@make test-arrays-bad-4 -s
	@make test-arrays-bad-5 -s


rebuild : all
	@echo Rebuilding recognizer...
	@make clean -s
	@make -s


clean :
	@echo Cleaning...
	@rm -rf $(OBJDIR) $(ACTUALPATH) recognizer
