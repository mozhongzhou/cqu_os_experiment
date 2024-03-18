/**
 * @file xfilter.h
 * Copyright 2012, 2013 MinGW.org project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/* Created by Casper S. Hornstrup <chorns@users.sourceforge.net> */
#ifndef __XFILTER_H
#define __XFILTER_H
#pragma GCC system_header
#include <_mingw.h>

/*
 * Address filtering for NDIS MACs
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ntddk.h"


#define ETH_LENGTH_OF_ADDRESS             6

#define ETH_IS_BROADCAST(Address) \
  ((((PUCHAR)(Address))[0] == ((UCHAR)0xff)) && (((PUCHAR)(Address))[1] == ((UCHAR)0xff)))

#define ETH_IS_MULTICAST(Address) \
  (BOOLEAN)(((PUCHAR)(Address))[0] & ((UCHAR)0x01))

#define ETH_COMPARE_NETWORK_ADDRESSES(_A, _B, _Result) \
{ \
	if (*(ULONG UNALIGNED *)&(_A)[2] > *(ULONG UNALIGNED *)&(_B)[2]) \
	{ \
    *(_Result) = 1; \
	} \
	else if (*(ULONG UNALIGNED *)&(_A)[2] < *(ULONG UNALIGNED *)&(_B)[2]) \
	{ \
    *(_Result) = (UINT)-1; \
	} \
	else if (*(USHORT UNALIGNED *)(_A) > *(USHORT UNALIGNED *)(_B)) \
	{ \
    *(_Result) = 1; \
	} \
	else if (*(USHORT UNALIGNED *)(_A) < *(USHORT UNALIGNED *)(_B)) \
	{ \
	  *(_Result) = (UINT)-1; \
	} \
	else \
	{ \
	  *(_Result) = 0; \
	} \
}

#define ETH_COMPARE_NETWORK_ADDRESSES_EQ(_A,_B, _Result) \
{ \
	if ((*(ULONG UNALIGNED *)&(_A)[2] == *(ULONG UNALIGNED *)&(_B)[2]) && \
    (*(USHORT UNALIGNED *)(_A) == *(USHORT UNALIGNED *)(_B))) \
	{ \
    *(_Result) = 0; \
	} \
	else \
	{ \
    *(_Result) = 1; \
	} \
}

#define ETH_COPY_NETWORK_ADDRESS(_D, _S) \
{ \
	*((ULONG UNALIGNED *)(_D)) = *((ULONG UNALIGNED *)(_S)); \
	*((USHORT UNALIGNED *)((UCHAR *)(_D) + 4)) = *((USHORT UNALIGNED *)((UCHAR *)(_S) + 4)); \
}

#define FDDI_LENGTH_OF_LONG_ADDRESS       6
#define FDDI_LENGTH_OF_SHORT_ADDRESS      2

#define FDDI_IS_BROADCAST(Address, AddressLength, Result)   \
  *Result = ((*(PUCHAR)(Address) == (UCHAR)0xFF) && \
  (*((PUCHAR)(Address) + 1) == (UCHAR)0xFF))

#define FDDI_IS_MULTICAST(Address, AddressLength, Result) \
  *Result = (BOOLEAN)(*(UCHAR *)(Address) & (UCHAR)0x01)

#define FDDI_IS_SMT(FcByte, Result) \
{ \
  *Result = ((FcByte & ((UCHAR)0xf0)) == 0x40); \
}


#define FDDI_COMPARE_NETWORK_ADDRESSES(_A, _B, _Length, _Result) \
{ \
	if (*(USHORT UNALIGNED *)(_A) > *(USHORT UNALIGNED *)(_B)) \
	{ \
	  *(_Result) = 1; \
	} \
	else if (*(USHORT UNALIGNED *)(_A) < *(USHORT UNALIGNED *)(_B)) \
	{ \
	  *(_Result) = (UINT)-1; \
	} \
	else if (_Length == 2) \
	{ \
	  *(_Result) = 0; \
	} \
	else if (*(ULONG UNALIGNED *)((PUCHAR)(_A) + 2) > *(ULONG UNALIGNED *)((PUCHAR)(_B) + 2)) \
	{ \
	  *(_Result) = 1; \
	} \
	else if (*(ULONG UNALIGNED *)((PUCHAR)(_A) + 2) < *(ULONG UNALIGNED *)((PUCHAR)(_B) + 2)) \
	{ \
	  *(_Result) = (UINT)-1; \
	} \
	else \
	{ \
	  *(_Result) = 0; \
	} \
}

#define FDDI_COMPARE_NETWORK_ADDRESSES_EQ(_A, _B, _Length, _Result) \
{                                                                   \
	if ((*(USHORT UNALIGNED *)(_A) == *(USHORT UNALIGNED *)(_B)) && \
	  (((_Length) == 2) || \
	    (*(ULONG UNALIGNED *)((PUCHAR)(_A) + 2) == *(ULONG UNALIGNED *)((PUCHAR)(_B) + 2)))) \
	{ \
	  *(_Result) = 0; \
	} \
	else \
	{ \
	  *(_Result) = 1; \
	} \
}

#define FDDI_COPY_NETWORK_ADDRESS(D, S, AddressLength) \
{ \
	PCHAR _D = (D); \
	PCHAR _S = (S); \
	UINT _C = (AddressLength); \
	for ( ; _C > 0 ; _D++, _S++, _C--) \
	{ \
	  *_D = *_S; \
	} \
}

#define TR_LENGTH_OF_FUNCTIONAL           4
#define TR_LENGTH_OF_ADDRESS              6

typedef ULONG TR_FUNCTIONAL_ADDRESS;
typedef ULONG TR_GROUP_ADDRESS;

#define TR_IS_NOT_DIRECTED(_Address, _Result) \
{ \
  *(_Result) = (BOOLEAN)((_Address)[0] & 0x80); \
}

#define TR_IS_FUNCTIONAL(_Address, _Result) \
{ \
	*(_Result) = (BOOLEAN)(((_Address)[0] & 0x80) && !((_Address)[2] & 0x80)); \
}

#define TR_IS_GROUP(_Address, _Result) \
{ \
  *(_Result) = (BOOLEAN)((_Address)[0] & (_Address)[2] & 0x80); \
}

#define TR_IS_SOURCE_ROUTING(_Address, _Result) \
{ \
  *(_Result) = (BOOLEAN)((_Address)[0] & 0x80); \
}

#define TR_IS_MAC_FRAME(_PacketHeader) ((((PUCHAR)_PacketHeader)[1] & 0xFC) == 0)

#define TR_IS_BROADCAST(_Address, _Result) \
{ \
	*(_Result) = (BOOLEAN)(((*(UNALIGNED USHORT *)&(_Address)[0] == 0xFFFF) || \
		(*(UNALIGNED USHORT *)&(_Address)[0] == 0x00C0)) && \
		(*(UNALIGNED ULONG  *)&(_Address)[2] == 0xFFFFFFFF)); \
}

#define TR_COMPARE_NETWORK_ADDRESSES(_A, _B, _Result) \
{ \
	if (*(ULONG UNALIGNED *)&(_A)[2] > *(ULONG UNALIGNED *)&(_B)[2]) \
	{ \
	  *(_Result) = 1; \
	} \
	else if (*(ULONG UNALIGNED *)&(_A)[2] < *(ULONG UNALIGNED *)&(_B)[2]) \
	{ \
	  *(_Result) = (UINT)-1; \
	} \
	else if (*(USHORT UNALIGNED *)(_A) > *(USHORT UNALIGNED *)(_B)) \
	{ \
	  *(_Result) = 1; \
	} \
	else if (*(USHORT UNALIGNED *)(_A) < *(USHORT UNALIGNED *)(_B)) \
	{ \
	  *(_Result) = (UINT)-1; \
	} \
	else \
	{ \
	  *(_Result) = 0; \
	} \
}

#define TR_COPY_NETWORK_ADDRESS(_D, _S) \
{ \
	*((ULONG UNALIGNED *)(_D)) = *((ULONG UNALIGNED *)(_S)); \
	*((USHORT UNALIGNED *)((UCHAR *)(_D)+4)) = *((USHORT UNALIGNED *)((UCHAR *)(_S) + 4)); \
}

#define TR_COMPARE_NETWORK_ADDRESSES_EQ(_A, _B, _Result) \
{ \
	if ((*(ULONG UNALIGNED  *)&(_A)[2] == *(ULONG UNALIGNED  *)&(_B)[2]) && \
	    (*(USHORT UNALIGNED *)&(_A)[0] == *(USHORT UNALIGNED *)&(_B)[0])) \
	{ \
    *(_Result) = 0; \
	} \
	else \
	{ \
    *(_Result) = 1; \
	} \
}

#ifdef __cplusplus
}
#endif

#endif /* __XFILTER_H */
