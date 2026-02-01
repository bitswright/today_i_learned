# How web actually works?

## Client-Server Model
- Client sends a request, server processes the request and sends back a response.
```
    Client -> Load Balancer -> Server -> Cache/DB
```
- Client never access the DB directly.

### Request-Response Lifecycle
1. Client build HTTP request.
2. DNS resolves domain -> IP.
3. TCP connection is established.
4. HTTP request is sent.
5. Load balancer selects a server and forwards the request.
6. Server applies business logic.
7. Server queries DB/chache to process the request.
8. Response is sent back to the client.

> Most latency occurs outside the code in Network and DB.

## Statefull vs Stateless Server
- **Statefull Server**: Server remembers client data between the requests.
    - Example: Server stores session in memory.
    - Problems:
        - Load balancer must use sticky session.
        - Hard to scale.
        - Server crash -> session lost

- **Stateless Server**: Server don't remember client data, everything needed (eg. Auth Token (JWT)) is sent in the request.
    - Advantages:
        - Simple load balancing.
        - Easy horizontal scaling.
        - Fault tolerant
    - If no data is stored in server, where is data stored then:
        | Type         | Location      |
        | ------------ | ------------- |
        | Auth state   | JWT/Redis     |
        | User data    | Database      |
        | Session data | Redis / DB    |
        | Files        | Object storage|
    - Server becomes compute-only.
    
## Horizontal vs Vertical Scaling

- **Vertical Scaling**: Bigger machine, more CPU/RAM
    - Problems:
        - Limited
        - Expensive
        - Single point of failure
- **Horizontal Scaling**: More machine, works behind load balancer
    - Advantages:
        - Cheap
        - Fault tolerant
        - Cloud-friendly
    - Statelessness allows horizontal scaling.

## Load Balancer
- Responsibilities 
    - Distribute traffic
    - Health check
    - Failover
    - Rate-limit (sometimes)
- Algorithms:
    - Round-Robin
    - Least Connections
        - works best when request processing time varies significantly.
        - could also improve to weighted-least connections algo if different servers have different resources.
    - Hash-based
        - hashes a field and sends request accordingly
        - primary purpose:
            - session affinity (sticky behaviour)
            - cache locality
            - reduce cross-server state sharing
        - improved version: consistent hashing -> when servers count change, only a small set of users gets impacted
- Load balancer doesn't make system faster, it helps servive traffic spikes.
- Load balancers could also be horizontally scalled and be redundant.
    - Active-Active: traffic distributed among LBs via DNS or Anycast
    - Active-Passive: LBs continuously monitor each other, if any LB fails health check, another takes over.
    
