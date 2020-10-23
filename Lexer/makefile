SRCDIR 	  = src
HEADERDIR = header
OBJDIR 	  = obj
OBJS  	  = scanner.o types.o lexeme.o lexer.o
OOPTS 	  = -Wall -Wextra -g -c
LOPTS 	  = -Wall -Wextra -g


all : scanner


scanner : $(OBJS)
	@echo Creating scanner executable...
	@gcc $(LOPTS) $(OBJDIR)/* -o scanner
	@echo Done.


scanner.o : $(SRCDIR)/scanner.c $(HEADERDIR)/types.h $(HEADERDIR)/lexeme.h $(HEADERDIR)/lexer.h
	@echo Compiling scanner...
	@mkdir -p $(OBJDIR)
	@gcc $(OOPTS) $(SRCDIR)/scanner.c -o $(OBJDIR)/$@


types.o : $(SRCDIR)/types.c $(HEADERDIR)/types.h
	@echo Compiling types...
	@mkdir -p $(OBJDIR)
	@gcc $(OOPTS) $(SRCDIR)/types.c -o $(OBJDIR)/$@


lexeme.o : $(SRCDIR)/lexeme.c $(HEADERDIR)/lexeme.h $(HEADERDIR)/types.h
	@echo Compiling lexeme...
	@mkdir -p $(OBJDIR)
	@gcc $(OOPTS) $(SRCDIR)/lexeme.c -o $(OBJDIR)/$@


lexer.o : $(SRCDIR)/lexer.c $(HEADERDIR)/lexer.h $(HEADERDIR)/lexeme.h $(HEADERDIR)/types.h
	@echo Compiling lexer...
	@mkdir -p $(OBJDIR)
	@gcc $(OOPTS) $(SRCDIR)/lexer.c -o $(OBJDIR)/$@


test0 : scanner
	@echo Running test0...
	@./scanner ./testing/test-0.bah


rebuild : all
	@echo Rebuilding scanner...
	@make clean -s
	@make -s


clean :
	@echo Cleaning...
	@rm -rf $(OBJDIR) scanner
