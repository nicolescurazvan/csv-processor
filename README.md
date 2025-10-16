# csv-processor

A simple C++ API to parse and process CSV files. It uses a 2D array of strings
as data and an array of strings as a header. The class is called `CSVDataFrame`.
The rows and the columns are counted from 0.

## Functions

* `CSVDataFrame(const char *path)`: constructor (from a file)
* `CSVDataFrame(CSVDataFrame &frm)`: copy constructor
* `std::string get(int row, int col)`: Returns the field at the row `row`
and the column `col` (an integer).
* `std::string get(int row, std::string col)`: Returns the field at the row
`row` and the column named `col`.
* `void change(int row, int col, std::string name)`: Changes the field located
at the row `row` and column `col` (an integer) with the value `name`.
* `void change(int row, std::string col, std::string name)`: Changes the field
located at the row `row` and the column named `col` with the value `name`.
* `void add_record()`: Adds a record at the end.
* `void add_record(int pos)`: Adds a record at the row `pos`. 
* `void delete_record(int pos)`: Deletes the record located at the row `pos`.
* `void add_column(int pos, std::string name)`: Adds a column at the position 
`pos` and the name is set to `name`.
* `void delete_column(int pos)`: Deletes the `pos`-th column.
* `void delete_column(std::string name)`: Deletes the column named `name`.
* `void filter(int col, bool (*predicate)(std::string))`: Filters the table
based on the `col`-th column values and the boolean function `predicate`. Basically,
it removes the rows where the `col`-th value doesn't pass the predicate.
* `void filter(std::string name, bool (*predicate)(std::string))`: Filters the
table based on the values on the column named `name` depending on the predicate
`predicate`.