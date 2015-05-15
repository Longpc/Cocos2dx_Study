#include "SqlUtils.h"

sqlite3* SqlUtil::openData(string path)
{
	sqlite3* pDB = NULL;

	char* errMsg = NULL;

	string sqlstr;

	int result;

	string dbPath = FileUtils::getInstance()->getWritablePath() + path;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	if (!FileUtils::getInstance()->->isFileExist(dbPath.c_str())) {

		Data data =
			FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(path.c_str()));

		unsigned char* readData = data.getBytes();

		FILE* file = fopen(dbPath.c_str(), "wb");

		fwrite(readData, data.getSize(), 1, file);

		fclose(file);

	}

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	/*Data data = FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(path.c_str()));

	unsigned char* readData = data.getBytes();

	if (!FileUtils::getInstance()->isFileExist(dbPath)){

		std::ofstream outfile(dbPath.c_str(), std::ofstream::out);

		outfile.write((char*)&readData[0], data.getSize());

		outfile.close();

	}*/
	dbPath  = FileUtils::getInstance()->getWritablePath();
	dbPath += path;

	FILE* file = fopen(dbPath.c_str(), "r");
	if (file == nullptr)
	{
		ssize_t size;
		const char* data = (char*)FileUtils::getInstance()->getFileData(dbPath.c_str(), "rb", &size);
		file = fopen(dbPath.c_str(), "wb");
		fwrite(data, size, 1, file);
		CC_SAFE_DELETE_ARRAY(data);
	}
	fclose(file);

#endif

	result = sqlite3_open(dbPath.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		return NULL;
	}
	return pDB;
}
int SqlUtil::createTable(sqlite3* db, string tablename, string prikeyfield, string prikeyType, vector<string> fields)
{
	string querry = "create table ";
	querry.append(tablename).append(" (").append(prikeyfield).append(" ").append(prikeyType).append(" primary key autoincrement, ");
	for (vector<string>::iterator i = fields.begin(); i != fields.end(); ++i)
	{
		querry.append(*i);
		if (i + 1 != fields.end()) {
			querry.append(", ");
		}
	}
	querry.append(")");
	cocos2d::log("Query %s", querry.c_str());
	sqlite3_stmt *statement;
	int result = sqlite3_prepare_v2(db, querry.c_str(), -1, &statement, NULL);
	if (result == SQLITE_OK)
	{
		int res = sqlite3_step(statement);
		result = res;
		sqlite3_finalize(statement);
		return res;
	}

	return result;
}

int SqlUtil::insertRow(sqlite3* db, string table, vector<string> field, vector<string> values)
{
	string querryStr = "";
	querryStr.append("insert into ").append(table).append("(");
	for (vector<string>::iterator i = field.begin(); i != field.end(); ++i)
	{
		querryStr.append(*i);
		if (i + 1 != field.end())
		{
			querryStr.append(", ");
		}
	}
	querryStr.append(") values('");
	for (vector<string>::iterator i = values.begin(); i != values.end(); ++i)
	{
		querryStr.append(*i);
		if (i + 1 != values.end())
		{
			querryStr.append("', '");
		}
	}
	querryStr.append("')");
	char *str = &querryStr[0];
	cocos2d::log("QUERY %s", querryStr.c_str());
	sqlite3_stmt *statement;
	int result = sqlite3_prepare_v2(db, querryStr.c_str(), -1, &statement, NULL);
	if (result == SQLITE_OK)
	{
		int res = sqlite3_step(statement);
		result = res;
		sqlite3_finalize(statement);
		return res;
	}

	return result;
}
int SqlUtil::deleteRow(sqlite3*db, string table, string fieldName, string value,bool stringFlg)
{
	string query;
	if (stringFlg = false) { 
		query = "delete from " + table + " where " + fieldName + " = " + value; 
	}
	else {
		query = "delete from " + table + " where " + fieldName + " = '" + value+"'";
	}

	sqlite3_stmt *statement;
	cocos2d::log("QUERY %s", query.c_str());
	int result = sqlite3_prepare(db, query.c_str(), -1, &statement, 0);
	if (result == SQLITE_OK)
	{
		int res = sqlite3_step(statement);
		result = res;
		sqlite3_finalize(statement);
		return res;
	}
	return result;
}



void SqlUtil::closeSQL(sqlite3* db)
{
	sqlite3_close(db);
}

int SqlUtil::truncateTable(sqlite3* db, string tableName)
{
	sqlite3_stmt *statement;
	string query = "TRUNCATE TABLE " + tableName;
	int result = sqlite3_prepare(db, query.c_str(), -1, &statement, 0);
	if ( result == SQLITE_OK)
	{
		int res = sqlite3_step(statement);
		result = res;
		sqlite3_finalize(statement);
		return res;
	}
	return result;
}

int SqlUtil::dropTable(sqlite3* db, string tableName)
{
	sqlite3_stmt *statement;
	string query = "DROP TABLE " + tableName;
	int result = sqlite3_prepare(db, query.c_str(), -1, &statement, 0);
	if ( result== SQLITE_OK)
	{
		int res = sqlite3_step(statement);
		result = res;
		sqlite3_finalize(statement);
		return res;
	}
	return result;
}

vector<string> SqlUtil::runQuery(sqlite3*db, string query)
{
	sqlite3_stmt *statement;
	int result;
	vector<char *> *data;
	char *text1 = "";
	vector<string> str;
	if (sqlite3_prepare(db, query.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		int res = sqlite3_step(statement);

		for (;;) {
			int rc = sqlite3_step(statement);
			if (rc == SQLITE_DONE)
				break;
			if (rc != SQLITE_ROW) {
				printf("error: %s!\n", sqlite3_errmsg(db));
				break;
			}
			char *text0 = (char *)sqlite3_column_text(statement, 0);
			text1 = (char *)sqlite3_column_text(statement, 1);
			char *text2 = (char *)sqlite3_column_text(statement, 2);
			//cocos2d::log("%s|%s|%s", text0, text1, text2);
			stringstream atr;
			str.push_back(text0);
			str.push_back(text1);
			str.push_back(text2);
		}
		result = res;
		sqlite3_finalize(statement);
		return str;
	}
	else {
		cocos2d::log("some error");
	}
	return str;
}


