#include "userlist.h"

UserList::UserList(UserList *userList)
{
    *this = *userList;
}

UserList::UserList(QVector<QVariant> model)
{
    // init QVector
    this->list = new QVector<User*>();

    // generate user and add to list
    // user has 7 propertys so i = i + 7
    if(model.size()>1){
        for (int i = 0; i<model.size(); i=i+7)
        {
            // create new Level
            User* temp = new User(model.mid(i, 7));
            // add pointer to list
            this->userEintragen(temp);
        }
    }
}

int UserList::userZaehlen()
{
    return this->list->size();
}

User* UserList::userHolen(int index)
{
    return this->list->at(index);
}

void UserList::userEntfernen(int index)
{
    delete this->list->at(index);
    this->list->remove(index);
}

void UserList::userEintragen(User* u)
{
    this->list->append(u);
}
