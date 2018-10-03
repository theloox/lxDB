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


#if defined(USE_MYSQL)
    #include "lxMySQL.h"
#elif defined(USE_PGSQL)
    #include "lxpgSQL.h"
#else
    #include "lxSQLite.h"
#endif
