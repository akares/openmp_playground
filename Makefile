# OS specific definitions (modify for your system)

# macOS or Linux:

CC          = gcc-14
CLINKER     = $(CC)
# OPTFLAGS    = -O3 -fopenmp -pedantic -Wall -Wextra
OPTFLAGS    = -fopenmp -pedantic -Wall -Wextra -g
LIBS        = -lm
PRE         = ./

CFLAGS	  = $(OPTFLAGS)

OBJ=o
EXE=.exe # add extensions to executables to simplify .gitignore rules
RM=rm -f

# Build targets

EXES=hello$(EXE) pi$(EXE) pi_par$(EXE)

all: $(EXES)

hello$(EXE): hello.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o hello$(EXE) hello.$(OBJ) $(LIBS)

pi$(EXE): pi.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o pi$(EXE) pi.$(OBJ) $(LIBS)

pi_par$(EXE): pi_par.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o pi_par$(EXE) pi_par.$(OBJ) $(LIBS)

test: $(EXES)
	# $(PRE)hello$(EXE)
	# $(PRE)pi$(EXE)
	$(PRE)pi_par$(EXE)

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
