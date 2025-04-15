LOCALBIN = $(HOME)/.local/bin
CURDIR = $(CWD)
PYSCRIPT = skeleton_setup.py
BIN = cppskel

.PHONY install uninstall doc manpage

$(LOCALBIN):
	@mkdir -p $@

install:
	@chmod +x $(CURDIR)/$(PYSCRIPT)
	@ln -s $(CURDIR)/$(PYSCRIPT) $(LOCALBIN)/$(BIN)
	@echo Installation done! You can now invoke cppskel

uninstall:
	@rm -f $(LOCALBIN)/$(BIN)
	@echo Desintallation done!

doc:
	@echo Not implemented yet!

manpage:
	@echo Not implemented yet!
