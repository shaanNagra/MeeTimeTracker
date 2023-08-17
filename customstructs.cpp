#include <QString>
#include <QSet>

struct project{
    int db_id;
    QString name;
    int color;
    QSet<QString> subprojects;
};
