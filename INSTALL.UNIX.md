 - [ ] 1. Install `OpenSSL@1.0.2g`
```bash
$ echo "Install OpenSSL@1.0.2g"
$ wget https://github.com/openssl/openssl/archive/OpenSSL_1_0_2g.tar.gz -O OpenSSL_1_0_2g.tar.gz
$ tar -xf OpenSSL_1_0_2g.tar.gz && cd openssl-OpenSSL_1_0_2g
$ ./config
$ make && sudo make install
$ cd .. && rm -rf openssl-OpenSSL_1_0_2g && rm -f OpenSSL_1_0_2g.tar.gz
```

 - [ ] 2. Install `CURL@7.4.8`
```bash
$ echo "Install CURL@7.4.8"
$ wget https://github.com/curl/curl/archive/curl-7_48_0.tar.gz -O curl-7_48_0.tar.gz
$ tar -xf curl-7_48_0.tar.gz && cd curl-curl-7_48_0
$ mkdir build && cd build
$ cmake ..
$ make && sudo make install
$ cd ../.. && rm -rf curl-curl-7_48_0 && rm -f curl-7_48_0.tar.gz
```

 - [ ] 3. Install `pugixml@1.7.0`
```bash
$ echo "Install pugixml@1.7.0"
$ wget https://github.com/zeux/pugixml/releases/download/v1.7/pugixml-1.7.tar.gz -O pugixml-1.7.tar.gz
$ tar -xf pugixml-1.7.tar.gz && cd pugixml-1.7
$ mkdir build && cd build 
$ cmake ../scripts/
$ make && sudo make install
$ cd ../.. && rm -rf pugixml-1.7 && rm -f pugixml-1.7.tar.gz
```
 - [ ] 4. Install `webdavclient@1.0.0`
```bash
$ echo "Install webdavclient@1.0.0"
$ wget https://github.com/designerror/webdav-client-cpp/archive/v1.0.0.tar.gz -O webdavclient-0.9.9.tar.gz
$ tar -xf webdavclient-1.0.0.tar.gz && cd webdav-client-cpp-1.0.0
$ mkdir build && cd build
$ cmake ..
$ make && sudo make install
$ cd ../.. && rm -rf webdav-client-cpp-1.0.0 && rm -f webdavclient-1.0.0.tar.gz
```

 - [ ] 5. Building tests for `webdavclient@1.0.0`
```bash
$ echo "Building tests for webdavclient@1.0.0"
$ wget https://github.com/designerror/webdav-client-cpp/archive/v1.0.0.tar.gz -O webdavclient-1.0.0.tar.gz
$ tar -xf webdavclient-1.0.0.tar.gz && cd webdav-client-cpp-1.0.0
$ mkdir build && cd build
$ cmake .. && make
$ ctest
$ cd ../.. && rm -rf webdav-client-cpp-1.0.0 && rm -f webdavclient-1.0.0.tar.gz
```
