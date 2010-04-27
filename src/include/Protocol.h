#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define PACKET_MAXSIZE 2048

// This file defines network protocols used in livejamming
// keep the definitions in order of the fields in protocol definition
// always define following offset relatively to previous offset

    //////////////////////////////////////////////////////////////////
   //                                                              //
  //                     PROTOCOL BASE (common to all versions)   //
 //                                                              //
//////////////////////////////////////////////////////////////////
#define PROTO_PROTOVERSION_OFF 0
#define PROTO_PROTOVERSION_SIZE 4




    //////////////////////////////////////////////////////////////////
   //                                                              //
  //                     PROTOCOL v1                              //
 //                                                              //
//////////////////////////////////////////////////////////////////
#define PROTOV1		1

// size of bit fields in packets
#define PROTOV1_TYPE_OFF (PROTO_PROTOVERSION_OFF + PROTO_PROTOVERSION_SIZE)
#define PROTOV1_TYPE_SIZE 6

#define PROTOV1_SESSIONID_OFF (PROTOV1_TYPE_OFF + PROTOV1_TYPE_SIZE)
#define PROTOV1_SESSIONID_SIZE 16

#define PROTOV1_DATALEN_OFF (PROTOV1_SESSIONID_OFF + PROTOV1_SESSIONID_SIZE)
#define PROTOV1_DATALEN_SIZE 12

#define PROTOV1_START_OF_DATA (((PROTOV1_DATALEN_OFF + PROTOV1_DATALEN_SIZE) % 8 == 0)? \
			       ((PROTOV1_DATALEN_OFF + PROTOV1_DATALEN_SIZE) / 8): \
			       ((PROTOV1_DATALEN_OFF + PROTOV1_DATALEN_SIZE) / 8 + 8))

//////////// Packet types  /////////////
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



    //////////////////////////////////////////////////////////////////
   //                                                              //
  //                     PROTOCOL v2                              //
 //                                                              //
//////////////////////////////////////////////////////////////////
#define PROTOV2			2
// Use same define logic as v1 so it is easily modifiable without having
// to recode part of the packet managers

#endif // ! __PROTOCOL_H__
