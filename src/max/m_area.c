// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_area.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)



static int near SearchArea(int search, char *input, PMAH pmahDest, BARINFO *pbi, int *piDidValid)
{
    MAH ma;
    HAFF haff;

    memset(&ma, 0, sizeof ma);

    *piDidValid = FALSE;
    strcpy(linebuf, input + 1);


    if (AreaFileFindNext(haff, &ma, FALSE) != 0)
    {
        AreaFileFindClose(haff);
        return TRUE;
    }


    while ((search == -1 ? AreaFileFindPrior : AreaFileFindNext)(haff, &ma, TRUE) == 0)
    {
        if ((ma.ma.attribs & MA_HIDDN) == 0 &&
            ValidMsgArea(NULL, &ma, VA_VAL | VA_PWD | VA_EXTONLY, pbi))
        {
            *piDidValid = TRUE;
            search = 0;
            SetAreaName(usr.msg, MAS(ma, name));
            CopyMsgArea(pmahDest, &ma);
            break;
        }
    }

    AreaFileFindClose(haff);
    DisposeMah(&ma);


static int near ChangeToArea(char *group, char *input, int first, PMAH pmahDest)
{
    MAH ma;
    char temp[PATHLEN];
    HAFF haff;

    memset(&ma, 0, sizeof ma);

    if (!*input)
    {
        if (first)
            ListMsgAreas(group, FALSE, !!*group);
        else
            return TRUE;
    }
    else if ((haff = AreaFileFindOpen(ham, input, AFFO_DIV)) != NULL)
    {
        int rc;


        if (*temp)
            strcat(temp, dot);

            strcpy(input, temp);
        else
        {
    int did_valid = FALSE;

    WhiteN();

    for (;;)
    {
        int search = 0;

        Puts(WHITE);

        InputGets(input, msg_prmpt, PRM(achg_keys)[0], PRM(achg_keys)[1], PRM(achg_keys)[2]);
        cstrupr(input);

        {
            if (SearchArea(search, input, pmah, pbi, &did_valid))
                return did_valid;
        }
        else if (*input == '\'' || *input == '`' || *input == '"')
            Display_File(0, NULL, ss, PRM(misc_path), quotes_misunderstood);
        {
            char *p = input;
            int up_level = 0;


            if (*p)
                strcpy(linebuf, p);


static int near FoundOurMsgDivision(HAFF haff, char *division, PMAH pmah)
{
    if (!division || *division == 0)
        return TRUE;

    return (AreaFileFindNext(haff, pmah, FALSE) == 0 && (pmah->ma.attribs & MA_DIVBEGIN) &&
            eqstri(PMAS(pmah, name), division));
}

void ListMsgAreas(char *div_name, int do_tag, int show_help)
{
    BARINFO bi;
    MAH ma;
    HAFF haff = 0;
    char nonstop = FALSE;
    char headfoot[PATHLEN];
    char *file;
    int ch;

    memset(&ma, 0, sizeof ma);

    if (*PRM(msgarea_list) && !do_tag)
    {

        if (!div_name || *div_name == 0 ||
            (haff = AreaFileFindOpen(ham, div_name, AFFO_DIV)) == NULL ||
            !FoundOurMsgDivision(haff, div_name, &ma) || eqstri(MAS(ma, path), dot))
        {
            file = PRM(msgarea_list);
        }
        else
        {
            file = MAS(ma, path);
        }

        Display_File(0, NULL, file);
    }
    else
    {
        Puts(CLS);

        display_line = display_col = 1;

        ParseCustomMsgAreaList(NULL, div_name, PRM(msg_header), headfoot, TRUE, '*');
        Puts(headfoot);

        if ((haff = AreaFileFindOpen(ham, div_name, AFFO_DIV)) == NULL)
            return;


            AreaFileFindChange(haff, NULL, AFFO_DIV);

            while (AreaFileFindNext(haff, &ma, FALSE) == 0)
            {

                if (!div_name && (ma.ma.attribs & MA_DIVBEGIN))
                    continue;


                if (ma.ma.attribs & MA_DIVEND)
                {
                    if (div_name && ma.ma.division == this_div)
                        break;
                    else
                        continue;
                }


                if ((!div_name || ma.ma.division == this_div + 1) &&
                    (ma.ma.attribs & MA_HIDDN) == 0 &&
                    (((ma.ma.attribs & MA_DIVBEGIN) && PrivOK(MAS(ma, acs), TRUE)) ||
                     ValidMsgArea(NULL, &ma, VA_NOVAL, &bi)))
                {
                    ch = !do_tag ? '*' : TagQueryTagList(&mtm, MAS(ma, name)) ? '@' : ' ';

                    ParseCustomMsgAreaList(&ma, div_name, PRM(msg_format), headfoot, FALSE, ch);

                    Puts(headfoot);
                    vbuf_flush();
                }

                if (halt())
                    break;

                if ((!do_tag && MoreYnBreak(&nonstop, CYAN)) || (do_tag && TagMoreBreak(&nonstop)))
                {
                    break;
                }
            }
        }

        ParseCustomMsgAreaList(NULL, div_name, PRM(msg_footer), headfoot, FALSE, '*');
        Puts(headfoot);

        Putc('\n');

