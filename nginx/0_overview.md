# NGINX

- Pronounced as Engine-X
- powerful web-server that uses non-threaded, event-driven architecture.
- Also popularly used for:
    - load-balancing
    - HTTP caching 
    - reverse proxy

- Note: 
    - In *Forward Proxy* **multiple clients** sends the request to a VPN server which then forwards this request to **a server**. 
    - Whereas, in *Reverse Proxy* **a client** sends the request to a server (popularly *nginx*) which internally decides out of **multiple servers** to which this request is to be sent. 
    - While doing reverse proxy (or even without it), nginx can also perform *load balancing* and *HTTP caching*. 
    - In load balancing, a server decides which server to forward the request to make sure a single server is not overwhelmed. 
    - In HTTP caching, a server caches some of HTTP data requested by user, to forward it itself next time, if same static data is requested.

### Advantages of NGINX
- Can handle 10K concurrent requests
- Cache HTTP Requests
- Act as reverse proxy
- Act as load balancer
- Act as an API Gateway (forwarding requests to different servers based on API requests)
- Serve and cache static files like images, videos, etc.
- Handle SSL certificates

### Pre-requisites
- Docker
- Linux
- AWS