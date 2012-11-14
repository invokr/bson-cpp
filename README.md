# bson-cpp

## The standalone BSON C++ implementation.

"BSON" stands for "binary JSON" - a binary storage format that is JSON inspired.

This is the C++ implementation, developed by [http://www.10gen.com/](10gen) for
[http://www.mongodb.org/](mongodb). This distribution merely rips it out of the
mongodb repository into its own.

Other BSON implementations are available for most languages at
http://bsonspec.org.

## Building

There is no need to build bson-cpp as the library is head-only.

## Installing

If you want access to the library accross your system, simply move the contents of /src 
to a directory included in your include_path (e.g. /usr/local/include).
It's a good idea to prefix the contents in case you get name-clashes with existing
files from mongodb.

## Usage

### Prerequisites

You want to include the bson header:

    #include <bson/bson.h>

Checkout the file src/bson/bsondemo/bsondemo.cpp for a quick overview.

### Creating an object

The following creates a BSON "person" object which contains name and age:

    BSONObjBuilder b;
    b.append("name", "Joe");
    b.append("age", 33);
    BSONObj p = b.obj();

Or more concisely:

    BSONObj p = BSONObjBuilder().append("name", "Joe").append("age", 33).obj();

We can also create objects with a stream-oriented syntax:

    BSONObjBuilder b;
    b << "name" << "Joe" << "age" << 33;
    BSONObj p = b.obj();

The macro BSON lets us be even more compact:

    BSONObj p = BSON( "name" << "Joe" << "age" << 33 );

### Serializing objects

Objects can be serialized by using the BufBuilder. This allows you to serialize multiple objects at once:
    
    BSONObj p = BSONObjBuilder().append("name", "Joe").append("age", 33).obj();
    BSONObj p2 = BSONObjBuilder().append("name", "Jane").append("age", 32).obj();
    BufBuilder b;
    p.appendSelfToBufBuilder( b );
    p2.appendSelfToBufBuilder( b );
    saveToFile(b.buf(), b.len());
    
You can also use the objdata() method of the BSONObj to serialize a single object:

    BSONObj p = BSONObjBuilder().append("name", "Joe").append("age", 33).obj();
    saveToFile(p.objdata(), p.objsize())
    
### Deserializing objects

Objects can be deserialized by providing the raw data as the first argument to the construct of BSONObj:

    const char* data = readFromFile(filename);
    BSONObj p(data);

BSONObj does not copy the data you provide:
    
    std::string data = readFromFileAsString(filename);
    BSONObj p(data.c_str());

    //e.g. {"my":"data"}
    std::cout << p.toString() << std::endl;

    //overwrite data variable
    data = "";

    //{}
    std::cout << p.toString() << std::endl;
    
To make sure that once your variables go out of scope and / or are modified, use the getOwned
method. This ensures that the data is actually owned by your BSONObj:

    std::string data = readFromFileAsString(filename);
    BSONObj p(data.c_str());

    if (!p.isOwned()) {
        p = p.getOwned();
    }

    //alternative:
    BSONObj p = BSONObj(data.c_str()).getOwned();

## License

The project is license under the very permissive Apache 2.0 license.

## Links

 - Origin standalone C++ Version: https://github.com/jbenet/bson-cpp
 - MongoDB: http://www.mongodb.org/
 - Bson Specs: http://www.bsonspec.org/
