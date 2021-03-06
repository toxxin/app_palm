#! gmake

#
# Copyright (C) 2006 Laurent Bessard
# 
# This file is part of canfestival, a library implementing the canopen
# stack
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# 

CC = arm-openwrt-linux-gcc
CXX = arm-openwrt-linux-g++
LD = arm-openwrt-linux-g++
OPT_CFLAGS = -O2
CFLAGS = $(OPT_CFLAGS)
PROG_CFLAGS =  -fPIC -DDEBUG_MSG_CONSOLE_ON -g
EXE_CFLAGS =  -lpthread -lrt -ldl
OS_NAME = Linux
ARCH_NAME = arm
PREFIX = arm-openwrt-linux-
TARGET = unix
CAN_DRIVER = can_socket
TIMERS_DRIVER = timers_unix
TESTSLAVE = "OwnSlave"

INCLUDES = -I../../include -I../../include/$(TARGET) -I../../include/$(CAN_DRIVER) -I../../include/$(TIMERS_DRIVER)

SLAVE_OBJS = TestSlave.o OwnSlave.o Slave.o

OBJS = $(SLAVE_OBJS) ../../src/libcanfestival.a ../../drivers/$(TARGET)/libcanfestival_$(TARGET).a

ifeq ($(TARGET),win32)
	TESTSLAVE = "OwnSlave.exe"
endif

ifeq ($(TIMERS_DRIVER),timers_win32)
	EXE_CFLAGS =
endif

ifeq ($(TIMERS_DRIVER),timers_xeno)
	PROGDEFINES = -DUSE_XENO
endif

ifeq ($(TIMERS_DRIVER),timers_rtai)
	PROGDEFINES = -DUSE_RTAI
endif

all: $(TESTSLAVE)

../../drivers/$(TARGET)/libcanfestival_$(TARGET).a:
	$(MAKE) -C ../../drivers/$(TARGET) libcanfestival_$(TARGET).a


$(TESTSLAVE): $(OBJS)
	$(LD) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ $(OBJS) $(EXE_CFLAGS)
	
TestSlave.c: TestSlave.od
	$(MAKE) -C ../../objdictgen gnosis
	python ../../objdictgen/objdictgen.py TestSlave.od TestSlave.c

%.o: %.c
	$(CC) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(SLAVE_OBJS)
	rm -f $(TESTSLAVE)
		
mrproper: clean
	rm -f TestSlave.c
	rm -f TestMaster.c
	
install: OwnSlave
	mkdir -p $(DESTDIR)$(PREFIX)/bin/
	cp $< $(DESTDIR)$(PREFIX)/bin/
	
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/OwnSlave
