// SPDX-License-Identifier: GPL-2.0-or-later


#define NOVARS
#define NOVER
#define MAX_NOPROTO

#include "max.h"
#include "prog.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static char *colon = ":";
static char *slash = "/";

void _fast ParseNNN(char *netnode, NETADDR *pn, word all)
{
    ParseNN(netnode, &pn->zone, &pn->net, &pn->node, &pn->point, all);
}

void _fast Parse_NetNode(char *netnode, word *zone, word *net, word *node, word *point)
{
    ParseNN(netnode, zone, net, node, point, FALSE);
}

void _fast ParseNN(char *netnode, word *zone, word *net, word *node, word *point, word all)
{
    char *p;

    p = netnode;

    if (all && point)
        *point = POINT_ALL;


    if (strchr(netnode, ':'))
    {
        if (zone)
        {

    if (p && *p)
    {
        if (strchr(netnode, '/'))
        {
            if (net)
            {

            if (strchr(netnode, ':') == NULL && zone)
                *zone = ZONE_ALL;

            *net = NET_ALL;
            *node = NODE_ALL;
            p += 3;
        }
    }

        {
            *node = NODE_ALL;


    if (p && *p == '.')
    {
        p++;

        if (point)
        {
            if (!p && *netnode == '.')
                p = netnode + 1;

            if (p && *p)
            {
                *point = atoi(p);

