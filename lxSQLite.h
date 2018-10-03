/***************************************************************************
 *   2005-2006 by Axel Gonzalez                                            *
 *   loox@e-shell.net                                                      *
 *                                                                         *
 *   This software is in the public domain. Permission to use, copy,       *
 *   modify, and distribute this software and its documentation for any    *
 *   purpose and without fee is hereby granted, without any conditions or  *
 *   restrictions. This software is provided "as is" without express or    *
 *   implied warranty.                                                     *
 *                                                                         *
 ***************************************************************************/


#include <sqlite3.h>

//#include "lxXSQL.cpp"
#include "lxXSQL.h"

#ifndef LXSQL_H
#define LXSQL_H

class lxSQL : public lxXSQL {

private:

    sqlite3 *db;
    sqlite3_stmt *pStmt;

    unsigned int nrows;
    ovArray<ovStrArray> all;
    unsigned int nall;
    

    //int CallBack(void *pArg, int argc, char **argv, char **columnNames);

public:

    lxSQL();
    ~lxSQL();


    int connect();

    int query(ovStr q);

    unsigned int num_rows();

    unsigned int num_fields();


    ovStrArray fetch_fields();
    int fetch_row();
    int fetch();

    ovStr result();

    long int insert_id();

    ovStr error();

    ovStr escape(ovStr str);
};

#endif
