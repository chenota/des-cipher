SRCDIR = src
OBJDIR = build

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

des.out: $(OBJDIR)/main.o $(OBJDIR)/des.o $(OBJDIR)/keygen.o $(OBJDIR)/pbox.o $(OBJDIR)/sbox.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -o des.out $<