#ifndef EVENTS_H
#define EVENTS_H

#define CONCAT_IMPL(a, b) a##b
#define MACRO_CONCAT(a, b) CONCAT_IMPL(a, b)

#define __event_handler_UNWRAPPED__(event_type, id, logic) appstatus_e id (event_info_t __event) logic __attribute__((constructor)) static void MACRO_CONCAT( __ev_handler_register, __COUNTER__)() { callback_array_append(& id, &event_type ); }

#define _event_handler(event_type, logic) __event_handler_UNWRAPPED__(event_type, MACRO_CONCAT(__ev_handler, __COUNTER__), logic)

#endif // EVENTS_H
