OBJDIR = obj
OBJS  = scanner.o types.o lexeme.o lexer.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g


all : scanner


scanner : $(OBJS)
	@echo Creating scanner executable...
	@gcc $(LOPTS) $(OBJDIR)/* -o scanner
	@echo Done.


scanner.o : scanner.c types.h lexeme.h lexer.h
	@echo Compiling scanner...
	@mkdir -p $(OBJDIR)
	@gcc $(OOPTS) scanner.c -o $(OBJDIR)/$@


types.o : types.c types.h
	@echo Compiling types...
	@mkdir -p $(OBJDIR)
	@gcc $(OOPTS) types.c -o $(OBJDIR)/$@


lexeme.o : lexeme.c lexeme.h types.h
	@echo Compiling lexeme...
	@mkdir -p $(OBJDIR)
	@gcc $(OOPTS) lexeme.c -o $(OBJDIR)/$@


lexer.o : lexer.c lexer.h lexeme.h types.h
	@echo Compiling lexer...
	@mkdir -p $(OBJDIR)
	@gcc $(OOPTS) lexer.c -o $(OBJDIR)/$@


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
