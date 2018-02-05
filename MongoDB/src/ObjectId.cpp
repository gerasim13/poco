//
// ObjectId.cpp
//
// Library: MongoDB
// Package: MongoDB
// Module:  ObjectId
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/MongoDB/ObjectId.h"
#include "Poco/Format.h"
#include <cstring>


namespace Poco {
namespace MongoDB {


ObjectId::ObjectId()
{
	std::memset(_id, 0, sizeof(_id));
}


ObjectId::ObjectId(const std::string& id)
{
	poco_assert_dbg(id.size() == 24);

	for(std::size_t i = 0; i < id.length(); i += 2)
	{
		_id[i] = (unsigned char)strtoul(id.substr(i, 2).c_str(), 0, 16);
	}
}


ObjectId::ObjectId(const ObjectId& copy)
{
	std::memcpy(_id, copy._id, sizeof(_id));
}


ObjectId::~ObjectId()
{
}


std::string ObjectId::toString(const std::string& fmt) const
{
	std::string s;

	for (int i = 0; i < 12; ++i)
	{
		s += format(fmt, (unsigned int) _id[i]);
	}
	return s;
}


} } // namespace Poco::MongoDB
