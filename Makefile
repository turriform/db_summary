CC:=gcc
TARGET:=prog

FLAGS:= -std=c11  -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -g 
          #-fsanitize=address

INCLUDE:= -I./include
LIBS:= -lm

SQLITE_INCLUDE:= -I./third_party/sqlite/include
SQLITE_LIB:= -L./third_party/sqlite/lib -lsqlite3

INCLUDE+= $(SQLITE_INCLUDE)
LIBS+= $(SQLITE_LIB)

POSTGRES_INCLUDE:= -I/usr/include/postgresql
POSTGRE_LIB:= -L/usr/lib/pgsql -lpq

INCLUDE+=$(POSTGRES_INCLUDE)
LIBS+=$(POSTGRE_LIB)

POSTGRES_PASS:=yourpassword

ARGS:= db_type=postgres host=localhost port=5432 user=postgres pass=$(POSTGRES_PASS) dbname=postgres dbtable=oscar dbfield=year

ARGS_MINIMAL_PG:= db_type=postgres pass=test_pass dbname=postgres dbtable=oscar dbfield=year


#db_type will fallback to SQLITE anyway
ARGS_SQLITE:= dbname=./database/oscar.sqlite3 dbtable=oscar dbfield=year

C_SRC:= $(wildcard ./src/*.c)



all:
	$(CC) $(C_SRC) $(INCLUDE) $(FLAGS) $(LIBS) -o ./bin/$(TARGET) && ./bin/$(TARGET) $(ARGS_SQLITE)

