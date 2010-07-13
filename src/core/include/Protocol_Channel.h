#ifndef __PROTOCOL_CHANNEL_H__
#define __PROTOCOL_CHANNEL_H__

#define CHANNEL_COMPONENTID			2

#define CHANNEL_JOIN				1
#define CHANNEL_JOIN_OK				2
#define CHANNEL_JOIN_NOK_ALREADYINCHAN		3

#define CHANNEL_JOINED				4
#define CHANNEL_JOINED_ACK			5

#define CHANNEL_MESSAGE				6
#define CHANNEL_MESSAGE_ACK			7
#define CHANNEL_MESSAGE_RECV			8
#define CHANNEL_MESSAGE_RECV_ACK		9

#define CHANNEL_LEAVE				10
#define CHANNEL_LEAVE_OK			11
#define CHANNEL_LEAVE_NOK_NOTINCHAN		12

#define CHANNEL_LEAVED				13
#define CHANNEL_LEAVED_ACK			14

#define CHANNEL_LIST				15
#define CHANNEL_LISTED				16


// binary data contained in packet in order of placement in the binary fields
#define PROTOV1_CHANNEL_CHANNELID_OFF		sizeof_bin(PROTOV1_START_OF_DATA)
#define PROTOV1_CHANNEL_CHANNELID_SIZE		17

#define PROTOV1_CHANNEL_CLIENTSESSIONID_OFF	PROTOV1_CHANNEL_CHANNELID_OFF + PROTOV1_CHANNEL_CHANNELID_SIZE
#define PROTOV1_CHANNEL_CLIENTSESSIONID_SIZE	PROTOV1_SESSIONID_SIZE

// data contained in packet in order of placement in the data fields
#define PROTOV1_CHANNEL_START_OF_DATA		(PROTOV1_START_OF_DATA + BINARYTOBYTE_LEN(PROTOV1_CHANNEL_CLIENTSESSIONID_OFF + PROTOV1_CHANNEL_CLIENTSESSIONID_SIZE))

#define PROTOV1_CHANNEL_DATA_MESSAGE		0

#define PROTOV1_CHANNEL_DATA_CHANNEL_NAME	0

#define PROTOV1_CHANNEL_DATA_CHANNEL_LIST	0

#define PROTOV1_CHANNEL_DATA_LOGIN		0

#endif // ! __PROTOCOL_CHANNEL_H__
