JFLAGS = -g
JC = javac

.SUFFIXES: .java .class

# Define the source directory
SRCDIR = .

# Define the output directory for compiled classes
BINDIR = .

# List of Java files to be compiled
CLASSES = MaxHeap.java MinHeap.java MedianHeap.java

default: classes

classes: $(CLASSES:.java=.class)

# Rule for compiling MaxHeap.java
MaxHeap.class: $(SRCDIR)/MaxHeap.java
	$(JC) $(JFLAGS) -d $(BINDIR) $<

# Rule for compiling MinHeap.java
MinHeap.class: $(SRCDIR)/MinHeap.java
	$(JC) $(JFLAGS) -d $(BINDIR) $<

# Rule for compiling MedianHeap.java
MedianHeap.class: $(SRCDIR)/MedianHeap.java
	$(JC) $(JFLAGS) -d $(BINDIR) $<

clean:
	$(RM) $(BINDIR)/*.class