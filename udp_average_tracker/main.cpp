//
//  main.cpp
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/29/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#include <iostream>

#include "sqlite3.h"
#include "udp_server.h"


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


void testDB(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    
    rc = sqlite3_open("./test.db", &db);
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }
    /* Create SQL statement */
    const char *sql = "CREATE TABLE COMPANY("  \
    "ID INT PRIMARY KEY     NOT NULL," \
    "NAME           TEXT    NOT NULL," \
    "AGE            INT     NOT NULL," \
    "ADDRESS        CHAR(50)," \
    "SALARY         REAL );";
    
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }
    sqlite3_close(db);
}

int main(int argc, const char * argv[]) {
    
    UdpServer udp_server(1153);
    udp_server.join();
    return 0;
}
