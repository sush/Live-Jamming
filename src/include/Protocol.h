#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

///////////// protocol v1 

// define taille

typedef enum 
 {
   SESSION_AUTH_REQUEST = 1,
   SESSION_AUTH_RESPOND_OK,
   SESSION_AUTH_RESPOND_NOK_BADAUTH,
   SESSION_AUTH_RESPOND_NOK_DUPLICATE,
   SESSION_DISCONNECT,
   SESSION_DISCONNECTED,
   SESSION_TIMEOUT,
   SESSION_KEEPALIVE
 }proto_v1_packet_type;

#endif // ! __PROTOCOL_H__
