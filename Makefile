# Generated automatically from Makefile.in by configure.
# $Id: Makefile.in,v 1.59 2002/03/24 22:20:19 jnelson Exp $

.SUFFIXES:
.SUFFIXES: .o .c
.PHONY: clean mrclean distclean depend all dist



GCC_FLAGS = -Wstrict-prototypes -Wpointer-arith -Wcast-align -Wcast-qual\
  -Wtraditional\
  -Wshadow\
  -Wconversion\
  -Waggregate-return\
  -Wmissing-prototypes\
  -Wnested-externs\
  -Wall \
  -Wundef -Wwrite-strings -Wredundant-decls -Winline


srcdir = .
VPATH = .:./../extras
LDFLAGS =  -g -lpthread
LIBS =  
CFLAGS = -g -O2 -pipe -Wall -I. $(INC)

# Change these if necessary

YACC = bison -y 
LEX = flex 
CC = gcc 
CPP = gcc -E

SOURCES = alias.c boa.c buffer.c cgi.c cgi_header.c config.c escape.c \
	get.c hash.c ip.c log.c mmap_cache.c pipe.c queue.c read.c \
	request.c response.c select.c signals.c util.c sublog.c
###SeanHou

ONVIF_OBJS  = onvif/src/duration.o
ONVIF_OBJS += onvif/src/soapC.o
ONVIF_OBJS += onvif/src/soapClient.o
ONVIF_OBJS += onvif/src/soapServer.o
ONVIF_OBJS += onvif/src/stdsoap2.o
ONVIF_OBJS += onvif/src/onvif_server.o
ONVIF_OBJS += onvif/src/onvif_server_interface.o
ONVIF_OBJS += onvif/src/onvif_function.o
ONVIF_OBJS += onvif/src/onvif_imaging.o
ONVIF_OBJS += onvif/src/onvif_media.o
ONVIF_OBJS += onvif/src/onvif_net.o
ONVIF_OBJS += onvif/src/onvif_devicemgmt.o
ONVIF_OBJS += onvif/src/onvif_discovery.o
ONVIF_OBJS += onvif/src/onvif_common.o
INC = -I onvif/src/

###end
OBJS = y.tab.o lex.yy.o $(SOURCES:.c=.o) timestamp.o $(ONVIF_OBJS)

all:	boa boa_indexer

boa:	$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS) $(INC)
	
boa_indexer:	index_dir.o escape.o   
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) boa core lex.yy.c y.tab.c y.tab.h *~ boa_indexer index_dir.o   
	
distclean:	mrclean

mrclean:	clean
	rm -f config.status config.cache config.h Makefile config.log

# parser dependencies

y.tab.c y.tab.h:	boa_grammar.y
	$(YACC) -d $^

lex.yy.c:	boa_lexer.l
	$(LEX) $^

# timestamp

timestamp.o:	$(SOURCES) boa_grammar.y boa_lexer.l

# depend stuff
.depend:
	$(CPP) -MM $(SOURCES) > .depend
        
depend:
	-rm -f .depend
	$(MAKE) .depend
        
include .depend

# tags
tags:	$(SOURCES)
	ctags -o tags $^ *.h

# dist
dist:
	$(MAKE) clean
	./makedist.sh
        
# object dump
boa.objdump:    boa
	objdump --disassemble-all --source boa > $@

