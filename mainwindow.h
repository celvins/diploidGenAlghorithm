/*
 * Author - Vardanyan Andranik Eduardovich
 *
 *
 *
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QTextEdit>
#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <iostream>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QMessageBox>
#include <QKeyEvent>
#include <qmath.h>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include "flags.h"
using namespace std;
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMessageBox msgBox;
    Flags * flags;
private:
    Ui::MainWindow *ui;
    QWidget window;
    QCheckBox fileOfPopulation, best_file, best_all_file;
    QPushButton okButton, closeButton, other;
    QGridLayout layout;
    QLineEdit kol_osob, kol_genov, kol_pokoleniy, p_mutation_down, p_mutation_up,
            koeff_e, stop_e, crossover_flat_down, crossover_simple_down,
            crossover_digital_down, crossover_flat_up, crossover_simple_up,
            crossover_digital_up, epsilon;
    QLabel file, fileBest, fileBestAll, kol_osob_l, kol_genov_l, kol_pokoleniy_l,
            p_mutation_down_l, p_mutation_down_l_1, p_mutation_up_l,
            koeff_l, stop_l, crossover_flat_l, crossover_simple_l,
            crossover_digital_l, crossover_l, epsilon_l, author;
private slots:
     void newFile(void);
     void start();
     void quit();
     void show_algorithm();
};

#endif // MAINWINDOW_H
