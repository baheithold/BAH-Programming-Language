CC 			 = gcc
SRCDIR 		 = src
HEADERDIR 	 = header
OBJDIR 		 = obj
LEXERPATH 	 = ../lexer
TESTDIR 	 = testing
EXPECTEDPATH = $(TESTDIR)/expected
ACTUALPATH 	 = $(TESTDIR)/actual
OBJS  	  	 = $(OBJDIR)/test-env.o $(OBJDIR)/environment.o $(OBJDIR)/types.o $(OBJDIR)/lexeme.o
OOPTS 		 = -Wall -Wextra -g -c
LOPTS 		 = -Wall -Wextra -g


all : test-env


test-env : $(OBJS)
	@echo Creating test-env executable...
	@$(CC) $(LOPTS) $(OBJDIR)/* -o test-env
	@echo Done.


$(OBJDIR)/test-env.o : $(TESTDIR)/test-env.c $(HEADERDIR)/environment.h $(LEXERPATH)/$(HEADERDIR)/types.h $(LEXERPATH)/$(HEADERDIR)/lexeme.h
	@echo Compiling test-env...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(TESTDIR)/test-env.c -o $@


$(OBJDIR)/types.o : $(LEXERPATH)/$(SRCDIR)/types.c $(LEXERPATH)/$(HEADERDIR)/types.h
	@echo Compiling types...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(LEXERPATH)/$(SRCDIR)/types.c -o $@


$(OBJDIR)/lexeme.o : $(LEXERPATH)/$(SRCDIR)/lexeme.c $(LEXERPATH)/$(HEADERDIR)/lexeme.h $(LEXERPATH)/$(HEADERDIR)/types.h
	@echo Compiling lexeme...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(LEXERPATH)/$(SRCDIR)/lexeme.c -o $@

$(OBJDIR)/environment.o : $(SRCDIR)/environment.c $(HEADERDIR)/environment.h $(LEXERPATH)/$(HEADERDIR)/lexeme.h $(LEXERPATH)/$(HEADERDIR)/types.h
	@echo Compiling environment...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/environment.c -o $@

test : test-env
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./test-env


rebuild : all
	@echo Rebuilding test-env...
	@make clean -s
	@make -s


clean :
	@echo Cleaning...
	@rm -rf $(OBJDIR) $(ACTUALPATH) test-env
