#include "svgitem.h"
#include "mainwindow.h"

SvgItem::SvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
: QGraphicsSvgItem (parent), m_closed(false), m_failed(false), m_power(false), m_color("#008000")
{
    setElementId(id);
    setDocument(document);
    setSharedRenderer(renderer);
    setPos(renderer->boundsOnElement(elementId()).x(), renderer->boundsOnElement(elementId()).y());
}

bool SvgItem::isClosed() const
{
    return m_closed;
}

bool SvgItem::isOpened() const
{
    return !m_closed;
}

bool SvgItem::isFailed() const
{
    return m_failed;
}

bool SvgItem::isRecovered() const
{
    return !m_failed;
}

bool SvgItem::hasPower() const
{
    return m_power;
}

void SvgItem::addContact(SvgItem *contact)
{
    if (!m_contacts.contains(contact))
    {
        m_contacts.append(contact);
    }
}

void SvgItem::openNeedle()
{

}

void SvgItem::closeNeedle()
{

}

bool SvgItem::isAllContactsClosed()
{
    bool ret = true;
    foreach (auto contact, contacts())
    {
        if (!contact->hasPower())
        {
            ret = false;
        }
    }
    return ret;
}

void SvgItem::setClosed(bool value)
{
    if (value)
    {
        if (!m_closed && !isFailed())
        {
            m_closed = true;
            closeNeedle();
            setColor(QColor("red"));
            update();
            //qDebug() << QString("%1 Closed").arg(elementId());
        }
    }
    else
    {
        if (m_closed && !isFailed())
        {
            m_closed = false;
            openNeedle();
            setColor(QColor("#008000"));
            update();
            //qDebug() << QString("%1 Opened").arg(elementId());
        }
    }
}

void SvgItem::forceClose()
{
    if (isAllContactsClosed())
    {
        QMessageBox::critical(MainWindow::instance, elementId(), "Tüm uçlarda enerji varken kapatılamaz.");
        return;
    }

    if (!m_closed && !isFailed())
    {
        setClosed(true);

        QTimer::singleShot(0, this, [=]{
            QProgressBar bar;
            bar.setRange(0,0);
            bar.setMaximumHeight(MainWindow::instance->statusBar()->height() - 10);
            MainWindow::instance->statusBar()->addWidget(&bar);

            bool hasContactsPower = false;
            foreach (auto contact, contacts())
            {
                if (contact->hasPower())
                {
                    hasContactsPower = true;
                }
            }

            if (hasContactsPower)
            {
                foreach (auto contact, contacts())
                {
                    contact->powerOn();
                }
            }

            MainWindow::instance->statusBar()->removeWidget(&bar);
        });

        emit closed();
    }
}

void SvgItem::forceOpen()
{
    if (m_closed && !isFailed())
    {
        setClosed(false);

        QTimer::singleShot(0, this, [=]{
            QProgressBar bar;
            bar.setRange(0,0);
            bar.setMaximumHeight(MainWindow::instance->statusBar()->height() - 10);
            MainWindow::instance->statusBar()->addWidget(&bar);

            findItem("transformer1_box")->powerOff();
            findItem("transformer2_box")->powerOff();
            findItem("transformer1_box")->powerOn();
            findItem("transformer2_box")->powerOn();

            MainWindow::instance->statusBar()->removeWidget(&bar);
        });

        emit opened();
    }
}

QDomDocument *SvgItem::document()
{
    return m_document;
}

void SvgItem::setDocument(QDomDocument *doc)
{
    if (m_document != doc)
    {
        m_document = doc;
    }
}

QColor SvgItem::color() const
{
    return m_color;
}

void SvgItem::setColor(QColor value)
{
    if (m_color != value)
    {
        m_color = value;

        QDomElement element = findDomElementById(m_document->documentElement(), elementId());
        if (element.isNull())
        {
            qDebug() << QString("Can't find elementid = %1  in DOM tree.").arg(elementId());
            return;
        }

        setDomElementColor(element, value);
        renderer()->load(m_document->toByteArray());
    }
}

void SvgItem::setPower(bool value)
{
    if (m_power != value)
    {
        m_power = value;
        update();
        //qDebug() << QString("%1 Powered %2").arg(elementId()).arg(value ? "On" : "Off");
    }
}

void SvgItem::setFailed(bool value)
{
    if (m_failed != value)
    {
        m_failed = value;
        update();
        //qDebug() << QString("%1 Failed %2").arg(elementId()).arg(value ? "True" : "False");
        value ? emit failed() : recovered();
    }
}

QList<SvgItem *> SvgItem::contacts()
{
    return m_contacts;
}

SvgItem *SvgItem::findItem(QString id)
{
    SvgItem* result = nullptr;

    foreach (QGraphicsItem* gItem, scene()->items())
    {
        SvgItem* svgItem = dynamic_cast<SvgItem*>(gItem);

        if (svgItem && svgItem->elementId() == id)
        {
            result = svgItem;
        }
    }

    if (!result) {
        qDebug() <<  id << " bulunamadı.";
    }
    return result;
}

QDomElement SvgItem::findDomElementById(QDomElement parentElement, QString id)
{
    QDomElement result;

    for (auto element = parentElement.firstChildElement(); !element.isNull();  element = element.nextSiblingElement())
    {
        if (element.attribute("id") == id)
        {
            result = element;
            break;
        }
        else if (element.hasChildNodes())
        {
            result = findDomElementById(element, id);
        }
    }

    return result;
}

void SvgItem::setDomElementColor(QDomElement element, QColor color)
{
    element.setAttribute("stroke", color.name());

    for (int i = 0; i < element.childNodes().count(); i++)
    {
        auto children = element.childNodes().at(i).toElement();
        setDomElementColor(children, color);
    }
}

void SvgItem::powerOnContacts()
{
    foreach (SvgItem* contact, contacts())
    {
        contact->powerOn();
    }
}

void SvgItem::powerOffContacts()
{
    foreach (SvgItem* contact, contacts())
    {
        contact->powerOff();
    }
}

void SvgItem::powerOn()
{
    if (!hasPower())
    {
        //qDebug() << QString("%1 PowerOn").arg(elementId());
        setPower(true);
        QApplication::processEvents();
        powerOnContacts();
    }
}

void SvgItem::powerOff()
{
    if (hasPower())
    {
        //qDebug() << QString("%1 PowerOff").arg(elementId());
        setPower(false);
        QApplication::processEvents();
        powerOffContacts();
    }
}

void SvgItem::close()
{
    if (!isClosed())
    {
        QMessageBox question(MainWindow::instance);
        question.setWindowTitle(elementId().split("_").first().toUpper());
        question.setText(QString("%1 nolu cihaz kapatılacak.\nDevam etmek istiyor musunuz?").arg(elementId().split("_").last().toUpper()));
        QAbstractButton *buttonNo = question.addButton("Hayır", QMessageBox::ButtonRole::NoRole);
        QAbstractButton *buttonYes = question.addButton("Evet", QMessageBox::ButtonRole::YesRole);
        question.exec();

        if (question.clickedButton() == buttonYes)
        {
            forceClose();
        }
    }
}

void SvgItem::open()
{
    if (!isOpened())
    {
        QMessageBox question(MainWindow::instance);
        question.setWindowTitle(elementId().split("_").first().toUpper());
        question.setText(QString("%1 nolu cihaz açılacak.\nDevam etmek istiyor musunuz?").arg(elementId().split("_").last().toUpper()));
        QAbstractButton *buttonNo = question.addButton("Hayır", QMessageBox::ButtonRole::NoRole);
        QAbstractButton *buttonYes = question.addButton("Evet", QMessageBox::ButtonRole::YesRole);
        question.exec();

        if (question.clickedButton() == buttonYes)
        {
            forceOpen();
        }
    }
}

void SvgItem::fail()
{
    if (!isFailed())
    {
        QPainterPath path(QPointF(0,0));
        path.lineTo(boundingRect().bottomRight());
        path.moveTo(boundingRect().topRight());
        path.lineTo(boundingRect().bottomLeft());

        m_redcross = scene()->addPath(mapToScene(path), QPen(QColor("red"), 4));
        m_failed = true;
        emit failed();
    }
}

void SvgItem::recover()
{
    if (!isRecovered())
    {
        scene()->removeItem(m_redcross);
        m_failed = false;
        emit recovered();
    }
}
