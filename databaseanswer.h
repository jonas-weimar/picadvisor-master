#ifndef DATABASEANSWER_H
#define DATABASEANSWER_H

#include <QString>

template<class T>
class DatabaseAnswer
{
public:

    DatabaseAnswer()
    {
        this->error = false;
    }

    void setError(QString error)
    {
        this->error = true;
        this->errorText = error;
    }

    void setObject(T* object)
    {
        this->object = object;
    }

    bool hasError()
    {
        return this->error;
    }

    QString errorToText()
    {
        return this->errorText;
    }

    T* getObject()
    {
        return this->object;
    }

private:
    QString errorText;
    bool error;
    T* object;
};

#endif // DATABASEANSWER_H
