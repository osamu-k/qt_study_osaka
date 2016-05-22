#include "bincalcwidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

BinCalcWidget::BinCalcWidget(QWidget *parent)
    : QWidget(parent)
    , m_value( 0 )
{
    setAutoFillBackground( true );
    setPalette( Qt::green );

    QLabel *label = new QLabel;
    label->setAutoFillBackground( true );
    label->setPalette( Qt::yellow );
    label->setAlignment( Qt::AlignRight );

    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setReadOnly( true );
    lineEdit->setAlignment( Qt::AlignRight );

//    QPushButton *button0 = new QPushButton( "0", this );
//    QPushButton *button1 = new QPushButton( "1", this );
    QPushButton *button0 = new QPushButton( "0" );
    QPushButton *button1 = new QPushButton( "1" );

    QPushButton *buttonAdd = new QPushButton( "+" );
    QPushButton *buttonSub = new QPushButton( "-" );
    QPushButton *buttonMul = new QPushButton( "*" );
    QPushButton *buttonDiv = new QPushButton( "/" );

    QPushButton *buttonEqual = new QPushButton( "=" );
    QPushButton *buttonClear = new QPushButton( "C" );

//    button1->move(100, 50);

//    button0->show();
//    button1->show();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget( button0 );
    layout->addWidget( button1 );

    QHBoxLayout *operatorLayout = new QHBoxLayout;
    operatorLayout->addWidget( buttonAdd );
    operatorLayout->addWidget( buttonSub );
    operatorLayout->addWidget( buttonMul );
    operatorLayout->addWidget( buttonDiv );

    QHBoxLayout *commandLayout = new QHBoxLayout;
    commandLayout->addWidget( buttonEqual );
    commandLayout->addWidget( buttonClear );

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget( label );
    mainLayout->addWidget( lineEdit );
    mainLayout->addLayout( layout );
    mainLayout->addLayout( operatorLayout );
    mainLayout->addLayout( commandLayout );

    setLayout( mainLayout );

    connect( button0, SIGNAL(clicked(bool)),
             this, SLOT(numberButtonClicked()) );
    connect( button1, SIGNAL(clicked(bool)),
             this, SLOT(numberButtonClicked()) );

    connect( buttonAdd, SIGNAL(clicked(bool)),
             this, SLOT(operatorButtonClicked()) );
    connect( buttonSub, SIGNAL(clicked(bool)),
             this, SLOT(operatorButtonClicked()) );
    connect( buttonMul, SIGNAL(clicked(bool)),
             this, SLOT(operatorButtonClicked()) );
    connect( buttonDiv, SIGNAL(clicked(bool)),
             this, SLOT(operatorButtonClicked()) );

    connect( buttonEqual, SIGNAL(clicked(bool)),
             this, SLOT(equalButtonClicked()) );
    connect( buttonClear, SIGNAL(clicked(bool)),
             this, SLOT(clearButtonClicked()) );
}

BinCalcWidget::~BinCalcWidget()
{

}

void BinCalcWidget::numberButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>( sender() );
    if( button == 0 )
        return;

    qDebug() << "number "<< button->text() << " button clicked !";

    QLineEdit *lineEdit = findChild<QLineEdit *>();
    if( lineEdit == 0 )
        return;

    lineEdit->insert( button->text() );
}

void BinCalcWidget::operatorButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>( sender() );
    if( button == 0 )
        return;

    QLineEdit *lineEdit = findChild<QLineEdit *>();
    if( lineEdit == 0 )
        return;
    QString lineText = lineEdit->text();
    if( lineText.isEmpty() )
        return;
    QLabel *label = findChild<QLabel *>();
    if( label == 0 )
        return;

    m_value = lineText.toInt( 0, 2 );
    m_operator = button->text();

    lineEdit->clear();

    label->setText( lineText + " " + m_operator );
}

void BinCalcWidget::equalButtonClicked()
{
    QLineEdit *lineEdit = findChild<QLineEdit *>();
    if( lineEdit == 0 )
        return;
    QString lineText = lineEdit->text();
    if( lineText.isEmpty() )
        return;
    QLabel *label = findChild<QLabel *>();
    if( label == 0 )
        return;

    int value2 = lineText.toInt( 0, 2 );
    if( m_operator == "+" ){
        m_value = m_value + value2;
    }
    else if( m_operator == "-" ){
        m_value = m_value - value2;
    }
    else if( m_operator == "*" ){
        m_value = m_value * value2;
    }
    else if( m_operator == "/" ){
        if( value2 == 0 )
            return;
        m_value = m_value / value2;
    }

    label->setText( QString::number( m_value, 2 ) );

    lineEdit->clear();
    m_operator.clear();
}

void BinCalcWidget::clearButtonClicked()
{
    QLineEdit *lineEdit = findChild<QLineEdit *>();
    if( lineEdit == 0 )
        return;
    QLabel *label = findChild<QLabel *>();
    if( label == 0 )
        return;

    lineEdit->clear();
    label->clear();
    m_operator.clear();
    m_value = 0;
}
