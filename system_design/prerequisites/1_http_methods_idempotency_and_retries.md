# HTTP Methods, Idempotency and Retries

## Why "HTTP Methods" are important in system design?
- They convey **intent**.
    - kind of operation, 
    - safe to retry or not, 
    - how caching and proxies will behave
- Shows API maturity.

### Core HTTP Methods
1. GET
    - Fetch data
    - Safe (no state change in server)
    - Idempotent: Calling multiple times won't imapact the server state if called multiple times, server will be in same state as if method called once.
        - Made Idempotent to safely retry GET request on failure, and proxies could store GET result for serving later.
        - Change in logs due to GET request does not break idempotency. Business logic state should not get impacted.
2. POST
    - Create new resource
    - Not Idempotent
3. PUT
    - Replace entire resource
    - Idempotent
4. PATCH
    - Partial update
    - Usually idempotent, but must be designed carefully
        - Eg.
            - PATCH login_count +1 -> Not idempotent (Delta will lead to non-idempotency)
            - PATCH login_count 10 -> idempotent
    - We could also send a idempotency_key in PATCH request, to make sure at server that a request with idempotency_key is executed only once.
5. DELETE
    - Delete resource
    - Idempotent



## Idempotency
- An operation is idempotent is performing it multiple times results in same effect as performing it once.
- It is imporant because, retries can happen due to:
    - Network timeouts
    - Load balancer retries
    - Client retry logic
- If APIs are not idempotent, it could led to data corruption.
- If an API is not idempotent, example a POST request, then it can be made idempotent by sending a key `idempotent_key`.
- Safe != Idempotency
    | Method | Safe | Idempotent |
    | ------ | ---- | ---------- | 
    | GET    | Yes  | Yes        | 
    | POST   | No   | No         | 
    | PUT    | No   | Yes        | 
    | PATCH  | No   | Usually    | 
    | DELETE | No   | Yes        |
    - Safe: Server state does not change (eg. GET, HEAD, OPTIONS)
    - Idempotency: Server state may change, but it will be same as API called once or multiple times.

## Designing Clean REST APIs
- Make resource based URLs
    - Example:
        - `/users`
        - `/users/{id}`
        - `/orders/{id}`
- Avoid verbs in URLs
    - Example: 
        - `/createUser` -> Incorrect
        - `/users`      -> Correct
- Versioning: To avoid breaking clients
    - Example: `/v1/users`

## Pagination
