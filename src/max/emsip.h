// SPDX-License-Identifier: GPL-2.0-or-later


static char emsi_seq[] = "**EMSI_";

static struct _emsi_caller eclr;

static word near EmsiGotInit(int ch);
static word near EmsiGetHeader(char *frame);
static word near EmsiReadLine(void);
static word near EmsiCalcCrc16(word len);
static dword near EmsiCalcCrc32(word len);
static word near EmsiCrcOK(word len);
static word near EmsiFtACK(void);
static word near EmsiFtNAK(void);
static word near EmsiFtIIR(void);
static word near EmsiFtICI(void);
static word near EmsiPollFrame(long t);
static word near EmsiFtBAD(void);
static word near EmsiGetField(char **buf, char *field, word len);
static word near EmsiTxBytes(char *buf, word len);
static void near EmsiBldA1(char *fmt, ...);
static void near EmsiBldISI(void);
static void near EmsiBldISM(void);
static void near EmsiBldBAD(void);

static struct _eft eft[] = {{"ACK", EMSI_ACK, EmsiFtACK, NULL, 16},
                            {"NAK", EMSI_NAK, EmsiFtNAK, NULL, 16},
                            {"", EMSI_BAD, EmsiFtBAD, EmsiBldBAD}};

static struct _efield ici_fields[] = {
    {eclr.ec_name, EC_NAME_LEN},       {eclr.ec_alias, EC_ALIAS_LEN},
    {eclr.ec_city, EC_CITY_LEN},       {eclr.ec_phdata, EC_PHDATA_LEN},
    {eclr.ec_phvoice, EC_PHVOICE_LEN}, {eclr.ec_pwd, EC_PWD_LEN},
    {eclr.ec_dob, EC_DOB_LEN},         {eclr.ec_crt, EC_CRT_LEN},
    {eclr.ec_proto, EC_PROTO_LEN},     {eclr.ec_cap, EC_CAP_LEN},
    {eclr.ec_req, EC_REQ_LEN},         {eclr.ec_sw, EC_SW_LEN},
    {eclr.ec_xlat, EC_XLAT_LEN},       {NULL, 0},
};
