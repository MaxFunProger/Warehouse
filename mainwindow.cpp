#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Generator.h"
#include "customdialog.h"
//#include <qdebug.h>
//#define std::cout qDebug()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->showMaximized();
    set_defaults(ROWS, COLUMS);

}


void MainWindow::Modeller(){
    int k, m, days_to_generate;
    k = ui->table->rowCount();
    days_to_generate = stoi(ui->set_days->text().toStdString());
    days_left = days_to_generate;
    m = stoi(ui->set_shops->text().toStdString());

    std::vector<ItemType*> types;
    std::vector<IAsker*> shops;
    std::string name;
    int capacity, days, days_critical, weight, packs, price, spoiled_price, price_factory;

    for (int i = 0; i < k; ++i){
        name = ui->table->item(i, 0)->text().toStdString();
        ui->table->item(i, 0)->setFlags(ui->table->item(i, 0)->flags() ^ Qt::ItemIsEditable);
        capacity = ui->table->item(i, 1)->text().toInt();
        ui->table->item(i, 1)->setFlags(ui->table->item(i, 1)->flags() ^ Qt::ItemIsEditable);
        days = ui->table->item(i, 2)->text().toInt();
        ui->table->item(i, 2)->setFlags(ui->table->item(i, 2)->flags() ^ Qt::ItemIsEditable);
        days_critical = ui->table->item(i, 3)->text().toInt();
        ui->table->item(i, 3)->setFlags(ui->table->item(i, 3)->flags() ^ Qt::ItemIsEditable);
        weight = ui->table->item(i, 4)->text().toInt();
        ui->table->item(i, 4)->setFlags(ui->table->item(i, 4)->flags() ^ Qt::ItemIsEditable);
        packs = ui->table->item(i, 5)->text().toInt();
        ui->table->item(i, 5)->setFlags(ui->table->item(i, 5)->flags() ^ Qt::ItemIsEditable);
        price = ui->table->item(i, 6)->text().toInt();
        ui->table->item(i, 6)->setFlags(ui->table->item(i, 6)->flags() ^ Qt::ItemIsEditable);
        spoiled_price = ui->table->item(i, 7)->text().toInt();
        ui->table->item(i, 7)->setFlags(ui->table->item(i, 7)->flags() ^ Qt::ItemIsEditable);
        price_factory = ui->table->item(i, 8)->text().toInt();
        ui->table->item(i, 8)->setFlags(ui->table->item(i, 8)->flags() ^ Qt::ItemIsEditable);

        types.emplace_back(new ItemType(name, capacity, days, days_critical, weight, packs, price, spoiled_price, price_factory));
    }

    shops.reserve(m);
    for (int i = 0; i < m; ++i) {
        shops.emplace_back(new Shop());
    }

    auto* warehouse = new Warehouse();
    auto* factory = new Factory();
    auto* generator = new Generator(warehouse, factory, shops, types);

    int cnt_days = days_to_generate;
    for (int day = 1; day <= cnt_days; ++day){
        generator->process();
        ui->table_storage->setRowCount(0);
        ui->table_factory->setRowCount(0);
        Logger logg = generator->log();
        QTableWidgetItem *newitem = nullptr;
        for (size_t i = 0; i < logg.items.size(); ++i){
            ui->table_storage->insertRow(ui->table_storage->rowCount());
            // qDebug() << "bug";
            newitem = new QTableWidgetItem(tr("%1").arg((i) * (0)));
            newitem->setText(QString::fromStdString(logg.items[i].name));
            ui->table_storage->setItem(i, 0, newitem);
            ui->table_storage->item(i, 0)->setFlags(ui->table_storage->item(i, 0)->flags() ^ Qt::ItemIsEditable);

            newitem = new QTableWidgetItem(tr("%1").arg((i) * (1)));
            newitem->setText(QString::number(logg.items[i].cnt));
            ui->table_storage->setItem(i, 1, newitem);
            ui->table_storage->item(i, 1)->setFlags(ui->table_storage->item(i, 1)->flags() ^ Qt::ItemIsEditable);

            newitem = new QTableWidgetItem(tr("%1").arg((i) * (2)));
            newitem->setText(QString::number(logg.items[i].cnt_spoiled));
            ui->table_storage->setItem(i, 2, newitem);
            ui->table_storage->item(i, 2)->setFlags(ui->table_storage->item(i, 2)->flags() ^ Qt::ItemIsEditable);

        }

        for (size_t i = 0; i < logg.fac_items.size(); ++i){
            ui->table_factory->insertRow(ui->table_factory->rowCount());

            newitem = new QTableWidgetItem(tr("%1").arg((i) * (0)));
            newitem->setText(QString::fromStdString(logg.fac_items[i].name));
            ui->table_factory->setItem(i, 0, newitem);
            ui->table_factory->item(i, 0)->setFlags(ui->table_factory->item(i, 0)->flags() ^ Qt::ItemIsEditable);

            newitem = new QTableWidgetItem(tr("%1").arg((i) * (1)));
            newitem->setText(QString::number(logg.fac_items[i].cnt));
            ui->table_factory->setItem(i, 1, newitem);
            ui->table_factory->item(i, 1)->setFlags(ui->table_factory->item(i, 1)->flags() ^ Qt::ItemIsEditable);

            newitem = new QTableWidgetItem(tr("%1").arg((i) * (2)));
            newitem->setText(QString::number(logg.fac_items[i].days));
            ui->table_factory->setItem(i, 2, newitem);
            ui->table_factory->item(i, 2)->setFlags(ui->table_factory->item(i, 2)->flags() ^ Qt::ItemIsEditable);
        }
        ui->profit_text->setText(QString::number(logg.money));
        ui->lost_text->setText(QString::number(logg.lose_money));
        ui->trashed_text->setText(QString::number(logg.erase_items));
        ui->discounted_text->setText(QString::number(logg.cnt_spoiled_sold));
        ui->passed->setText(QString::number(ui->passed->text().toInt() + 1));
        if (!FLAG_ALL)
            loop();
        //std::cout << "============================== Day " << day << " ==============================\n";
    }
    delete generator;
}

void MainWindow::set_defaults(int rows, int colums){
    QStringList horzHeaders;

    ui->table_factory->setRowCount(0);
    ui->table_factory->setColumnCount(3);
    horzHeaders << "Name" << "Count" << "Days until arrival";
    ui->table_factory->setHorizontalHeaderLabels(horzHeaders);
    horzHeaders.clear();

    ui->table_storage->setRowCount(0);
    ui->table_storage->setColumnCount(3);
    horzHeaders << "Name" << "Count" << "Count of spoiled";
    ui->table_storage->setHorizontalHeaderLabels(horzHeaders);
    horzHeaders.clear();

    ui->table->setRowCount(rows);
    ui->table->setColumnCount(colums);
    horzHeaders << "Name" << "Capacity" << "Days" << "Days Critical" << "Weight" << "Packs" << "Price" << "Spoiled Price" << "Factory Price";
    ui->table->setHorizontalHeaderLabels(horzHeaders);
    horzHeaders.clear();
    std::vector<std::vector<std::string> > inp(3);
    for (int i = 0; i < 3; ++i){
        inp[i].resize(9);
    }
    inp[0] = {"Kolbasa", "100", "7", "2", "10", "5", "2500", "2400", "2000"};
    inp[1] = {"Potato", "5000", "10", "1", "5", "1", "250", "220", "180"};
    inp[2] = {"Milk", "1000", "14", "3", "1", "20", "1340", "950", "700"};
    QTableWidgetItem *newit = nullptr;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 9; ++j){
            newit = new QTableWidgetItem(tr("%1").arg((i) * (j)));
            newit->setText(QString::fromStdString(inp[i][j]));
            ui->table->setItem(i, j, newit);
        }
    }

}



MainWindow::~MainWindow()
{
    qDebug() << "end";
    flag = true;
    delete ui;
}





void MainWindow::on_start_button_clicked()
{
    Modeller();
}






void MainWindow::on_add_prod_clicked()
{
    ui->table->insertRow(ui->table->rowCount());


    CustomDialog d("Set modelling values", this);
    d.addLabel("Please enter your values");
    std::string name, capacity, days, days_critical, weight, packs, price, spoiled_price, price_factory;
    d.addLineEdit("Name of product:  ", &name, "Item name");
    d.addLineEdit("Capacity of storage (in packs):  ", &capacity, "100");
    d.addLineEdit("Days till spoil:  ", &days, "10");
    d.addLineEdit("Days left to sell by discounted price:  ", &days_critical, "2");
    d.addLineEdit("Weight of pack:  ", &weight, "12");
    d.addLineEdit("Packs:  ", &packs, "20");
    d.addLineEdit("Price:  ", &price, "1000");
    d.addLineEdit("Discounted price:  ", &spoiled_price, "700");
    d.addLineEdit("Factory price:  ", &price_factory, "500");

    d.exec();

    for (int i = 0; i < 9; ++i){
        QTableWidgetItem *newit = new QTableWidgetItem(tr("%1").arg((ui->table->rowCount() - 1) * (0)));
        newit->setText(QString::fromStdString(name));
        ui->table->setItem(ui->table->rowCount() - 1, 0, newit);

        newit = new QTableWidgetItem(tr("%1").arg((ui->table->rowCount() - 1) * (1)));
        newit->setText(QString::fromStdString(capacity));
        ui->table->setItem(ui->table->rowCount() - 1, 1, newit);

        newit = new QTableWidgetItem(tr("%1").arg((ui->table->rowCount() - 1) * (2)));
        newit->setText(QString::fromStdString(days));
        ui->table->setItem(ui->table->rowCount() - 1, 2, newit);

        newit = new QTableWidgetItem(tr("%1").arg((ui->table->rowCount() - 1) * (3)));
        newit->setText(QString::fromStdString(days_critical));
        ui->table->setItem(ui->table->rowCount() - 1, 3, newit);

        newit = new QTableWidgetItem(tr("%1").arg((ui->table->rowCount() - 1) * (4)));
        newit->setText(QString::fromStdString(weight));
        ui->table->setItem(ui->table->rowCount() - 1, 4, newit);

        newit = new QTableWidgetItem(tr("%1").arg((ui->table->rowCount() - 1) * (5)));
        newit->setText(QString::fromStdString(packs));
        ui->table->setItem(ui->table->rowCount() - 1, 5, newit);

        newit = new QTableWidgetItem(tr("%1").arg((ui->table->rowCount() - 1) * (6)));
        newit->setText(QString::fromStdString(price));
        ui->table->setItem(ui->table->rowCount() - 1, 6, newit);

        newit = new QTableWidgetItem(tr("%1").arg((ui->table->rowCount() - 1) * (7)));
        newit->setText(QString::fromStdString(spoiled_price));
        ui->table->setItem(ui->table->rowCount() - 1, 7, newit);

        newit = new QTableWidgetItem(tr("%1").arg((ui->table->rowCount() - 1) * (8)));
        newit->setText(QString::fromStdString(price_factory));
        ui->table->setItem(ui->table->rowCount() - 1, 8, newit);

    }


}


void MainWindow::on_next_day_but_clicked()
{
    emit quitloop();
}


void MainWindow::on_all_days_but_clicked()
{
    FLAG_ALL = true;
    emit quitloop();
}


void MainWindow::on_start_gen_clicked()
{
    ui->start_gen->setDisabled(true);
    ui->add_prod->setDisabled(true);
    ui->set_days->setDisabled(true);
    ui->set_shops->setDisabled(true);
    Modeller();
}

void MainWindow::loop(){
    loop_.exit();
    if (!flag){
        QObject::connect(this, SIGNAL(quitloop()), &loop_, SLOT(quit()), Qt::QueuedConnection);
        loop_.exec();
    }
}

void MainWindow::on_next_days_but2_clicked()
{
    emit quitloop();
}


void MainWindow::on_gen_all_but2_clicked()
{
    FLAG_ALL = true;
    emit quitloop();
}


void MainWindow::on_next_day_but3_clicked()
{
    emit quitloop();
}


void MainWindow::on_gen_all_but3_clicked()
{
    FLAG_ALL = true;
    emit quitloop();
}

