echo "Install OpenSSL@1.0.2g"
wget https://github.com/openssl/openssl/archive/OpenSSL_1_0_2g.tar.gz -O OpenSSL_1_0_2g.tar.gz
tar -xf OpenSSL_1_0_2g.tar.gz && cd openssl-OpenSSL_1_0_2g
./config
make && make install_sw
cd .. && rm -rf openssl-OpenSSL_1_0_2g && rm -f OpenSSL_1_0_2g.tar.gz

echo "Install CURL@7.4.8"
wget https://github.com/curl/curl/archive/curl-7_48_0.tar.gz -O curl-7_48_0.tar.gz
tar -xf curl-7_48_0.tar.gz && cd curl-curl-7_48_0
mkdir build && cd build && cmake ..
make && make install
cd ../.. && rm -rf curl-curl-7_48_0 && rm -f curl-7_48_0.tar.gz

echo "Install pugixml@1.7.0"
wget https://github.com/zeux/pugixml/releases/download/v1.7/pugixml-1.7.tar.gz -O pugixml-1.7.tar.gz
tar -xf pugixml-1.7.tar.gz && cd pugixml-1.7
mkdir build && cd build && cmake ../scripts/
make && make install
cd ../.. && rm -rf pugixml-1.7 && rm -f pugixml-1.7.tar.gz
