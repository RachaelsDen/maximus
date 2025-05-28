// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __EMSI_H_DEFINED
#define __EMSI_H_DEFINED

void EmsiInitHandshake(void);
word EmsiCheck(int ch);
void EmsiTxFrame(word ft);

#define EMSI_MAX 2048

enum _emsi_frame
{
    EMSI_ACK = 1,
    EMSI_NAK,
    EMSI_IRQ,
    EMSI_IIR,
    EMSI_ICI,
    EMSI_ISI,
    EMSI_ISM,
    EMSI_CHT,
    EMSI_TCH,
    EMSI_BAD
};


struct _efield
{
    char *where;
    word maxlen;
};

#define EC_NAME_LEN 35
#define EC_ALIAS_LEN 20
#define EC_CITY_LEN 35
#define EC_PHDATA_LEN 14
#define EC_PHVOICE_LEN 14
#define EC_PWD_LEN 14
#define EC_DOB_LEN 8
#define EC_CRT_LEN 60
#define EC_PROTO_LEN 60
#define EC_CAP_LEN 60
#define EC_REQ_LEN 60
#define EC_SW_LEN 40
#define EC_XLAT_LEN 1

struct _emsi_caller
{
    char ec_name[EC_NAME_LEN];
    char ec_alias[EC_ALIAS_LEN];
    char ec_city[EC_CITY_LEN];
    char ec_phdata[EC_PHDATA_LEN];
    char ec_phvoice[EC_PHVOICE_LEN];
    char ec_pwd[EC_PWD_LEN];
    char ec_dob[EC_DOB_LEN];
    char ec_crt[EC_CRT_LEN];
    char ec_proto[EC_PROTO_LEN];
    char ec_cap[EC_CAP_LEN];
    char ec_req[EC_REQ_LEN];
    char ec_sw[EC_SW_LEN];
    char ec_xlat[EC_XLAT_LEN];
};

#endif
