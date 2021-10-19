[![Actions Status](https://github.com/inql/OnePass/workflows/Ubuntu/badge.svg)](https://github.com/inql/OnePass/actions)
[![codecov](https://codecov.io/gh/inql/OnePass/branch/main/graph/badge.svg?token=DEUYS6PCT4)](https://codecov.io/gh/inql/OnePass)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/inql/OnePass)](https://github.com/inql/OnePass/releases)

# OnePass

Program that allows user to create a database and store your passwords inside.
Database is protected with a password (minimum 20 characters long).

## Technologies used

Project was created with Modern C++ (17)
* boost (for serialization, program options, and enum creation)
* CryptoPP (for encoding/encryption)
* google test for testing
* conan for dependency management

## Prerequirements

* CMake v3.15+ - found at https://cmake.org/
* C++ Compiler - needs to support at least the C++17 standard, i.e. MSVC, GCC, Clang
* conan v1.40+ - install with `pip install conan`
  * boost v1.76.0+
  * CryptoPP v8.5.0+
  * But with conan installed, it will handle all of this :)

## Building

Create build directory:
`mkdir build && cd build`

Build executable(by default ${HOME}/bin)
```
cmake .. -DOnePass_BUILD_EXECUTABLE=1 -DCMAKE_INSTALL_PREFIX=${HOME}
cmake --build . --target install
```

Tests are being built by default.
Running tests:
`ctest -C Release`

## Features

OnePass provides console interface.

All options provided:
```
  --help                  Print this message 
  --init                  Initialize a database
  --search                search for entries
  --add                   Add or update an entry in the database
  --list                  shows the lists of passwords -keys- stored in the 
                          database
  --version               shows OnePass version
  --encrypt arg (=salsa2) Encryption algorithm, posible values: none, salsa2
  --encoding arg (=none)  Encoding, posible values: none, base64, url
  --password arg          Password for database
  --file arg (=.db)       File name and path for the database
  --key arg               A unique name for an entry in the database
  --value arg             A strong password
  --username arg          The user name associated with the password, example: 
                          user@domain.com
  --tags arg              comma separated tags, example: personal, email
  --url arg               an url, example: https://www.domain.com
  --email arg             set the email of the account
  --keyword arg           a text to find inside database
  --show                  show the actual password
  --history               shows modification history
```

### Init

Used for initializing a database.
Requires `--init` and `--password` arguments and optionally:
* `--encrypt` - encryption algorithm, salsa2 if not provided
* `--encoding` - encoding algorithm, none if not provided

```
./OnePass --init --password examplePassword!QAZ2wsx
```

Optionally, file path can be provided:

```
./OnePass --init --password examplePassword!QAZ2wsx -f ~/mydb
```
### Add

Used to add/update entry within the database.
Requires `--password`, `--add`, `--file (or default)`, `--key` arguments and at least one of the following:
* `--username`
* `--value`
* `--tags`
* `--url`

```
./OnePass --add --password examplePassword!QAZ2wsx --key github --value p@$$s\/\/0rd --username user --tags git --url https://github.com
```

### Search

Allows for searching though the database based on the keyword provided.
Requires `--search` and `--keyword` arguments and optionally:
* `--show` - shows passwords for the entries
* `--history` - shows modification history

```
./OnePass --search --keyword git --show
```



## License

This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details

## TBD

- [ ] GUI - Qt
- [ ] Interactive session
- [ ] Make doxygen work zzz
