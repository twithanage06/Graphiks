#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QTimer>
#include <QScrollBar>

#include <exception>
#include <string>
#include <valarray>
#include <vector>

#include "tokeniser.hpp"
#include "parser.hpp"
#include "evaluator.hpp"

double calculate(const std::string& equation) {
    auto tokens = tokenise(equation);

    Parser parser(tokens);
    auto tree = parser.parse();

    return evaluator(*tree);
}

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    //Makes window
    QWidget window;
    window.setStyleSheet(R"(
    QWidget {
        background-color: white;
    }

    QLineEdit {
        background-color: white;
        color: black;
    }

    QLabel {
        color: black;
    }
    )");

    window.setWindowTitle("Graphiks");
    window.resize(450,300);
    //Splits the window into vertical stacks for widgets
    QVBoxLayout *layout = new QVBoxLayout(&window);
    
    //Calculation history
    QScrollArea *scroll = new QScrollArea(&window);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    QWidget *history = new QWidget();
    QVBoxLayout *historyLayout = new QVBoxLayout(history);
    historyLayout->setAlignment(Qt::AlignTop);
    scroll->setWidget(history);

    //Inputbox
    QLineEdit *input = new QLineEdit(&window);
    input->setPlaceholderText("Enter an expression...");
    layout->addWidget(scroll, 1);
    layout->addWidget(input);

    //Gets the text from the input box and outputs the relevant information to the history box
    auto renderExpression = [input, historyLayout, scroll]() {
        //Get the text
        QString expression = input->text();

        //Convert it to a regular string so tokeniser can use it
        std::string equation = expression.toStdString();

        //This shows the expression
        QLabel *expressionLabel = new QLabel(expression);
        historyLayout->addWidget(expressionLabel);

        //Calculate the answer and clear the textbox if the calculation was succesful
        double answer = calculate(equation);
        input->clear();

        //Make a label for answer and align it to the right
        QLabel *resultLabel = new QLabel(QString::number(answer));
        resultLabel->setAlignment(Qt::AlignRight);
        historyLayout->addWidget(resultLabel);

        //Make the scrollbar follow the equations instead of staying at the top
        QTimer::singleShot(0, scroll, [scroll]() {
            auto bar = scroll->verticalScrollBar();
            bar->setValue(bar->maximum());
        });

        //For debugging
        qDebug() << expression;
    };
    //Helper to keep the scrollbar down
    QScrollBar *bar = scroll->verticalScrollBar();
    QObject::connect(bar, &QScrollBar::rangeChanged, scroll, [bar](int min, int max) {
        bar->setValue(max);
    });

    QObject::connect(input, &QLineEdit::returnPressed, &window, renderExpression);

    window.show();
    return app.exec();
}