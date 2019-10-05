#include "stdafx.h"
#include "Packing.h"


Packing::Packing()
{
}


Packing::~Packing()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is used to pack the message to send to the players during gametime
////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned short Packing::PackMsg(MSG_STRUCT * msg, unsigned char * buff)
{
	unsigned short msglen;
	unsigned char *lenptr;

	PackShort(buff, msg->code);
	lenptr = buff;
	buff += sizeof(unsigned short);
	PackBytes(buff, msg->username, 20);
	PackLong(buff, msg->longValue);
	PackShort(buff, msg->shortvalue);
	PackByte(buff, msg->byteValue);
	PackLong(buff, msg->intValue);
	PackShort(buff, msg->datalen);
	PackBytes(buff, msg->data, msg->datalen);


	msglen = sizeof(unsigned short)
		+ sizeof(unsigned short)
		+ sizeof(msg->username)
		+ sizeof(unsigned long)
		+ sizeof(unsigned short)
		+ 1
		+ sizeof(unsigned long)
		+ sizeof(unsigned short)
		+ msg->datalen;

	PackShort(lenptr, msglen);
	return msglen;








}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is used to unpack the message that is recieved from the players during game time
////////////////////////////////////////////////////////////////////////////////////////////////////
void Packing::UnpackMSG(MSG_STRUCT * msg, unsigned char * buff)
{
	UnpackShort(buff, msg->code);
	UnpackShort(buff, msg->length);
	UnpackBytes(buff, msg->username,20);
	UnpackLong(buff, msg->longValue);
	UnpackShort(buff, msg->shortvalue);
	UnpackByte(buff, msg->byteValue);
	UnpackLong(buff, msg->intValue);
	UnpackShort(buff, msg->datalen);
	UnpackBytes(buff, msg->data, msg->datalen);

}
