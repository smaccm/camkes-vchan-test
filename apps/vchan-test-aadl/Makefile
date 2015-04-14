#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the GNU General Public License version 2. Note that NO WARRANTY is provided.
# See "LICENSE_GPLv2.txt" for details.
#
# @TAG(NICTA_GPL)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := vchan-test-aadl.camkes

include Vchan/Vchan.mk
include VchanProxy/VchanProxy.mk
include HelloWorldServerAADL/HelloWorld.mk
include HelloWorldClient/HelloWorldClient.mk

include ${PWD}/tools/camkes/camkes.mk

