const http = require('http');
const os = require('os');
const fs = require('fs');

// Creating a web server
http.createServer((_req, res) => {
    console.log("Got Request");
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end("Hello World");
}).listen(8080);

// Modules in NodeJS
console.log("Current OS Platform is", os.platform());

// Reading a file synchronously
FileData = fs.readFileSync('./data/contacts.txt', 'utf-8');
console.log("File content:", FileData);

// Reading a file asynchronously
fs.readFile('./data/contacts.txt', 'utf8', (err, data) => {
    if(err) {
        console.log("Error while reading the file:", err);
    }
    else {
        console.log("File Data:", data);
    }
});
console.log("This line will be printed before printing file content, because file is being read asynchronously");

// Objects
let user = {
    name: 'Alice',
    age: 25,
    greet() {
        console.log(`Hi, I'm ${this.name}`)
    }
};

console.log("User name:", user.name);
user.greet();

// Arrays
let colors = ['red', 'green', 'blue', 'orange'];
colors.forEach(color => console.log("Color:", color));
colors.forEach((color, index) => console.log(`Color ${index + 1}: ${color}`));
let lengths = colors.map(color => color.length) // creates a new array with lengths of each color string
console.log(lengths);

