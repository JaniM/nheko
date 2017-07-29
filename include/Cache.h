/*
 * nheko Copyright (C) 2017  Konstantinos Sideris <siderisk@auth.gr>
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

#pragma once

#include <lmdb++.h>

#include "RoomState.h"

class Cache
{
public:
	Cache(const QString &userId);

	void insertRoomState(const QString &roomid, const RoomState &state);
	void setNextBatchToken(const QString &token);
	bool isInitialized();

	QString nextBatchToken();
	QMap<QString, RoomState> states();

	inline void unmount();
	inline QString memberDbName(const QString &roomid);

private:
	lmdb::env env_;
	lmdb::dbi stateDb_;
	lmdb::dbi roomDb_;

	bool isMounted_;

	QString userId_;
};

inline void Cache::unmount()
{
	isMounted_ = false;
}

inline QString Cache::memberDbName(const QString &roomid)
{
	return QString("m.%1").arg(roomid);
}
