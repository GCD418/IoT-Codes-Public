import socket
import threading

class ClientHandler:
    """Class responsible for handling client connections"""
    
    def __init__(self, client_socket, address):
        self.client_socket = client_socket
        self.address = address
    
    def handle(self):
        """Handle client communication"""
        print(f"[+] New connection from {self.address}")
        try:
            while True:
                data = self.client_socket.recv(1024)
                if not data:
                    break
                print(f"[Received] {self.address}: {data.decode()}")
                self.client_socket.sendall(data)  # Echo back the received data
        except Exception as e:
            print(f"[!] Error with {self.address}: {e}")
        finally:
            print(f"[-] Connection closed from {self.address}")
            self.client_socket.close()

class SocketServer:
    """Socket server that listens for and handles multiple client connections"""
    
    def __init__(self, host='192.168.79.17', port=12345):
        self.host = host
        self.port = port
        self.server_socket = None
    
    def setup(self):
        """Configure and set up the server socket"""
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)  # Allows up to 5 queued connections
        print(f"[*] Listening on {self.host}:{self.port}")
    
    def start(self):
        """Start the server and accept incoming connections"""
        self.setup()
        try:
            while True:
                client_socket, address = self.server_socket.accept()
                client_handler = ClientHandler(client_socket, address)
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
