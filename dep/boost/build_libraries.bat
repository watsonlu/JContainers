b2 variant=release link=static threading=multi runtime-link=static --with-serialization --with-date_time --with-filesystem --with-thread --build-dir=garbage --stagedir=boost_lib stage


DEL /q /s garbage

