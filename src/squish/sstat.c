// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sstat.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)


static void near ReadArea(int fd, struct _ahlist *al, struct _tarea *ta)
{
    struct _tnode tn;
    struct _stlist *sl;
    struct _nodtot *nt;

    al->in_msgs += ta->in_msgs;
    al->in_bytes += ta->in_bytes / 100;

    while (ta->n_nodes--)
    {
        if (read(fd, (char *)&tn, sizeof tn) != sizeof tn)
            return;

#ifdef DEBUG
        printf("    Node         = %s\n", Address(&tn.node));
        printf("        OutMsgs  = %ld\n", tn.out_msgs);
        printf("        OutBytes = %ld\n", tn.out_bytes);
#endif


        for (nt = nodtot; nt; nt = nt->next)
            if (MatchNN(&nt->node, &tn.node))
                break;


        if (read(fd, (char *)&tarea, sizeof tarea) != sizeof tarea)
            break;

#ifdef DEBUG
        printf("Area: %s\n", tarea.tag);
        printf(" InMsgs: %lu\n", tarea.in_msgs);
        printf("InBytes: %lu\n", tarea.in_bytes);
#endif

        for (al = ahlist; al; al = al->next)
            if (eqstri(tarea.tag, al->tag))
                break;


        if (total_in_bytes == 0 || total_in_msgs == 0 || al->total_out_bytes == 0 ||
            al->total_out_msgs == 0)
        {
            printf("   (No outbound traffic for specified nodes.)\n");
            continue;
        }

        printf("   Node            Byte Out MsgOut %% Bytes %%  Msgs %% TBCst %% TMCst\n");
        printf("   --------------- -------- ------ ------- ------- ------- -------\n");

        for (sl = al->slist; sl; sl = sl->next)
        {
            double area_percent_bytes, area_percent_msgs;

            area_percent_bytes = ((double)sl->out_bytes / (double)al->total_out_bytes) *
                                 ((double)al->in_bytes / (double)total_in_bytes) * (double)100;

            area_percent_msgs = ((double)sl->out_msgs / (double)al->total_out_msgs) *
                                ((double)al->in_msgs / (double)total_in_msgs) * (double)100;

            printf("   %-15s %8ld %6ld %3d.%02d%% %3d.%02d%% %6.02f%% %6.02f%%\n",
                   Address(&sl->node), sl->out_bytes * 100L, sl->out_msgs,
                   Percent(sl->out_bytes, al->total_out_bytes),
                   Percent(sl->out_msgs, al->total_out_msgs), (float)area_percent_bytes,
                   (float)area_percent_msgs);

            for (nt = nodtot; nt; nt = nt->next)
                if (MatchNN(&nt->node, &sl->node))
                {
                    nt->total_percent_bytes += area_percent_bytes;
                    nt->total_percent_msgs += area_percent_msgs;
                    break;
                }
        }
    }

    printf("\nNODE TOTALS:\n\n");

    printf("   Node             %%Bytes %% Msgs\n");
    printf("   ---------------- ------ ------\n");

    for (nt = nodtot; nt; nt = nt->next)
    {
        printf("   %-15s  %05.02f%% %05.02f%%\n", Address(&nt->node), nt->total_percent_bytes,
               nt->total_percent_msgs);
    }
}

static void near ParseConfigLine(char *line)
{
    static char *cfgdelim = " \t\n\r,";
    char *s;


    s = strtok(line, cfgdelim);


        while ((s = strtok(NULL, cfgdelim)) != NULL)
        {
            node = smalloc(sizeof(struct _nodelist));

            node->n = last;

            ParseNN(s, &node->n.zone, &node->n.net, &node->n.node, &node->n.point, FALSE);

            last = node->n;

