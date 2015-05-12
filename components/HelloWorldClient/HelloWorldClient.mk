CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

HelloWorldClient_CFILES := $(wildcard ${CURRENT_DIR}/src/*.c)

HelloWorldClient_LIBS := sel4camkes sel4vchan # sel4arm-vmm 

