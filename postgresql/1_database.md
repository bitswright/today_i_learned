# PostgreSQL Database

- Create Table:
    ```SQL
    CREATE TABLE cars(
        brand VARCHAR(255),
        model VARCHAR(255),
        year INT
    );
    ```

- Insert into:
    ```SQL
    INSERT INTO cars(brand, model, year)
    VALUES ('Ford', 'Mustang', 1964);

    INSERT INTO cars (brand, model, year)
    VALUES
        ('Volvo', 'p1800', 1968),
        ('BMW', 'M1', 1978),
        ('Toyota', 'Celica', 1975);
    ```

- Select Data:
    ```SQL
    SELECT * from cars;

    SELECT brand, year from cars;
    ```

- Alter Table:
    ```SQL
    ALTER TABLE cars
    ADD color VARCHAR(255);

    ALTER TABLE cars
    ADD horsepower VARCHAR(4),
    DROP color;

    ALTER TABLE cars
    ALTER COLUMN horsepower TYPE INT USING horsepower::INT;

    ALTER TABLE cars
    ADD color VARCHAR(255);
    ```

- Update
    ```SQL
    UPDATE cars
    SET horsepower = '500'
    WHERE brand = 'Ford';

    UPDATE cars
    SET color = 'Red';

    UPDATE cars
    SET color = 'white', year = 1970
    WHERE brand = 'Toyota';
    ```

- 