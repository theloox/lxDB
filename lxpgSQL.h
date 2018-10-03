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


#include <libpq-fe.h>


#include "lxXSQL.h"

#ifndef LXSQL_H
#define LXSQL_H

class lxSQL : public lxXSQL {

private:

    PGconn *pgsql;
    PGresult *res;

    unsigned int curr_row;

public:

    lxSQL();
    lxSQL(PGconn *r);
    ~lxSQL();


    int connect();

    int query(ovStr &q);
    int query(const char *q);

    unsigned int num_rows();

    unsigned int num_fields();


    ovStrArray fetch_fields();
    int fetch_row();
    int fetch();

    ovStr result();
    ovStr result(unsigned int n);

    long int insert_id();

    ovStr error();

    ovStr escape(ovStr str);
};

#endif
