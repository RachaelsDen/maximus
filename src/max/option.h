// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef OPTION_H_DEFINED__
#define OPTION_H_DEFINED__


    CHANGE_BLOCK = 600,
    chg_city,
    chg_password,
    chg_help,
    chg_nulls,
    chg_width,
    chg_length,
    chg_tabs,
    chg_more,
    chg_video,
    chg_editor,
    chg_clear,
    chg_ibm,
    chg_phone,
    chg_realname,
    chg_hotkeys,
    chg_language,
    chg_userlist,
    chg_protocol,
    chg_fsr,
    chg_archiver,
    chg_rip,

    EDIT_BLOCK = 700,
    edit_save,
    edit_abort,
    edit_list,
    edit_edit,
    edit_insert,
    edit_delete,
    edit_continue,
    edit_to,
    edit_from,
    edit_subj,
    edit_handling,
    read_diskfile,
    edit_quote,



} option;

#ifdef SILT

struct _st
{
    option opt;
    char *token;
};

#ifdef SILT_INIT

struct _st silt_table[] = {{msg_reply_area, "msg_reply_area"},
                           {msg_dload_attach, "msg_download_attach"},
                           {msg_track, "msg_track"},
                           {link_menu, "link_menu"},
                           {o_return, "return"},
                           {mex, "mex"},
                           {msg_restrict, "msg_restrict"},
                           {climax, "climax"},
                           {msg_toggle_kludges, "msg_kludges"},
                           {msg_unreceive, "msg_unreceive"},
                           {msg_upload_qwk, "msg_upload_qwk"},
                           {chg_archiver, "chg_archiver"},
                           {msg_edit_user, "msg_edit_user"},
                           {chg_fsr, "chg_fsr"},
                           {msg_current, "msg_current"},
                           {msg_browse, "msg_browse"},
                           {chg_userlist, "chg_userlist"},
                           {chg_protocol, "chg_protocol"},
                           {msg_tag, "msg_tag"},
                           {chg_language, "chg_language"},
                           {file_tag, "file_tag"},
                           {o_chat_cb, "chat_cb"},
                           {o_chat_pvt, "chat_pvt"},
                           {chg_hotkeys, "chg_hotkeys"},
                           {msg_change, "msg_change"},
                           {chat_toggle, "chat_toggle"},
                           {o_page, "chat_page"},
                           {o_menupath, "menupath"},
                           {display_menu, "display_menu"},
                           {display_file, "display_file"},
                           {xtern_erlvl, "xtern_erlvl"},
                           {xtern_dos, "xtern_dos"},
                           {xtern_dos, "xtern_os2"},
                           {xtern_dos, "xtern_shell"},
                           {xtern_run, "xtern_run"},
                           {xtern_chain, "xtern_chain"},
                           {xtern_concur, "xtern_concur"},
                           {key_poke, "key_poke"},
                           {clear_stacked, "clear_stacked"},
                           {goodbye, "goodbye"},
