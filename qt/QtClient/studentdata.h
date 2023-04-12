#ifndef STUDENTDATA_H
#define STUDENTDATA_H

#include <QObject>

class StudentData : public QObject
{
    Q_OBJECT
public:
    explicit StudentData(QObject *parent = nullptr);

signals:

public slots:
};

#endif // STUDENTDATA_H