# `WaitGroup`

- A `sync.WaitGroup` is a counter that lets one goroutine wait for a group of other goroutines to finish.
- Problem it solves: when you launch goroutines with `go func()`, the main goroutine doesn't automatically wait for them. 
- Without a `WaitGroup`, the test function would return immediately before the goroutines even started running.
- Example:
    ```go
    // Without WaitGroup — broken
    func main() {
        go fmt.Println("hello")   // launched but...
        go fmt.Println("world")   // ...main exits before these run
    }
    // program exits, goroutines never get to run
    ```

- `WaitGroup` fix this with 3 methods:
    - `wg.Add(n)`: "I'm about to launch n goroutines, count them"
    - `wg.Done()`: "one goroutine finished, decrement the counter"
    - `wg.Wait()`: "block here until the counter reaches zero"
- Simple example:
    ```go
    func main() {
        var wg sync.WaitGroup

        wg.Add(3)

        go func() {
            defer wg.Done()
            fmt.Println("goroutine 1")
        }()

        go func() {
            defer wg.Done()
            fmt.Println("goroutine 2")
        }()

        go func() {
            defer wg.Done()
            fmt.Println("goroutine 3")
        }()

        wg.Wait()
        fmt.Println("all done")
    }
    ```

#### Note:
- `wg.Add()` must be called before launching the goroutine, never inside it. 
    - If you put `Add` inside the goroutine, the main goroutine might reach `Wait()` before the goroutine even calls `Add`, see a counter of zero, and return immediately — missing goroutines entirely.

#### The key mental model
- main goroutine: the program's lifetime when it exits, everything exits
- other goroutines:  guests at a party if the host (main) leaves, the party is over for everyone regardless of what the guests are doing