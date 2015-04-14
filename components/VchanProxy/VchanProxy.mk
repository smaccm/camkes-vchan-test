CURRENT_DIR := $(dir $(abspath $(lastword ${MAKEFILE_LIST})))

VchanProxy_CFILES := $(wildcard ${CURRENT_DIR}/src/*.c)
VchanProxy_HFILES := $(wildcard $(CURRENT_DIR)/../../include/*.h)
VchanProxy_LIBS := sel4camkes sel4vmm sel4utils sel4vka sel4allocman sel4vspace sel4simple sel4simple-stable sel4platsupport
