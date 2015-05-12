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
#include <autoconf.h>

#include <sel4/sel4.h>
#include <sel4utils/util.h>

#include <HelloWorldClient.h>

#include <sel4vchan/vchan_component.h>
#include <sel4vchan/vchan_copy.h>
#include <sel4vchan/vchan_sharemem.h>

#define DPRINTF(num, ...) printf(__VA_ARGS__);
#define DBG_CLIENT 5

#define VCHAN_CLIENT_DOM 50
#define VCHAN_SERVER_DOM 0
#define VCHAN_PORT 25

/*
#define CORE_SIZE 4096
static char core_buf[CORE_SIZE];
extern char *morecore_area;
extern size_t morecore_size;
*/

static int send_packet(libvchan_t *con);
static int send_string(const char *string, libvchan_t *con);

static camkes_vchan_con_t con = {
    .connect = &vchan_con_new_connection,
    .disconnect = &vchan_con_rem_connection,
    .get_buf = &vchan_con_get_buf,
    .status = &vchan_con_status,

    .alert = &vchan_con_ping,
    .wait = &vevent_wait,
    .poll = &vevent_poll,

    .dest_dom_number = 50,
    .source_dom_number = 0,
};


void pre_init(void) {
/*
    con.data_buf = (void *) share_mem;
    morecore_area = core_buf;
    morecore_size = CORE_SIZE;
    init_camkes_vchan(&con);
*/
}

int send_packet(libvchan_t *con) {

        size_t sz;
        vchan_packet_t pak;
        int x;

        for(x = 0; x < NUM_PACKETS; x++) {
                sprintf(pak.pnum, "I%d", x);
                while(libvchan_buffer_space(con) < sizeof(pak)) printf(".");
                sz = libvchan_send(con, &pak, sizeof(pak));
                if(sz < sizeof(pak)) {
                        DPRINTF(DBG_CLIENT, "--BAD PACKET -- SEND\n");
                        return -1;
                }
        }

        DPRINTF(DBG_CLIENT, "client: pack end\n");

        return 0;
}

int send_string(const char *string, libvchan_t *con) {
        size_t sz;
        vchan_header_t msg = {
                .msg_type = MSG_HELLO,
                .len = strlen(string),
        };

        DPRINTF(DBG_CLIENT, "client: send hello\n");
        /* Send hello */
        sz = libvchan_write(con, &msg, sizeof(msg));
        assert(sz == sizeof(msg));

        DPRINTF(DBG_CLIENT, "client: wait for ack\n");
        /* Wait for ack */
        libvchan_wait(con);
        sz = libvchan_read(con, &msg, sizeof(msg));
        assert(sz == sizeof(msg));
        assert(msg.msg_type == MSG_ACK);

        /* Send string */
        DPRINTF(DBG_CLIENT, "client: send string %s\n", string);
        sz = libvchan_write(con, string, strlen(string));
        assert(sz = strlen(string));

        // /* Wait for conclude */
        // printf("client: wait for conclude\n");
        // libvchan_wait(con);
        // sz = libvchan_read(con, &msg, sizeof(msg));
        // if(sz < sizeof(msg) || msg.msg_type != MSG_CONC) {
        //      return -1;
        // }

        DPRINTF(DBG_CLIENT, "client: finished sending string\n");

        return 0;
}

int run(void) {
    int ecount = 0;

    con.data_buf = (void *) share_mem;

    DPRINTF(DBG_CLIENT, "client: Creating connection\n");
    libvchan_t *ctrl = libvchan_client_init(VCHAN_CLIENT_DOM, VCHAN_PORT);
    if(ctrl != NULL)
        ctrl = link_vchan_comp(ctrl, &con);
    assert(ctrl != NULL);
    printf("client: Connection Established!\n");

    char test[] = "Hello World!, this is a test string.";
    ecount += send_string(test, ctrl);
    if(ecount == 0) {
                ecount += send_packet(ctrl);
    }
    DPRINTF(DBG_CLIENT, "client: %d errors\n", ecount);

    DPRINTF(DBG_CLIENT, "client: done\n");
}
