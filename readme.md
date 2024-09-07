
```bash
# from ./
# should make and the program 

sudo apt-get install postgresql postgresql-contrib 
sudo apt-get install libpq-dev

cd third_party
sh sqlite_build.sh
cd ..
make
```

### params

```bash
db_type=postgres            # not required will fallback to sqlite
host=localhost              # not required will fallback to localhost 
port=5432                   # not required will fallback to 5432, not needed for sqlite
user=postgres               # not required will fallback to postgres, not needed for sqlite 
pass=test_pass              # not required if you dont need it
dbname=dbname               # required
dbtable=dbtablename         # required 
dbfield=dbfieldname         # required
```

### usage for sqlite
```bash
./bin/prog  dbname=./database/oscar.sqlite3 dbtable=oscar dbfield=year
```
### usage for postgres
```bash
./bin/prog db_type=postgres host=localhost port=5432 user=postgres pass=yourpass dbname=postgres dbtable=oscar dbfield=year
```

### sqlite example output
```
Args
Database        SQLite
Username:       N/A
Password:       Not supplied
DB Name         ./database/oscar.sqlite3
DB Table        oscar
DB Field        year
SQLite selected... starting
Successfully opened ./database/oscar.sqlite3
Summary: 
Avg             1972.50
Min             1928.00
Max             2017.00
Sum             177525.00
Dispersion      674.92
Shutting down ./database/oscar.sqlite3
```

### postgres example output

```
Args
Database        Postgres
Username:       N/A
Password:       ********
DB Name         postgres
DB Table        oscar
DB Field        year

Postgres selected... starting
Connection ok
Got results from query: SELECT year FROM oscar
Processing numeric values
Summary: 
Avg             1950.09
Min             0.00
Max             2016.00
Sum             175508.00
Dispersion      43381.28
```
