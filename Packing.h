#pragma once
#define MSGCODE 0x0001
class Packing
{
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the data structure for the message 
////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct
	{
		unsigned short code;
		unsigned short length;
		unsigned char username[20];
		unsigned long longValue;
		unsigned short shortvalue;
		unsigned char byteValue;
		int intValue;
		unsigned short datalen;
		unsigned char data[100];

	}MSG_STRUCT;
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the macros required for packing the message
////////////////////////////////////////////////////////////////////////////////////////////////////
#define PackBytes(bf, bytes, len) \
    memcpy(bf, bytes, len); \
    bf += len;

#define PackLong(bf, l) \
    *bf++ = (l >> 24) & 0xFF; \
    *bf++ = (l >> 16) & 0xFF; \
    *bf++ = (l >> 8) & 0xFF; \
    *bf++ = l & 0xFF;    

#define PackShort(bf, s) \
    *bf++ = (s >> 8) & 0xFF; \
    *bf++ = s & 0xFF;    

#define PackByte(bf, b) \
    *bf++ = b;    

	// UNPACKING
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the macros for unpacking the messages contents
////////////////////////////////////////////////////////////////////////////////////////////////////
#define UnpackBytes(bf, bytes, len) \
    memcpy(bytes, bf, len); \
    bf += len;

#define UnpackLong(bf, l) \
    l = (*bf++ << 24); \
    l += (*bf++ << 16); \
    l += (*bf++ << 8); \
    l += *bf++;

#define UnpackShort(bf, s) \
    s = (*bf++ << 8); \
    s += *bf++;

#define UnpackByte(bf, b) \
    b = *bf++;



public:
	Packing();
	~Packing();
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create a method that will pack the contents of the message before sending to the user
////////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned short PackMsg(MSG_STRUCT *msg, unsigned char *buff);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create a method that will pack the contents of the message before sending to the user
////////////////////////////////////////////////////////////////////////////////////////////////////
	void UnpackMSG(MSG_STRUCT *msg, unsigned char *buff);

};

