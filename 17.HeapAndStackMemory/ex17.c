#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *msg);
void Address_print(struct Address * addr);
void Database_load();
struct Connection *Database_open(const char *filename, char mode);
void Database_close();
void Database_write();
void Database_create();
void Database_set(int id, const char *name, const char *email);
void Database_get(int id);
void Database_delete(int id);
void Database_list();

static struct Connection *conn;

void die(const char *msg)
{
    if (errno) 
        perror(msg);
    else
        printf("ERROR: %s\n", msg);
    
    Database_close();
    exit(1);
}

void Address_print(struct Address * addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load()
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);

    if (rc != 1)
        die("Failed to load database");
}

struct Connection *Database_open(const char *filename, char mode)
{
    conn = malloc(sizeof(struct Connection));
    if (!conn)
        die("Memory error");
    
    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
        die("Memory error");

    if (mode == 'c')
        conn->file = fopen(filename, "w");
    else
    {
        conn->file = fopen(filename, "r+");
        if (conn->file)
            Database_load();
    }

    if (!conn->file)
        die("Failed to open the file");

    return conn;
}

void Database_close()
{
    if (conn)
    {
        if (conn->file)
            fclose(conn->file);
        if (conn->db)
            free(conn->db);
        free(conn);
    }
}

void Database_write()
{
    rewind(conn->file);
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);

    if (rc != 1)
        die("Failed to write database.");

    rc = fflush(conn->file);
    if (rc == -1)
        die("Cannot flush database.");
}

void Database_create()
{
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        struct Address addr = { .id = i, .set = 0 };
        conn->db->rows[i] = addr; 
    }
}

void Database_set(int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set)
        die("Already set, delete it first");

    char *res = strncpy(addr->name, name, MAX_DATA);
    if (!res) die("Name copy failed");
    addr->name[MAX_DATA - 1] = '\0';

    res = strncpy(addr->email, email, MAX_DATA);
    if (!res) die("Email copy failed");
    addr->email[MAX_DATA - 1] = '\0';

    addr->id = id;
    addr->set = 1;
}

void Database_get(int id)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set)
        Address_print(addr);
    else
        die("ID is not set");
}

void Database_delete(int id)
{
    struct Address *addr = &conn->db->rows[id];
    addr->set = 0;
}

void Database_list()
{
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        struct Address *addr = &conn->db->rows[i];
        if (addr->set)
        {
            Address_print(addr);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    
    conn = Database_open(filename, action);
    int id = 0;

    if (argc > 3) id = atoi(argv[3]);
    if (id >= MAX_ROWS) die("There's not that many records.");

    switch (action)
    {
        case 'c':
        {    
            Database_create();
            Database_write();
            break;
        }
        case 'g':
        {
            if (argc != 4) die("Need an id to get");

            Database_get(id);
            break;
        }
        case 's':
        {
            if (argc != 6) die("Need id, name, email to set");

            Database_set(id, argv[4], argv[5]);
            Database_write();
            break;
        }
        case 'd':
        {
            if (argc != 4) die("Need id to delete");

            Database_delete(id);
            Database_write();
            break;
        }
        case 'l':
        {
            Database_list();
            break;
        }
        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list");
    }
    
    Database_close();
    return 0;
}
