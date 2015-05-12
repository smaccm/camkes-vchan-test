CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

HelloWorld_CFILES := $(wildcard ${CURRENT_DIR}/src/*.c)
HelloWorld_HFILES += $(wildcard $(CURRENT_DIR)/include/*.h)
HelloWorld_LIBS := sel4camkes sel4vchan # sel4arm-vmm 
