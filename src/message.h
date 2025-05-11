#ifndef MESSAGE_H
#define MESSAGE_H

#include <CoreFoundation/CoreFoundation.h>

#define YABAI_PORT_NAME "com.koekeishiya.yabai.port"
#define YABAI_FAILURE_PREFIX '!'

void handle_message(FILE *rsp, char *message);
bool message_loop_begin(char *socket_path);

#endif
