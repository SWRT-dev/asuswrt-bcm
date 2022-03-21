EXEC = 11N_UDPserver
OBJS = 11N_UDPserver.o

all: $(EXEC)

$(EXEC): $(OBJS)
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

install:
	@install -D $(EXEC) $(INSTALLDIR)/usr/sbin/$(EXEC)

clean:
	-rm -f $(EXEC) *.elf *.o

%.o: %.c
	@echo " [$(EXEC)] CC $@"
	@$(CC) $(CFLAGS) -o $@ -c $<

