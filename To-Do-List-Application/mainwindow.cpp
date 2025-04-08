#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), taskTable(new QTableWidget(this)),
    taskTitle(new QLineEdit(this)),dueDate(new QDateEdit(QDate::currentDate(), this)),
    priorityBox(new QComboBox(this)), addButton(new QPushButton("Add Task", this)),
    editButton(new QPushButton("Edit Task", this)),
    deleteButton(new QPushButton("Delete Task", this)){

    setupUI();

    //Signal-Slot-Verbindungen
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(editButton, &QPushButton::clicked, this,&MainWindow::editTask);
    connect(deleteButton,&QPushButton::clicked, this,&MainWindow::deleteTask);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI(){
    //Layout
    QWidget *centralWidget=new QWidget(this);
    QVBoxLayout *layout =new QVBoxLayout(centralWidget);

    //Task Table
    taskTable->setColumnCount(3);
    taskTable->setHorizontalHeaderLabels({"Title","Due Date","Priority"});
    taskTable->horizontalHeader()->setStretchLastSection(true);

    //Priority Box
    priorityBox->addItems({"High","Medium","Low"});

    //Add Widgets to Layout
    layout-> addWidget(taskTable);
    layout-> addWidget(new QLabel("Task Title:"));
    layout-> addWidget(taskTitle);
    layout-> addWidget(new QLabel("Due Date:"));
    layout-> addWidget(dueDate);
    layout-> addWidget(new QLabel("Priority:"));
    layout-> addWidget(priorityBox);
    layout-> addWidget(addButton);
    layout-> addWidget(editButton);
    layout-> addWidget(deleteButton);

    setCentralWidget(centralWidget);

}
void MainWindow::addTask() {
    if (taskTitle->text().isEmpty()){
        QMessageBox::warning(this, "Error", "Task title cannot be empty!");
        return;
    }

    int row = taskTable->rowCount();
    taskTable->insertRow(row);
    taskTable->setItem(row, 0, new QTableWidgetItem(taskTitle->text()));
    taskTable->setItem(row, 1, new QTableWidgetItem(dueDate->date().toString("yyyy-MM-dd")));
    taskTable->setItem(row, 2, new QTableWidgetItem(priorityBox->currentText()));

    taskTitle->clear();
    dueDate->setDate(QDate::currentDate());
    priorityBox->setCurrentIndex(0);
}
void MainWindow::editTask() {
    int row = taskTable->currentRow();
     if (row < 0){
        QMessageBox::warning(this, "Error","No task selected!");
         return;
     }

     taskTable ->item(row,0)->setText(taskTitle->text());
     taskTable->item(row,1)->setText(dueDate->date().toString("yyyy-MM-dd"));
     taskTable->item(row,2)->setText(priorityBox->currentText());
}
void MainWindow::deleteTask(){
     int row = taskTable->currentRow();
     if(row>=0){
         taskTable->removeRow(row);
     }else {
         QMessageBox::warning(this, "Error", "No task selected!");
     }
 }

