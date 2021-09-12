# How to run phindows with TCP/IP connection

1. In etc/inetd.conf uncomment/add the following line:
```
phrelay stream tcp nowait root /usr/bin/phrelay phrelay -x
```
2. In /etc/services,
```
phrelay 4868/tcp
```
3. Reboot
4. In terminal:
```
inetd
phrelay -x
```