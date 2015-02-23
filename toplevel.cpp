/***************************************************************************
 *   Copyright (C) 2013 by CSSlayer <wengxt@gmail.com>                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include <QBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

#include "toplevel.h"

TopLevel::TopLevel(QWidget* parent) : QWidget(parent,
                                              Qt::Tool | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus
                                            | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->setMargin(0);
    lay->setSpacing(0);
    setLayout(lay);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void TopLevel::setCenterWidget(QWidget* widget)
{
    if (m_widget) {
        m_widget->removeEventFilter(this);
        layout()->removeWidget(m_widget);
    }
    m_widget = widget;
    widget->installEventFilter(this);
    widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout()->addWidget(widget);
    layout()->activate();//?
}

void TopLevel::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    setMask(rect());
    updateLocation();
}

bool TopLevel::eventFilter(QObject* object, QEvent* event)
{
    if (object == m_widget.data() &&
        event->type() == QEvent::Resize) {
        setMinimumSize(m_widget->sizeHint());
        setMaximumSize(m_widget->sizeHint());
    }
    return QObject::eventFilter(object, event);
}

void TopLevel::resizeEvent(QResizeEvent* resize)
{
    QWidget::resizeEvent(resize);
    setMask(rect());
    updateLocation();
}

void TopLevel::setSpotRect(const QRect& rect)
{
    m_spotRect = rect;
    updateLocation();
}

void TopLevel::updateLocation()
{
    if (this->isVisible() == false)
        return;

    QRect screenRect = QApplication::desktop()->screenGeometry(QPoint(m_spotRect.x(), m_spotRect.y()));
    int x;
    x = qMin(m_spotRect.x(), screenRect.x() + screenRect.width() - width());
    x = qMax(x, screenRect.x());
    int oy = m_spotRect.y() + m_spotRect.height();
    int y = oy + 10;
    if (y < screenRect.y()) {
        y = screenRect.y();
    }

    if (y > screenRect.y() + screenRect.height()) {
        y = screenRect.height();
    }

    if (y + height() > screenRect.y() + screenRect.height()) {
        /// minus 20 to make preedit bar never overlap the input context
        y = oy - (height() + ((m_spotRect.height() == 0)?20:(m_spotRect.height() + 10)));
    }

    QPoint p(x, y);
    if (p != pos())
        move(p);
}

void TopLevel::setTopLevelVisible(bool aux, bool preedit, bool lookupTable)
{
    this->setVisible(aux || preedit || lookupTable);
}
