/* BEGIN_COMMON_COPYRIGHT_HEADER
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * https://sourceforge.net/projects/razor-qt/
 *
 * Copyright: 2010-2011 Razor team
 * Authors:
 *   Petr Vanek <petr@scribus.info>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "helloworld.h"
#include <QtDebug>
#include <QGraphicsScene>
#include <QInputDialog>


EXPORT_RAZOR_DESKTOP_WIDGET_PLUGIN_CPP(HelloWorld)


HelloWorld::HelloWorld(QGraphicsScene * scene, const QString & configId, ReadSettings * config)
    : DesktopWidgetPlugin(scene, configId, config)
{
    QSettings * s = config->settings();
    s->beginGroup(configId);
    
    setOpenExternalLinks(true);
    QString text(s->value("text", "Lorem Ipsum").toString());
    setHtml(text);
    
    QString color(s->value("color", "").toString());
    if (! color.isEmpty())
        setDefaultTextColor(QColor(color));

    QFont f = font();
    f.setPixelSize(48);
    setFont(f);
    
    //setFlag(QGraphicsItem::ItemIsMovable);
    
    s->endGroup();
}

HelloWorld::~HelloWorld()
{
}

    
QString HelloWorld::info()
{
    return QObject::tr("Display simple text. A debugging/sample widget.");
}

QString HelloWorld::instanceInfo()
{
    return tr("Hello World:") + " " + m_configId;
}

void HelloWorld::setSizeAndPosition(const QPointF & position, const QSizeF & size)
{
    qDebug() << "Moving to" << position;
    setPos(position);
}

void HelloWorld::configure()
{
    bool ok;
    QString txt = QInputDialog::getText(0, tr("Display Text Configuretion"), tr("Edit HTML"), QLineEdit::Normal, toHtml(), &ok);
    if (!ok)
        return;
    setHtml(txt);
    save();
}

void HelloWorld::save()
{
    QSettings *s = m_config->settings();
    s->beginGroup(m_configId);
    s->setValue("plugin", "helloworld");
    s->setValue("x", pos().x());
    s->setValue("y", pos().y());
    s->setValue("w", boundingRect().width());
    s->setValue("h", boundingRect().height());
    s->setValue("text", toHtml());
    s->setValue("color", defaultTextColor().name());
    s->endGroup();
}