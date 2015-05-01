#ifndef FAMLDB_H
#define FAMLDB_H

typedef int FAMLRESULT;
#define FAMLOK 0
#define FAMLFAIL 1

#include <QtSql/QSql>
#include <QStringList>

typedef struct {
    int id;
    QString name;
    bool isActive;
} postCat;

class FamlDb
{
public:
    static FamlDb * Instance();
    FAMLRESULT StoreLog(QString logmsg);
    FAMLRESULT ClearLogs();
    QStringList GetLogs();

    FAMLRESULT StoreNewPostCat(QString str);
    FAMLRESULT StorePostCat(int id, QString str, bool isActive);
    QList<postCat> GetPostCats();

private:
    FamlDb();
    ~FamlDb();
    FAMLRESULT create_tbl(QString str);
};

#endif // FAMLDB_H
