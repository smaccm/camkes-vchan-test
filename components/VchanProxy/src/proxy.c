/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */

#include <stdio.h>
#include <stdint.h>

#include <sel4/sel4.h>
#include <sel4utils/util.h>

#include <VchanProxy.h>

// #include <vmm/vmm.h>
#include <sel4vchan/vchan_copy.h>
#include <sel4vchan/vchan_sharemem.h>

#define DPRINTF(num, ...) printf(__VA_ARGS__);
void copy_vChan_demo__structs_vchan_ctrl(vchan_ctrl_t *dest, vChan_demo__structs_vchan_ctrl *src) {
   dest->domain = src->domain;
   dest->dest = src->dest;
   dest->port = src->thePort;
}

void copy_vChan_demo__structs_vchan_connect(vchan_connect_t *dest, vChan_demo__structs_vchan_connect *src) {
   dest->server = src->server;
   dest->eventfd = src->eventfd;
   dest->event_mon = src->event_mon;
   copy_vChan_demo__structs_vchan_ctrl(&(dest->v), &(src->v));
}


void rpc_in_new_connection(int32_t *returns, vChan_demo__structs_vchan_connect con) {
   vchan_connect_t conp;
   copy_vChan_demo__structs_vchan_connect(&conp, &con);
   *returns = vchan_com_out_new_connection(conp);
}


void rpc_in_rem_connection(int32_t *returns, vChan_demo__structs_vchan_connect con) {
   vchan_connect_t conp;
   copy_vChan_demo__structs_vchan_connect(&conp, &con);
   *returns = (int32_t)vchan_com_out_rem_connection(conp);
}

void rpc_in_get_buf(int32_t *returns, vChan_demo__structs_vchan_ctrl con, int32_t cmd) {
   vchan_ctrl_t conp;
   copy_vChan_demo__structs_vchan_ctrl(&conp, &con); 
   *returns = (int32_t)vchan_com_out_get_buf(conp, (int)cmd);
}

void rpc_in_status(int32_t *returns, vChan_demo__structs_vchan_ctrl con) {
   vchan_ctrl_t conp;
   copy_vChan_demo__structs_vchan_ctrl(&conp, &con);
  *returns = (int32_t)vchan_com_out_status(conp);
}

void rpc_in_ping() {
  vchan_com_out_ping();
}

void vevent_out_callback(void *arg) {
  vevent_in_write_void();
  vevent_out_reg_callback(vevent_out_callback, arg);
}

int run(void) {
  vevent_out_reg_callback(vevent_out_callback, NULL);
  return 0;
}
