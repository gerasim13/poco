//
// Array.h
//
// Library: MongoDB
// Package: MongoDB
// Module:  ObjectId
//
// Definition of the ObjectId class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef MongoDB_ObjectId_INCLUDED
#define MongoDB_ObjectId_INCLUDED


#include "Poco/MongoDB/MongoDB.h"
#include "Poco/MongoDB/Element.h"
#include "Poco/Timestamp.h"


namespace Poco {
namespace MongoDB {


class MongoDB_API ObjectId
	/// ObjectId is a 12-byte BSON type, constructed using:
	///
	///   - a 4-byte timestamp,
	///   - a 3-byte machine identifier,
	///   - a 2-byte process id, and
	///   - a 3-byte counter, starting with a random value.
	///
	/// In MongoDB, documents stored in a collection require a unique _id field that acts
	/// as a primary key. Because ObjectIds are small, most likely unique, and fast to generate,
	/// MongoDB uses ObjectIds as the default value for the _id field if the _id field is not
	/// specified; i.e., the mongod adds the _id field and generates a unique ObjectId to assign
	/// as its value.
{
public:
	typedef SharedPtr<ObjectId> Ptr;

	explicit ObjectId(const std::string& id);
		/// Creates an ObjectId from a string.
		///
		/// The string must contain a hexadecimal representation
		/// of an object ID. This means a string of 24 characters.

	ObjectId(const ObjectId& copy);
		/// Creates an ObjectId by copying another one.

	virtual ~ObjectId();
		/// Destroys the ObjectId.

	Timestamp timestamp() const;
		/// Returns the timestamp which is stored in the first four bytes of the id

	std::string toString(const std::string& fmt = "%02x") const;
		/// Returns the id in string format. The fmt parameter
		/// specifies the formatting used for individual members
		/// of the ID char array.

private:
	ObjectId();

	static int fromHex(char c);	
	static char fromHex(const char* c);
	
	unsigned char _id[12];

	friend class BSONWriter;
	friend class BSONReader;
	friend class Document;
};


//
// inlines
//
inline Timestamp ObjectId::timestamp() const
{
	int time;
	char* T = (char *) &time;
	T[0] = _id[3];
	T[1] = _id[2];
	T[2] = _id[1];
	T[3] = _id[0];
	return Timestamp::fromEpochTime((time_t) time);
}


inline int ObjectId::fromHex(char c)
{
	switch (c) {
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'a':
		case 'A':
			return 0xa;
		case 'b':
		case 'B':
			return 0xb;
		case 'c':
		case 'C':
			return 0xc;
		case 'd':
		case 'D':
			return 0xd;
		case 'e':
		case 'E':
			return 0xe;
		case 'f':
		case 'F':
			return 0xf;
		default:
			break;
	}
	return 0;
}


inline char ObjectId::fromHex(const char* c)
{
	return (char)((fromHex(c[0]) << 4 ) | fromHex(c[1]));
}


// BSON Embedded Document
// spec: ObjectId
template<>
struct ElementTraits<ObjectId::Ptr>
{
	enum { TypeId = 0x07 };

	static std::string toString(const ObjectId::Ptr& id,
		int indent = 0,
		const std::string& fmt = "%02x")
	{
		return id->toString(fmt);
	}
};


template<>
inline void BSONReader::read<ObjectId::Ptr>(ObjectId::Ptr& to)
{
	_reader.readRaw((char*) to->_id, 12);
}


template<>
inline void BSONWriter::write<ObjectId::Ptr>(ObjectId::Ptr& from)
{
	_writer.writeRaw((char*) from->_id, 12);
}


} } // namespace Poco::MongoDB


#endif // MongoDB_ObjectId_INCLUDED
