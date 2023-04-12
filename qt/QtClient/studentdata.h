#ifndef STUDENTDATA_H
#define STUDENTDATA_H

#include <QObject>
#include <QVariant>
class StudentData
{
    Q_GADGET
    Q_PROPERTY(QVariant name READ name WRITE setName)
    Q_PROPERTY(QVariant telephone READ telephone WRITE setTelephone)
    Q_PROPERTY(QVariant fire READ fire WRITE setFire)
    QVariant m_name;
    QVariant m_telephone;
    QVariant m_fire;

public:
    explicit StudentData(){}
    bool operator==(const StudentData&stu){
        if(stu.name() == this->name() && stu.telephone() == this->telephone() && stu.fire() == this->fire())
            return true;
        else
            return false;
    }

QVariant name() const
{
    return m_name;
}

QVariant telephone() const
{
    return m_telephone;
}

QVariant fire() const
{
    return m_fire;
}


public slots:
void setName(QVariant name)
{
    if (m_name == name)
        return;

    m_name = name;
}
void setTelephone(QVariant telephone)
{
    if (m_telephone == telephone)
        return;

    m_telephone = telephone;
}
void setFire(QVariant fire)
{
    if (m_fire == fire)
        return;

    m_fire = fire;
}
};
Q_DECLARE_METATYPE(StudentData);

#endif // STUDENTDATA_H
