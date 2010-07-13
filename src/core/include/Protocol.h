#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define sizeof_bin(A)		(sizeof(A) * 8)
#define BINARYTOBYTE_LEN(A)	((A) / 8 + (((A) % 8 == 0) ? (0) : (1)))

typedef unsigned int field_t;

#define NOTARESPONSE	0

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

// binary data contained in packet in order of placement in the binary fields
#define PROTOV1_COMPONENTID_OFF (PROTO_PROTOVERSION_OFF + PROTO_PROTOVERSION_SIZE)
#define PROTOV1_COMPONENTID_SIZE 10

#define PROTOV1_REQUESTID_OFF (PROTOV1_COMPONENTID_OFF + PROTOV1_COMPONENTID_SIZE)
#define PROTOV1_REQUESTID_SIZE 6

#define PROTOV1_SESSIONID_OFF (PROTOV1_REQUESTID_OFF + PROTOV1_REQUESTID_SIZE)
#define PROTOV1_SESSIONID_SIZE 32

#define PROTOV1_DATALEN_OFF (PROTOV1_SESSIONID_OFF + PROTOV1_SESSIONID_SIZE)
#define PROTOV1_DATALEN_SIZE 12

// data contained in packet
#define PROTOV1_START_OF_DATA BINARYTOBYTE_LEN(PROTOV1_DATALEN_OFF + PROTOV1_DATALEN_SIZE)

///// NOT WORKING runtime8 cuz MACRO ///

#define PACKET_TYPE_NAME(x) #x
///////////////////////////////////////


    //////////////////////////////////////////////////////////////////
   //                                                              //
  //                     PROTOCOL v2                              //
 //                                                              //
//////////////////////////////////////////////////////////////////
#define PROTOV2			2
// Use same define logic as v1 so it is easily modifiable without having
// to recode part of the packet managers

#endif // ! __PROTOCOL_H__
