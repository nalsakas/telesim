#ifndef SVGITEM_H
#define SVGITEM_H

#include <QtWidgets>
#include <QtSvg>
#include <QtXml>

class SvgItem : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    enum {A = UserType + 1, YA, MA, K, LINE, RAIL, TEXT, BOX, YST, GT};
    SvgItem(QDomDocument* document, QSvgRenderer* renderer, QString id, QGraphicsItem *parent = nullptr);
    bool isOpened() const;
    bool isClosed() const;
    bool isAllContactsClosed();
    void setClosed(bool value);
    bool isFailed() const;
    void setFailed(bool value);
    bool isRecovered() const;
    bool hasPower() const;
    void setPower(bool value);
    void powerOnContacts();
    void powerOffContacts();
    QColor color() const;
    void setColor(QColor value);
    QList<SvgItem *> contacts();
    void addContact(SvgItem* contact);

protected:
    virtual void openNeedle();
    virtual void closeNeedle();
    QDomDocument *document();
    void setDocument(QDomDocument *doc);
    SvgItem *findItem(QString id);
    QDomElement findDomElementById(QDomElement parentElement, QString id);
    virtual void setDomElementColor(QDomElement element, QColor color);

public slots:
    virtual void powerOn();
    virtual void powerOff();
    virtual void forceOpen();
    virtual void forceClose();
    void open();
    void close();
    void fail();
    void recover();


signals:
    void closed();
    void opened();
    void failed();
    void recovered();

private:
    bool m_closed;
    bool m_failed;
    bool m_power;
    QColor m_color;

    QDomDocument* m_document;
    QGraphicsPathItem* m_redcross;
    QList<SvgItem*> m_contacts;

    // QGraphicsItem interface
public:
    virtual int type() const override = 0;
};

#endif // SVGITEM_H
