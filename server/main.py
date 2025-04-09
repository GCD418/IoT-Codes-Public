import socket
import threading

class ClientHandler:
    def __init__(self, client_socket, address, server):
        self.client_socket = client_socket
        self.address = address
        self.server = server
        self.is_actuator = False
    
    def handle(self):
        print(f"[+] New connection from {self.address}")
        try:
            while True:
                data = self.client_socket.recv(1024)
                if not data:
                    break
                
                message = data.decode()
                print(f"[Received] {self.address}: {message}")
                
                if message.startswith("GET;ACTUATOR_INTERVALS"):
                    # Register this client as the actuator
                    self.is_actuator = True
                    self.server.actuator = self
                    response = "255,0,0;255,255,0;0,255,0;"
                    print(f"[Sending to Actuator] {response}")
                    self.client_socket.sendall(response.encode())
                
                elif message.startswith("PUT;"):
                    try:
                        value = message.split(";")[1]
                        # Forward to actuator if available
                        if self.server.actuator:
                            forward_message = f"POST;{value}"
                            print(f"[Forwarding to Actuator] {forward_message}")
                            self.server.actuator.client_socket.sendall(forward_message.encode())
                            self.client_socket.sendall("OK".encode())
                        else:
                            print("[Warning] No actuator registered to forward message")
                            self.client_socket.sendall("ERROR: No actuator available".encode())
                    except (IndexError, ValueError) as e:
                        print(f"[Error] Invalid PUT command: {e}")
                        self.client_socket.sendall("ERROR: Invalid command format".encode())
                else:
                    self.client_socket.sendall(b"20,40,60,")
                    
        except Exception as e:
            print(f"[!] Error with {self.address}: {e}")
        finally:
            if self.is_actuator and self.server.actuator == self:
                self.server.actuator = None
                print("[!] Actuator disconnected")
            print(f"[-] Connection closed from {self.address}")
            self.client_socket.close()

class SocketServer:
    
    def __init__(self, host='192.168.56.184', port=12345):
        self.host = host
        self.port = port
        self.server_socket = None
        self.actuator = None 
    
    def setup(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)
        print(f"[*] Listening on {self.host}:{self.port}")
    
    def start(self):
        self.setup()
        try:
            while True:
                client_socket, address = self.server_socket.accept()
                client_handler = ClientHandler(client_socket, address, self)
                client_thread = threading.Thread(target=client_handler.handle)
                client_thread.start()
        except KeyboardInterrupt:
            print("\n[!] Shutting down server")
        finally:
            if self.server_socket:
                self.server_socket.close()

if __name__ == "__main__":
    server = SocketServer()
    server.start()
