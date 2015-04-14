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

#include <HelloWorld.h>
#include "smaccm_test1_impl_types.h"

#include "vmm/vmm.h"
#include "vmm/vchan_copy.h"
#include "vmm/vchan_sharemem.h"

#include "vchan-shim.h"

#define DPRINTF(num, ...) printf(__VA_ARGS__);

void copy_vChan_demo__structs_vchan_ctrl(vChan_demo__structs_vchan_ctrl *dest,  vchan_ctrl_t *src) {
   dest->domain = src->domain;
   dest->dest = src->dest;
   dest->thePort = src->port;
}

void copy_vChan_demo__structs_vchan_connect(vChan_demo__structs_vchan_connect *dest, vchan_connect_t *src) {
   dest->server = src->server;
   dest->eventfd = src->eventfd;
   dest->event_mon = src->event_mon;
   copy_vChan_demo__structs_vchan_ctrl(&(dest->v), &(src->v));
}


int vchan_con_new_connection(vchan_connect_t con) {
   int32_t ret;
   vChan_demo__structs_vchan_connect conp;
   copy_vChan_demo__structs_vchan_connect(&conp, &con);
   rpc_new_connection(&ret, conp);
   return (int)ret;
}

int vchan_con_rem_connection(vchan_connect_t con) {
   int32_t ret;
   vChan_demo__structs_vchan_connect conp;   
   copy_vChan_demo__structs_vchan_connect(&conp, &con);
   rpc_rem_connection(&ret, conp);
   return (int)ret;
}

intptr_t vchan_con_get_buf(vchan_ctrl_t args, int cmd) {
   int32_t ret;
   vChan_demo__structs_vchan_ctrl argsp;      
   copy_vChan_demo__structs_vchan_ctrl(&argsp, &args);
   rpc_get_buf(&ret, argsp, (int32_t)cmd);
   return (int)ret;
}

int vchan_con_status(vchan_ctrl_t args) {
   int32_t ret;
   vChan_demo__structs_vchan_ctrl argsp;
   copy_vChan_demo__structs_vchan_ctrl(&argsp, &args);
   rpc_status(&ret, argsp);
   return (int)ret;
}

int vchan_con_alert_status(vchan_ctrl_t args) {
   return 0;
   // missing alert_status() in rpc
/*
   int32_t ret;
   vChan_demo__structs_vchan_ctrl argsp;
   copy_vChan_demo__structs_vchan_ctrl(&argsp, &args);
   rpc_alert_status(&ret, argsp);
   return (int)ret;
*/
}

void vchan_con_ping() {
   rpc_ping();
}

void vevent_wait(void) {
  smaccm_receiver_vevent_sem_wait();
}

int vevent_poll(void) {
  // TODO
}

int vevent_reg_callback(void (*callback)(void*), void *arg) {
  // TODO
  return 0;
}

bool vevent_write_void() {
  // set semaphore to be ued by wait and poll
  smaccm_receiver_vevent_sem_post();
}

