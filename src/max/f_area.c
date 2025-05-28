// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_area.c,v 1.1.1.1 2002/10/01 17:50:58 sdudley Exp $";
#pragma on(unreferenced)



static int near SearchArea(int search, char *input, PFAH pfahDest, BARINFO *pbi, int *piDidValid)
{
    FAH fa;
    HAFF haff;

    memset(&fa, 0, sizeof fa);
    *piDidValid = FALSE;
    strcpy(linebuf, input + 1);


    if (AreaFileFindNext(haff, &fa, FALSE) != 0)
    {
        AreaFileFindClose(haff);
        return TRUE;
    }


    while ((search == -1 ? AreaFileFindPrior : AreaFileFindNext)(haff, &fa, TRUE) == 0)
    {
        if ((fa.fa.attribs & FA_HIDDN) == 0 &&
            ValidFileArea(NULL, &fa, VA_VAL | VA_PWD | VA_EXTONLY, pbi))
        {
            *piDidValid = TRUE;
            search = 0;
            SetAreaName(usr.files, FAS(fa, name));
            CopyFileArea(pfahDest, &fa);
            break;
        }
    }

    AreaFileFindClose(haff);
    DisposeFah(&fa);


static int near ChangeToArea(char *group, char *input, int first, PFAH pfahDest)
{
    FAH fa;
    char temp[PATHLEN];
    HAFF haff;

    memset(&fa, 0, sizeof fa);

    if (!*input)
    {
        if (first)
            ListFileAreas(group, !!*group);
        else
            return TRUE;
    }
    else if ((haff = AreaFileFindOpen(haf, input, AFFO_DIV)) != NULL)
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

        InputGets(input, file_prmpt, PRM(achg_keys)[0], PRM(achg_keys)[1], PRM(achg_keys)[2]);
        cstrupr(input);

        {
            if (SearchArea(search, input, pfah, pbi, &did_valid))
                return did_valid;
        }
        else if (*input == '\'' || *input == '`' || *input == '"')
            Display_File(0, NULL, ss, PRM(misc_path), quotes_misunderstood);
        {
            char *p = input;
            int up_level = 0;


            if (*p)
                strcpy(linebuf, p);


        if (!FoundOurFileDivision(haff, div_name, &fa))
        {
            AreaFileFindReset(haff);
            div_name = "";
        }

        {
            sword this_div = div_name && *div_name ? fa.fa.division : -1;


                if (!div_name && (fa.fa.attribs & FA_DIVBEGIN))
                    continue;


                if (fa.fa.attribs & FA_DIVEND)
                {
                    if (div_name && fa.fa.division == this_div)
                        break;
                    else
                        continue;
                }


                if ((!div_name || fa.fa.division == this_div + 1) &&
                    (fa.fa.attribs & FA_HIDDN) == 0 &&
                    (((fa.fa.attribs & FA_DIVBEGIN) && PrivOK(FAS(fa, acs), TRUE)) ||
                     ValidFileArea(NULL, &fa, VA_NOVAL, &bi)))
                {
                    ParseCustomFileAreaList(&fa, div_name, PRM(file_format), headfoot, FALSE);

                    Puts(headfoot);
                    vbuf_flush();
                }

                if (halt() || MoreYnBreak(&nonstop, CYAN))
                    break;
            }
        }

        ParseCustomFileAreaList(NULL, div_name, PRM(file_footer), headfoot, FALSE);
        Puts(headfoot);

        Putc('\n');

