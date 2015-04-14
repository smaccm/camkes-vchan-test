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

#include <HelloWorld.h>

#include "vmm/vchan_component.h"
#include "vmm/vchan_copy.h"
#include "vmm/vchan_sharemem.h"

#define DPRINTF(num, ...) printf(__VA_ARGS__);
#define DBG_SERVER 4

#define VCHAN_CLIENT_DOM 50
#define VCHAN_SERVER_DOM 0
#define VCHAN_PORT 25

#define CORE_SIZE 4096
static char core_buf[CORE_SIZE];
extern char *morecore_area;
extern size_t morecore_size;

static char char_buf[256];

static void rec_packet(libvchan_t * con);
static void puffout_strings(libvchan_t * con);

static camkes_vchan_con_t con = {
    .connect = &vchan_con_new_connection,
    .disconnect = &vchan_con_rem_connection,
    .get_buf = &vchan_con_get_buf,
    .status = &vchan_con_status,

    .alert = &vchan_con_ping,
    .wait = &vevent_wait,
    .poll = &vevent_poll,

    .component_dom_num = VCHAN_CLIENT_DOM,
};

void pre_init(void) {
    con.data_buf = (void *) share_mem;
    morecore_area = core_buf;
    morecore_size = CORE_SIZE;
    init_camkes_vchan(&con);
}

static void rec_packet(libvchan_t * con) {
    size_t sz;
    int x;
    char comp[6];
    vchan_packet_t pak;
    for(x = 0; x < NUM_PACKETS; x++) {
        sprintf(comp, "I%d", x);
        libvchan_wait(con);
        sz = libvchan_read(con, &pak, sizeof(pak));
        assert(sz == sizeof(pak));
        assert(strcmp(comp, pak.pnum) == 0);
    }

}

static void puffout_strings(libvchan_t * con) {
    size_t sz, len;
    vchan_header_t head;

    DPRINTF(DBG_SERVER,"hello: waiting for hello message\n");

    /* Wait for hello */
    libvchan_wait(con);

    sz = libvchan_read(con, &head, sizeof(head));
    assert(sz == sizeof(head));
    assert(head.msg_type == MSG_HELLO);
    head.msg_type = MSG_ACK;
    len = head.len;

    DPRINTF(DBG_SERVER,"hello: sending hello msg ack\n");

    /* Send off ack */
    sz = libvchan_write(con, &head, sizeof(head));
    assert(sz == sizeof(head));

    DPRINTF(DBG_SERVER,"hello: waiting for string\n");

    /* Read data */
    libvchan_wait(con);
    sz = libvchan_read(con, &char_buf, len);
    assert(sz == len);

    DPRINTF(DBG_SERVER,"hello: got string: %s\n", char_buf);

    // head.msg_type = MSG_CONC;
    // sz = libvchan_write(con, &head, sizeof(head));
    // assert(sz == sizeof(head));
}


int run(void) {
    libvchan_t *connection;

    DPRINTF(DBG_SERVER,"hello: init\n");

    connection = libvchan_server_init(VCHAN_SERVER_DOM, VCHAN_PORT, 0, 0);
    assert(connection != NULL);

    DPRINTF(DBG_SERVER,"hello: Connection Active\n");

    DPRINTF(DBG_SERVER,"hello: doing handshake\n");
    puffout_strings(connection);
    DPRINTF(DBG_SERVER,"hello: receiving packets\n");
    rec_packet(connection);

    DPRINTF(DBG_SERVER,"hello: done\n");
}
