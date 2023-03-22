#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <regex>
#include <string>

int currentFloorA = 1;
int currentFloorB = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectElevatorButtons();
    connectDoorButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Calls the elevator to the floor a door button is pressed
void MainWindow::callElevator(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    std::string buttonText = buttonSender->objectName().toStdString();

    int currentFloor = stoi(extractNums(buttonText));

    if((ui->obstructB->checkState() == Qt::Checked) && ui->obstructA->checkState() == Qt::Unchecked || abs(currentFloorA - currentFloor) <= abs(currentFloorB - currentFloor) && ui->obstructA->checkState() == Qt::Unchecked){
        ui->floorA1->setText("");
        ui->floorA2->setText("");
        ui->floorA3->setText("");
        ui->floorA4->setText("");

        currentFloorA = currentFloor;
        switch(currentFloor){
            case 1:
                ui->floorA1->setText("Elevator");
                break;
            case 2:
                ui->floorA2->setText("Elevator");
                break;
            case 3:
                ui->floorA3->setText("Elevator");
                break;
            case 4:
                ui->floorA4->setText("Elevator");
                break;
        }
        consoleOut(0);
    }else if (ui->obstructB->checkState() == Qt::Unchecked){
        ui->floorB1->setText("");
        ui->floorB2->setText("");
        ui->floorB3->setText("");
        ui->floorB4->setText("");

        currentFloorB = currentFloor;
        switch(currentFloor){
            case 1:
                ui->floorB1->setText("Elevator");
                break;
            case 2:
                ui->floorB2->setText("Elevator");
                break;
            case 3:
                ui->floorB3->setText("Elevator");
                break;
            case 4:
                ui->floorB4->setText("Elevator");
                break;
        }
        consoleOut(2);
    }else{
        consoleOut(-1);
    }
}

void MainWindow::moveElevatorA(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    std::string buttonText = buttonSender->objectName().toStdString();

    if(ui->obstructA->checkState() == Qt::Checked){
        //remove ability to move
        consoleOut(6);
        return;
    }

    currentFloorA = stoi(extractNums(buttonText));



    ui->floorA1->setText("");
    ui->floorA2->setText("");
    ui->floorA3->setText("");
    ui->floorA4->setText("");

    switch(currentFloorA){
        case 1:
            ui->floorA1->setText("Elevator");
            break;
        case 2:
            ui->floorA2->setText("Elevator");
            break;
        case 3:
            ui->floorA3->setText("Elevator");
            break;
        case 4:
            ui->floorA4->setText("Elevator");
            break;
    }
    consoleOut(1);
}

void MainWindow::moveElevatorB(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    std::string buttonText = buttonSender->objectName().toStdString();

    if(ui->obstructB->checkState() == Qt::Checked){
        consoleOut(7);
        return;
    }

    currentFloorB = stoi(extractNums(buttonText));


    ui->floorB1->setText("");
    ui->floorB2->setText("");
    ui->floorB3->setText("");
    ui->floorB4->setText("");

    switch(currentFloorB){
        case 1:
            ui->floorB1->setText("Elevator");
            break;
        case 2:
            ui->floorB2->setText("Elevator");
            break;
        case 3:
            ui->floorB3->setText("Elevator");
            break;
        case 4:
            ui->floorB4->setText("Elevator");
            break;
    }
    consoleOut(3);
}

void MainWindow::helpA(){
    consoleOut(4);
}

void MainWindow::helpB(){
    consoleOut(5);
}

void MainWindow::doorObsA(){
    if(ui->obstructA->checkState() == Qt::Checked){
        //remove ability to move
        consoleOut(6);
    }
}

void MainWindow::doorObsB(){
    if(ui->obstructB->checkState() == Qt::Checked){
        //remove ability to move
        consoleOut(7);
    }
}

void MainWindow::fire(){
    ui->floorB1->setText("");
    ui->floorB2->setText("");
    ui->floorB3->setText("");
    ui->floorB4->setText("");
    ui->floorA1->setText("");
    ui->floorA2->setText("");
    ui->floorA3->setText("");
    ui->floorA4->setText("");
    ui->floorA1->setText("Elevator");
    ui->floorB1->setText("Elevator");
    consoleOut(8);
}

void MainWindow::overLoadA(){
    consoleOut(9);
}

void MainWindow::overLoadB(){
    consoleOut(10);
}

void MainWindow::powerout(){
    ui->floorB1->setText("");
    ui->floorB2->setText("");
    ui->floorB3->setText("");
    ui->floorB4->setText("");
    ui->floorA1->setText("");
    ui->floorA2->setText("");
    ui->floorA3->setText("");
    ui->floorA4->setText("");
    ui->floorA1->setText("Elevator");
    ui->floorB1->setText("Elevator");
    consoleOut((11));
}

void MainWindow::allocation1(){
    consoleOut(12);
}

void MainWindow::allocation2(){
    consoleOut(13);
}


// Connect elevator floor buttons
void MainWindow::connectElevatorButtons(){
    connect(ui->a1, SIGNAL(released()), this, SLOT (moveElevatorA()));
    connect(ui->a2, SIGNAL(released()), this, SLOT (moveElevatorA()));
    connect(ui->a3, SIGNAL(released()), this, SLOT (moveElevatorA()));
    connect(ui->a4, SIGNAL(released()), this, SLOT (moveElevatorA()));

    connect(ui->b1, SIGNAL(released()), this, SLOT (moveElevatorB()));
    connect(ui->b2, SIGNAL(released()), this, SLOT (moveElevatorB()));
    connect(ui->b3, SIGNAL(released()), this, SLOT (moveElevatorB()));
    connect(ui->b4, SIGNAL(released()), this, SLOT (moveElevatorB()));

    connect(ui->helpA, SIGNAL(released()), this, SLOT (helpA()));
    connect(ui->helpB, SIGNAL(released()), this, SLOT (helpB()));

    connect(ui->obstructA, SIGNAL(stateChanged(int)), this, SLOT (doorObsA()));
    connect(ui->obstructB, SIGNAL(stateChanged(int)), this, SLOT (doorObsB()));

    connect(ui->fire, SIGNAL(released()), this, SLOT (fire()));

    connect(ui->overloadA, SIGNAL(released()), this, SLOT (overLoadA()));
    connect(ui->overloadB, SIGNAL(released()), this, SLOT (overLoadB()));

    connect(ui->powerout, SIGNAL(released()), this, SLOT (powerout()));

    connect(ui->strat1, SIGNAL(clicked()), this, SLOT (allocation1()));
    connect(ui->strat2, SIGNAL(clicked()), this, SLOT (allocation2()));

}


// Connects elevator door buttons
void MainWindow::connectDoorButtons(){
    connect(ui->up1, SIGNAL(released()), this, SLOT (callElevator()));
    connect(ui->up2, SIGNAL(released()), this, SLOT (callElevator()));
    connect(ui->up3, SIGNAL(released()), this, SLOT (callElevator()));
    connect(ui->down4, SIGNAL(released()), this, SLOT (callElevator()));
    connect(ui->down3, SIGNAL(released()), this, SLOT (callElevator()));
    connect(ui->down2, SIGNAL(released()), this, SLOT (callElevator()));

}

std::string MainWindow::extractNums(std::string source){
    std::string out = "";
    for(int i = 0; i < source.length(); i++){
        if(isdigit(source[i])){
            out += source[i];
        }
    }
    return out;
}

void MainWindow::consoleOut(int in){
    switch(in){
    case -1:
        ui->out->insertPlainText("No elevator is currently available \n\n");
        break;
    case 0: // Elevator A for calling the elevator by door button
        ui->out->insertPlainText("Elevator A moves to and arrives at floor ");
        ui->out->insertPlainText(QString::number(currentFloorA) + "\n");
        ui->out->insertPlainText("The bell on floor ");
        ui->out->insertPlainText(QString::number(currentFloorA) + " rings and the door opens for 10 seconds\n");
        ui->out->insertPlainText("The passenger enters and the door on floor ");
        ui->out->insertPlainText(QString::number(currentFloorA) + " closes\n\n");
        break;

    case 1: // For moving the passenger to the desired floor
        ui->out->insertPlainText("The passenger presses the button for ");
        ui->out->insertPlainText(QString::number(currentFloorA) + "\n");
        ui->out->insertPlainText("The elevator moves to ");
        ui->out->insertPlainText(QString::number(currentFloorA) + "\n");
        ui->out->insertPlainText("The bell on floor ");
        ui->out->insertPlainText(QString::number(currentFloorA) + " rings and the door opens for 10 seconds\n");
        ui->out->insertPlainText("The passenger exits and the door on floor ");
        ui->out->insertPlainText(QString::number(currentFloorA) + " closes\n\n");
        break;

    case 2: // Elevator B for calling the elevator by door button
        ui->out->insertPlainText("Elevator B moves to and arrives at floor ");
        ui->out->insertPlainText(QString::number(currentFloorB) + "\n");
        ui->out->insertPlainText("The bell on floor ");
        ui->out->insertPlainText(QString::number(currentFloorB) + " rings and the door opens for 10 seconds\n");
        ui->out->insertPlainText("The passenger enters and the door on floor ");
        ui->out->insertPlainText(QString::number(currentFloorB) + " closes\n\n");
        break;

    case 3: // For moving the passenger to the desired floor
        ui->out->insertPlainText("The passenger presses the button for ");
        ui->out->insertPlainText(QString::number(currentFloorB) + "\n");
        ui->out->insertPlainText("Elevator B moves to floor ");
        ui->out->insertPlainText(QString::number(currentFloorB) + "\n");
        ui->out->insertPlainText("The bell on floor ");
        ui->out->insertPlainText(QString::number(currentFloorB) + " rings and the door opens for 10 seconds\n");
        ui->out->insertPlainText("The passenger exits and the door on floor ");
        ui->out->insertPlainText(QString::number(currentFloorB) + " closes\n\n");
        break;

    case 4: // Help elevator A
        ui->out->insertPlainText("The help button has been pressed by a passenger in elevator A\n");
        ui->out->insertPlainText("Elevator A is connected to the building safety service through voice\n\n");
        break;

    case 5: // Help elevator B
        ui->out->insertPlainText("The help button has been pressed by a passenger in elevator B\n");
        ui->out->insertPlainText("Elevator B is connected to the building safety service through voice\n\n");
        break;

    case 6: // A door obstacle is present in elevator A
        ui->out->insertPlainText("A door obstacle has been detected in elevator A\n");
        ui->out->insertPlainText("The door cannot close\n\n");
        break;

    case 7: // A door obstacle is present in elevator B
        ui->out->insertPlainText("A door obstacle has been detected in elevator B\n");
        ui->out->insertPlainText("The door cannot close\n\n");
        break;

    case 8: // Fire occurs all elevators are moved to floor 1
        ui->out->insertPlainText("A fire in the building has been detected \n");
        ui->out->insertPlainText("All elevators have been moved to the safest floor (default 1)\n\n");
        break;

    case 9: // Overload in elevator A
        ui->out->insertPlainText("Overload signal is sounded in elevator A\n");
        ui->out->insertPlainText("Passengers reduce the weight in elevator A to an appropriate amount\n");
        ui->out->insertPlainText("Normal operation continues \n\n");
        break;

    case 10: // Overload in Elevator B
        ui->out->insertPlainText("Overload signal is sounded in elevator B\n");
        ui->out->insertPlainText("Passengers reduce the weight in elevator B to an appropriate amount\n");
        ui->out->insertPlainText("Normal operation continues\n\n");
        break;

    case 11: // Power occurs all elevators are moved to floor 1
        ui->out->insertPlainText("A power outage in the building has been detected \n");
        ui->out->insertPlainText("All elevators have been moved to the safest floor (default 1)\n\n");
        break;

    case 12: // Allocation strat 1
        ui->out->insertPlainText("Elevators have switched to strategy 1 and will now attempt to serve the nearest floor \n\n");
        break;

    case 13: // Allocation strat 2
        ui->out->insertPlainText("Elevators have switched to strategy 1 and will now attempt to serve floor 1 first \n\n");
        break;
    }

}




