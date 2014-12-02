CFLAGS =-lpthread -lssl -lcrypto 

ONVIF_OBJS  = src/duration.o
ONVIF_OBJS += src/soapC.o
ONVIF_OBJS += src/soapClient.o
ONVIF_OBJS += src/soapServer.o
ONVIF_OBJS += src/stdsoap2.o
ONVIF_OBJS += src/onvif_server.o
ONVIF_OBJS += src/onvif_server_interface.o
ONVIF_OBJS += src/onvif_function.o
ONVIF_OBJS += src/onvif_imaging.o
ONVIF_OBJS += src/onvif_media.o
ONVIF_OBJS += src/onvif_net.o
ONVIF_OBJS += src/onvif_devicemgmt.o
ONVIF_OBJS += src/onvif_discovery.o
ONVIF_OBJS += src/onvif_common.o

default:all
all:$(ONVIF_OBJS)
	@echo "over"

%.o:%.c
	-@echo -e "\033[41;32m  compiling $<... \033[0m"
	@gcc $(CFLAGS) -c $< -o $@

