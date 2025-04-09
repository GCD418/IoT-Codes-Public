import socket
import threading

def handle_client(client_socket, address):
    print(f"[+] New connection from {address}")
    ahora = False
    try:
        while True:
            data = client_socket.recv(1024)
            if not data:
                break
            # if ahora == True:
            #     print("Entra en ahora")
            #     client_socket.sendall(b"PUT;1\n")
            #     ahora = False
            #     continue
            print(f"[Received] {address}: {data.decode()}")
            if data.decode() == "GET;ACTUATOR_INTERVALS":
                client_socket.sendall(b"255,0,0;255,255,0;0,255,0;\n") 
                ahora = True
                continue
            #client_socket.sendall(data)  # Echo back the received data
            #client_socket.sendall(b"PUT;1")  # Echo back the received data
            #client_socket.sendall(b"20,40,55,")  # Echo back the received data
            # client_socket.sendall("20,40,55".encode())  # Convert string to bytes before sending
    except Exception as e:
        print(f"[!] Error with {address}: {e}")
    finally:
        print(f"[-] Connection closed from {address}")
        client_socket.close()

def start_server(host='192.168.0.7', port=12345):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)  # Allows up to 5 queued connections
    print(f"[*] Listening on {host}:{port}")

    while True:
        client_socket, address = server.accept()
        client_thread = threading.Thread(target=handle_client, args=(client_socket, address))
        client_thread.start()

if __name__ == "__main__":
    start_server()
