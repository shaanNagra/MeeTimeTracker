#include <QString>
#include <QSet>

struct projectStruct{
    int db_id;
    QString name;
    int color;
    QSet<QString> subprojects;
};
