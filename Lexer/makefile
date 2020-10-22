OBJS  = scanner.o types.o lexeme.o lexer.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g


all : scanner


scanner : $(OBJS)
	@echo Creating scanner executable...
	@gcc $(LOPTS) $(OBJS) -o scanner
	@echo Done.


scanner.o : scanner.c types.h lexeme.h lexer.h
	@echo Compiling scanner...
	@gcc $(OOPTS) scanner.c


types.o : types.c types.h
	@echo Compiling types...
	@gcc $(OOPTS) types.c


lexeme.o : lexeme.c lexeme.h types.h
	@echo Compiling lexeme...
	@gcc $(OOPTS) lexeme.c


lexer.o : lexer.c lexer.h lexeme.h types.h
	@echo Compiling lexer...
	@gcc $(OOPTS) lexer.c


rebuild : all
	@echo Rebuilding scanner...
	@make clean -s
	@make -s


clean :
	@echo Cleaning...
	@rm -rf $(OBJS) scanner
