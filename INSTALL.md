**Ubuntu**

```bash
# Install OpenSSL

wget https://github.com/openssl/openssl/archive/OpenSSL_1_0_2g.tar.gz -O OpenSSL_1_0_2g.tar.gz
tar -xf OpenSSL_1_0_2g.tar.gz && cd OpenSSL_1_0_2g
./config
 make && sudo make install
 cd .. rm -rf OpenSSL*
 ```

```bash
# Install libcurl

wget https://github.com/curl/curl/archive/curl-7_48_0.tar.gz -O curl-7_48_0.tar.gz
tar -xf curl-7_48_0.tar.gz && cd curl-curl-7_48_0
mkdir build && cd build && cmake ..
make && sudo make install
cd ../.. rm -rf curl*
```

```bash
# Install pugixml

wget https://github.com/zeux/pugixml/releases/download/v1.7/pugixml-1.7.tar.gz -O pugixml-1.7.tar.gz
tar -xf pugixml-1.7.tar.gz && cd pugixml-1.7
mkdir build && cd build && cmake ../scripts/ -DBUILD_SHARED_LIBS:BOOL=TRUE
make && sudo make install
cd ../.. rm -rf pugixml*
```

```
# Install webdavclient

wget https://github.com/designerror/webdav-client-cpp/archive/v0.9.3.tar.gz -0 webdavclient-0.9.3.tar.gz
tar -xf webdavclient-0.9.3.tar.gz && cd webdavclient-0.9.3
mkdir build && cd build && cmake ..
make && sudo make install
cd ../.. rm -rf webdavclient*
```