# OS specific definitions (modify for your system)

# macOS or Linux:

CC          = gcc-14
CLINKER     = $(CC)
# OPTFLAGS    = -O3 -fopenmp -Wall -Wextra
OPTFLAGS    = -fopenmp -Wall -Wextra -g
LIBS        = -lm
PRE         = ./

CFLAGS	  = $(OPTFLAGS)

OBJ=o
EXE=.exe # add extensions to executables to simplify .gitignore rules
RM=rm -f

# Build targets

EXES=hello$(EXE)

all: $(EXES)

hello$(EXE): hello.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o hello$(EXE) hello.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)hello$(EXE)

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
