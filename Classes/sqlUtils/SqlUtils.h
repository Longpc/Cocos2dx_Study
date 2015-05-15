#ifndef _SQL_UTILS_H_

#include "sqlite3.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
class SqlUtil
{
public:
	/*read or create new sql database file
		@name string: a name of db3 file
	Return sqlite3 object for query
	*/
	static sqlite3* openData(string name);
	/*create new table
		@db sqlite3: current object
		@tablename string: a name of table
		@prikeyfield string: name for field set as primary key
		@prikeyType string: type for primary key field
		@fields vector<string>: list of names and types for another fields. Ex {"field1 text","field2 int","field3 varchar(255)",....}
	Return: int value as result code of sqlite3_exec query
	*/
	static int createTable(sqlite3* db, string tablename, string prikeyfield,string prikeyType, vector<string> fields);
	/*insert values into table
		@db sqlite3*: current object.
		@table string: name of table to insert values
		@field vector<string>: list of fields. Ex: {"field1","field1",...}
		@values vector<string>: values has same order with field. Ex: {"value1","value2",...}
	Return: int value as result code of sqlite3_exec query
	*/
	static int insertRow(sqlite3* db, string table, vector<string> field, vector<string> values);
	/*
	For delete row from table
		@
		@
		@
		@
		@stringFlg bool: set to true if your field 's data type is text, string, varchar
	return code of sqlite3_exec query
	*/
	static int deleteRow(sqlite3*db, string table, string fieldName, string value,bool stringFlg = false);
	/*
	For run define sql statement
		@db sqlite3*: current sql object
		@query string: your query
	Return true if query success and false in case of failed
	*/
	static vector<string> runQuery(sqlite3*db, string query);
	/*close sql
		@db sqlite3* curent sqlite object
	*/
	static void closeSQL(sqlite3* db);

	static int truncateTable(sqlite3* db, string tableName);
	static int dropTable(sqlite3* db, string tableName);
private:

};


#endif // !1

