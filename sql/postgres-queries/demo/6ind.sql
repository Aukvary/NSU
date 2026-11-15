-- 1а
SELECT DISTINCT
    timezone
FROM
    airports
ORDER BY
    timezone;

-- 1б
SELECT DISTINCT
    airplane_code,
    fare_conditions
FROM
    seats
ORDER BY
    airplane_code,
    fare_conditions;

-- 2
SELECT DISTINCT
    r.arrival_airport,
    a.timezone
FROM
    routes r
    JOIN airports a ON r.arrival_airport = a.airport_code
WHERE
    r.departure_airport = 'LED'
ORDER BY
    r.arrival_airport;

-- Д3
SELECT
    flight_id,
    route_no,
    NULLIF (GREATEST (0, ROUND(EXTRACT(EPOCH FROM (actual_departure - scheduled_departure)) / 60)), 0) AS delay_minutes,
    ROUND((NULLIF (GREATEST (0, EXTRACT(EPOCH FROM (actual_departure - scheduled_departure))), 0) / NULLIF (EXTRACT(EPOCH FROM (scheduled_arrival - scheduled_departure)), 0) * 100)::NUMERIC, 1) AS delay_percent
FROM
    flights
WHERE
    actual_departure IS NOT NULL
ORDER BY
    delay_minutes DESC NULLS LAST
LIMIT 10;

-- Д4а
SELECT
    ticket_no,
    flight_id,
    seat_no,
    boarding_no,
    boarding_time
FROM
    boarding_passes
WHERE
    flight_id = (
        SELECT
            flight_id
        FROM
            flights
        WHERE
            status IN ('Boarding', 'Departed')
        LIMIT 1)
ORDER BY
    boarding_time ASC NULLS LAST,
    boarding_no;

-- Д4б
SELECT
    flight_id,
    route_no,
    status,
    scheduled_arrival,
    actual_arrival
FROM
    flights
ORDER BY
    actual_arrival DESC NULLS FIRST,
    flight_id
LIMIT 10;

-- Д5а
SELECT
    airport_code,
    airport_name,
    city,
    timezone
FROM
    airports
ORDER BY
    timezone,
    airport_code
LIMIT 10 OFFSET 20;

-- Д5б
SELECT
    airplane_code,
    model,
    RANGE,
    speed
FROM
    airplanes
ORDER BY
    RANGE DESC
LIMIT 1 OFFSET 3;

-- Д6а
SELECT DISTINCT
    timezone,
    split_part(timezone, '/', 1) AS region,
    replace(split_part(timezone, '/', 2), '_', ' ') AS city,
    upper(replace(split_part(timezone, '/', 2), '_', ' ')) AS city_upper,
    length(timezone) AS tz_length
FROM
    airports
WHERE
    timezone LIKE 'Asia/%'
ORDER BY
    timezone;

-- Д6б
SELECT
    seat_no,
    LEFT (seat_no,
        -1)::INT AS row_num,
    RIGHT (seat_no,
        1) AS seat_letter
FROM
    seats
WHERE
    airplane_code = '32'
ORDER BY
    row_num,
    seat_letter;

-- Д7 (RIGHT JOIN)
SELECT
    a.airplane_code,
    a.model
FROM
    routes r
    RIGHT JOIN airplanes a ON r.airplane_code = a.airplane_code
WHERE
    r.route_no IS NULL;

-- Д7 (LEFT JOIN)
SELECT
    a.airplane_code,
    a.model
FROM
    airplanes a
    LEFT JOIN routes r ON a.airplane_code = r.airplane_code
WHERE
    r.route_no IS NULL;

-- Д8
SELECT
    a.airplane_code,
    a.model,
    c.fare_conditions
FROM
    airplanes a
    CROSS JOIN (
        VALUES ('Economy'),
            ('Comfort'),
            ('Business')) AS c (fare_conditions)
ORDER BY
    a.airplane_code,
    c.fare_conditions;

-- Д9
SELECT
    a.airplane_code,
    c.fare_conditions
FROM
    airplanes a
    CROSS JOIN (
        VALUES ('Economy'),
            ('Comfort'),
            ('Business')) AS c (fare_conditions)
EXCEPT
SELECT
    airplane_code,
    fare_conditions
FROM
    seats
ORDER BY
    airplane_code,
    fare_conditions;

-- 10 (UNION)
SELECT
    departure_airport AS airport_code
FROM
    routes
WHERE
    arrival_airport = 'LED'
UNION
SELECT
    arrival_airport AS airport_code
FROM
    routes
WHERE
    departure_airport = 'LED'
ORDER BY
    airport_code;

-- 10 (UNION ALL)
SELECT
    departure_airport AS airport_code
FROM
    routes
WHERE
    arrival_airport = 'LED'
UNION ALL
SELECT
    arrival_airport AS airport_code
FROM
    routes
WHERE
    departure_airport = 'LED'
ORDER BY
    airport_code;

-- 11
SELECT
    book_ref,
    passenger_id
FROM
    tickets
WHERE
    ticket_no < '0005432020000'
    AND outbound = TRUE
INTERSECT
SELECT
    book_ref,
    passenger_id
FROM
    tickets
WHERE
    ticket_no < '0005432020000'
    AND outbound = FALSE
ORDER BY
    book_ref
LIMIT 10;
