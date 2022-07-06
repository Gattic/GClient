# # Python 3 server example
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse, parse_qs

hostName = "0.0.0.0"
serverPort = 45022

class MyServer(BaseHTTPRequestHandler):

    def loadFile(self, fname):
        f = open(fname, "r")
        lines = f.read()
        return str(lines)

    # Helper function called in both post and get requests
    def reqHandler(self, isPost):
        print(self.path)
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

        #if isPost:
        #timestamp=parsedQuery['timestamp']
        #print(timestamp)
        print(parsedQuery)

        # TODO: Change name/file based on path
        fname = "python/index.html"

        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        webFile = self.loadFile(fname)
        self.wfile.write(bytes(webFile, "utf-8"))

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
