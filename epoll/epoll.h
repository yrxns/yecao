#include <sys/epoll.h>
#include <string.h>
#include  <unistd.h>
#include "../error/error.h"

#define MAX_EVENTS 300

class epoll {
public:
    epoll() {
        epfd = epoll_create(0);
        if (epfd == -1) {
            errmsg("epoll()");
        }

        events  = new epoll_event[MAX_EVENTS];
        bzero(events, sizeof(struct epoll_event) *  MAX_EVENTS);
    }
    ~epoll() {
        close(epfd);
        delete [] events;
    }

    void addfd(int fd, uint32_t op) {
        struct epoll_event ev;
        bzero(&ev, sizeof(ev));
        ev.data.fd = fd;
        ev.events =  op;

        if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
            errmsg("addfd()");
        }
    }
    void delfd(int fd) {
        if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr) == -1) {
            errmsg("delfd()");
        }
    }
    void modfd(int fd, uint32_t op) {
        struct epoll_event ev;
        bzero(&ev, sizeof(ev));
        ev.data.fd = fd;
        ev.events =  op;

        if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
            errmsg("delfd()");
        }
    }

    int poll(int timeout) {
        int n = epoll_wait(epfd, events, MAX_EVENTS, timeout);
        if  (n == -1) {
            errmsg("poll...epoll_wait()");
        }
        return n;
    }

    int operator [](int i)  {
        return events[i].data.fd;
    }

private:
    int epfd;
    struct epoll_event* events;
};
