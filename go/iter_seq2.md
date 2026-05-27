# `iter.Seq2`

- Problem: I want a write a function, on whose result I can iterate.
    ```go
    for e := range Func1() {
        fmt.Println(e)
    } 
    ```
    - But `range` in Go can iterate over a few built-in things like slice, maps, channels, strings.

- In Go 1.23, a functionality was added to range over a function if it has a specific signature:
    ```go
    func(yeild func(E) bool)        // signature of iter.Seq[E]
    func(yeild func(K, V) bool)     // signature of iter.Seq2[K, V]
    func(yeild func() bool)
    ```
- `yeild` is the callback function which is called for each item. 
    - Think of it like: "here is the next item, process it"

- Go internally converts the function range:
    ```go
    for k, v := range someFunc {
        // loop body
    }
    ```
    To
    ```go
    someFunc(func(k K, v V) bool {
        // your loop body goes here
        return true // keep going
    })
    ```
- If we `break` early, then `yeild` returns `false`.

