#ifndef __PROTOCOL_JAM_H__
#define __PROTOCOL_JAM_H__

#define JAM_COMPONENTID				5

#define JAM_SEND				1
#define JAM_RECV				2

#define PROTOV1_JAM_JAMID_OFF			PROTOV1_START_OF_DATA * 8
#define PROTOV1_JAM_JAMID_SIZE			17

#define PROTOV1_JAM_CLIENTSESSIONID_OFF		PROTOV1_JAM_JAMID_OFF + PROTOV1_JAM_JAMID_SIZE
#define PROTOV1_JAM_CLIENTSESSIONID_SIZE	PROTOV1_SESSIONID_SIZE

#define PROTOV1_JAM_AUDIODATALEN_OFF		PROTOV1_JAM_CLIENTSESSIONID_OFF + PROTOV1_JAM_CLIENTSESSIONID_SIZE
#define PROTOV1_JAM_AUDIODATALEN_SIZE		16

#define PROTOV1_JAM_START_OF_DATA		(PROTOV1_START_OF_DATA + BINARYTOBYTE_LEN(PROTOV1_JAM_AUDIODATALEN_OFF + PROTOV1_JAM_AUDIODATALEN_SIZE))

#define PROTOV1_JAM_DATA_AUDIO			0

#endif // ! __PROTOCOL_JAM_H__
