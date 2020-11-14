CC 			 = gcc
SRCDIR 		 = src
HEADERDIR 	 = header
OBJDIR 		 = obj
LEXERPATH 	 = ../lexer
PARSERPATH 	 = ../parser
TESTDIR 	 = testing
BINDIR 		 = bin
EXPECTEDPATH = $(TESTDIR)/expected
ACTUALPATH 	 = $(TESTDIR)/actual
OBJS  	  	 = $(OBJDIR)/pp.o $(OBJDIR)/prettyPrinter.o $(OBJDIR)/parser.o $(OBJDIR)/types.o $(OBJDIR)/lexeme.o $(OBJDIR)/lexer.o
OOPTS 		 = -Wall -Wextra -g -c
LOPTS 		 = -Wall -Wextra -g


all : $(BINDIR)/pp


$(BINDIR)/pp : $(OBJS)
	@echo Creating pp executable...
	@mkdir -p $(BINDIR)
	@$(CC) $(LOPTS) $(OBJDIR)/* -o $(BINDIR)/pp
	@echo Done.


$(OBJDIR)/pp.o : $(SRCDIR)/pp.c $(HEADERDIR)/prettyPrinter.h $(LEXERPATH)/$(HEADERDIR)/types.h $(LEXERPATH)/$(HEADERDIR)/lexeme.h $(LEXERPATH)/$(HEADERDIR)/lexer.h $(PARSERPATH)/$(HEADERDIR)/parser.h
	@echo Compiling pp...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/pp.c -o $@


$(OBJDIR)/prettyPrinter.o : $(SRCDIR)/prettyPrinter.c $(HEADERDIR)/prettyPrinter.h $(LEXERPATH)/$(HEADERDIR)/types.h $(LEXERPATH)/$(HEADERDIR)/lexeme.h $(LEXERPATH)/$(HEADERDIR)/lexer.h $(PARSERPATH)/$(HEADERDIR)/parser.h
	@echo Compiling prettyPrinter...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/prettyPrinter.c -o $@


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


$(OBJDIR)/parser.o : $(PARSERPATH)/$(SRCDIR)/parser.c $(LEXERPATH)/$(HEADERDIR)/lexer.h $(LEXERPATH)/$(HEADERDIR)/lexeme.h $(LEXERPATH)/$(HEADERDIR)/types.h
	@echo Compiling parser...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(PARSERPATH)/$(SRCDIR)/parser.c -o $@


test-bad-filename : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out


test-variables : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-class : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-imports : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-0 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-1 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-2 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-3 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-4 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-variables-bad-5 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-0 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-1 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-2 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-3 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-4 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-5 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-6 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-7 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-8 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-9 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-functions-bad-10 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-class-bad-0 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-class-bad-1 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-class-bad-2 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-0 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-1 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-2 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-3 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-4 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-conditionals-bad-5 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-0 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-1 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-2 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-3 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-4 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-5 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-6 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-7 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-8 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-9 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-10 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-11 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-12 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-13 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-14 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-15 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-16 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-17 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-18 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-19 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-20 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-21 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-22 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-loops-bad-23 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-0 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-1 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-2 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-3 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-4 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-arrays-bad-5 : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-full : $(BINDIR)/pp
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/pp ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff ./$(EXPECTEDPATH)/$@.out ./$(ACTUALPATH)/$@.out


test-all : $(BINDIR)/pp
	@echo Testing $@...
	@make test-bad-filename
	@make test-variables -s
	@make test-functions -s
	@make test-class -s
	@make test-conditionals -s
	@make test-loops -s
	@make test-arrays -s
	@make test-imports -s
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
	@make test-full -s


rebuild : all
	@echo Rebuilding pp...
	@make clean -s
	@make -s


clean :
	@echo Cleaning...
	@rm -rf $(OBJDIR) $(BINDIR) $(ACTUALPATH)
