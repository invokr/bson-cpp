add_library(bson SHARED
    bson/oid.cpp
    mongo/nonce.cpp
    mongo/md5.cpp
    mongo/md5main.cpp
)

target_link_libraries(bson
    ${Boost_SYSTEM_LIBRARY}
)

add_executable(bsondemo
    bson/bsondemo/bsondemo.cpp
)

target_link_libraries(bsondemo
    bson
)
