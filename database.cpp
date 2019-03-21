#include "database.h"

Database::Database()
{
    // create database path
    this->path = QApplication::applicationDirPath() + "/database/administration.sqlite";

    // initialise database with given path
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(this->path);
}

Database::Database(QString path)
{
    // create database path
    this->path = QApplication::applicationDirPath() + path;

    // initialise database with given path
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(this->path);
}

Database::~Database()
{

}

void Database::reinit()
{
    // create database path
    this->path = QApplication::applicationDirPath() + "/database/administration.sqlite";

    // initialise database with given path
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(this->path);
}
