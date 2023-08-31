#include <QString>
#include <QSet>

struct ProjectStruct{
    int db_id;
    QString name;
    int color;
    QSet<QString> subprojects;
};
