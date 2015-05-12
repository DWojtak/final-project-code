import socket

UDP_IP="192.168.1.199"
UDP_PORT = 8888

sock= socket.socket(socket.AF_INET, #internet
                    socket.SOCK_DGRAM) #UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
        data, addr = sock.recvfrom(1024) #buffer size is 1025 bytes
        print "recieved message:", data
        target = open ("/var/www/index.html", 'w')
        target.write("<html>")
        target.write("<body bgcolor=")
        target.write(data)
        target.write(">")
        target.write("<h1>")
        target.write(data)
        target.write("</h1>")
        target.write("<meta http-equiv=")
        target.write("refresh")
        target.write(" content=")
        target.write("3;>")
        target.write("</body></html>")
        target.close()
        
