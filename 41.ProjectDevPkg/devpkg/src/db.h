#ifndef _DEVPKG_DB_H
#define _DEVPKG_DB_H

#include <stdbool.h>

#define DB_FILE "/usr/local/.devpkg/db"
#define DB_DIR "/usr/local/.devpkg"

#define DB_ERR -1
#define DB_OK 0
#define DB_NOT_FOUND 0
#define DB_FOUND 1

int DB_init();
int DB_list();
int DB_update(const char *url);
int DB_find(const char *url);

#endif // _DEVPKG_DB_H
