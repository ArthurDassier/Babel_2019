/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Database.cpp
*/

#include "Database.hpp"

db::Database::Database(const std::string &db_name)
{
    connect(db_name);
}

db::Database::~Database()
{
    sqlite3_close(getHandle());
}

bool db::Database::connect(const std::string &db_name)
{
    int rc = 0;
    sqlite3 *db_p;
    const char *data = "Callback function called";

    sqlite3_open(db_name.c_str(), &db_p);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(getHandle()) << std::endl;
        return false;
    } else {
        setDB(db_p);
        std::cout << "Opened database successfully" << std::endl;
    }
    return true;
}

bool db::Database::createTable(const std::string &table)
{
    std::ostringstream oss;

    oss << "CREATE TABLE IF NOT EXISTS " << table << ";";
    return sqlStmt(oss.str());
}

bool db::Database::insertData(std::unique_ptr<Data> data)
{
    return sqlStmt(data->getInsertionQuery());
}

void db::Database::getData(const std::string &dataType, const std::vector<std::string> &attributes)// = {"*"}) //std::unique_ptr<Data> data)
{
    int end = 0;
    std::ostringstream oss;
   
    oss << "SELECT ";
    for (auto &attribute : attributes) {
        end = attribute.compare(attributes.back());
        oss << attribute << (end != 0 ? "," : " ");
    }
    oss << "from " << dataType;
    Records records = selectStmt(oss.str());
    for (auto &record : records)
    {
        for (auto &it : record)
            std::cout << it << " ";
        std::cout << std::endl;
    }
}

bool db::Database::upsertData(const std::string &dataType, const std::string &sql)
{
    std::ostringstream oss;

    oss << "UPDATE " << dataType << " set " << sql << ";";
    return sqlStmt(oss.str());
}

bool db::Database::deleteData(const std::string &dataType, const std::string &sql)
{
    std::ostringstream oss;

    oss << "DELETE from " << dataType << " where " << sql << ";";
    return sqlStmt(oss.str());
}

int db::Database::sqlStmt(const std::string &stmt)
{
    char *errmsg = nullptr;
    int ret = sqlite3_exec(db, stmt.c_str(), 0, 0, &errmsg);
    
    if (ret != SQLITE_OK) {
        std::cerr << "Error in sql statement " << stmt << "[" << errmsg << "]" << std::endl;
        return 1;
    }
    return 0;
}

db::Records db::Database::selectStmt(const std::string &stmt)
{
    Records records;
    char *errmsg = nullptr;
    int ret = sqlite3_exec(db, stmt.c_str(), select_callback, &records, &errmsg);
    
    if (ret != SQLITE_OK) {
        std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]" << std::endl;
    } else {
        std::cout << records.size() << " records returned." << std::endl;
    }
    return records;
}

int db::Database::select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
    Records *records = static_cast<Records *>(p_data);
    try {
        records->emplace_back(p_fields, p_fields + num_fields);
    } catch (...) {
        return 1;
    }
    return 0;
}