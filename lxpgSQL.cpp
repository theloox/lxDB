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


#include "lxpgSQL.h"


lxSQL::lxSQL()
{
    this->res = NULL;

    //this->pgsql = new(PGconn);

}


lxSQL::lxSQL(PGconn *r)
{
    this->res = NULL;

    //if (r == NULL)
    //    this->pgsql = new(PGconn);
}


lxSQL::~lxSQL()
{
    if (this->res != NULL)
        PQclear(this->res);

    PQfinish(this->pgsql);
    //delete(this->pgsql);
}


int lxSQL::connect()
{
    ovStr port_str;

    if (this->port != 0)
        port_str.printf("%d", this->port);


    if ((this->pgsql = PQsetdbLogin(this->host, port_str, this->options, NULL, this->database, this->user, this->password)) == NULL)
        return(1);

    if (PQstatus(this->pgsql) != CONNECTION_OK)
        return(2); 

    return(0);
}


int lxSQL::query(ovStr &q)
{

    PGresult *r;
    ExecStatusType rs;

    r = PQexec(this->pgsql, q);

    if (r == NULL)
        return(1);

    if (this->res != NULL) {
        PQclear(this->res);
        this->res = NULL;
    }

    this->res = r;

    rs = PQresultStatus(r);


    if (rs == PGRES_COMMAND_OK)
        return(0);

    if (rs != PGRES_TUPLES_OK)
        return(2);

    //this->res = mysql_store_result(this->mysql);

    this->fields.Clean();
    this->record.Clean();


    this->fetch_fields();


    return(0);
}


int lxSQL::query(const char *q)
{

    PGresult *r;
    ExecStatusType rs;


    this->curr_row = 0;

    r = PQexec(this->pgsql, q);

    if (r == NULL)
        return(1);

    if (this->res != NULL) {
        PQclear(this->res);
        this->res = NULL;
    }

    this->res = r;

    rs = PQresultStatus(r);


    if (rs == PGRES_COMMAND_OK)
        return(0);

    if (rs != PGRES_TUPLES_OK)
        return(2);

    //this->res = mysql_store_result(this->mysql);

    this->fields.Clean();
    this->record.Clean();


    this->fetch_fields();


    return(0);
}


unsigned int lxSQL::num_rows()
{
    if (this->res == NULL)
        return(0);

    return(PQntuples(this->res));
}


unsigned int lxSQL::num_fields()
{
    if (this->res == NULL)
        return(0);

    return(PQnfields(this->res));
}


ovStrArray lxSQL::fetch_fields()
{
    unsigned int num_fields;
    unsigned int i;

    char *fi;


    if (this->res == NULL)
        return(this->fields);


    if (!this->fields.Count()) {
        num_fields = PQnfields(this->res);

        this->fields.Clean();

        for (i = 0; i < num_fields; i++) {

            fi = PQfname(this->res, i);

            if (fi == NULL)
                break;

            this->fields.Add(fi);
        }
    }

    return(this->fields);
}


int lxSQL::fetch_row()
{
    unsigned int num_fields;
    unsigned int num_rows;
    unsigned int i;

    ovStrArray r;


    i = 0;


    this->record.Clean();

    if (this->res == NULL)
        return(i);

    num_fields = this->nf();

    num_rows = this->nr();


    if (this->curr_row >= num_rows)
        return(i);

    for (i = 0; i < num_fields; i++) {
        this->record.Add(PQgetvalue(this->res, this->curr_row, i));
    }

    this->curr_row++;

    return(i);
}


int lxSQL::fetch()
{
    unsigned int num_fields;
    unsigned int num_rows;
    unsigned int i;


    i = 0;

    this->record.Clean();

    if (this->res == NULL)
        return(i);

    num_fields = this->nf();

    num_rows = this->nr();


    if (this->curr_row >= num_rows)
        return(i);

    for (i = 0; i < num_fields; i++) {
        this->record.Add(PQgetvalue(this->res, this->curr_row, i), this->fields[i]);
    }

    this->curr_row++;

    return(i);
}


ovStr lxSQL::result()
{
    this->fetch_row();

    return(this->record[(unsigned int)0]);
}


ovStr lxSQL::result(unsigned int n)
{
    this->fetch_row();

    return(this->record[n]);
}


long int lxSQL::insert_id()
{
    return(PQoidValue(this->res));
}

ovStr lxSQL::error()
{
    ovStr r;

    r = PQresultErrorMessage(this->res);

    return(r);
}

ovStr lxSQL::escape(ovStr str)
{

    str.replace("\\", "\\\\");
    str.replace("\'", "\\\'");
    str.replace("\"", "\\\"");

    return(str);
}
