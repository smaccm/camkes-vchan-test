CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

HelloWorldClient_CFILES := $(wildcard ${CURRENT_DIR}/src/*.c)
HelloWorldClient_HFILES += $(wildcard $(CURRENT_DIR)/include/*.h)
HelloWorldClient_LIBS := sel4camkes sel4vmm sel4utils sel4vka sel4allocman sel4vspace 

