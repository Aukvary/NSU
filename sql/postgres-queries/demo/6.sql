-- 1.1
SELECT
    airplane_code,
    RANGE,
    speed
FROM
    airplanes
ORDER BY
    RANGE DESC;

-- 1.2
SELECT
    airport_code,
    timezone,
    coordinates[1] AS latitude,
    coordinates[0] AS longitude
FROM
    airports
ORDER BY
    airport_code
LIMIT 10;

-- 2.1
SELECT
    airplane_code,
    model,
    RANGE,
    speed
FROM
    airplanes
WHERE
    RANGE BETWEEN 5000 AND 10000
    AND speed > 800
ORDER BY
    RANGE;

-- 2.2
SELECT
    airport_code,
    airport_name,
    city,
    timezone,
    coordinates[1] AS latitude
FROM
    airports
WHERE
    timezone IN ('Asia/Yekaterinburg', 'Asia/Novosibirsk', 'Asia/Krasnoyarsk')
    AND coordinates[1] > 55
ORDER BY
    timezone,
    latitude DESC;

-- 3.1
SELECT
    flight_id,
    route_no,
    status,
    scheduled_departure,
    actual_departure,
    scheduled_arrival
FROM
    flights
WHERE
    actual_departure IS NOT NULL
    AND actual_arrival IS NULL;

-- 3.2
SELECT
    ticket_no,
    flight_id,
    seat_no,
    boarding_no,
    boarding_time
FROM
    boarding_passes
WHERE
    boarding_time IS NULL
ORDER BY
    flight_id,
    seat_no
LIMIT 10;

-- 4.1а
SELECT
    airport_code,
    airport_name,
    city,
    timezone
FROM
    airports
WHERE
    timezone LIKE 'Asia/%';

-- 4.1б
SELECT
    airport_code,
    airport_name,
    city,
    timezone
FROM
    airports
WHERE
    airport_code LIKE 'S_O';

-- 4.1в
SELECT
    airport_code,
    airport_name,
    city,
    timezone
FROM
    airports
WHERE
    timezone LIKE '%\_%';

-- 4.2
SELECT
    ticket_no,
    book_ref,
    passenger_id,
    passenger_name
FROM
    tickets
WHERE
    passenger_name ILIKE 'Ivan %'
ORDER BY
    ticket_no
LIMIT 10;

-- 5.1
SELECT
    airplane_code,
    model,
    ROUND(RANGE::NUMERIC / speed, 2) AS hours_exact,
    ROUND(RANGE::NUMERIC * 60 / speed)::INT / 60 AS hours,
    ROUND(RANGE::NUMERIC * 60 / speed)::INT % 60 AS minutes,
    (RANGE::NUMERIC / speed) * INTERVAL '1 hour' AS flight_interval
FROM
    airplanes;

-- 5.2
SELECT
    ticket_no,
    INITCAP(split_part(passenger_name, ' ', 2)) || ' ' ||
    LEFT (passenger_name,
        1) || '.' AS short_name,
    LENGTH(passenger_name) AS name_length
FROM
    tickets
ORDER BY
    ticket_no
LIMIT 10;

-- 5.3
SELECT
    flight_id,
    route_no,
    to_char(scheduled_departure, 'DD.MM.YYYY HH24:MI') AS scheduled_departure_str,
    EXTRACT(ISODOW FROM scheduled_departure) AS day_of_week,
    actual_departure - scheduled_departure AS delay
FROM
    flights
WHERE
    actual_departure - scheduled_departure > INTERVAL '1 hour'
ORDER BY
    delay DESC
LIMIT 10;

-- 5.4
SELECT
    book_ref,
    book_date::DATE AS booking_date,
    EXTRACT(HOUR FROM book_date) AS booking_hour,
    date_trunc('month', book_date)::DATE AS month_start,
    total_amount
FROM
    bookings
WHERE
    EXTRACT(HOUR FROM book_date) BETWEEN 0 AND 4
    AND total_amount > 100000
ORDER BY
    total_amount DESC
LIMIT 10;

-- 6.1
SELECT
    airplane_code,
    model,
    RANGE,
    CASE WHEN RANGE < 3000 THEN
        'ближнемагистральный'
    WHEN RANGE BETWEEN 3000 AND 6000 THEN
        'среднемагистральный'
    ELSE
        'дальнемагистральный'
    END AS category
FROM
    airplanes;

-- 6.2
SELECT
    flight_id,
    COALESCE(actual_departure, scheduled_departure) AS departure_time,
    CASE WHEN actual_departure IS NOT NULL THEN
        'факт'
    ELSE
        'план'
    END AS departure_source,
    COALESCE(to_char(actual_arrival, 'DD.MM HH24:MI'), 'не прибыл') AS arrival_status
FROM
    flights
ORDER BY
    flight_id
LIMIT 10;

-- 7.1
SELECT
    b.book_ref,
    b.book_date,
    b.total_amount,
    t.ticket_no,
    t.passenger_name,
    CASE WHEN t.outbound THEN
        'туда'
    ELSE
        'обратно'
    END AS direction
FROM
    bookings b
    JOIN tickets t ON b.book_ref = t.book_ref
WHERE
    b.total_amount > 500000
ORDER BY
    b.total_amount DESC,
    b.book_ref
LIMIT 15;

-- 7.2
SELECT
    r.route_no,
    lower(r.validity) AS validity_start,
    r.departure_airport,
    r.arrival_airport,
    arr.timezone AS arrival_timezone,
    r.airplane_code,
    a.range,
    a.speed,
    r.duration
FROM
    routes r
    JOIN airports dep ON r.departure_airport = dep.airport_code
    JOIN airports arr ON r.arrival_airport = arr.airport_code
    JOIN airplanes a ON r.airplane_code = a.airplane_code
WHERE
    r.departure_airport IN ('SVO', 'DME', 'VKO')
    AND dep.timezone <> arr.timezone;

-- 7.3
SELECT
    s.ticket_no,
    s.flight_id,
    s.fare_conditions,
    s.price,
    COALESCE(bp.seat_no, 'нет талона') AS seat_no
FROM
    segments s
    LEFT JOIN boarding_passes bp ON s.ticket_no = bp.ticket_no
        AND s.flight_id = bp.flight_id
    ORDER BY
        s.ticket_no,
        s.flight_id
    LIMIT 20;

-- 7.4
SELECT
    s.seat_no,
    s.fare_conditions
FROM
    seats s
    LEFT JOIN boarding_passes bp ON s.seat_no = bp.seat_no
        AND bp.flight_id = 10877
WHERE
    s.airplane_code = '32'
    AND bp.seat_no IS NULL
ORDER BY
    s.fare_conditions,
    s.seat_no
LIMIT 15;
