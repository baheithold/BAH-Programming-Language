CC 			 = gcc
SRCDIR 		 = src
HEADERDIR 	 = header
OBJDIR 		 = obj
LEXERPATH 	 = ../Lexer
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


test : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer test.bah > $(ACTUALPATH)/$@.out


test-bad-filename : recognizer
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@./recognizer ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out


rebuild : all
	@echo Rebuilding recognizer...
	@make clean -s
	@make -s


clean :
	@echo Cleaning...
	@rm -rf $(OBJDIR) $(ACTUALPATH) recognizer
