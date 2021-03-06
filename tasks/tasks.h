#ifndef TASKS_H
#define TASKS_H

#include <QString>
#include <QVector>
#include <QtDebug>

struct JobStruct
{
    QString       name;
    QVector<uint> p;
    QVector<uint> s;
    uint          id;

    bool operator<(const JobStruct& a)
    {
        return id < a.id;
    }

    JobStruct(QString name = nullptr, QVector<uint> task_time = {0}, QVector<uint> adapt_time = {0})
        : name(name)
        , p(task_time)
        , s(adapt_time)
    {
        for (int i = s.size(); i < p.size(); i++)
        {
            s.append(0);
        }
    }
};

class TasksClass
{
    QList<JobStruct> task;
    uint             operation_time(uint idx_machine, uint idx_task);
    uint             adapt_time(uint idx_machine, uint idx_task);
    uint             start_operation(uint idx_machine, uint idx_task);
    uint             stop_operation(uint idx_machine, uint idx_task);

public:
    TasksClass();
    void       add_task(JobStruct job);
    uint       calc_makespan(void);
    int        size(void);
    JobStruct& operator[](int idx);
    TasksClass operator+(TasksClass& x)
    {
        for (auto i : x)
        {
            i.id = this->task[this->size() - 1].id + 1;
            this->add_task(i);
        }

        return *this;
    }
    QList<JobStruct>::iterator begin(void);
    QList<JobStruct>::iterator end(void);
    QList<QString>             name_prj(void);
};

#endif // TASKS_H
