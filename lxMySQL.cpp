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


#include "lxMySQL.h"


lxSQL::lxSQL()
{
    this->res = NULL;

    this->mysql = new(MYSQL);

    mysql_init(this->mysql);
}


lxSQL::lxSQL(MYSQL *r)
{
    this->res = NULL;

    if (r == NULL)
        this->mysql = new(MYSQL);

    mysql_init(this->mysql);
}


lxSQL::~lxSQL()
{
    if (this->res != NULL)
        mysql_free_result(this->res);

    delete(this->mysql);
}


int lxSQL::connect()
{
    if (mysql_real_connect(this->mysql, this->host, this->user, this->password, this->database, this->port, (this->socket == "" ? NULL : (const char *)this->socket), this->flags))
        return(1);

    return(0);
}


int lxSQL::query(ovStr q)
{

    int r;

    r = mysql_query(this->mysql, q);

    if (r != 0)
        return(r);

    if (this->res != NULL) {
        mysql_free_result(this->res);
        this->res = NULL;
    }


    if (!mysql_field_count(this->mysql))
        return(0);


    this->res = mysql_store_result(this->mysql);

    this->fields.Clean();
    this->record.Clean();


    this->fetch_fields();


    return(0);
}


unsigned int lxSQL::num_rows()
{
    if (this->res == NULL)
        return(0);

    return(mysql_num_rows(this->res));
}


unsigned int lxSQL::num_fields()
{
    if (this->res == NULL)
        return(0);

    return(mysql_num_fields(this->res));
}


ovStrArray lxSQL::fetch_fields()
{
    unsigned int num_fields;
    unsigned int i;

    MYSQL_FIELD *fi;


    if (this->res == NULL)
        return(this->fields);


    if (!this->fields.Count()) {
        num_fields = mysql_num_fields(this->res);

        fi = mysql_fetch_fields(this->res);


        this->fields.Clean();

        for (i = 0; i < num_fields; i++) {
            this->fields.Add(fi[i].name);
        }
    }

    return(this->fields);
}


int lxSQL::fetch_row()
{
    unsigned int num_fields;
    unsigned int i;

    ovStrArray r;

    MYSQL_ROW row;


    i = 0;

    this->record.Clean();

    if (this->res == NULL)
        return(i);

    num_fields = mysql_num_fields(this->res);

    if (row = mysql_fetch_row(this->res)) {
        for (i = 0; i < num_fields; i++) {
            this->record.Add(row[i] ? row[i] : "");
        }
    }

    return(i);
}


int lxSQL::fetch()
{
    unsigned int num_fields;
    unsigned int i;

    MYSQL_ROW row;


    i = 0;

    this->record.Clean();

    if (this->res == NULL)
        return(i);

    num_fields = mysql_num_fields(this->res);

    if (row = mysql_fetch_row(this->res)) {
        for (i = 0; i < num_fields; i++) {
            this->record.Add((row[i] ? row[i] : ""), this->fields[i]);
        }
    }

    return(i);
}


ovStr lxSQL::result()
{
    this->fetch_row();

    return(this->record[(unsigned int)0]);
}

long int lxSQL::insert_id()
{
    return(mysql_insert_id(this->mysql));
}

ovStr lxSQL::error()
{
    ovStr r;

    r = mysql_error(this->mysql);

    return(r);
}

ovStr lxSQL::escape(ovStr str)
{

    str.replace("\\", "\\\\");
    str.replace("\'", "\\\'");
    str.replace("\"", "\\\"");

    return(str);
}
