import socket
import sys
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#server_address = ('', 9090)
#print >>sys.stderr, 'starting up on %s port %s' % server_address
#sock.bind(server_address)

#sock.listen(1)

#s = socket() 
s.connect(('112.108.39.164', 9090)) 
s.send('raw\r\n\r\n')

print "==========="

while True:
    print >>sys.stderr, 'watiting for a connection'
    ping = 1
    #data = 'dron %s' % ping
    message = '{ "op": "subscribe" , "topic" : "/say_hello_world"}'
    s.send('\x00'+message+'\xff')
    while True:
        print "??????"
        #data = connection.recv(16)
        data = s.recv(100);
        print >>sys.stderr, 'received "%s"' % data
        ping += 1
        #data = 'dron %s' % ping
        if ping == 100 :
            break
        time.sleep(1)
