# Strategy Pattern - Explained Simply with Compression Example (Go)

## What Problem Are We Solving?

Imagine you're building a file compression tool like WinRAR or 7-Zip. Users want to compress files using different formats:

- **ZIP** - Works everywhere, okay compression
- **GZIP** - Great for web servers
- **LZ4** - Super fast, less compression
- **BZIP2** - Slow but excellent compression

**The Question:** How do you write code that handles all these compression formats cleanly?

---

## The Wrong Way (What Beginners Usually Do)

Most people start with a bunch of `if-else` or `switch` statements:

```go
func CompressFile(filename string, format string) {
    data := readFile(filename)
    
    switch format {
    case "zip":
        // ZIP compression logic
        fmt.Println("Using ZIP algorithm...")
        // 50 lines of ZIP-specific code
        // Connect to zip library...
        
    case "gzip":
        // GZIP compression logic
        fmt.Println("Using GZIP algorithm...")
        // 40 lines of GZIP-specific code
        // Connect to gzip library...
        
    case "lz4":
        // LZ4 compression logic
        fmt.Println("Using LZ4 algorithm...")
        // 45 lines of LZ4-specific code
        
    case "bzip2":
        // BZIP2 compression logic
        fmt.Println("Using BZIP2 algorithm...")
        // 35 lines of BZIP2-specific code
        
    default:
        fmt.Println("Unknown format!")
    }
}
```

### Why This Is Bad

| Problem | What Happens |
|---------|--------------|
| **Giant function** | One function with 200+ lines of mixed code |
| **Hard to change** | Want to improve GZIP? Hope you don't break ZIP! |
| **Hard to test** | Can't test LZ4 without loading all other code |
| **Hard to add new formats** | Every new format = editing this function |
| **Code duplication** | Similar setup/cleanup code repeated in each case |

Think of it like a messy toolbox where all tools are tangled together. Want to grab the screwdriver? You have to untangle it from the hammer, wrench, and pliers first!

---

## The Right Way: Strategy Pattern

### The Idea in Plain English

Instead of one giant function with all compression logic mixed together:

> **Put each compression algorithm in its own separate box. The compressor just asks the box to "compress" - it doesn't care what's inside the box.**

It's like having separate machines:
- ZIP Machine
- GZIP Machine
- LZ4 Machine

You just feed your file to whichever machine you need. Each machine knows how to do its job.

---

## Building It Step by Step

### Step 1: Create a "Contract" (What Every Compression Must Do)

First, we define what ANY compression algorithm should be able to do. In Go, we use an "interface" - think of it as a job requirement.

```go
package main

// CompressionStrategy is the contract.
// Any compression algorithm MUST have these abilities.
type CompressionStrategy interface {
    // Compress takes data and returns compressed data
    Compress(data []byte) []byte
    
    // Decompress takes compressed data and returns original data
    Decompress(data []byte) []byte
    
    // GetExtension returns the file extension (like ".zip")
    GetExtension() string
    
    // GetName returns human-readable name
    GetName() string
}
```

**In simple terms:** This says "If you want to be a compression algorithm, you MUST have these 4 abilities: compress, decompress, give me your file extension, and tell me your name."

---

### Step 2: Create Each Compression Algorithm (The Strategies)

Now we create each compression method as its own type. Each one follows the "contract" above.

```go
package main

import "fmt"

// ============================================
// ZIP Compression Strategy
// ============================================

type ZIPCompression struct{}

func (z *ZIPCompression) Compress(data []byte) []byte {
    fmt.Println("  📦 ZIP: Scanning for repeated patterns...")
    fmt.Println("  📦 ZIP: Building compression dictionary...")
    fmt.Println("  📦 ZIP: Encoding data...")
    
    // In real life, this would use compress/flate package
    // For demo, we'll simulate compression
    compressed := simulateCompression(data, 0.65) // ZIP ~65% ratio
    
    fmt.Printf("  📦 ZIP: Compressed %d bytes → %d bytes\n", 
        len(data), len(compressed))
    return compressed
}

func (z *ZIPCompression) Decompress(data []byte) []byte {
    fmt.Println("  📦 ZIP: Reading compression dictionary...")
    fmt.Println("  📦 ZIP: Decoding data...")
    return simulateDecompression(data, 0.65)
}

func (z *ZIPCompression) GetExtension() string {
    return ".zip"
}

func (z *ZIPCompression) GetName() string {
    return "ZIP"
}

// ============================================
// GZIP Compression Strategy
// ============================================

type GZIPCompression struct{}

func (g *GZIPCompression) Compress(data []byte) []byte {
    fmt.Println("  🗜️  GZIP: Applying DEFLATE algorithm...")
    fmt.Println("  🗜️  GZIP: Adding GZIP headers...")
    
    // In real life, this would use compress/gzip package
    compressed := simulateCompression(data, 0.60) // GZIP ~60% ratio
    
    fmt.Printf("  🗜️  GZIP: Compressed %d bytes → %d bytes\n", 
        len(data), len(compressed))
    return compressed
}

func (g *GZIPCompression) Decompress(data []byte) []byte {
    fmt.Println("  🗜️  GZIP: Reading GZIP headers...")
    fmt.Println("  🗜️  GZIP: Applying INFLATE algorithm...")
    return simulateDecompression(data, 0.60)
}

func (g *GZIPCompression) GetExtension() string {
    return ".gz"
}

func (g *GZIPCompression) GetName() string {
    return "GZIP"
}

// ============================================
// LZ4 Compression Strategy (Speed focused)
// ============================================

type LZ4Compression struct{}

func (l *LZ4Compression) Compress(data []byte) []byte {
    fmt.Println("  ⚡ LZ4: Running high-speed compression...")
    fmt.Println("  ⚡ LZ4: Optimizing for speed over size...")
    
    // LZ4 is faster but compresses less
    compressed := simulateCompression(data, 0.75) // LZ4 ~75% ratio
    
    fmt.Printf("  ⚡ LZ4: Compressed %d bytes → %d bytes (FAST!)\n", 
        len(data), len(compressed))
    return compressed
}

func (l *LZ4Compression) Decompress(data []byte) []byte {
    fmt.Println("  ⚡ LZ4: Ultra-fast decompression...")
    return simulateDecompression(data, 0.75)
}

func (l *LZ4Compression) GetExtension() string {
    return ".lz4"
}

func (l *LZ4Compression) GetName() string {
    return "LZ4"
}

// ============================================
// BZIP2 Compression Strategy (Size focused)
// ============================================

type BZIP2Compression struct{}

func (b *BZIP2Compression) Compress(data []byte) []byte {
    fmt.Println("  🐢 BZIP2: Running Burrows-Wheeler transform...")
    fmt.Println("  🐢 BZIP2: Applying Move-to-Front encoding...")
    fmt.Println("  🐢 BZIP2: Huffman encoding (this takes time)...")
    
    // BZIP2 is slower but compresses more
    compressed := simulateCompression(data, 0.45) // BZIP2 ~45% ratio
    
    fmt.Printf("  🐢 BZIP2: Compressed %d bytes → %d bytes (SMALL!)\n", 
        len(data), len(compressed))
    return compressed
}

func (b *BZIP2Compression) Decompress(data []byte) []byte {
    fmt.Println("  🐢 BZIP2: Reversing Huffman encoding...")
    fmt.Println("  🐢 BZIP2: Reversing Move-to-Front...")
    fmt.Println("  🐢 BZIP2: Reversing Burrows-Wheeler...")
    return simulateDecompression(data, 0.45)
}

func (b *BZIP2Compression) GetExtension() string {
    return ".bz2"
}

func (b *BZIP2Compression) GetName() string {
    return "BZIP2"
}
```

**Notice:** Each compression algorithm is completely independent. ZIP code knows nothing about GZIP. LZ4 knows nothing about BZIP2. They're separate boxes!

---

### Step 3: Create the File Compressor (The "Context")

The file compressor doesn't care HOW you compress. It just needs SOME compression method.

```go
package main

import "fmt"

// FileCompressor uses a compression strategy.
// It doesn't know the details of any algorithm.
// It just knows "I have something that can compress."
type FileCompressor struct {
    strategy CompressionStrategy
}

// NewFileCompressor creates a new compressor with a strategy
func NewFileCompressor(strategy CompressionStrategy) *FileCompressor {
    return &FileCompressor{strategy: strategy}
}

// SetStrategy lets you change the compression algorithm anytime!
func (fc *FileCompressor) SetStrategy(strategy CompressionStrategy) {
    fmt.Printf("\n✓ Switched compression to: %s\n", strategy.GetName())
    fc.strategy = strategy
}

// GetStrategy returns current strategy name
func (fc *FileCompressor) GetStrategy() string {
    return fc.strategy.GetName()
}

// CompressFile compresses a file using the current strategy
func (fc *FileCompressor) CompressFile(filename string, data []byte) []byte {
    fmt.Println()
    fmt.Println("================================================")
    fmt.Printf("COMPRESSING: %s\n", filename)
    fmt.Printf("Using: %s compression\n", fc.strategy.GetName())
    fmt.Printf("Original size: %d bytes\n", len(data))
    fmt.Println("================================================")
    
    // Here's the magic - we just call Compress()
    // We don't care if it's ZIP, GZIP, or anything else
    compressed := fc.strategy.Compress(data)
    
    newFilename := filename + fc.strategy.GetExtension()
    fmt.Printf("\n✅ Created: %s\n", newFilename)
    
    ratio := float64(len(compressed)) / float64(len(data)) * 100
    fmt.Printf("📊 Compression ratio: %.1f%%\n", ratio)
    
    return compressed
}

// DecompressFile decompresses data using the current strategy
func (fc *FileCompressor) DecompressFile(filename string, data []byte) []byte {
    fmt.Println()
    fmt.Println("================================================")
    fmt.Printf("DECOMPRESSING: %s\n", filename)
    fmt.Printf("Using: %s decompression\n", fc.strategy.GetName())
    fmt.Println("================================================")
    
    decompressed := fc.strategy.Decompress(data)
    
    fmt.Printf("\n✅ Decompressed: %d bytes → %d bytes\n", 
        len(data), len(decompressed))
    
    return decompressed
}
```

**The Magic Line:** `fc.strategy.Compress(data)`

The compressor doesn't know or care how the compression happens. It just calls `.Compress()` and the right thing happens!

---

### Step 4: Helper Functions (For Simulation)

```go
package main

// simulateCompression pretends to compress data
// In real code, you'd use actual compression libraries
func simulateCompression(data []byte, ratio float64) []byte {
    newSize := int(float64(len(data)) * ratio)
    return make([]byte, newSize)
}

// simulateDecompression pretends to decompress data
func simulateDecompression(data []byte, ratio float64) []byte {
    originalSize := int(float64(len(data)) / ratio)
    return make([]byte, originalSize)
}

// createSampleData creates fake file data for demo
func createSampleData(sizeMB float64) []byte {
    size := int(sizeMB * 1024 * 1024)
    return make([]byte, size)
}
```

---

### Step 5: See It In Action!

```go
package main

import "fmt"

func main() {
    // Create sample "file" data (5 MB)
    fileData := createSampleData(5.0)
    filename := "my_photos"
    
    fmt.Println("🗂️  FILE COMPRESSION TOOL")
    fmt.Println("==========================")
    fmt.Printf("File: %s\n", filename)
    fmt.Printf("Size: %.2f MB\n", float64(len(fileData))/1024/1024)
    
    // ============================================
    // EXAMPLE 1: Compress with ZIP
    // ============================================
    fmt.Println("\n\n📌 EXAMPLE 1: Using ZIP compression")
    
    zipStrategy := &ZIPCompression{}
    compressor := NewFileCompressor(zipStrategy)
    
    compressor.CompressFile(filename, fileData)
    
    // ============================================
    // EXAMPLE 2: Compress same file with GZIP
    // ============================================
    fmt.Println("\n\n📌 EXAMPLE 2: Using GZIP compression")
    
    gzipStrategy := &GZIPCompression{}
    compressor.SetStrategy(gzipStrategy)
    
    compressor.CompressFile(filename, fileData)
    
    // ============================================
    // EXAMPLE 3: Need speed? Use LZ4
    // ============================================
    fmt.Println("\n\n📌 EXAMPLE 3: Need SPEED? Using LZ4")
    
    lz4Strategy := &LZ4Compression{}
    compressor.SetStrategy(lz4Strategy)
    
    compressor.CompressFile(filename, fileData)
    
    // ============================================
    // EXAMPLE 4: Need smallest file? Use BZIP2
    // ============================================
    fmt.Println("\n\n📌 EXAMPLE 4: Need SMALLEST FILE? Using BZIP2")
    
    bzip2Strategy := &BZIP2Compression{}
    compressor.SetStrategy(bzip2Strategy)
    
    compressed := compressor.CompressFile(filename, fileData)
    
    // ============================================
    // EXAMPLE 5: Decompress
    // ============================================
    fmt.Println("\n\n📌 EXAMPLE 5: Decompressing the BZIP2 file")
    
    compressor.DecompressFile(filename+".bz2", compressed)
    
    // ============================================
    // SUMMARY: Compare all algorithms
    // ============================================
    fmt.Println("\n\n" + "=" * 60)
    fmt.Println("📊 COMPRESSION COMPARISON")
    fmt.Println("=" * 60)
    fmt.Println()
    fmt.Println("| Algorithm | Speed    | Compression | Best For              |")
    fmt.Println("|-----------|----------|-------------|-----------------------|")
    fmt.Println("| ZIP       | Medium   | Good (65%)  | Universal sharing     |")
    fmt.Println("| GZIP      | Medium   | Better (60%)| Web servers           |")
    fmt.Println("| LZ4       | ⚡ Fast  | OK (75%)    | Real-time processing  |")
    fmt.Println("| BZIP2     | 🐢 Slow  | Best (45%)  | Archival storage      |")
}
```

---

## What Did We Achieve?

### Before (Switch Statement Mess)
```
CompressFile()
├── case "zip" → 50 lines of ZIP code
├── case "gzip" → 40 lines of GZIP code
├── case "lz4" → 45 lines of LZ4 code
├── case "bzip2" → 35 lines of BZIP2 code
└── case "zstd" → ... (keeps growing!)
```

### After (Strategy Pattern)
```
FileCompressor
└── strategy.Compress()  ← Just this one line!

ZIPCompression.Compress()    ← Separate type
GZIPCompression.Compress()   ← Separate type
LZ4Compression.Compress()    ← Separate type
BZIP2Compression.Compress()  ← Separate type
```

---

## Why Is This Better? (Benefits)

| Benefit | Explanation |
|---------|-------------|
| **Easy to add new formats** | Just create a new type. Don't touch existing code! |
| **Easy to test** | Test each algorithm separately |
| **Easy to understand** | Each type does ONE thing |
| **Swap at runtime** | User can switch algorithms without restarting |
| **No messy switch** | Clean, organized code |
| **Single responsibility** | ZIP only knows ZIP, GZIP only knows GZIP |

---

## Visual Summary

```
    User selects compression format
              │
              ▼
    ┌─────────────────────┐
    │   FileCompressor    │
    │                     │
    │  "I need to         │
    │   compress this     │
    │   file somehow"     │
    └──────────┬──────────┘
               │
               │ Uses whichever strategy
               │ was set by the user
               │
               ▼
    ┌─────────────────────────────────────────────┐
    │     CompressionStrategy (Interface)         │
    │     "Anyone who can Compress()"             │
    └─────────────────────────────────────────────┘
               △       △       △       △
               │       │       │       │
      ┌────────┴─┐ ┌───┴───┐ ┌─┴──┐ ┌──┴───┐
      │   ZIP    │ │ GZIP  │ │LZ4 │ │BZIP2 │
      │          │ │       │ │    │ │      │
      │Compress()│ │Compress│ │Comp│ │Comp  │
      │uses      │ │uses    │ │uses│ │uses  │
      │DEFLATE   │ │DEFLATE+│ │LZ4 │ │BWT+  │
      │          │ │headers │ │algo│ │Huffman│
      └──────────┘ └────────┘ └────┘ └──────┘
```

---

## Key Go Concepts Used

| Concept | What It Means |
|---------|---------------|
| **Interface** | A contract that types must follow (like `CompressionStrategy`) |
| **Type** | A custom data structure (like `ZIPCompression`) |
| **Method** | A function attached to a type (like `func (z *ZIPCompression) Compress()`) |
| **Pointer receiver** | The `*` means the method can modify the type's data |

---

## Key Vocabulary

| Term | Meaning |
|------|---------|
| **Strategy** | A specific algorithm (e.g., ZIPCompression) |
| **Context** | The class that uses strategies (e.g., FileCompressor) |
| **Interface** | The rules that all strategies must follow |
| **Composition** | "Has a" relationship (Compressor HAS a strategy) |

---

## Think About It

**Question:** What if you wanted to add ZSTD compression (Facebook's modern algorithm)?

**Answer:** Just create a new type!

```go
type ZSTDCompression struct{}

func (z *ZSTDCompression) Compress(data []byte) []byte {
    fmt.Println("  🚀 ZSTD: Using modern dictionary compression...")
    compressed := simulateCompression(data, 0.50)
    fmt.Printf("  🚀 ZSTD: Compressed %d → %d bytes\n", 
        len(data), len(compressed))
    return compressed
}

func (z *ZSTDCompression) Decompress(data []byte) []byte {
    fmt.Println("  🚀 ZSTD: Fast decompression...")
    return simulateDecompression(data, 0.50)
}

func (z *ZSTDCompression) GetExtension() string {
    return ".zst"
}

func (z *ZSTDCompression) GetName() string {
    return "ZSTD"
}
```

You didn't touch FileCompressor, ZIPCompression, or any other type! That's the power of Strategy Pattern.

---

## Complete Working Code

Save all the code sections above into a single file called `compression.go` and run:

```bash
go run compression.go
```

You'll see the different compression algorithms in action!

---

## When to Use Which Algorithm? (Bonus)

| Scenario | Best Choice | Why |
|----------|-------------|-----|
| Sharing files with anyone | ZIP | Everyone can open ZIP |
| Web server responses | GZIP | Browsers understand it |
| Game assets loading | LZ4 | Super fast decompression |
| Backup archives | BZIP2/ZSTD | Smallest file size |
| Log file compression | GZIP/ZSTD | Good balance |
| Video streaming | LZ4 | Speed is critical |
