SRCDIR = src
OBJDIR = build

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

des.out: $(OBJDIR)/des.o $(OBJDIR)/keygen.o $(OBJDIR)/pbox.o $(OBJDIR)/sbox.o
	$(CC) -o des.out $<