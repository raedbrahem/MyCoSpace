#include "sqleventmodel.h"
#include "connection.h"
#include <QDebug>
#include <QFileInfo>

SqlEventModel::SqlEventModel()
{

}

QList<QObject*> SqlEventModel::eventsForDate(const QDate &date)
{

    QSqlQuery query;

    query.prepare("SELECT * FROM RESERVATION where DATERES like :date");
    query.bindValue(":date", date);
    query.exec();

    QList<QObject*> events;
    while (query.next()) {
        Event *event = new Event(this);
        event->setName(query.value("NOMRES").toString());

        QDateTime startDate;
        startDate.setDate(query.value("DATERES").toDate());
        //startDate.setTime(QTime(0, 0).addSecs(query.value("startTime").toInt()));
        QString start="00000";
        startDate.setTime(QTime(0, 0).addSecs(start.toInt()));
        event->setStartDate(startDate);

        QDateTime endDate;
        endDate.setDate(query.value("DATERES").toDate());
        endDate.setTime(QTime(0, 0).addSecs(start.toInt()));
        event->setEndDate(endDate);

        events.append(event);
    }

    return events;

}



