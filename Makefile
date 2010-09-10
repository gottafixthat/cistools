VERSION    = 1
PATCHLEVEL = 1
RELEASE    = 1

export VERSION
export PATCHLEVEL
export RELEASE

export FULLVERSION=$(VERSION).$(PATCHLEVEL).$(RELEASE)

INCDIR	=  /usr/local/include
CFLAGS	= -g -fno-strength-reduce -I. -I./libdes -Wall -fPIC
LFLAGS  = -lcrypt -L./libdes -ldes
SHELL   = /bin/sh
CC	= gcc

INSTDIR = /usr/local

# CFLAGS += -DDBDEBUG

####### End of automatically generated section

####### Files

SUBDIRS =	libdes

SOURCES =	StrTools.cpp Cfg.cpp CCValidate.cpp
SOURCES +=	ADBColumn.cpp ADBRow.cpp ADB.cpp ADBTable.cpp ADBList.cpp
ifdef ADBQT
    SOURCES += ADBLogin.cpp
endif
CSOURCES =	bdes.c

HEADERS =	StrTools.h Cfg.h CCValidate.h ADB.h bdes.h

OBJECTS =	$(SOURCES:.cpp=.o)
COBJECTS +=	$(CSOURCES:.c=.o)

ifdef ADBQT
SRCMETA =	moc_ADB.cpp
endif

OBJMETA =	$(SRCMETA:.cpp=.o)

TARGET	=	libcistools

####### Implicit rules

.SUFFIXES: .cpp .c

.cpp.o:
	$(CC) -c $(CFLAGS) -I$(INCDIR) $<

.c.o:
	$(CC) -c $(CFLAGS) -I$(INCDIR) $<

####### Build rules

all: $(SUBDIRS) $(SRCMETA) $(OBJMETA) str-lib

str-lib: $(OBJECTS) $(COBJECTS)
	ar r $(TARGET).a $(OBJECTS) $(COBJECTS) $(OBJMETA) libdes/libdes.a
	ranlib $(TARGET).a
	gcc -shared -o $(TARGET).so $(OBJECTS) $(COBJECTS) $(OBJMETA) libdes/libdes.a

$(SUBDIRS): FORCE
	cd $@; $(MAKE)

$(TARGET): $(SRCMETA) $(OBJECTS) $(COJBECTS) $(OBJMETA)
	$(CC) $(OBJECTS) $(COBJECTS) $(OBJMETA) -o $(TARGET) $(LFLAGS)

depend:
	@makedepend -I$(INCDIR) $(SOURCES) $(CSOURCES) 2> /dev/null

showfiles:
	@echo $(SOURCES) $(CSOURCES) $(HEADERS) Makefile

install: all
	install $(HEADERS) $(INSTDIR)/include
	install $(TARGET).a  $(INSTDIR)/lib
	install $(TARGET).so  $(INSTDIR)/lib

uninstall: all
	set -e; for i in $(HEADERS); do rm -f $(INSTDIR)/include/$$i ; done
	-rm -f $(INSTDIR)/lib/$(TARGET).a
	-rm -f $(INSTDIR)/lib/$(TARGET).so

clean:
	set -e; for i in $(SUBDIRS); do cd $$i ; echo make clean in $$i ; $(MAKE) clean ; cd ..; done
	-rm -f $(TARGET).so $(TARGET).a *.o *.bak *~ *% #*
	-rm -f $(SRCMETA) $(TARGET)

rpms:
	# set -e; for i in $(SUBDIRS); do cd $$i ; $(MAKE) clean ; cd .. ; done
	-cat rpm/cistools.spec | sed -e s/{VERSION}/$(FULLVERSION)/ -e s/{RELEASE}/$(RELEASE)/ > rpm/cistools-$(FULLVERSION).spec
	-rm -rf /var/tmp/cistools
	-mkdir /var/tmp/cistools
	-mkdir /var/tmp/cistools/BUILD
	-mkdir /var/tmp/cistools/RPMS
	-mkdir /var/tmp/cistools/RPMS/i386
	-mkdir /var/tmp/cistools/SRPMS
	-mkdir /var/tmp/cistools/SPECS
	-mkdir /var/tmp/cistools/SOURCES
	-mkdir /var/tmp/cistools/cistools-$(FULLVERSION)
	-tar --exclude .svn --exclude RPM -zcf /var/tmp/cistools/cistools-$(FULLVERSION).tgz Makefile *c *cpp *h libdes
	-tar -C /var/tmp/cistools/cistools-$(FULLVERSION) -zxf /var/tmp/cistools/cistools-$(FULLVERSION).tgz
	-tar -C /var/tmp/cistools -zcf /var/tmp/cistools/SOURCES/cistools-$(FULLVERSION).tgz cistools-$(FULLVERSION)
	-cat rpm/cistools.spec | sed -e s/{VERSION}/$(FULLVERSION)/ -e s/{RELEASE}/$(RELEASE)/ > /var/tmp/cistools/SPECS/cistools-$(FULLVERSION).spec
	-rpmbuild -ba /var/tmp/cistools/SPECS/cistools-$(FULLVERSION).spec
	-cp /var/tmp/cistools/RPMS/i386/cistools-$(FULLVERSION)-$(RELEASE).i386.rpm rpm/
	-cp /var/tmp/cistools/SRPMS/cistools-$(FULLVERSION)-$(RELEASE).src.rpm rpm/
	#-rm -rf /var/tmp/cistools

FORCE:

####### Meta objects


# DO NOT DELETE THIS LINE -- make depend depends on it.
