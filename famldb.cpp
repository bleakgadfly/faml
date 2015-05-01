#include "famldb.h"
#include <QtSql/QtSql>

#define logstbl "logs (  id integer primary key autoincrement, msg varchar, dt date default CURRENT_DATE );"
#define postcatstbl "postcat ( id integer primary key autoincrement, name varchar, active integer default 1 );"

QSqlDatabase db;
FamlDb * faml = NULL;

FamlDb::FamlDb() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + QDir::separator() + "faml.db3");

    if(db.open()) {
        auto logResult = FamlDb::create_tbl(logstbl);
        auto postcatResult = FamlDb::create_tbl(postcatstbl);

        if(logResult != FAMLOK || postcatResult != FAMLOK) {
            qDebug("An issued occured when creating tables");
        }
    } else {
        qDebug() << "Could not open database: " << db.databaseName() << ", got " << db.lastError(); \
    }
}

FamlDb::~FamlDb() {
    qDebug() << "Closing database";
    db.close();
}

FamlDb * FamlDb::Instance() {
    if(!faml)
        faml = new FamlDb;

    return faml;
}

FAMLRESULT FamlDb::create_tbl(QString str) {
    auto q = QString("CREATE TABLE %1").arg(str);
    QSqlQuery query(db);
    if(!query.exec(q)) {
        if(!query.lastError().text().contains("exists")) {
            qDebug() << query.lastError();
            return FAMLFAIL;
        }
    }

    return FAMLOK;
}

FAMLRESULT FamlDb::StoreLog(QString logmsg) {
    QSqlQuery query(db);
    auto q = QString("INSERT INTO logs (msg) values ('%1');").arg(logmsg);

    if(!query.exec(q)) {
        qDebug() << query.lastError();
        return FAMLFAIL;
    }

    return FAMLOK;
}

FAMLRESULT FamlDb::ClearLogs() {
    QSqlQuery query(db);
    QString q("DELETE FROM logs;");

    if(!query.exec(q)) {
        qDebug() << query.lastError();
        return FAMLFAIL;
    } else {
        query.exec("VACUUM;");
        return FAMLOK;
    }
}

QStringList FamlDb::GetLogs() {
    QSqlQuery query(db);
    QString q("SELECT msg, dt FROM logs ORDER BY id DESC;");
    QStringList logs;

    if(!query.exec(q)) {
        qDebug() << query.lastError();
    } else {
        while(query.next()) {
            logs << QString("%1:%2").arg(query.value("dt").toString())
                                    .arg(query.value("msg").toString());
        }
    }

    return logs;
}

FAMLRESULT FamlDb::StoreNewPostCat(QString str) {
    QSqlQuery query(db);
    auto q = QString("INSERT INTO postcat (name) values ('%1');").arg(str);

    if(!query.exec(q)) {
        qDebug() << query.lastError();
        return FAMLFAIL;
    }

    return FAMLOK;
}

FAMLRESULT FamlDb::StorePostCat(int id, QString str, bool isActive) {
    QSqlQuery query(db);
    auto q = QString("UPDATE postcat SET name = '%1', active = %2 WHERE id = %3;")
            .arg(str).arg(isActive).arg(id);

    if(!query.exec(q)) {
        qDebug() << query.lastError();
        return FAMLFAIL;
    }

    return FAMLOK;
}

QList<postCat> FamlDb::GetPostCats() {
    QList<postCat> lst;
    QSqlQuery query(db);
    QString q("SELECT id, name, active FROM postcat ORDER BY name DESC;");

    if(!query.exec(q)) {
        qDebug() << query.lastError();
    } else {
        while(query.next()) {
            postCat cat = { query.value("id").toInt(),
                            query.value("name").toString(),
                            query.value("active").toBool()
                            };

            lst << cat;
        }
    }

    return lst;
}
