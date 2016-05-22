#ifndef BINCALCWIDGET_H
#define BINCALCWIDGET_H

#include <QWidget>

class BinCalcWidget : public QWidget
{
    Q_OBJECT

public:
    BinCalcWidget(QWidget *parent = 0);
    ~BinCalcWidget();

private slots:
    void numberButtonClicked();
    void operatorButtonClicked();
    void equalButtonClicked();
    void clearButtonClicked();

private:
    QString m_operator;
    int m_value;
};

#endif // BINCALCWIDGET_H
