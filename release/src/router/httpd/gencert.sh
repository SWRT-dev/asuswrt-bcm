#!/bin/sh
SECS=1262278080

cd /etc

NVCN=`nvram get local_domain`
if [ "$NVCN" == "" ]; then
	NVCN="www.asusrouter.com"
fi

cp -L openssl.cnf openssl.config

I=0
for CN in $NVCN; do
        echo "$I.commonName=CN" >> openssl.config
        echo "$I.commonName_value=$CN" >> openssl.config
        I=$(($I + 1))
done

# add startdate option for certificate
echo "default_startdate=`date +%Y%m%d%H%M%S%Z`" >> openssl.config

# create the key and certificate request
#openssl req -new -out /tmp/cert.csr -config openssl.config -keyout /tmp/privkey.pem -newkey rsa:1024 -passout pass:password
# remove the passphrase from the key
#openssl rsa -in /tmp/privkey.pem -out key.pem -passin pass:password
# convert the certificate request into a signed certificate
#openssl x509 -in /tmp/cert.csr -out cert.pem -req -signkey key.pem -setstartsecs $SECS -days 3653 -set_serial $1

# create the key and certificate request
OPENSSL_CONF=/etc/openssl.config openssl req -new -out /tmp/cert.csr -keyout /tmp/privkey.pem -newkey rsa:2048 -passout pass:password
# remove the passphrase from the key
#OPENSSL_CONF=/etc/openssl.cnf openssl rsa -in /tmp/privkey.pem -out key.pem -passin pass:password
# convert the certificate request into a signed certificate
#OPENSSL_CONF=/etc/openssl.cnf RANDFILE=/dev/urandom openssl x509 -in /tmp/cert.csr -out cert.pem -req -signkey key.pem -days 3653 -sha256

# 2020/01/03 import the self-certificate
OPENSSL_CONF=/etc/openssl.config openssl rsa -in /tmp/privkey.pem -out key.pem -passin pass:password
OPENSSL_CONF=/etc/openssl.config RANDFILE=/dev/urandom openssl req -x509 -new -nodes -in /tmp/cert.csr -key key.pem -days 3653 -sha256 -out cert.pem

#	openssl x509 -in /etc/cert.pem -text -noout

# server.pem for WebDav SSL
cat key.pem cert.pem > server.pem

# 2020/01/03 import the self-certificate
cp cert.pem cert.crt

rm -f /tmp/cert.csr /tmp/privkey.pem openssl.config
