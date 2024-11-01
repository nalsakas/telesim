#include "stationsdockwidget.h"

StationsDockWidget::StationsDockWidget(QWidget *parent) :
    QDockWidget(parent)
{
    QWidget* widget = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout;

    QPushButton* buttonAll = new QPushButton("HEPSİ");
    buttonAll->setCheckable(true);
    buttonAll->setChecked(true);
    layout->addWidget(buttonAll);

    QPushButton* buttonNotr1 = new QPushButton("NÖTR 1");
    buttonNotr1->setCheckable(true);
    layout->addWidget(buttonNotr1);

    QPushButton* buttonStation1 = new QPushButton("İSTASYON 1");
    buttonStation1->setCheckable(true);
    layout->addWidget(buttonStation1);

    QPushButton* buttonTransformer1 = new QPushButton("TRAFO 1");
    buttonTransformer1->setCheckable(true);
    layout->addWidget(buttonTransformer1);

    QPushButton* buttonStation2 = new QPushButton("İSTASYON 2");
    buttonStation2->setCheckable(true);
    layout->addWidget(buttonStation2);

    QPushButton* buttonStation3 = new QPushButton("İSTASYON 3");
    buttonStation3->setCheckable(true);
    layout->addWidget(buttonStation3);

    QPushButton* buttonNotr2 = new QPushButton("NÖTR 2");
    buttonNotr2->setCheckable(true);
    layout->addWidget(buttonNotr2);

    QPushButton* buttonStation4 = new QPushButton("İSTASYON 4");
    buttonStation4->setCheckable(true);
    layout->addWidget(buttonStation4);

    QPushButton* buttonTransformer2 = new QPushButton("TRAFO 2");
    buttonTransformer2->setCheckable(true);
    layout->addWidget(buttonTransformer2);

    QPushButton* buttonStation5 = new QPushButton("İSTASYON 5");
    buttonStation5->setCheckable(true);
    layout->addWidget(buttonStation5);

    widget->setLayout(layout);

    group = new QButtonGroup(this);
    group->setExclusive(true);
    group->addButton(buttonAll, ALL);
    group->addButton(buttonNotr1, NOTR1);
    group->addButton(buttonStation1, STATION1);
    group->addButton(buttonTransformer1, TRANSFORMER1);
    group->addButton(buttonStation2, STATION2);
    group->addButton(buttonStation3, STATION3);
    group->addButton(buttonNotr2, NOTR2);
    group->addButton(buttonStation4, STATION4);
    group->addButton(buttonTransformer2, TRANSFORMER2);
    group->addButton(buttonStation5, STATION5);

    connect(group, SIGNAL(buttonClicked(int)), this, SIGNAL(buttonClicked(int)));

    setWidget(widget);
    setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

    QTimer::singleShot(0, this, [=]{emit buttonClicked(ALL);});
}
