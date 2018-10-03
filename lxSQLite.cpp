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


#include "lxSQLite.h"


//create database general
lxSQL::lxSQL()
{
    db = NULL;
    init_callback = NULL;

    nrows = 0;
    nall = 0;
}


//close db
lxSQL::~lxSQL()
{
    sqlite3_close(db);
}


int lxSQL::connect()
{
    int op, not_exists;
    FILE *f;


    not_exists = 0;

    if (database == "") {
        //database = ":memory";
    }
    else {
        if ((f = fopen(database,"r")) == NULL)
            not_exists = 1;
        else
            fclose(f);
    }

    op = sqlite3_open(database, &db);

    if (op != SQLITE_OK) {
        db = NULL;
        return(0);
    }

    if (not_exists && init_callback != NULL)
        this->init_callback(this);

    return(1);
}


int lxSQL::query(ovStr q)
{
    char *pzTail;
    ovStrArray rec;

    int i, nf;
    int r;

    r = 0;


    pStmt = NULL;


    nrows = 0;

    nall = 0;
    all.Clean();

    fields.Clean();
    record.Clean();


    if (db == NULL)
        return(SQLITE_ERROR);

    //remove spaces... they may cause core dumps
    q.trim();

    if (q == "")
        return(SQLITE_ERROR);


    //init vm
    r = sqlite3_prepare(db, (const char *)q, q.Len(), &pStmt, (const char **)&pzTail);


    //fetch_fields();
    //nf = num_fields();

    while ((r = sqlite3_step(pStmt)) == SQLITE_ROW)
    {
        if (fields.IsEmpty()) {
            fetch_fields();
            nf = num_fields();
        }

        rec.Clean();

        rec.Alloc(nf);

        for (i = 0; i < nf; i++)
        {
            rec.Add((const char *)sqlite3_column_text(pStmt, i));
        }

        nrows++;
        all.Add(rec);
    }


    //end vm
    sqlite3_finalize(pStmt);


    if (r != SQLITE_OK || pStmt == NULL)
    {
#ifdef DEBUG
        //sqlite_freemem(pzErrMsg);
#endif
        return(r);
    }


#ifdef DEBUG
    if (r == SQLITE_ERROR) {
        //error = 
        printf("");
    }
#endif

    return(SQLITE_OK);

}


unsigned int lxSQL::num_rows()
{
    if (pStmt == NULL)
        return(0);

    return(nrows);

}


unsigned int lxSQL::num_fields()
{
    if (!fields.IsEmpty())
        return(fields.Count());

    if (pStmt == NULL)
        return(0);

    return(sqlite3_column_count(pStmt));
}


ovStrArray lxSQL::fetch_fields()
{
    unsigned int nf;
    unsigned int i;


    if (db == NULL)
        return(fields);

    if (pStmt == NULL)
        return(fields);


    if (!this->fields.Count()) {

        nf = num_fields();

        fields.Clean();

        fields.Alloc(nf);

        for (i = 0; i < nf; i++) {
            fields.Add(sqlite3_column_name(pStmt, i));
        }
    }

    return(fields);
}


int lxSQL::fetch_row()
{

    record.Clean();

    if (pStmt == NULL)
        return(0);

    if (nall >= nrows)
        return(0);

    record = all[nall++];

    return(nall);
}


int lxSQL::fetch()
{
    unsigned int nf;
    unsigned int i, r;


    record.Clean();

    if (pStmt == NULL)
        return(0);

    if (nrows == 0)
        return(0);

    if (nall >= nrows)
        return(0);

    nf = num_fields();

    for (i = 0; i < nf; i++) {
        record.Add(all[nall][i], fields[i]);
    }

    nall++;

    return(nall);
}


ovStr lxSQL::result()
{
    this->fetch_row();

    return(this->record[(unsigned int)0]);
}


long int lxSQL::insert_id()
{
    return(sqlite3_last_insert_rowid(db));
}


ovStr lxSQL::error()
{
    ovStr r;

    r = sqlite3_errmsg(db);

    return(r);
}

ovStr lxSQL::escape(ovStr str)
{
    str.replace("'","''");
    return(str);
}
