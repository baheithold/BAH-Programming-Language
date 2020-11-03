CC 			 = gcc
SRCDIR 		 = src
HEADERDIR 	 = header
OBJDIR 		 = obj
TESTDIR 	 = testing
BINDIR 		 = bin
EXPECTEDPATH = $(TESTDIR)/expected
ACTUALPATH 	 = $(TESTDIR)/actual
OBJS  	  	 = $(OBJDIR)/scanner.o $(OBJDIR)/types.o $(OBJDIR)/lexeme.o $(OBJDIR)/lexer.o
OOPTS 		 = -Wall -Wextra -g -c
LOPTS 		 = -Wall -Wextra -g


all : $(BINDIR)/scanner


$(BINDIR)/scanner : $(OBJS)
	@echo Creating scanner executable...
	@mkdir -p $(BINDIR)
	@$(CC) $(LOPTS) $(OBJDIR)/* -o $(BINDIR)/scanner
	@echo Done.


$(OBJDIR)/scanner.o : $(SRCDIR)/scanner.c $(HEADERDIR)/types.h $(HEADERDIR)/lexeme.h $(HEADERDIR)/lexer.h
	@echo Compiling scanner...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/scanner.c -o $@


$(OBJDIR)/types.o : $(SRCDIR)/types.c $(HEADERDIR)/types.h
	@echo Compiling types...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/types.c -o $@


$(OBJDIR)/lexeme.o : $(SRCDIR)/lexeme.c $(HEADERDIR)/lexeme.h $(HEADERDIR)/types.h
	@echo Compiling lexeme...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/lexeme.c -o $@


$(OBJDIR)/lexer.o : $(SRCDIR)/lexer.c $(HEADERDIR)/lexer.h $(HEADERDIR)/lexeme.h $(HEADERDIR)/types.h
	@echo Compiling lexer...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/lexer.c -o $@


test-variables : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-functions : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-conditionals : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-loops : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-lambda : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-class : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-operators : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-keywords : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-punctuation : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-types : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-import : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-types-real-error : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-types-string-error : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out
	@diff $(EXPECTEDPATH)/$@.out $(ACTUALPATH)/$@.out


test-full : $(BINDIR)/scanner
	@echo Running $@...
	@mkdir -p $(ACTUALPATH)
	@$(BINDIR)/scanner ./$(TESTDIR)/$@.bah > $(ACTUALPATH)/$@.out


test-all : $(BINDIR)/scanner
	@make test-variables -s
	@make test-functions -s
	@make test-conditionals -s
	@make test-loops -s
	@make test-lambda -s
	@make test-class -s
	@make test-operators -s
	@make test-keywords -s
	@make test-punctuation -s
	@make test-types -s
	@make test-import -s
	@make test-types-real-error -s
	@make test-types-string-error -s


rebuild : all
	@echo Rebuilding scanner...
	@make clean -s
	@make -s


clean :
	@echo Cleaning...
	@rm -rf $(OBJDIR) $(BINDIR) $(ACTUALPATH)
