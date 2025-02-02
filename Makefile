SRCDIR = src
OBJDIR = build

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -Werror -c -o $@ $<

des.out: $(OBJDIR)/main.o $(OBJDIR)/des.o $(OBJDIR)/keygen.o $(OBJDIR)/pbox.o $(OBJDIR)/sbox.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -Werror -o des.out $<