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


#include <ovStr/ovStr.h>
#include <ovStr/ovStrArray.h>
#include <ovStr/ovArray.h>


#ifndef LXXSQL_H
#define LXXSQL_H


class lxXSQL {

protected:

    ovStr host;
    unsigned int port;
    ovStr user;
    ovStr password;
    ovStr database;
    ovStr socket;
    unsigned int flags;
    ovStr options;

    void (*init_callback)(lxXSQL *db);



    ovStrArray fields;
    ovStrArray record;

public:

    lxXSQL();
    ~lxXSQL();

    void set_host(ovStr str);
    void set_port(const unsigned int n);
    void set_user(ovStr str);
    void set_password(ovStr str);
    void set_database(ovStr str);
    void set_socket(ovStr str);
    void set_flags(const unsigned int n);
    void set_options(ovStr str);

    void set_init_callback(void (*callback)(lxXSQL *db));


    virtual int connect() = 0;

    virtual int query(ovStr &q) = 0;
    virtual int query(const char *q) = 0;

    virtual unsigned int num_rows() = 0;
    unsigned int nr();

    virtual unsigned int num_fields() = 0;
    unsigned int nf();

    virtual ovStrArray fetch_fields() = 0;
    virtual int fetch_row() = 0;
    virtual int fetch() = 0;
    int next();
    ovStrArray get_record();
    ovStrArray r();
    ovStr get_field(ovStr str);
    ovStr f(ovStr str);

    virtual ovStr result() = 0;
    virtual ovStr result(unsigned int n) = 0;

    virtual long int insert_id() = 0;

    virtual ovStr error() = 0;

    virtual ovStr escape(ovStr str) = 0;

};

#endif
