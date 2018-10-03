/***************************************************************************
 *   2005-2007 by Axel Gonzalez                                            *
 *   loox@e-shell.net                                                      *
 *                                                                         *
 *   This software is in the public domain. Permission to use, copy,       *
 *   modify, and distribute this software and its documentation for any    *
 *   purpose and without fee is hereby granted, without any conditions or  *
 *   restrictions. This software is provided "as is" without express or    *
 *   implied warranty.                                                     *
 *                                                                         *
 ***************************************************************************/


#include "lxXSQL.h"

#ifndef LXXSQL_CPP
#define LXXSQL_CPP



lxXSQL::lxXSQL()
{
    this->port = 0;
    this->flags= 0;
}


lxXSQL::~lxXSQL()
{


}


void lxXSQL::set_host(ovStr str)
{
    this->host = str;
}


void lxXSQL::set_port(const unsigned int n)
{
    this->port = n;
}


void lxXSQL::set_user(ovStr str)
{
    this->user = str;
}


void lxXSQL::set_password(ovStr str)
{
    this->password = str;
}


void lxXSQL::set_database(ovStr str)
{
    this->database = str;
}


void lxXSQL::set_socket(ovStr str)
{
    this->socket = str;
}


void lxXSQL::set_flags(const unsigned int n)
{
    this->flags = n;
}


void lxXSQL::set_options(ovStr str)
{
    this->options = str;
}


void lxXSQL::set_init_callback(void (*callback)(lxXSQL *db))
{
    this->init_callback = callback;
}



unsigned int lxXSQL::nr()
{
    return(this->num_rows());
}


unsigned int lxXSQL::nf()
{
    return(this->num_fields());
}


int lxXSQL::next()
{
    return(this->fetch());
}


ovStrArray lxXSQL::get_record()
{
    return(this->record);
}


ovStrArray lxXSQL::r()
{
    return(this->record);
}


ovStr lxXSQL::get_field(ovStr str)
{
    return(this->record[str]);
}


ovStr lxXSQL::f(ovStr str)
{
    return(this->record[str]);
}


#endif
