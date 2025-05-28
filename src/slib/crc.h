// SPDX-License-Identifier: GPL-2.0-or-later



#define CRC32POLY 0xedb88320L

#define CRC16CCITT 0x1021
#define CRC16CCITTREV 0x8408
#define CRC16 0x8005
#define CRC16REV 0xa001

#define updcrc32(c, crc) xcrc32(c, crc)

#define updcrc16(cp, crc) (crctab[((crc >> 8) & 255) ^ (byte)cp] ^ (crc << 8))
