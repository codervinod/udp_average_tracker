//
//  db_store.cpp
//  udp_average_tracker
//
//  Created by Vinod Gupta on 10/29/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#include "sqlite_store.h"
#include <sstream>

SqLiteStore::SqLiteStore(std::string store)
    :_store(store),_db(NULL)
{
    
}

SqLiteStore::~SqLiteStore()
{
    if(_db)
        sqlite3_close(_db);
}

bool SqLiteStore::Connect()
{
    int rc = sqlite3_open(_store.c_str(), &_db);
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(_db));
        return false;
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }
    return true;

}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

bool SqLiteStore::ExecQuery(std::string sql)
{
    char *zErrMsg=0;
    int rc=-1;
    
    /* Execute SQL statement */
    rc = sqlite3_exec(_db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    
    return true;

}

bool SqLiteStore::InitTables()
{
    const char *sql1 = "CREATE TABLE IF NOT EXISTS TIMELOG("  \
    "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
    "value INTEGET," \
    "time TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL" \
    ");";
    
    bool ret= ExecQuery(sql1);
    
    const char *sql2 = "CREATE TABLE IF NOT EXISTS AVERAGE_TIMELOG("  \
    "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
    "value INTEGET," \
    "time TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL" \
    ");";
    
    return ExecQuery(sql2) && ret;//create even if other returned false
}

bool SqLiteStore::SetVal(time_t time,unsigned int value)
{
    std::stringstream ss;
    ss<<"INSERT INTO TIMELOG (value,time) VALUES(";
    ss<<value<<","<<time<<");";
    
    return ExecQuery(ss.str());
}

bool SqLiteStore::SetAverage(time_t time,unsigned int value)
{
    std::stringstream ss;
    ss<<"INSERT INTO AVERAGE_TIMELOG (value,time) VALUES(";
    ss<<value<<","<<time<<");";
    
    return ExecQuery(ss.str());
}


