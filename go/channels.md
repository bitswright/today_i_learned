# Channel

- pipe between goroutines
- one goroutine puts in a value and other goroutine takes it out.
- processes are synced without shared memory because:
    - sending is blocked until someone receives
    - receiving is blocked until someone sends

## Creating and using a channel
- Creating a channel:
    ```go
    ch := make(chan int)       // creates a channel that carrier int values
    ```
- Sending a value
    ```go
    ch <- 42
    ```
- Receive a value
    ```go
    v := <- ch
    ```

## Blocking behaviour
```go
func main() {
    ch := make(chan int)

    go func() {
        time.Sleep(2 * time.Second)
        ch <- 42               // sends after 2 seconds
    }()

    fmt.Println("waiting...")
    v := <-ch                  // blocks here until goroutine sends
    fmt.Println("got:", v)
}
```
- The main goroutine is frozen at `<-ch` until the other goroutine sends. This is not a busy loop — the goroutine is parked and uses no CPU while waiting.

## Unbuffered vs Buffered
- Unbuffered: 
    - sender blocks until receiver is ready.
    - handoff happens simultaneously
        ```go
        package main

        import (
            "fmt"
            "sync"
            "time"
        )

        func main() {
            ch := make(chan int)

            var wg sync.WaitGroup

            wg.Add(1)

            go func() {
                defer wg.Done()
                fmt.Println("Sleeping for 2 seconds before sending the value...")
                time.Sleep(2 * time.Second)
                fmt.Println("2 seconds over sending the value")
                ch <- 100
                // though sender is ready to send the value, 
                // but since receiver is not ready, sender gets blocked
                fmt.Println("value sent")
            }()

            fmt.Println("Sleeping for 4 seconds before receiving the value...")
            time.Sleep(4 * time.Second)
            fmt.Println("4 seconds over, ready to receive the value")
            val := <-ch
            fmt.Printf("Value received: %d\n", val)

            wg.Wait()
        }
        ```

- Buffered:
    - sender only blocks when buffer is full
        ```go
        ch := make(chan int, 3)   // buffer holds 3 values
        ch <- 1   // goes into buffer, sender does not block
        ch <- 2   // goes into buffer, sender does not block
        ch <- 3   // goes into buffer, sender does not block
        ch <- 4   // buffer full → sender blocks until someone reads
        ```

## Closing a channel
- closing a channel means no more values will be sent
    ```go
    close(ch)
    ```
- sender should only close the channel ideally
- closing a closed channel panics
- sending on a closed channel panics.
- receiving from a closed channel doesn't panic
    ```go
    v, ok := <- ch
    // ok = false means channel is closed and empty
    ```
- ranging over a channel - stops automatically when closed
    ```go
    for v := range ch {
        fmt.Println(v)
    }
    ```

## `select`: waiting on multiple channels
- like a `switch` but for channels
- waits until one of its cases is ready, then runs that case
    ```go
    select {
    case v := <- ch1:
        fmt.Println("got from ch1:", v)
    case v := <- ch2:
        fmt.Println("got from ch2:", v)
    }
    ```
- if both ready at same time, go picks one randomly
- `default` case fires if nothing is ready:
    ```go
    select {
    case v := <- ch:
        fmt.Println("got from ch:", v)
    default:
        fmt.Println("nothing ready, moving on")
    }
    ```

## `done` channel pattern
- commonly used in go code for signalling a goroutine to stop.
- receiving from a closed channel returns immediately, always.
- a broadcast signal is sent to all goroutine waiting on it.
```go
done := make(chan struct{})   // struct{} carries no data, just a signal
```
- size of `struct{}` is zero bytes memory
- Example:
    ```go
    // goroutine waiting for stop signal
    go func() {
        for {
            select {
            case <-done:
                fmt.Println("stopping")
                return
            default:
                fmt.Println("working...")
                time.Sleep(100 * time.Millisecond)
            }
        }
    }()

    time.Sleep(500 * time.Millisecond)
    close(done)   // signal the goroutine to stop
    ```

## `Ticker` — a channel that sends on a timer
- `time.NewTicker(d)` returns a ticker whose `.C` field is a channel. It sends the current time on that channel every `d` duration:
    ```go
    goticker := time.NewTicker(1 * time.Second)
    ```
- Example:
    ```go
    for t := range ticker.C {
        fmt.Println("tick at", t)
    }
    ```
- Always call `ticker.Stop()` when done — otherwise the ticker's internal goroutine leaks.