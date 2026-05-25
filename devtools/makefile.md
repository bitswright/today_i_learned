# Makefile

- A Makefile is a file that defines named commands (called `target`s) you can run with `make <target>`. 
- Instead of remembering and typing long commands like `go test -race -count=1 ./...` every time, you just type `make test`.
- `make` is a Unix tool that's been around since 1976. 
- Almost every serious project (C, Go, Python, Rust) uses one as a **command runner**.

## The anatomy of a Makefile
```makefile
target: dependencies
	command
```
  - 3 parts
  - 1 critical rule: `command` line must start with TAB and not SPACEs.
  - Variables are referenced with $(VAR_NAME).

## `.PHONY`
- By default, `make` checks if a file with the `target`'s name exists. If a file exists in your directory, make would do nothing (it'd say `"already up to date"`).
- `.PHONY` tells `make` "these are just command names, not real files — always run them":
    ```makefile
    .PHONY: build test clean
    ```
- Always declare your targets as `.PHONY` unless you're actually generating files.

## Dependencies between targets
```makefile
test: build   
	go test ./...
```
- runs build first, then test

## `all` target
- Default target: what runs when you just type `make`
```makefile
all: build
```

## `@` suppresses echo
- By default, make prints each command before running it. 
- Prefixing with `@` silences that. 
