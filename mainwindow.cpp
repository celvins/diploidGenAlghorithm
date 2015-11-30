#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithm.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    newAct = new QAction(tr("&Best_fitness"), this);
//    newAct1 = new QAction(tr("&Gen_Algorthm"), this);
//    fileMenu1 = this->menuBar()->addMenu(tr("&Алгоритм"));
//    fileMenu = this->menuBar()->addMenu(tr("&Графики"));
//    fileMenu->addAction(newAct);
//    fileMenu1->addAction(newAct1);
//    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
//    connect(newAct1, SIGNAL(triggered()), this, SLOT(show_algorithm()));
    okButton.setText(tr("OK"));
    closeButton.setText(tr("Exit"));
    QObject::connect(&okButton, SIGNAL(clicked()), this, SLOT(start()));
    QObject::connect(&closeButton, SIGNAL(clicked()), this, SLOT(quit()));
    kol_osob_l.setText(tr("Number of individuals:"));
    kol_osob.setText(tr("100"));
    koeff_l.setText(tr("Correction factor"));
    koeff_e.setText(tr("0"));
    kol_genov_l.setText(tr("Number of genes:"));
    kol_genov.setText(tr("6"));
    stop_l.setText(tr("Sample Output"));
    stop_e.setText(tr("1e-2"));
    kol_pokoleniy_l.setText(tr("Number of generations:"));
    kol_pokoleniy.setText(tr("10000"));
    p_mutation_down_l.setText(tr("The probability of mutations in the genes(%)"));
    p_mutation_down_l_1.setText(tr("From:"));
    p_mutation_down.setText(tr("0"));
    p_mutation_up_l.setText(tr("To:"));
    p_mutation_up.setText(tr("25"));
    crossover_l.setText(tr("The probability of using a crossover(%)"));
    crossover_digital_l.setText(tr("Digital crossover"));
    crossover_digital_down.setText(tr("11"));
    crossover_digital_up.setText(tr("100"));
    crossover_flat_l.setText(tr("Flat crossover"));
    crossover_flat_down.setText(tr("-2"));
    crossover_flat_up.setText(tr("-1"));
    crossover_simple_l.setText(tr("Simple crossover"));
    crossover_simple_down.setText(tr("0"));
    crossover_simple_up.setText(tr("10"));
    epsilon_l.setText(tr("Epsilon"));
    epsilon.setText(tr("15"));
    layout.addWidget(&kol_osob_l,0,0);
    layout.addWidget(&kol_osob,0,1);
    layout.addWidget(&koeff_l,0,2);
    layout.addWidget(&koeff_e,0,3);
    layout.addWidget(&kol_genov_l,1,0);
    layout.addWidget(&kol_genov,1,1);
    layout.addWidget(&stop_l,1,2);
    layout.addWidget(&stop_e,1,3);
    layout.addWidget(&kol_pokoleniy_l,2,0);
    layout.addWidget(&kol_pokoleniy,2,1);
    layout.addWidget(&p_mutation_down_l,5,2);
    layout.addWidget(&p_mutation_down_l_1,6,0);
    layout.addWidget(&p_mutation_down,6,1);
    layout.addWidget(&p_mutation_up_l,6,2);
    layout.addWidget(&p_mutation_up,6,3);
    layout.addWidget(&crossover_l,7,2);
    layout.addWidget(&crossover_simple_l, 8, 0);
    layout.addWidget(&crossover_simple_down, 8, 1); layout.addWidget(&crossover_simple_up, 8, 2);
    layout.addWidget(&crossover_flat_l, 9, 0);
    layout.addWidget(&crossover_flat_down, 9, 1); layout.addWidget(&crossover_flat_up, 9, 2);
    layout.addWidget(&crossover_digital_l, 10, 0);
    layout.addWidget(&crossover_digital_down, 10, 1); layout.addWidget(&crossover_digital_up, 10, 2);
    layout.addWidget(&epsilon_l, 7, 3);
    layout.addWidget(&epsilon, 8, 3);
    file.setText("Save population");
    layout.addWidget(&file, 11, 0);
    layout.addWidget(&fileOfPopulation, 11, 1);
    layout.addWidget(&okButton,11,3);
    layout.addWidget(&closeButton,11,5);
    window.setLayout(&layout);
    window.setWindowTitle(tr("Diploid genetic algorithm"));
    window.show();
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::quit(){window.close();}
void MainWindow::show_algorithm(){window.show();}
void MainWindow::start(){
    int kolGenov = 0, kolOsob = 0, kolGener = 0, p_mut_down = 0, p_mut_up = 0,
            p_cross_dig_down = 0, p_cross_simple_down = 0, p_cross_flat_down = 0,
            p_cross_dig_up = 0, p_cross_simple_up = 0, p_cross_flat_up = 0;
    double  koef = 0, stop = 0, epsi = 0;
    bool flagSavePopulation = false;
    kolGenov = kol_genov.text().toInt();
    kolOsob = kol_osob.text().toInt();
    kolGener = kol_pokoleniy.text().toInt();
    p_mut_down = p_mutation_down.text().toInt();
    p_mut_up = p_mutation_up.text().toInt();
    koef = koeff_e.text().toFloat();
    stop = stop_e.text().toFloat();
    p_cross_dig_down = crossover_digital_down.text().toInt(); p_cross_dig_up = crossover_digital_up.text().toInt();
    p_cross_flat_down = crossover_flat_down.text().toInt(); p_cross_flat_up = crossover_flat_up.text().toInt();
    p_cross_simple_down = crossover_simple_down.text().toInt(); p_cross_simple_up = crossover_simple_up.text().toInt();
    epsi = epsilon.text().toFloat();
    if(fileOfPopulation.isChecked())
        flagSavePopulation = true;
    else
        flagSavePopulation = false;
    algorithm object_algorithm(kolGenov, kolOsob, kolGener, p_mut_down, p_mut_up, flagSavePopulation, koef, stop,
                               p_cross_dig_down, p_cross_flat_down, p_cross_simple_down,
                               p_cross_dig_up, p_cross_flat_up, p_cross_simple_up, epsi); //Start evolution
    window.close();
}
void MainWindow::newFile() {

}
