# ESPOTIFAI-API

### Overview

This repository contains the implementation of espotifai-api, which provides the basic
functionalities of Spotify API to the espotifai-gui application.

### Dependencies

All the dependencies below have support for Linux/Windows/MacOS

- boost
- gtest
- jsoncpp
- libcurl
- mongocxx

### Build the lib

```bash
$ git clone https://github.com/carvalhudo/espotifai-api
$ cd espotifai-api
$ cmake . -B build
$ cmake --build build
```

### Running the tests

```bash
$ cd tests
$ cmake . -B build
$ cmake --build build
$ ./espotifai_api_tests
```
