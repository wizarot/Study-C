#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// 设置文档大小
#define MAX_DATA 512
#define MAX_ROWS 10

// 结构体 数据结构
struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];

};

// 结构体 数据库
struct Database {
    // Address类型的数组
    struct Address rows[MAX_ROWS];
};

// 连接 结构体
struct Connection {
    // 文件操作指针?
    FILE *file;
    // 指向数据库结构体指针
    struct Database *db;
};

// 失败就让它直接崩溃
void die(const char *message) {
    if (errno) {
        // 不清楚到底什么情况会出发这种情况的错误?
        perror(message);
    } else {
        printf("ERROR: %s \n", message);
    }

    exit(1);
}

// 打印一行数据记录
void Address_print(struct Address *addr) {
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}
// 读取数据库文件中的数据
void Database_load(struct Connection *conn) {
    // 从文件流中读取数据
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    //  读取失败的话,那么直接结束.
    if (rc != 1) die("Faild to load Database.");
}

// 
struct Connection *Database_open(const char *filename, char mode) {
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memory ERROR");

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die("Memory ERROR");

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) die("Faild to open the file");

    return conn;
};

void Database_close(struct Connection *conn) {
    if (conn) {
        if (conn->file) fclose(conn->file);
        if (conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn) {
    rewind(conn->file);
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);

    if (rc != 1) die("Faild to write Database.");

    rc = fflush(conn->file);
    if (rc == -1) die("Cannot flush Database.");
}

void Database_create(struct Connection *conn) {
    int i = 0;
    for (int i = 0; i < MAX_ROWS; ++i) {
        struct Address addr = {.id = i, .set = 0};
        conn->db->rows[i] = addr;
    }

}

void Database_set(struct Connection *conn, int id, const char *name, const char *email) {
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set ,delete it first.");

    addr->set = 1;
    char *res = strncpy(addr->name, name, MAX_DATA);

    if (!res) die("Name copy faild.");

    res = strncpy(addr->email, email, MAX_DATA);

    if (!res) die("Email copy faild.");
}

void Database_get(struct Connection *conn, int id) {
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID not set");
    }
}

void Database_delete(struct Connection *conn, int id) {
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn) {
    int i = 0;
    struct Database *db = conn->db;

    for (int i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if (argc > 3) id = atoi(argv[3]);
    if (id >= MAX_ROWS) die("There's not that many records.");

    switch (action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4) die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4) die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        case 'h':
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}

























