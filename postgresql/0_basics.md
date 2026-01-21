# PostgreSQL

- advanced relational database system
- supports both relational (SQL) and non-relational (NoSQL/JSON) queries.
- free and open-source
- used in backend for dynamic websites and web applications
- supports all basic features of other relational database systems

## Basic Commands

- Connect to Database: `psql -U <UserName> -d <Database>`
    - Note: If the database name is same as current user, then only `psql` command will work fine. To create database, use command `createdb <DatabaseName>` outside `psql`.
- List databases: `\l`
- Quit: `\q`
- Check version: `SELECT version();`
