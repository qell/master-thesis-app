﻿#include <QElapsedTimer>
#include <brute_force/brute_force.h>
#include <database/database.h>
#include <simulated_annealing/simulated_annealing.h>
#include <tasks/tasks.h>

int main()
{
    QElapsedTimer timer;
    Database      db;

    QVector<QVector<double>> sa_param = {
        {8000, 10, 0.5}, {80000, 10, 0.5}, {800000, 10, 0.5}, {8000, 1000, 0.5}, {8000, 100, 0.5},
        {8000, 10, 0.5}, {8000, 10, 0.2},  {8000, 10, 0.5},   {8000, 10, 0.8},
    };

    TasksClass prj1 = db.fetch_by_id(1, 1);
    TasksClass prj2 = db.fetch_by_id(2, 1);
    TasksClass prj3 = db.fetch_by_id(3, 1);
    TasksClass prj4 = db.fetch_by_id(4, 0);
    TasksClass prj5 = db.fetch_by_id(5, 1);

    TasksClass test_case = prj1 + prj2 + prj3 + prj4 + prj5;

    TasksClass result;

    qDebug() << "Badania";
    qDebug() << "Ilosć zadań:" << test_case.size() << "\n";

    qDebug() << "Brute Force";
    timer.start();
    result = brute_force(test_case);
    qDebug() << "Czas wykonywania :" << timer.nsecsElapsed() << "ns";
    qDebug() << "Rozwiązanie:";
    for (int i = 0; i < result.size(); i++)
    {
        qDebug() << (i + 1) << ":" << result[i].name;
    }
    qDebug() << "Moment końcowy procesu:" << result.calc_makespan();
    qDebug() << "\n";

    for (auto j : sa_param)
    {
        qDebug() << "Simulated Annealing"
                 << "T_start=" << j[0] << "T_stop=" << j[1] << "lambda=" << j[2];
        timer.start();
        result = simulated_annealing(test_case, j[0], j[1], j[2]);
        qDebug() << "Czas wykonywania :" << timer.nsecsElapsed() << "ns";
        qDebug() << "Rozwiązanie:";
        for (int i = 0; i < result.size(); i++)
        {
            qDebug() << (i + 1) << ":" << result[i].name;
        }
        qDebug() << "Moment końcowy procesu:" << result.calc_makespan();
        qDebug() << "\n";
    }

    return 0;
}
