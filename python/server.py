# # Python 3 server example
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse, parse_qs

hostName = "0.0.0.0"
serverPort = 45022

class MyServer(BaseHTTPRequestHandler):

    # Helper function called in both post and get requests
    def reqHandler(self, isPost):
        o = urlparse(self.path)
        parsedQuery=parse_qs(o.query)

        # Check for admin mode
        clientIP = self.client_address[0]
        if clientIP == "127.0.0.1":
            commandFound = False
            if "shutdown" in parsedQuery:
                # Shut down the server
                self.send_response(200)
                self.send_header("Content-type", "text/html")
                self.end_headers()
                self.wfile.write(bytes("Server shutdown initiated.", "utf-8"))
                exit()

            # Always exit this request after admin mode
            if commandFound:
                self.send_response(200)
                self.send_header("Content-type", "text/html")
                self.end_headers()
                self.wfile.write(bytes("Thank you.", "utf-8"))
                return

        # Normal requests now

        #timestamp=parsedQuery['timestamp']
        #print(timestamp)
        print(parsedQuery)

        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        if(isPost):
            self.wfile.write(bytes("hello-post:<br>", "utf-8"))
        else:
            self.wfile.write(bytes("hello-get:<br>", "utf-8"))
        self.wfile.write(bytes(str(parsedQuery), "utf-8"))

    def do_GET(self):
        self.reqHandler(False)

    def do_POST(self):
        self.reqHandler(True)

if __name__ == "__main__":        

    # Listen
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")



# examples
import subprocess
from multiprocessing import Process, Lock

#spawn a thread
        #tArgs = ""
        #p = Process(target = processData, args = (tArgs,))
        #p.start()


# parse url

        #URLexample="http://localhost:8080/?derp=herp&var2=value2&var3=value3"
        #parsed_url = urlparse(URLexample)
        #parse_qs(parsed_url.query)
        # {'i': ['main'], 'enc': [' Hello '], 'mode': ['front'], 'sid': ['12ab']}
 
# run commands

        #command = "ls -la" # "~/dev/Gattic/build/Gattic nogui " + serviceName
        #p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
