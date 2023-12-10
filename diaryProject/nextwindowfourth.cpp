/// ЗАМЕТКИ
/// ЗАМЕТКИ
/// ЗАМЕТКИ
#include "nextwindowfourth.h"
#include "./ui_nextwindowfourth.h"
#include "note.h"
#include <QStack>
#include <QMessageBox>
#include "dbpostgre.h"

note* notes = new note();
QStack<note*> takenActions2;

nextWindowFourth::nextWindowFourth(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::nextWindowFourth)
{
    ui->setupUi(this);
}

nextWindowFourth::~nextWindowFourth()
{
    delete ui;
}


void nextWindowFourth::on_pushButton_clicked()
{
    this->close();      // Закрываем окно
    emit fourthWindow(); // И вызываем сигнал на открытие главного окна
}



void nextWindowFourth::on_pushButton_3_clicked()    // отменить предыдущее действие
{
    if(takenActions2.isEmpty()){
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("Предупреждение");
        msg->setText("Вы не выполнили никаких действий");
        msg->exec();
        return;
    }
    else{
        takenActions2.pop();
        if(!takenActions2.isEmpty()){
            notes = takenActions2.top();
        }
        else{
            ui->listWidget->clear();
        }
        ui->listWidget->clear();
        QString temp;

        foreach(temp, notes->getPage(ui->calendar->selectedDate().toString()) /*page[ui->calendar->selectedDate().toString()]*/)
            ui->listWidget->addItem(temp);
    }
}


void nextWindowFourth::on_pushButton_4_clicked()        // добавление в заметки
{
    takenActions2.push(notes);
    ui->listWidget->clear();
    notes->appendPage(ui->calendar->selectedDate().toString(), QString::number(notes->getPage(ui->calendar->selectedDate().toString()).count() + 1) +
            ". " + ui->lineEdit->text() + "\n" + ui->textEdit->toPlainText() + "\n");
    QTextCharFormat format;
    QBrush brush;
    QColor color;
    int r=139,g=0,b=255,a=155;
    color.setRgb(r,g,b,a);;
    brush.setColor(color);
    format.setBackground(brush);
    ui->calendar->setDateTextFormat(ui->calendar->selectedDate(),format);
    ui->lineEdit->clear();
    ui->textEdit->clear();
    QString temp;

    foreach(temp, notes->getPage(ui->calendar->selectedDate().toString()))
        ui->listWidget->addItem(temp);
}


void nextWindowFourth::on_pushButton_6_clicked()        // установить название
{
    if(ui->lineEdit_4->text().isEmpty()){
        QMessageBox* msg = new QMessageBox();
        msg->setWindowTitle("Предупреждение");
        msg->setText("Вы ничего не ввели");
        msg->exec();
        return;
    }
    takenActions2.push(notes);
    notes->setDescription(ui->lineEdit_4->text().toStdString());
    ui->label->setText(ui->lineEdit_4->text());
}



// запись в бд
void nextWindowFourth::on_pushButton_7_clicked()
{
//    ofstream out;          // поток для записи
//    out.open("D:\\My shit)\\coursachTry\\notes.txt"); // окрываем файл для записи
//    out << *notes;
//    out.close();
    QSqlDatabase db = initializeDb();

    if(db.open()){
        QSqlQuery query;

        if(query.prepare("INSERT INTO public.task (ended_tasks, tasks) VALUES (?, ?)")){
            query.addBindValue("Завершенные задачи");
            query.addBindValue("Активные задачи");


            if (query.exec()) {
                qDebug() << "Данные успешно добавлены в таблицу tasks";
            } else {
                qDebug() << "Ошибка при добавлении данных в таблицу tasks:";
                    qDebug() << "SQL-запрос:" << query.lastQuery();
                    qDebug() << "Значения параметров:";
                    qDebug() << ":ended_tasks" << query.boundValue(":ended_tasks").toString();
                    qDebug() << ":tasks" << query.boundValue(":tasks").toString();
            }
        }
        else{
            qDebug() << "Ошибка при подготовке запроса:";
        }
    }

    db.close();
}


// чтение из бд
void nextWindowFourth::on_pushButton_8_clicked()
{
    ifstream in;
    notes->clearAllPages();
    in.open("D:\\My shit)\\coursachTry\\tasks.txt");
    in >> *notes;
    in.close();
}




void nextWindowFourth::on_calendar_selectionChanged()
{
    ui->listWidget->clear();
    ui->label->setText(ui->calendar->selectedDate().toString());
    QString temp;

    foreach(temp, notes->getPage(ui->calendar->selectedDate().toString()))
    ui->listWidget->addItem(temp);
}

