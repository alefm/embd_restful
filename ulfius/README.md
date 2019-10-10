# Ulfius Mock

## Prerequisitos
O Ulfius utilizado no mock possui as seguintes dependencias:

* libmicrohttpd (required), minimum 0.9.53 if you require Websockets support
* liborcania (required), for ulfius common functions
* libjansson (optional), minimum 2.4, required for json support
* libgnutls, libgcrypt (optional), required for Websockets and https support

A instalação do Ulfius é bem simples e está bem descrita na sua [documentação](https://github.com/babelouest/ulfius/blob/master/INSTALL.md), disponível no github.

Para compilação da biblioteca foi utilizado os seguintes comandos:

```console
$ git clone https://github.com/babelouest/ulfius.git
$ cd ulfius
$ make YDERFLAG=1 WEBSOCKETFLAG=1 CURLFLAG=1
$ sudo make install
```

## Instalação

```console
$ cd /ulfius
$ mkdir build && cd build
$ cmake ../
$ make && sudo make install
```

Cross-Compile
```console
$ cd /ulfius
$ mkdir build && cd build
$ cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-RaspberryPi.cmake ../
$ make
```

## Banco de dados

O banco de dados que será utilizado é o sqlite3
