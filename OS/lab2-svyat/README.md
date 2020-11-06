# OS lab2 

## Description

### It's a server application for FreeBSD that can create processes, get system info, and get list pf processes

## Installation

* clone repository
  ```
  git clone https://github.com/DebDoDab/Itmem.git
  ```
* move to directory
  ```
  cd ItMem/OS/lab2-svyat
  ```
* build and execute application
  ```
  mkdir build
  cd build
  cmake ..
  make
  sudo ./lab2-svyat
  ```
  
## List of methods

* GET /ps
  
* GET /system_info
  
* POST /create_process
    * {"command": "...", "args": "...", "uid": "...", "type": "background/foreground"}
    * return "OK" if type == "background" else {"exitcode": "...", "output": "..."}
  
* POST /kill
  	* return "OK"

## Usage

### Use curl to go http queries

```
curl -X GET http://localhost:8083/ps
```

```
curl -X POST -d '{"command": "grep", "args": "-ri processes .", "uid": "123456", "type": "foreground"}' http://localhost:8083/create_process
```
      
