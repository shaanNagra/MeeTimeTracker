#ifndef MTTDATABASEINF_H
#define MTTDATABASEINF_H

#include <QSqlDatabase>
#include <QString>

class MTTDatabaseInf
{
public:
    MTTDatabaseInf();

    bool InitDatabase(const QString &db_name);
    //bool InitDatabase();

    bool InitDatabase(const QString &db_path, const QString &db_name, const QString conn_name);
private:

    QString db_name;
    QString db_hostname;
    bool CreateDatabaseStructre(const QSqlDatabase &db);
};

#endif // MTTDATABASEINF_H
