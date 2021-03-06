/* //device/libs/telephony/ril_event.h
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


// Max number of fd's we watch at any one time.  Increase if necessary.
#define MAX_FD_EVENTS 8

typedef void (*ril_event_cb)(int fd, short events, void *userdata);

struct ril_event {
    struct ril_event *next;
    struct ril_event *prev;

    int fd;                  //事件相关设备句柄。最重要的就是RILJ与RILC之间的Socket文件句柄
    int index;
    bool persist;            //说明当前的Event需要保持，不能从watch_table中删除
    struct timeval timeout;
    ril_event_cb func;       //当前Event的处理函数
    void *param;             //调用当前Event处理函数时的参数
};

// Initialize internal data structs
void ril_event_init();

// Initialize an event
void ril_event_set(struct ril_event * ev, int fd, bool persist, ril_event_cb func, void * param);

// Add event to watch list
void ril_event_add(struct ril_event * ev);

// Add timer event
void ril_timer_add(struct ril_event * ev, struct timeval * tv);

// Remove event from watch list
void ril_event_del(struct ril_event * ev);

// Event loop
void ril_event_loop();

