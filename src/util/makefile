CC 			 = gcc
SRCDIR 		 = src
HEADERDIR 	 = header
OBJDIR 		 = obj
TESTDIR 	 = testing
BINDIR 		 = bin
EXPECTEDPATH = $(TESTDIR)/expected
ACTUALPATH 	 = $(TESTDIR)/actual
OBJS  	  	 = $(OBJDIR)/filetester.o $(OBJDIR)/util.o
OOPTS 		 = -Wall -Wextra -g -c
LOPTS 		 = -Wall -Wextra -g


all : $(BINDIR)/filetester


$(BINDIR)/filetester : $(OBJS)
	@echo Creating filetester executable...
	@mkdir -p $(BINDIR)
	@$(CC) $(LOPTS) $(OBJDIR)/* -o $(BINDIR)/filetester
	@echo Done.


$(OBJDIR)/filetester.o : $(TESTDIR)/filetester.c $(HEADERDIR)/util.h
	@echo Compiling filetester...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(TESTDIR)/filetester.c -o $@


$(OBJDIR)/util.o : $(SRCDIR)/util.c $(HEADERDIR)/util.h
	@echo Compiling util...
	@mkdir -p $(OBJDIR)
	@$(CC) $(OOPTS) $(SRCDIR)/util.c -o $@


test-filetester : $(BINDIR)/filetester
	@mkdir -p $(ACTUALPATH);
	@echo Testing $@-0...
	@$(BINDIR)/filetester test.bah > $(ACTUALPATH)/filetester-0.out
	@diff ./$(EXPECTEDPATH)/filetester-0.out ./$(ACTUALPATH)/filetester-0.out
	@echo Testing $@-1...
	@$(BINDIR)/filetester t.bah > $(ACTUALPATH)/filetester-1.out
	@diff ./$(EXPECTEDPATH)/filetester-1.out ./$(ACTUALPATH)/filetester-1.out
	@echo Testing $@-2...
	@$(BINDIR)/filetester .bah > $(ACTUALPATH)/filetester-2.out
	@diff ./$(EXPECTEDPATH)/filetester-2.out ./$(ACTUALPATH)/filetester-2.out
	@echo Testing $@-3...
	@$(BINDIR)/filetester tbah > $(ACTUALPATH)/filetester-3.out
	@diff ./$(EXPECTEDPATH)/filetester-3.out ./$(ACTUALPATH)/filetester-3.out
	@echo Testing $@-4...
	@$(BINDIR)/filetester t.bax > $(ACTUALPATH)/filetester-4.out
	@diff ./$(EXPECTEDPATH)/filetester-4.out ./$(ACTUALPATH)/filetester-4.out
	@echo Testing $@-5...
	@$(BINDIR)/filetester t.bxh > $(ACTUALPATH)/filetester-5.out
	@diff ./$(EXPECTEDPATH)/filetester-5.out ./$(ACTUALPATH)/filetester-5.out
	@echo Testing $@-6...
	@$(BINDIR)/filetester t.xah > $(ACTUALPATH)/filetester-6.out
	@diff ./$(EXPECTEDPATH)/filetester-6.out ./$(ACTUALPATH)/filetester-6.out
	@echo Testing $@-7...
	@$(BINDIR)/filetester t.bahx > $(ACTUALPATH)/filetester-7.out
	@diff ./$(EXPECTEDPATH)/filetester-7.out ./$(ACTUALPATH)/filetester-7.out
	@echo Testing $@-8...
	@$(BINDIR)/filetester t.ba > $(ACTUALPATH)/filetester-8.out
	@diff ./$(EXPECTEDPATH)/filetester-8.out ./$(ACTUALPATH)/filetester-8.out
	@echo Testing $@-9...
	@$(BINDIR)/filetester t.b > $(ACTUALPATH)/filetester-9.out
	@diff ./$(EXPECTEDPATH)/filetester-9.out ./$(ACTUALPATH)/filetester-9.out
	@echo Testing $@-10...
	@$(BINDIR)/filetester t. > $(ACTUALPATH)/filetester-10.out
	@diff ./$(EXPECTEDPATH)/filetester-10.out ./$(ACTUALPATH)/filetester-10.out
	@echo Testing $@-11...
	@$(BINDIR)/filetester t.cpp > $(ACTUALPATH)/filetester-11.out
	@diff ./$(EXPECTEDPATH)/filetester-11.out ./$(ACTUALPATH)/filetester-11.out


rebuild : all
	@echo Rebuilding recognizer...
	@make clean -s
	@make -s


clean :
	@echo Cleaning...
	@rm -rf $(OBJDIR) $(BINDIR) $(ACTUALPATH)
