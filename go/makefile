GOCMD=go
GOBUILD=$(GOCMD) build
GORUN=$(GOCMD) run

BINDIR=bin
SRCDIR=src

EXEC=playground

export GOPATH+=:$(PWD)


all: build

build:
	$(GOBUILD) -o $(BINDIR)/$(EXEC) $(SRCDIR)/main.go

run: build
	@./$(BINDIR)/$(EXEC)

clean:
	@rm -rf $(BINDIR)/$(EXEC)
