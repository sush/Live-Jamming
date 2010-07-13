#ifndef __PROTOCOL_SESSION_H__
#define __PROTOCOL_SESSION_H__

#define SESSION_COMPONENTID			1

#define SESSION_AUTHREQUEST			1
#define SESSION_AUTHRESPONSE_OK			2
#define SESSION_AUTHRESPONSE_NOK_BADAUTH	3
#define SESSION_AUTHRESPONSE_NOK_DUPLICATE	4
#define	SESSION_DISCONNECT			5
#define SESSION_DISCONNECTED			6
#define SESSION_TIMEOUT				7
#define	SESSION_KEEPALIVE			8

// binary data contained in packet in order of placement in the binary fields


// ASCII data contained in packet in order of placement in the data fields
#define PROTOV1_SESSION_START_OF_DATA			PROTOV1_START_OF_DATA

#define PROTOV1_SESSION_DATA_LOGIN			0
#define PROTOV1_SESSION_DATA_PASS			1

#endif // ! __PROTOCOL_SESSION_H__
