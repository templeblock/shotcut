/*
 * Copyright (c) 2012 Meltytech, LLC
 * Author: Dan Dennedy <dan@dennedy.org>
 *
 * GL shader based on BSD licensed code from Peter Bengtsson:
 * http://www.fourcc.org/source/YUV420P-OpenGL-GLSLang.c
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MELTEDPLAYLISTMODEL_H
#define MELTEDPLAYLISTMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtNetwork/QTcpSocket>
#include <mvcp.h>

class MeltedPlaylistModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        COLUMN_ACTIVE = 0,
        COLUMN_INDEX,
        COLUMN_RESOURCE,
        COLUMN_IN,
        COLUMN_OUT,
        COLUMN_COUNT
    };

    enum MvcpCommands {
        MVCP_IGNORE,
        MVCP_LIST,
        MVCP_GOTO
    };

    explicit MeltedPlaylistModel(QObject *parent = 0);
    ~MeltedPlaylistModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//    Qt::DropActions supportedDropActions() const;
//    bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
//    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
//    Qt::ItemFlags flags(const QModelIndex &index) const;
//    QStringList mimeTypes() const;
//    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

    void gotoClip(int);

signals:
    void loaded();

public slots:
    void onConnected(const QString& address, quint16 port = 5250, quint8 unit = 0);
    void onDisconnected();
    void refresh();
    void onUnitChanged(quint8 unit);
    void onClipIndexChanged(quint8 unit, int index);
    void onGenerationChanged(quint8 unit);

private slots:
    void readResponse();
//    void onSocketError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket m_socket;
    quint8 m_unit;
    mvcp_list m_list;
    mvcp_response m_response;
    int m_index;
    QList<int> m_commands;
};

#endif // MELTEDPLAYLISTMODEL_H
