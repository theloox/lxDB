/***************************************************************************
 *   2005-2007 by Axel Gonzalez                                                 *
 *   loox@e-shell.net                                                      *
 *                                                                         *
 *   This software is in the public domain. Permission to use, copy,       *
 *   modify, and distribute this software and its documentation for any    *
 *   purpose and without fee is hereby granted, without any conditions or  *
 *   restrictions. This software is provided "as is" without express or    *
 *   implied warranty.                                                     *
 *                                                                         *
 ***************************************************************************/

#include "lxXSQL.cpp"

#if defined(USE_MYSQL)
    #include "lxMySQL.cpp"
#elif defined(USE_PGSQL)
    #include "lxpgSQL.cpp"
#else
    #include "lxSQLite.cpp"
#endif
