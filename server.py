import socket
import sys
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('112.108.39.164', 8080)
print >>sys.stderr, 'starting up on %s port %s' % server_address
sock.bind(server_address)

sock.listen(1)

while True:
    print >>sys.stderr, 'watiting for a connection'
    connection, client_address = sock.accept()
    ping = 1
    data = 'dron %s' % ping
    try:
        while True:
            print "??????"
            connection.sendall(data)
            ping += 1
            data = 'dron %s' % ping
            if ping == 100 :
                connection.close()
                break
            time.sleep(1)
            #data = connection.recv(16)
            #print >>sys.stderr, 'received "%s"' % data
            #if data:
            #    print >>sys.stderr, 'sending data back to the client'
            #    connection.sendall(data)
            #else:
            #    print >>sys.stderr, 'no more data from', client_address
            #    break
    finally:
        connection.close()


