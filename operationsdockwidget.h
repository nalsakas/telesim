#ifndef OPERATIONSDOCKWIDGET_H
#define OPERATIONSDOCKWIDGET_H

#include <QtWidgets>

class OperationsDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit OperationsDockWidget(QWidget *parent = nullptr);
    ~OperationsDockWidget();

    void updateModelAll();
    void updateModelNotr1();
    void updateModelNotr2();
    void updateModelStation1();
    void updateModelStation2();
    void updateModelStation3();
    void updateModelStation4();
    void updateModelStation5();
    void updateModelTransformer1();
    void updateModelTransformer2();

signals:
    void itemOpened(QString text);
    void itemClosed(QString text);

public slots:
    void on_buttonClicked(int id);
    void reload();
    void on_itemChanged(QStandardItem* item);

private:
    QStandardItemModel* model;
    QTreeView* treeView;
    int buttonState;
};

#endif // OPERATIONSDOCKWIDGET_H
