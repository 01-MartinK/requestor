SHELL = /bin/sh
CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4)
GLIB_COMPILE_RESOURCES = $(shell $(PKGCONFIG) --variable=glib_compile_resources gio-2.0)

# Directories
SRC_DIR := src
BUILD_DIR := build

SRC := $(SRC_DIR)/main.c $(SRC_DIR)/requestorapp.c $(SRC_DIR)/requestorappwin.c
BUILT_SRC := $(BUILD_DIR)/resources.c
RESOURCE_XML := $(SRC_DIR)/requestorapp.gresource.xml
UI_FILES := $(SRC_DIR)/window.ui

OBJS = $(BUILT_SRC:.c=.o) $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Output binary
TARGET := $(BUILD_DIR)/requestorapp

# Ensure build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(TARGET)

$(BUILT_SRC): $(RESOURCE_XML) $(UI_FILES) | $(BUILD_DIR)
	$(GLIB_COMPILE_RESOURCES) $(RESOURCE_XML) \
		--target=$@ --sourcedir=$(SRC_DIR) --generate-source

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c -o $@ $(CFLAGS) -lcurl $<

$(BUILD_DIR)/resources.o: $(BUILD_DIR)/resources.c
	$(CC) -c -o $@ $(CFLAGS) -lcurl $<

$(TARGET): $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS) -lcurl

clean:
	rm -rf $(BUILD_DIR)
