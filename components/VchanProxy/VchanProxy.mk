CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

VchanProxy_CFILES := $(wildcard ${CURRENT_DIR}/src/*.c)
VchanProxy_HFILES := $(wildcard $(CURRENT_DIR)/../../include/*.h)
VchanProxy_LIBS := sel4camkes sel4vchan # sel4arm-vmm
