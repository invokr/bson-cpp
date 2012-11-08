# bson-cpp

## The standalone BSON C++ implementation.

"BSON" stands for "binary JSON" - a binary storage format that is JSON inspired.

This is the C++ implementation, developed by [http://www.10gen.com/](10gen) for
[http://www.mongodb.org/](mongodb). This distribution merely rips it out of the
mongodb repository into its own.

Other BSON implementations are available for most languages at
http://bsonspec.org.

## Building

This project uses cmake as its build system.
To build the projects, run the following commands. You will find a shared library in dist/lib and a demo executable in dist/bin.

    cd /path/to/projectsource
    mkdir build && cd build
    cmake .. && make

## Installing

There is no install script / Makefile included.
You can use the library by adding src/ to the include path and dist/lib to the link path.

## Usage

### Prerequisites

You want to link against the library, and include the bson header:

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

## License

The project is license under the very permissive Apache 2.0 license.
Checkout the source files for more information on it.

## Links

 - Origin standalone C++ Version: https://github.com/jbenet/bson-cpp
 - MongoDB: http://www.mongodb.org/
 - Bson Specs: http://www.bsonspec.org/
