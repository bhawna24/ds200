cmake_minimum_required(VERSION 3.8)
project(MINIRELVER2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES

        algebra/delete.c
        algebra/select.c
        algebra/insert.c
        algebra/project.c
        schema/destroy.c
        include/defs.h
        include/error.h
        physical/functions.c
        run/main.c
        physical/error.c
        schema/createdb.c
        physical/createcats.c
        schema/opendb.c
        schema/closedb.c
        schema/create.c
        schema/print.c
        schema/load.c
        schema/destroydb.c
        physical/findrelnum.c
        physical/opencats.c
        physical/findrec.c
        physical/getnextrec.c
        physical/readpage.c
        physical/flushpage.c
        physical/closecats.c
        physical/closerel.c
        physical/writerec.c
        physical/openrel.c
        physical/insertrec.c
        physical/deleterec.c
        )

add_executable(MINIRELVER2 ${SOURCE_FILES} )