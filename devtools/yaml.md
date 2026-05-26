# YAML 
- stands for "YAML Ain't Markup Language" (recursive acronym)
- human-readable format for writing structured data (cleaner alternative for JSON/XML designed for humans)
- used for config files, CI/CD pipelines, Kubernetes manifests, Docker Compose, GitHub Actions, etc.
- **Core Idea**: YAML represents data as key-value pairs, lists, and nested structures — using indentation (spaces only, never tabs) to show hierarchy.

## Data Structures:
- Key-value pairs:
    ```YAML
    name: kivi
    version: 1.0.0
    debug: false
    port: 8080
    ```
- Lists:
    - Using prefix `-` (one item per line)
        ```YAML
        fruits:
          - apple
          - banana
          - mango
        ```
    - Inline (called "flow style")
        ```YAML
        fruits: [apple, banana, mango]
        ```
    - Nested structures:
        ```YAML
        server:
          host: loca lhost
          port: 8080
          tls:
            enabled: true
            cert: /etc/kivi/cert.pem
            key: /etc/kivi/key.pem
        ```
    - List of objects:
        ```YAML
        linters:
          - name: errcheck
            enabled: true
          - name: staticcheck
            enabled: true
          - name: gofmt
            enabled: false
        ```

- Comments: starts with `#` (YAML one of the few data formats to support comments)
- No quotes required for strings except for some cases.
    - Quotes required in following cases:
        - contains special characters (like colon, backslashes)
    - Multiline string
        - newlines to be preserved, then use `|`
            ```YAML
            description: |
              This is line one.
              This is line two.
              Each newline is kept.
            ```
        - fold newlines into spaces, then use `>`
            ```YAML
            summary:
              This is a long sentence
              that gets joined into
              one single line.
            ```
- YAML infers types automatically.
    - string, 
    - integer, 
    - float, 
    - boolean, 
    - null/~/BLANK
- This automatic typing is actually a famous YAML footgun — the Norway problem. Country code NO gets parsed as boolean false because YAML treats no, yes, on, off as booleans in older specs. Always quote values that look like they could be misinterpreted.
- Type can also be explicitly tagged using `!!type`
    ```YAML
    string_zipcode: !!str 10001 
    exact_integer: !!float 42
    ```

## Anchors and aliases (reusing values)
- YAML has a feature for referencing repeated data — you define an anchor with & and reference it with *:
    ```YAML
    defaults: &defaults
      timeout: 30s
      retries: 3

    production:
      <<: *defaults        # merges all keys from defaults
      host: prod.kivi.io

    staging:
      <<: *defaults        # same defaults, different host
      host: staging.kivi.io
    ```
- `<<`: is the "merge key" — it pulls all fields from the referenced anchor into the current object. Heavily used in Docker Compose files.
